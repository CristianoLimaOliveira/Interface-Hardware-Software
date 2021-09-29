#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
//#include <time.h>

#define NUM_THREADS 4

uint32_t quantidadeDeLinhasMatriz1;
uint32_t quantidadeDeColunasMatriz1;
uint32_t quantidadeDeLinhasMatriz2;
uint32_t quantidadeDeColunasMatriz2;
float *ptrMatriz1;
float *ptrMatriz2;
float *ptrMatrizResultante;

struct estruturaPorThread
{
    uint32_t delimitador1;
    uint32_t delimitador2;
};

void * multiplicaVetores(void *args){
    struct estruturaPorThread *seletor = (struct estruturaPorThread *)(args);
    float result=0;

    for (uint32_t i = seletor->delimitador1; i < seletor->delimitador2; i++){
        for (uint32_t j = 0; j < quantidadeDeColunasMatriz2; j++){
            for (uint32_t k = 0; k < quantidadeDeColunasMatriz1; k++){
                result += ptrMatriz1[ i*quantidadeDeColunasMatriz1+k ] * ptrMatriz2[ k*quantidadeDeColunasMatriz2+j ];
            }
            ptrMatrizResultante[i*quantidadeDeColunasMatriz2+j]=result;
            result=0;
        }
    }

    pthread_exit(0);
}

int main(int argc, char *argv[]){
    uint32_t quantidadeDeMultiplicacoes, quantidadeDeElementosMatriz1, quantidadeDeElementosMatriz2, quantidadeDeElementosMatrizResultante;
    uint32_t contadorFormatador;
    pthread_t threads[NUM_THREADS];
    struct estruturaPorThread blocoThread1, blocoThread2, blocoThread3, blocoThread4;

    FILE* fp_input = fopen( argv[1], "r" );
    FILE* fp_output = fopen( argv[2], "w" );

    fscanf(fp_input, "%u", &quantidadeDeMultiplicacoes);

    for(uint32_t contadorPrimeiroFor = 0; contadorPrimeiroFor < quantidadeDeMultiplicacoes; contadorPrimeiroFor++){
        fscanf(fp_input, "%u", &quantidadeDeLinhasMatriz1);
        fscanf(fp_input, "%u", &quantidadeDeColunasMatriz1);

        quantidadeDeElementosMatriz1 = quantidadeDeLinhasMatriz1 * quantidadeDeColunasMatriz1;
        ptrMatriz1 = (float*) malloc(quantidadeDeElementosMatriz1 * sizeof(float));

        for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatriz1; contadorSegundoFor++){
            fscanf(fp_input, "%f", &ptrMatriz1[contadorSegundoFor]);
        }

        fscanf(fp_input, "%u", &quantidadeDeLinhasMatriz2);
        fscanf(fp_input, "%u", &quantidadeDeColunasMatriz2);

        quantidadeDeElementosMatriz2 = quantidadeDeLinhasMatriz2 * quantidadeDeColunasMatriz2;
        ptrMatriz2 = (float*) malloc(quantidadeDeElementosMatriz2 * sizeof(float));

        for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatriz2; contadorSegundoFor++){
            fscanf(fp_input, "%f", &ptrMatriz2[contadorSegundoFor]);
        }

        quantidadeDeElementosMatrizResultante = quantidadeDeLinhasMatriz1 * quantidadeDeColunasMatriz2;
        ptrMatrizResultante =(float*) calloc(quantidadeDeElementosMatrizResultante, sizeof(float));
        
        blocoThread1.delimitador1 = 0;
        blocoThread1.delimitador2 = (uint32_t)(quantidadeDeLinhasMatriz1/4);
        blocoThread2.delimitador1 = (uint32_t)(quantidadeDeLinhasMatriz1/4);
        blocoThread2.delimitador2 = (uint32_t)(quantidadeDeLinhasMatriz1/4)*2;
        blocoThread3.delimitador1 = (uint32_t)(quantidadeDeLinhasMatriz1/4)*2;
        blocoThread3.delimitador2 = (uint32_t)(quantidadeDeLinhasMatriz1/4)*3;
        blocoThread4.delimitador1 = (uint32_t)(quantidadeDeLinhasMatriz1/4)*3;
        blocoThread4.delimitador2 = quantidadeDeLinhasMatriz1;
        pthread_create(&threads[0], NULL, multiplicaVetores, (void *)(&blocoThread1));
        pthread_create(&threads[1], NULL, multiplicaVetores, (void *)(&blocoThread2));
        pthread_create(&threads[2], NULL, multiplicaVetores, (void *)(&blocoThread3));
        pthread_create(&threads[3], NULL, multiplicaVetores, (void *)(&blocoThread4));
        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);
        pthread_join(threads[2], NULL);
        pthread_join(threads[3], NULL);

        contadorFormatador = 0;
        fprintf(fp_output,"M%u:\n", contadorPrimeiroFor);
        for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatrizResultante; contadorSegundoFor++){
            if(contadorFormatador<quantidadeDeColunasMatriz2-1){
                fprintf(fp_output," %.2f", ptrMatrizResultante[contadorSegundoFor]);
                contadorFormatador += 1;
            }else{
                fprintf(fp_output," %.2f\n", ptrMatrizResultante[contadorSegundoFor]);
                contadorFormatador = 0;
            }
        }

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
