#ifndef CLIENTE_H
#define CLIENTE_H
#include <semaphore.h>
#include "main.h" // aqui estou incluindos as variaveis clientes_atendidos, tempo_total_espera;


void* cliente(void* arg);

#endif /* CLIENTE_H */
