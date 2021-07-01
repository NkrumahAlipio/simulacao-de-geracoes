#include <stdlib.h>
#define GER_PROC_COELHO_COD 3
#define GER_PROC_RAPOSA_COD 2
#define GER_ALIM_RAPOSA_COD 3
#define N_GER 5
#define LIN 10
#define COL 10
#define N_OBJS 5
#define VAZIO_COD 0
#define ROCHA_COD 1
#define RAPOSA_COD 2
#define COELHO_COD 3
#define ERRO_COD 4

#ifndef POS
#define POS 1
typedef struct Posicao
{
    int lin;
    int col;
} Pos;
#endif
