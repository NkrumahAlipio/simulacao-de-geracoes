#include "const.h"

typedef struct Coelho
{
    int ger;
    Pos pos;
} Coelho;

Coelho criarCoelho(int lin, int col)
{
    Coelho coelho;
    coelho.ger = 0;
    coelho.pos.lin = lin;
    coelho.pos.col = col;
    return coelho;
}

int coelhoContains(int arr[], int size, int val)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}

void eliminarCoelho(Coelho *coelhos, int *tamanho, int *pos)
{
    for (int i = *pos; i < *tamanho; i++)
    {
        coelhos[i] = coelhos[i + 1];
    }
    *tamanho = *tamanho - 1;
    *pos = *pos - 1;
}

void verificarCoelhos(Coelho *coelhos, int *tamanho, int lin, int col, int matriz[][col])
{
    for (int i = 0; i < *tamanho - 1; i++)
    {
        for (int j = i + 1; j < *tamanho; j++)
        {
            if (coelhos[i].pos.lin == coelhos[j].pos.lin && coelhos[i].pos.col == coelhos[j].pos.col)
            {
                if (coelhos[i].ger > coelhos[j].ger)
                {
                    eliminarCoelho(coelhos, tamanho, &j);
                }
                else
                {
                    eliminarCoelho(coelhos, tamanho, &i);
                }
            }
        }
    }
}

void moverCoelhos(Coelho *coelhos, int *tamanho, int lin, int col, int matriz[][col])
{

    for (int i = 0; i < *tamanho; i++)
    {

        int n_vazias = 0;
        int vazias[4];

        if (coelhos[i].pos.lin != 0 && (matriz[coelhos[i].pos.lin - 1][coelhos[i].pos.col] == VAZIO_COD || COELHO_COD))
        {
            vazias[n_vazias++] = 0;
        }

        if (coelhos[i].pos.col != col - 1 && (matriz[coelhos[i].pos.lin][coelhos[i].pos.col + 1] == VAZIO_COD || COELHO_COD))
        {
            vazias[n_vazias++] = 1;
        }

        if (coelhos[i].pos.lin != lin - 1 && (matriz[coelhos[i].pos.lin + 1][coelhos[i].pos.col] == VAZIO_COD || COELHO_COD))
        {
            vazias[n_vazias++] = 2;
        }

        if (coelhos[i].pos.col != 0 && (matriz[coelhos[i].pos.lin][coelhos[i].pos.col - 1] == VAZIO_COD || COELHO_COD))
        {
            vazias[n_vazias++] = 3;
        }

        if (n_vazias == 0)
            break;

        int pos = (coelhos[i].ger + coelhos[i].pos.lin + coelhos[i].pos.col) % n_vazias;

        while (!coelhoContains(vazias, n_vazias, pos))
            pos = (pos + 1) % n_vazias;

        if (coelhos[i].ger == GER_PROC_COELHO_COD)
        {
            coelhos[*tamanho] = criarCoelho(coelhos[i].pos.lin, coelhos[i].pos.col);
            *tamanho = *tamanho + 1;
            coelhos[i].ger = 0;
        }
        else
        {
            matriz[coelhos[i].pos.lin][coelhos[i].pos.col] = VAZIO_COD;
        }

        if (pos == 0)
        {
            matriz[coelhos[i].pos.lin - 1][coelhos[i].pos.col] = COELHO_COD;
            coelhos[i].pos.lin = coelhos[i].pos.lin - 1;
        }
        else if (pos == 1)
        {
            matriz[coelhos[i].pos.lin][coelhos[i].pos.col + 1] = COELHO_COD;
            coelhos[i].pos.col = coelhos[i].pos.col + 1;
        }
        else if (pos == 2)
        {
            matriz[coelhos[i].pos.lin + 1][coelhos[i].pos.col] = COELHO_COD;
            coelhos[i].pos.lin = coelhos[i].pos.lin + 1;
        }
        else if (pos == 3)
        {
            matriz[coelhos[i].pos.lin][coelhos[i].pos.col - 1] = COELHO_COD;
            coelhos[i].pos.col = coelhos[i].pos.col - 1;
        }

        coelhos[i].ger = coelhos[i].ger + 1;
    }
    verificarCoelhos(coelhos, tamanho, lin, col, matriz);
}
