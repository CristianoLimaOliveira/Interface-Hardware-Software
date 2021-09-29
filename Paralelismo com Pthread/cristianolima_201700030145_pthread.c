#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
//#include <time.h>

#define NUM_THREADS 4

struct estruturaPorThread
{
    uint64_t quantidadeDeLinhasMatriz1;
    uint64_t quantidadeDeColunasMatriz1;
    uint64_t quantidadeDeLinhasMatriz2;
    uint64_t quantidadeDeColunasMatriz2;
    float *ptrMatriz1;
    float *ptrMatriz2;
    float *ptrMatrizResultante;
    uint64_t indicaLinhaMatriz1;
    uint64_t indicaColunaMatriz2;
};

void * multiplicaVetores(void *args){
    struct estruturaPorThread *ptrDados = (struct estruturaPorThread *)(args);

    float resul = 0;
    for(uint64_t j=0; j < ptrDados->quantidadeDeLinhasMatriz2; j++){
        resul += ptrDados->ptrMatriz1[ptrDados->indicaLinhaMatriz1 * ptrDados->quantidadeDeColunasMatriz1 + j] * ptrDados->ptrMatriz2[ptrDados->indicaColunaMatriz2 + j * ptrDados->quantidadeDeColunasMatriz2];
    }

    ptrDados->ptrMatrizResultante[ptrDados->quantidadeDeColunasMatriz2 * ptrDados->indicaLinhaMatriz1 + ptrDados->indicaColunaMatriz2]=resul;

    return 0;
}

int main(int argc, char *argv[]){
    uint64_t quantidadeDeMultiplicacoes, quantidadeDeLinhasMatriz1, quantidadeDeLinhasMatriz2, quantidadeDeColunasMatriz1, quantidadeDeColunasMatriz2, quantidadeDeElementosMatriz1, quantidadeDeElementosMatriz2, quantidadeDeElementosMatrizResultante;
    float *ptrMatriz1=NULL, *ptrMatriz2=NULL, *ptrMatrizResultante=NULL;
    uint32_t indexArrayDados, indexThread, indexDados, contadorFormatador;
    struct estruturaPorThread *ptrDados=NULL;
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

        indexThread = 0;
        indexDados = 0;
        while(!fim){
            while(indexThread<NUM_THREADS && indexDados<quantidadeDeElementosMatrizResultante){
                pthread_create(&threads[indexThread], NULL, multiplicaVetores, (void *)(&ptrDados[indexDados]));
                indexThread += 1;
                indexDados += 1;
            }

            while(indexThread>0){
                pthread_join(threads[indexThread-1], NULL);
                indexThread-=1;
            }

            if(indexDados==quantidadeDeElementosMatrizResultante){
                fim=true;
            }
        }
        fim=false;

        contadorFormatador = 0;
        fprintf(fp_output,"M%u:\n", contadorPrimeiroFor);
        for(uint32_t contadorSegundoFor = 0; contadorSegundoFor < quantidadeDeElementosMatrizResultante; contadorSegundoFor++){
            if(contadorFormatador<quantidadeDeColunasMatriz2-1){
                fprintf(fp_output," %.2f", ptrDados[0].ptrMatrizResultante[contadorSegundoFor]);
                contadorFormatador += 1;
            }else{
                fprintf(fp_output," %.2f\n", ptrDados[0].ptrMatrizResultante[contadorSegundoFor]);
                contadorFormatador = 0;
            }
        }

        free(ptrMatriz1);
        free(ptrMatriz2);
        free(ptrMatrizResultante);
        free(ptrDados);
        ptrMatriz1=NULL;
        ptrMatriz2=NULL;
        ptrMatrizResultante=NULL;
        ptrDados=NULL;
    }

    fclose(fp_input);
    fclose(fp_output);

    return 0;
}