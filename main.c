#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LONGUEUR_MINIMALE 32

int checkcharspe_passwd(const char* passwd){
    const char* special_char = "!@#$^&*()-+_=[]{}|;:-\",.<>?/";
    while(*passwd){
        const char* s = special_char;
        while(*s){
            if (*passwd == *s){
                return 20;
            } 
            s++;
        }
        passwd++;
    }
    return 0;
}

int checkchiffres_passwd(const char* passwd){
    while(*passwd){
        if (*passwd >= '0' && *passwd <= '9'){
            return 8;
        }
        passwd++;
    }
    return 0;
}

int checkmaj_passwd(const char* passwd){
    while(*passwd){
        if (*passwd >= 'A' && *passwd <= 'Z'){
            return 2; 
        }
        passwd++;
    }
    return 0;
}

int checkmin_passwd(const char* passwd){
    while(*passwd){
        if (*passwd >= 'a' && *passwd <= 'z'){
            return 4; 
        }
        passwd++;
    }
    return 0;
}

int checklenght_passwd(const char* passwd){
    if (strlen(passwd) < LONGUEUR_MINIMALE){ 
        return 0; 
    }
    return 1;
}

void get_passwd(char* password){
    printf("Entrez mot de passe à tester : ");
    scanf("%s", password);
}

int score(const char* passwd){
    int total_score = 0;

    total_score += checkmin_passwd(passwd);
    total_score += checkmaj_passwd(passwd);
    total_score += checklenght_passwd(passwd);
    total_score += checkcharspe_passwd(passwd);
    total_score += checkchiffres_passwd(passwd);
  
    return total_score;
}

void recommandation(int score){
    switch(score){
      case 1:// lenght
        printf("Add maj , min , numbers & special char\n");
        break;
      case 2://maj
        printf("Add char (32 or more), min, numbers & special char\n");
        break;
      case 3:// maj + lenght
        printf("Add min, numbers & special char\n");
        break;
      case 4:// min
        printf("Add char (32 or more), maj, numbers & special char\n");
        break;
      case 5:// lenght + min
        printf("Add maj, numbers, special char\n");
        break;
      case 6: // maj + min
        printf("Add char (32 or more), numbers & special char\n");
        break;
      case 7: // maj + lenght + min
        printf("Add numbers & specialchar\n");
        break;
      case 8: // numbers
        printf("Add charutilisation  (32 or more), maj, min & special char\n");
        break;
      case 9: //numbers + lenght
        printf("Add maj, min, &  special char \n");
        break;
      case 10: // numbers + maj
        printf("Add char (32 or more), min & special char\n");
        break;
      case 11:// numbers + maj + lenght
        printf("Add min, special char\n");
        break;
      case 12: // numbers + min
        printf("Add char (32 or more), maj & special char\n");
        break;
      case 13: // numbers + maj + lenght
        printf("Add maj & special char\n");
        break;
      case 14:// numbers + maj +min 
        printf("Add char (32 or more), special char\n");
        break;
      case 15: // all - special char
        printf("Add special char\n");
        break;
      case 20: //special char 
        printf("Add char (32 or more), min ,maj , numbers\n");
        break;
      case 21:// specalchar +lenght
        printf("Add maj, min & numbers\n");
        break;
      case 22:// special char + maj
        printf("Add char (32 or more),min,  numbers");
        break;
      case 24:// special char +  min
        printf("Add char (32 or more), maj & numbers");
        break;
      case 28: // special char + numbers

        printf("Add char (32 or more ) min, min\n");

        break;
      case 35: // all in one
        printf("Very strong password !!! GG \n");
        break;
    }
}

int check_dico(const char* passwd, const char* worldlist_file){
  FILE *file = fopen(worldlist_file, "r");
  if(!file){
    printf("Error: canot open worldlis %s, check path\n", worldlist_file);
    return -1; // retourne une Error
  }
  char line[256];
  while (fgets(line, sizeof(line), file)){
  // supprime la saut de ligne 
  line[strcspn(line, "\n")] = 0;

  if (strcmp(passwd, line)== 0){
    fclose(file);
    return 1;
    }
  }

  fclose(file);
  return 0;
}

void help(const char* program_name){
  printf("Usage: %s <options> <worldlist>\n", program_name);
  printf("Options:\n");
  printf(" -h, --help       See Help\n");
  printf(" <worldlist>      Path to worldlist\n");
}

int main(int argc, char **argv){
  if (argc < 2){
    printf("Use %s <worldlist>\n", argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
  help(argv[0]);
  return 0;
  }

  char password[200];
    get_passwd(password);

   if (check_dico(password, argv[1])){
    printf("Password found change now !");
    }else{
       int total_score = score(password);
       printf("Ur password score is : %d/35\n", total_score);
       recommandation(total_score);
    } 

    return 0;
}

