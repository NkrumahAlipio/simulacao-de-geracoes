#include <stdlib.h>
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
