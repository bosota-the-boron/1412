#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KEY_SIZE 32
#define MAX_FAILURES 3

int failure_counter = 0;

// Fonction pour générer une clé symétrique à partir d'un mot de passe
void genkey_from_password(const char* password, unsigned char* key) {
    size_t len = strlen(password);
    for (int i = 0; i < KEY_SIZE; i++) {
        key[i] = password[i % len] + i;  // Simple transformation pour générer une clé
    }
}

// Stocker la clé dans un fichier
void store_key(const unsigned char* key, const char* filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("ERROR: Impossible d'ouvrir le fichier pour stocker la clé !!!\n");
        exit(EXIT_FAILURE);
    }
    fwrite(key, 1, KEY_SIZE, file);
    fclose(file);
}

// Charger la clé depuis un fichier
void load_key(unsigned char* key, const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("ERROR: Impossible d'ouvrir le fichier pour charger la clé !!!\n");
        exit(EXIT_FAILURE);
    }
    fread(key, 1, KEY_SIZE, file);
    fclose(file);
}

// Chiffrement/déchiffrement XOR
void xor_encrypt_decrypt(unsigned char* data, size_t data_len, const unsigned char* key) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key[i % KEY_SIZE];
    }
}

// Fonction pour lire un fichier dans une mémoire tampon (buffer)
unsigned char* read_file(const char* filepath, size_t* file_size) {
    FILE* file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("ERROR: Impossible d'ouvrir le fichier\n");
        exit(EXIT_FAILURE);
    }

    // Déterminer la taille du fichier
    fseek(file, 0, SEEK_END);
    *file_size = ftell(file);
    rewind(file);

    // Allouer la mémoire pour contenir le fichier
    unsigned char* buffer = (unsigned char*)malloc(*file_size);
    if (buffer == NULL) {
        perror("ERROR: Échec d'allocation mémoire pour le fichier\n");
        exit(EXIT_FAILURE);
    }

    // Lire le fichier dans le buffer
    fread(buffer, 1, *file_size, file);
    fclose(file);
    return buffer;
}

// Fonction pour écrire un buffer dans un fichier
void write_file(const char* filepath, unsigned char* data, size_t data_len) {
    FILE* file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("ERROR: Impossible d'ouvrir le fichier pour écrire\n");
        exit(EXIT_FAILURE);
    }

    fwrite(data, 1, data_len, file);
    fclose(file);
}

// Gestion des échecs avec suppression de la clé après trois tentatives échouées
void handle_failure(const char* filename) {
    failure_counter++;
    if (failure_counter >= MAX_FAILURES) {
        printf("Max échecs atteints. Suppression de la clé...\n");
        remove(filename);  // Suppression du fichier contenant la clé
        exit(EXIT_FAILURE);
    }
}

int main() {
    unsigned char key[KEY_SIZE];
    char filename[] = "keyfile.bin";

    // Générer une nouvelle clé à partir d'un mot de passe fourni par l'utilisateur
    char password[256];
    printf("Entrez un mot de passe pour générer la clé : ");
    fgets(password, 256, stdin);
    password[strcspn(password, "\n")] = 0;  // Retirer le retour à la ligne
    genkey_from_password(password, key);

    printf("Clé générée : \n");
    for (int i = 0; i < KEY_SIZE; i++) {
        printf("%02x ", key[i]);
    }
    printf("\n");

    // Stocker la clé
    store_key(key, filename);
    printf("Clé stockée dans %s\n", filename);

    // Demander à l'utilisateur s'il veut chiffrer ou déchiffrer un fichier
    char choice[10];
    printf("Voulez-vous (1) Chiffrer ou (2) Déchiffrer un fichier ? (Entrez 1 ou 2) : ");
    fgets(choice, sizeof(choice), stdin);
    int operation = atoi(choice);

    // Demander le chemin du fichier à traiter
    char filepath[256];
    printf("Entrez le chemin du fichier à traiter : ");
    fgets(filepath, sizeof(filepath), stdin);
    filepath[strcspn(filepath, "\n")] = 0;  // Retirer le retour à la ligne

    // Lire le fichier dans un buffer
    size_t file_size;
    unsigned char* file_data = read_file(filepath, &file_size);

    // Effectuer l'opération choisie (chiffrement ou déchiffrement)
    if (operation == 1) {
        // Chiffrement
        xor_encrypt_decrypt(file_data, file_size, key);
        write_file(filepath, file_data, file_size);
        printf("Fichier chiffré avec succès : %s\n", filepath);
    } else if (operation == 2) {
        // Déchiffrement
        xor_encrypt_decrypt(file_data, file_size, key);
        write_file(filepath, file_data, file_size);
        printf("Fichier déchiffré avec succès : %s\n", filepath);
    } else {
        printf("Choix non valide\n");
    }

    // Libérer la mémoire allouée
    free(file_data);

    return 0;
}

