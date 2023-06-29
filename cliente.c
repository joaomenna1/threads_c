#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "cliente.h"

extern int estoque_pao;
extern int estoque_salsicha;
extern int estoque_molho;
extern pthread_mutex_t mutex_estoque;
extern sem_t sem_fornecedor;

pthread_mutex_t mutex_atendimento;


void* cliente(void* arg) {
    int id = *(int*)arg;
    free(arg);

    // Tempo de chegada do cliente
    struct timespec tempo_chegada;
    tempo_chegada.tv_sec = 0;
    tempo_chegada.tv_nsec = (rand() % 200) * 1000000;  // Tempo aleatório entre 0ms e 200ms
    nanosleep(&tempo_chegada, NULL);

    struct timespec tempo_inicio = {0, 0}, tempo_fim;
    clock_gettime(CLOCK_MONOTONIC, &tempo_inicio);

    pthread_mutex_lock(&mutex_estoque);
    if (estoque_pao > 0 && estoque_salsicha > 0 && estoque_molho > 0) {
        estoque_pao--;
        estoque_salsicha--;
        estoque_molho--;

        printf("Cliente %d: kikao recebido. Estoque: pão %d, salsicha %d, molho %d\n", id, estoque_pao, estoque_salsicha, estoque_molho);

        usleep(10000);  // Preparação do kikao

        printf("Cliente %d: kikao consumido\n", id);
    } else {
        printf("Cliente %d: kikao indisponível\n", id);
    }
    pthread_mutex_unlock(&mutex_estoque);

    sem_post(&sem_fornecedor);

   clock_gettime(CLOCK_MONOTONIC, &tempo_fim);
   double tempo_espera = (tempo_fim.tv_sec - tempo_inicio.tv_sec) +
                         (tempo_fim.tv_nsec - tempo_inicio.tv_nsec) / 1e9;

    pthread_mutex_lock(&mutex_atendimento);
    tempo_total_espera += tempo_espera;
    clientes_atendidos++;
    pthread_mutex_unlock(&mutex_atendimento);


    pthread_exit(NULL);
}
