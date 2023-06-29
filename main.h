#ifndef MAIN_H
#define MAIN_H

extern int clientes_atendidos;
extern double tempo_total_espera;

#include <pthread.h>

extern pthread_mutex_t mutex_atendimento;

#endif 
