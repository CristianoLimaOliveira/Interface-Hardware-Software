#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#define NUM_THREADS 4

struct estruturaPorThread
{
    uint64_t quantidadeDeLinhasMatriz1;
    uint64_t quantidadeDeColunasMatriz1;
    uint64_t quantidadeDeLinhasMatriz2;
    uint64_t quantidadeDeColunasMatriz2;
    double *ptrMatriz1;
    double *ptrMatriz2;
    double *ptrMatrizResultante;
    uint64_t indicaLinhaMatriz1;
    uint64_t indicaColunaMatriz2;
};

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

void * multiplicaVetores(void *args){
    struct estruturaPorThread *ptrDados = (struct estruturaPorThread *)(args);

    double resul = 0;
    for(uint64_t j=0; j < ptrDados->quantidadeDeLinhasMatriz2; j++){
        resul += ptrDados->ptrMatriz1[ptrDados->indicaLinhaMatriz1 * ptrDados->quantidadeDeColunasMatriz1 + j] * ptrDados->ptrMatriz2[ptrDados->indicaColunaMatriz2 + j * ptrDados->quantidadeDeColunasMatriz2];
    }

    ptrDados->ptrMatrizResultante[ptrDados->quantidadeDeLinhasMatriz1 * ptrDados->indicaColunaMatriz2 + ptrDados->indicaLinhaMatriz1]=resul;
    printf("%lu %lu %lf\n\n", ptrDados->indicaLinhaMatriz1, ptrDados->indicaColunaMatriz2, resul);

    return 0;
}

int main(int argc, char *argv[]){
    uint64_t quantidadeDeMultiplicacoes, quantidadeDeLinhasMatriz1, quantidadeDeLinhasMatriz2, quantidadeDeColunasMatriz1, quantidadeDeColunasMatriz2, quantidadeDeElementosMatriz1, quantidadeDeElementosMatriz2, quantidadeDeElementosMatrizResultante;
    double *ptrMatriz1=NULL, *ptrMatriz2=NULL, *ptrMatrizResultante=NULL;
    uint32_t indexArrayDados;
    struct estruturaPorThread *ptrDados=NULL;
    pthread_t threads[NUM_THREADS];

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
        ptrDados = malloc(quantidadeDeElementosMatrizResultante * sizeof(struct estruturaPorThread));

        indexArrayDados = 0;
        for(uint64_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeColunasMatriz2; contadorSegundoFor++){
            for(uint64_t contadorTerceiroFor = 0; contadorTerceiroFor < quantidadeDeLinhasMatriz1; contadorTerceiroFor++){
                ptrDados[indexArrayDados].quantidadeDeLinhasMatriz1 = quantidadeDeLinhasMatriz1;
                ptrDados[indexArrayDados].quantidadeDeColunasMatriz1 = quantidadeDeColunasMatriz1;
                ptrDados[indexArrayDados].quantidadeDeLinhasMatriz2 = quantidadeDeLinhasMatriz2;
                ptrDados[indexArrayDados].quantidadeDeColunasMatriz2 = quantidadeDeColunasMatriz2;
                ptrDados[indexArrayDados].ptrMatriz1 = ptrMatriz1;
                ptrDados[indexArrayDados].ptrMatriz2 = ptrMatriz2;
                ptrDados[indexArrayDados].ptrMatrizResultante = ptrMatrizResultante;
                ptrDados[indexArrayDados].indicaLinhaMatriz1 = contadorTerceiroFor;
                ptrDados[indexArrayDados].indicaColunaMatriz2 = contadorSegundoFor;
                indexArrayDados += 1;
            }
        }

        /*for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatrizResultante; contadorSegundoFor++){
            printf("%u %lu %lu %lu %lu %u %u\n", contadorSegundoFor, ptrDados[contadorSegundoFor].quantidadeDeLinhasMatriz1, ptrDados[contadorSegundoFor].quantidadeDeColunasMatriz1, ptrDados[contadorSegundoFor].quantidadeDeLinhasMatriz2, ptrDados[contadorSegundoFor].quantidadeDeColunasMatriz2, ptrDados[contadorSegundoFor].indicaLinhaMatriz1, ptrDados[contadorSegundoFor].indicaColunaMatriz2);
        }*/

        pthread_create(&threads[0], NULL, multiplicaVetores, (void *)(&ptrDados[0]));
        pthread_create(&threads[1], NULL, multiplicaVetores, (void *)(&ptrDados[1]));
        pthread_create(&threads[2], NULL, multiplicaVetores, (void *)(&ptrDados[2]));
        pthread_create(&threads[3], NULL, multiplicaVetores, (void *)(&ptrDados[3]));
        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);
        pthread_join(threads[2], NULL);
        pthread_join(threads[3], NULL);

        for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatrizResultante; contadorSegundoFor++){
            printf("%lf ", ptrDados[0].ptrMatrizResultante[contadorSegundoFor]);
        }

        free(ptrMatriz1);
        free(ptrMatriz2);
        free(ptrMatrizResultante);
        free(ptrDados);
        ptrMatriz1=NULL;
        ptrMatriz2=NULL;
        ptrMatrizResultante=NULL;
        ptrDados=NULL;
        printf("\n");
    }

    fclose(fp_input);
    fclose(fp_output);

    return 0;
}