#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "fornecedor.h"

extern int estoque_pao;
extern int estoque_salsicha;
extern int estoque_molho;
extern pthread_mutex_t mutex_estoque;
extern sem_t sem_fornecedor;

void* fornecedor(void* arg) {
    while (1) {
        sem_wait(&sem_fornecedor);

        pthread_mutex_lock(&mutex_estoque);
        
        // Verificar se o estoque está vazio antes de reabastecer
        if (estoque_pao == 0) {
            estoque_pao = 10; // Reabastece com 10 pães
            printf("Fornecedor: pão reabastecido. Estoque: %d\n", estoque_pao);
        }
        
        if (estoque_salsicha == 0) {
            estoque_salsicha = 10; // Reabastece com 10 salsichas
            printf("Fornecedor: salsicha reabastecida. Estoque: %d\n", estoque_salsicha);
        }
        
        if (estoque_molho == 0) {
            estoque_molho = 10; // Reabastece com 10 molhos
            printf("Fornecedor: molho reabastecido. Estoque: %d\n", estoque_molho);
        }
        
        pthread_mutex_unlock(&mutex_estoque);
    }
    pthread_exit(NULL);
}
