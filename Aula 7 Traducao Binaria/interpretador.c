#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct memoria{
    uint8_t byte0;
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
};

int main(int argc, char* argv[]){
    struct memoria codigo_entrada[25];
    FILE *ponteiro_arquivo;

    ponteiro_arquivo = fopen(argv[1],"r");

    if(ponteiro_arquivo == NULL){
        return 1;
    }

    int i=0;
    while(!feof(ponteiro_arquivo))
    {
        fscanf(ponteiro_arquivo, "%hhx %hhx %hhx %hhx", &codigo_entrada[i].byte0, &codigo_entrada[i].byte1, &codigo_entrada[i].byte2, &codigo_entrada[i].byte3);
        i++;
    }

    fclose(ponteiro_arquivo);

    for(int i=0; i<25; i++){
        printf("0x%02hhx 0x%02hhx 0x%02hhx 0x%02hhx\n", codigo_entrada[i].byte0, codigo_entrada[i].byte1, codigo_entrada[i].byte2, codigo_entrada[i].byte3);
    }

    return 0;
}