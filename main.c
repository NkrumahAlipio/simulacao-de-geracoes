#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>
#include "coelho.h"
#include "raposa.h"

int main(int argc, char const *argv[])

{
    int matriz[LIN][COL];

    int n_coelhos = 0;
    int n_raposas = 0;
    Coelho coelhos[1000];
    Raposa raposas[100];

    for (int i = 0; i < LIN; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            matriz[i][j] = VAZIO_COD;
        }
    }

    matriz[0][0] = ROCHA_COD;
    matriz[0][2] = COELHO_COD;
    coelhos[n_coelhos++] = criarCoelho(0, 2);
    matriz[0][5] = ROCHA_COD;
    matriz[2][5] = COELHO_COD;
    coelhos[n_coelhos++] = criarCoelho(2, 5);

    matriz[9][9] = RAPOSA_COD;
    raposas[n_raposas++] = criarRaposa(9, 9);

    for (int i = 0; i < N_GER; i++)
    {
        moverCoelhos(coelhos, &n_coelhos, LIN, COL, matriz);

        moverRaposas(raposas, &n_raposas, LIN, COL, matriz);
        for (int j = 0; j < LIN; j++)
        {
            for (int k = 0; k < COL; k++)
            {
                printf("%d ", matriz[j][k]);
            }
            printf("\n");
        }

        printf("\n");
    }

    return 0;
}
