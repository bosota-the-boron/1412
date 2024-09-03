/*1. Generation de la key
 *2. Chiffrement/dechiffrement basique
  3. Stockage et Gestion des clés*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 32

// Generation key symétrique "simple"
void genkey(unsigned char* key){
  for (int i = 0; i < KEY_SIZE; i++){
    key[i] = rand() % 256; // Genrere un octet "aléatoire"
  }
}

// Stockage key  >>> file 
void store_key(const unsigned char* key, const char* filename){
  FILE *file = fopen(filename, "wb");
  if (file == NULL){
    perror("ERROR: File content key canot open !!!\n");
    exit(EXIT_FAILURE);
  }
  fwrite(key, 1, KEY_SIZE, file);
  fclose(file);
}

// Load key <<< file
void load_key(unsigned char* key, const char* filename){
  FILE *file = fopen(filename, "rb");
  if (file == NULL){
    perror("ERROR: FAILURE OPEN KEY");
    exit(EXIT_FAILURE);
  }
  fread(key, 1, KEY_SIZE, file);
  fclose(file);
}

// Chiffrement/dechiffrement en passant par XOR

void xor_encrypt_decrypt(unsigned char* data, size_t data_len, const unsigned char* key){
  for (size_t i = 0; i < data_len; i++){
    data[i] ^= key[i % KEY_SIZE]; // XOR avec la clé
  }
}

int main(){
  unsigned char key[KEY_SIZE];
  char filename[] = "keyfile.bin";
  //generer nouvelle key
  genkey(key);
  printf("KEY : \n");
  for (int i = 0; i < KEY_SIZE; i++){
    printf("%02x ", key[i]);
  }
  printf("\n");

  //stock key
  store_key(key, filename);
  printf("KEY in %s\n", filename);

  //load key <<<< file 
  unsigned char loaded_key[KEY_SIZE];
  load_key(loaded_key, filename);
  printf("KEY load by : %s\n", filename);
  for (int i = 0; i < KEY_SIZE; i++){
    printf("%02x", loaded_key[i]);
  }
  printf("\n");

  //test
  unsigned char data[] = "zazx suce d'enomes chibre";
  size_t data_len = strlen((char*)data);
  
  //encrypt
  xor_encrypt_decrypt(data, data_len, loaded_key);
  printf("ENCRYPT DATA : %s\n", data);

  //decrypt
  xor_encrypt_decrypt(data, data_len, loaded_key);
  printf("DECRYPT DATA : %s\n", data);

  return 0;
}


/*
 * 1. key fixe ? 
 * 2. entré password user 
 *
 * */
