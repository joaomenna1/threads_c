#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "cliente.h"
#include "fornecedor.h"
#include "main.h"

#define MAX_CLIENTES 10000

int estoque_pao = 0;
int estoque_salsicha = 0;
int estoque_molho = 0;
pthread_mutex_t mutex_estoque;
sem_t sem_fornecedor;

int clientes_atendidos = 0;
double tempo_total_espera = 0.0;



int main() {
    srand(time(NULL));

    pthread_t thread_clientes[MAX_CLIENTES];
    pthread_t thread_fornecedor;

    pthread_mutex_init(&mutex_estoque, NULL);
    sem_init(&sem_fornecedor, 0, 0);

    pthread_create(&thread_fornecedor, NULL, fornecedor, NULL);

    for (int i = 0; i < MAX_CLIENTES; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&thread_clientes[i], NULL, cliente, id);
    }

    for (int i = 0; i < MAX_CLIENTES; i++) {
        pthread_join(thread_clientes[i], NULL);
    }

    pthread_cancel(thread_fornecedor);

    pthread_mutex_destroy(&mutex_estoque);
    sem_destroy(&sem_fornecedor);
    pthread_mutex_destroy(&mutex_atendimento);

    double tempo_medio_espera = 0.0;
    if (clientes_atendidos > 0) {
        tempo_medio_espera = tempo_total_espera / clientes_atendidos;
    }
    
    printf("Tempo médio de espera (segundos): %.2lf \n", tempo_medio_espera);
    printf("Clientes atendidos: %d\n", clientes_atendidos);


    return 0;
}
