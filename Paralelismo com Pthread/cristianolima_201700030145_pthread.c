#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
/* ESBOÇO
void multiplicaVetores(int indicaLinhaMatriz1, int indicaColunaMatriz2, int quantidadeDeLinhasMatriz1, int quantidadeDeColunasMatriz1, int quantidadeDeLinhasMatriz2, int quantidadeDeColunasMatriz2, double *ptrMatriz1, double *ptrMatriz2, double *ptrMatrizResultante){
    double result = 0;
    for(int i=0; i < quantidadeDeColunasMatriz1; i++){
        for(int j=0; j < quantidadeDeLinhasMatriz2; j++){
            resul += ptrMatriz1[indicaLinhaMatriz1 * quantidadeDeColunasMatriz1 + i] * ptrMatriz2[indicaColunaMatriz2 + j * quantidadeDeColunasMatriz2];
        }
    }

    ptrMatrizResultante[quantidadeDeLinhasMatriz1 * indicaColunaMatriz2 + indicaLinhaMatriz1]=resul;
}*/

int main(int argc, char *argv[]){
    uint64_t quantidadeDeMultiplicacoes, quantidadeDeLinhasMatriz1, quantidadeDeLinhasMatriz2, quantidadeDeColunasMatriz1, quantidadeDeColunasMatriz2, quantidadeDeElementosMatriz1, quantidadeDeElementosMatriz2, quantidadeDeElementosMatrizResultante;
    double *ptrMatriz1=NULL, *ptrMatriz2=NULL, *ptrMatrizResultante=NULL;

    printf("%s\n%s\n", argv[1], argv[2]);

    FILE* fp_input = fopen( argv[1], "r" );
    FILE* fp_output = fopen( argv[2], "w" );

    fscanf(fp_input, "%lu", &quantidadeDeMultiplicacoes);
    printf("%lu\n", quantidadeDeMultiplicacoes);
    
    for(uint32_t contadorPrimeiroFor = 0; contadorPrimeiroFor < quantidadeDeMultiplicacoes; contadorPrimeiroFor++){
        fscanf(fp_input, "%lu", &quantidadeDeLinhasMatriz1);
        fscanf(fp_input, "%lu", &quantidadeDeColunasMatriz1);
        
        quantidadeDeElementosMatriz1 = quantidadeDeLinhasMatriz1 * quantidadeDeColunasMatriz1;
        ptrMatriz1 = malloc(quantidadeDeElementosMatriz1 * sizeof(double));

        for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatriz1; contadorSegundoFor++){
            fscanf(fp_input, "%lf", &ptrMatriz1[contadorSegundoFor]);
            fprintf(fp_output, "%lf ", ptrMatriz1[contadorSegundoFor]);
        }

        fscanf(fp_input, "%lu", &quantidadeDeLinhasMatriz2);
        fscanf(fp_input, "%lu", &quantidadeDeColunasMatriz2);

        quantidadeDeElementosMatriz2 = quantidadeDeLinhasMatriz2 * quantidadeDeColunasMatriz2;
        ptrMatriz2 = malloc(quantidadeDeElementosMatriz2 * sizeof(double));

        fprintf(fp_output, "\n");
        for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatriz1; contadorSegundoFor++){
            fscanf(fp_input, "%lf", &ptrMatriz2[contadorSegundoFor]);
            fprintf(fp_output, "%lf ", ptrMatriz2[contadorSegundoFor]);
        }
        fprintf(fp_output, "\n");

        quantidadeDeElementosMatrizResultante = quantidadeDeLinhasMatriz1 * quantidadeDeColunasMatriz2;
        ptrMatrizResultante = malloc(quantidadeDeElementosMatrizResultante * sizeof(double));

        free(ptrMatriz1);
        free(ptrMatriz2);
        free(ptrMatrizResultante);
        ptrMatriz1=NULL;
        ptrMatriz2=NULL;
        ptrMatrizResultante=NULL;
    }

    fclose(fp_input);
    fclose(fp_output);

    return 0;
}