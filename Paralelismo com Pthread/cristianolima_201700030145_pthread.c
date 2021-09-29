#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
//#include <time.h>

#define NUM_THREADS 4

uint64_t quantidadeDeLinhasMatriz1;
uint64_t quantidadeDeColunasMatriz1;
uint64_t quantidadeDeLinhasMatriz2;
uint64_t quantidadeDeColunasMatriz2;
float *ptrMatriz1;
float *ptrMatriz2;
float *ptrMatrizResultante;
uint64_t passo=0;

void * multiplicaVetores(void *args){
    uint64_t i = passo++;

    for (int j = 0; j < quantidadeDeColunasMatriz2; j++)
        for (int k = 0; k < quantidadeDeColunasMatriz1; k++){
            ptrMatrizResultante[i*quantidadeDeColunasMatriz2+j] += ptrMatriz1[ i*quantidadeDeColunasMatriz1+k ] * ptrMatriz2[ k*quantidadeDeColunasMatriz2+j ];
        }
    return 0;
}

int main(int argc, char *argv[]){
    uint64_t quantidadeDeMultiplicacoes, quantidadeDeElementosMatriz1, quantidadeDeElementosMatriz2, quantidadeDeElementosMatrizResultante;
    uint32_t indexThread, indexDados, contadorFormatador;
    pthread_t threads[NUM_THREADS];
    bool fim=false;

    FILE* fp_input = fopen( argv[1], "r" );
    FILE* fp_output = fopen( argv[2], "w" );

    fscanf(fp_input, "%lu", &quantidadeDeMultiplicacoes);
    
    for(uint32_t contadorPrimeiroFor = 0; contadorPrimeiroFor < quantidadeDeMultiplicacoes; contadorPrimeiroFor++){
        fscanf(fp_input, "%lu", &quantidadeDeLinhasMatriz1);
        fscanf(fp_input, "%lu", &quantidadeDeColunasMatriz1);
        
        quantidadeDeElementosMatriz1 = quantidadeDeLinhasMatriz1 * quantidadeDeColunasMatriz1;
        ptrMatriz1 = malloc(quantidadeDeElementosMatriz1 * sizeof(float));

        for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatriz1; contadorSegundoFor++){
            fscanf(fp_input, "%f", &ptrMatriz1[contadorSegundoFor]);
        }

        fscanf(fp_input, "%lu", &quantidadeDeLinhasMatriz2);
        fscanf(fp_input, "%lu", &quantidadeDeColunasMatriz2);

        quantidadeDeElementosMatriz2 = quantidadeDeLinhasMatriz2 * quantidadeDeColunasMatriz2;
        ptrMatriz2 = malloc(quantidadeDeElementosMatriz2 * sizeof(float));

        for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatriz2; contadorSegundoFor++){
            fscanf(fp_input, "%f", &ptrMatriz2[contadorSegundoFor]);
        }

        quantidadeDeElementosMatrizResultante = quantidadeDeLinhasMatriz1 * quantidadeDeColunasMatriz2;
        ptrMatrizResultante = malloc(quantidadeDeElementosMatrizResultante * sizeof(float));

        indexThread = 0;
        indexDados = 0;
        while(!fim){
            while(indexThread<NUM_THREADS && indexDados<quantidadeDeLinhasMatriz1){
                pthread_create(&threads[indexThread], NULL, multiplicaVetores, NULL);
                indexThread += 1;
                indexDados += 1;
            }

            while(indexThread>0){
                pthread_join(threads[indexThread-1], NULL);
                indexThread-=1;
            }

            if(indexDados==quantidadeDeLinhasMatriz1){
                fim=true;
            }
        }
        fim=false;

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
        passo=0;
    }

    fclose(fp_input);
    fclose(fp_output);

    return 0;
}