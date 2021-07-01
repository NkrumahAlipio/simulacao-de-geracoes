#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mpi/mpi.h>
#include "coelho.h"
#include "raposa.h"

char *minusculo(char *s)
{
    int i = 0;

    while (s[i] != '\0')
    {
        s[i] = tolower(s[i]);
        i++;
    }
    return s;
}

int main(int argc, char const *argv[])

{
    int ger_proc_coelhos;
    int ger_proc_raposas;
    int ger_alim_raposas;
    int n_ger;
    int lin, col;
    int n_obj;
    int x, y;

    printf("Digite o numero de geracoes ate um coelho procriar: ");
    scanf("%d", &ger_proc_coelhos);
    printf("\nDigite a numero de geracoes ate uma raposa procriar: ");
    scanf("%d", &ger_proc_raposas);
    printf("\nDigite a numero de geracoes ate uma raposa morrer a fome: ");
    scanf("%d", &ger_alim_raposas);
    printf("\nDigite o numero de geracoes a simular: ");
    scanf("%d", &n_ger);
    printf("\nDigite o numero de linhas: ");
    scanf("%d", &lin);
    printf("\nDigite o numero de colunas: ");
    scanf("%d", &col);
    printf("\nDigite o numero de objectos: ");
    scanf("%d", &n_obj);

    int n_coelhos = 0;
    int n_raposas = 0;
    Coelho coelhos[1000];
    Raposa raposas[1000];

    int matriz[lin][col];

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < lin; j++)
        {
            matriz[i][j] = VAZIO_COD;
        }
    }

    for (int i = 0; i < n_obj; i++)
    {
        printf("\nDigite o tipo do %dº objecto:(rocha,raposa,coelho): ", i + 1);
        char obj[100];
        scanf("%s", obj);

        printf("Digite a linha do %dº objeto: ", i + 1);
        scanf("%d", &x);

        printf("Digite a coluna do %dº objeto: ", i + 1);
        scanf("%d", &y);

        if (strcmp(minusculo(obj), "rocha") == 0)
        {
            matriz[x][y] = ROCHA_COD;
        }

        else if (strcmp(minusculo(obj), "coelho") == 0)
        {
            matriz[x][y] = 2;
            coelhos[n_coelhos++] = criarCoelho(x, y);
        }
        else if (strcmp(minusculo(obj), "raposa") == 0)
        {
            matriz[x][y] = 3;
            raposas[n_raposas++] = criarRaposa(x, y);
        }
        else
        {
            printf("Objecto invalido");
            i--;
        }
    }

    for (int i = 0; i < n_ger; i++)
    {
        moverCoelhos(coelhos, &n_coelhos, lin, col, matriz, ger_proc_coelhos);

        moverRaposas(raposas, &n_raposas, lin, col, matriz, ger_proc_coelhos, ger_alim_raposas);

        for (int j = 0; j < lin; j++)
        {
            for (int k = 0; k < col; k++)
            {
                printf("%d ", matriz[j][k]);
            }
            printf("\n");
        }

        printf("\n");
    }

    MPI_Finalize();

    return 0;
}
