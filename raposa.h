#include "const.h"

typedef struct Raposa
{
    int ger;
    int fome;
    Pos pos;
} Raposa;

Raposa criarRaposa(int lin, int col)
{
    Raposa raposa;
    raposa.ger = 0;
    raposa.fome = 0;
    raposa.pos.lin = lin;
    raposa.pos.col = col;
    return raposa;
}

int raposaContains(int arr[4][2], int size, int val)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i][0] == val)
            return 1;
    }
    return 0;
}

void eliminarRaposa(Raposa *raposas, int *tamanho, int *pos)
{
    for (int i = *pos; i < *tamanho - 1; i++)
    {
        raposas[i] = raposas[i + 1];
    }

    *tamanho = *tamanho - 1;
    *pos = *pos - 1;
}

void verificarRaposas(Raposa *raposas, int *nova_pos, int *tamanho, int lin, int col, int matriz[][col])
{

    for (int i = 0; i < *tamanho - 1; i++)
    {
        for (int j = i + 1; j < *tamanho; j++)
        {
            if (raposas[i].pos.lin == raposas[j].pos.lin && raposas[i].pos.col == raposas[j].pos.col)
            {
                if (nova_pos[i] == RAPOSA_COD || nova_pos[i] == VAZIO_COD)
                {
                    if (raposas[i].fome == raposas[j].fome)
                    {
                        if (raposas[i].ger > raposas[j].ger)
                        {
                            eliminarRaposa(raposas, tamanho, &j);
                        }
                        else
                        {
                            eliminarRaposa(raposas, tamanho, &i);
                        }
                    }
                    else if (raposas[i].fome > raposas[j].fome)
                    {
                        eliminarRaposa(raposas, tamanho, &j);
                    }
                    else
                    {
                        eliminarRaposa(raposas, tamanho, &i);
                    }
                }
                else if (nova_pos[i] == COELHO_COD)
                {
                    if (raposas[i].ger > raposas[j].ger)
                    {
                        eliminarRaposa(raposas, tamanho, &j);
                    }
                    else
                    {
                        eliminarRaposa(raposas, tamanho, &i);
                    }
                }
            }
        }
    }
}

void moverRaposas(Raposa *raposas, int *tamanho, int lin, int col, int matriz[][col])
{
    int n_tamanho = *tamanho;
    int nova_pos[n_tamanho];
    for (int i = 0; i < n_tamanho; i++)
    {
        if (raposas[i].fome == GER_ALIM_RAPOSA_COD)
        {
            matriz[raposas[i].pos.lin][raposas[i].pos.col] = VAZIO_COD;
            eliminarRaposa(raposas, tamanho, &i);
            n_tamanho--;
            break;
        }

        int n_vazias = 0;
        int vazias[4][2];

        if (raposas[i].pos.lin != 0 && (matriz[raposas[i].pos.lin - 1][raposas[i].pos.col] != ROCHA_COD))
        {
            vazias[n_vazias][0] = 0;
            vazias[n_vazias++][1] = matriz[raposas[i].pos.lin - 1][raposas[i].pos.col];
        }

        if (raposas[i].pos.col != col - 1 && (matriz[raposas[i].pos.lin][raposas[i].pos.col + 1] != ROCHA_COD))
        {
            vazias[n_vazias][0] = 1;
            vazias[n_vazias++][1] = matriz[raposas[i].pos.lin][raposas[i].pos.col + 1];
        }

        if (raposas[i].pos.lin != lin - 1 && (matriz[raposas[i].pos.lin + 1][raposas[i].pos.col] != ROCHA_COD))
        {
            vazias[n_vazias][0] = 2;
            vazias[n_vazias++][1] = matriz[raposas[i].pos.lin + 1][raposas[i].pos.col];
        }

        if (raposas[i].pos.col != 0 && (matriz[raposas[i].pos.lin][raposas[i].pos.col - 1] != ROCHA_COD))
        {
            vazias[n_vazias][0] = 3;
            vazias[n_vazias++][1] = matriz[raposas[i].pos.lin][raposas[i].pos.col - 1];
        }

        if (n_vazias == 0)
        {
            nova_pos[i] = ERRO_COD;
            break;
        }

        int pos = (raposas[i].ger + raposas[i].pos.lin + raposas[i].pos.col) % n_vazias;

        while (!raposaContains(vazias, n_vazias, pos))
            pos = (pos + 1) % n_vazias;

        if (raposas[i].ger == GER_PROC_RAPOSA_COD)
        {
            raposas[*tamanho] = criarRaposa(raposas[i].pos.lin, raposas[i].pos.col);
            *tamanho = *tamanho + 1;
            raposas[i].ger = 0;
        }
        else
        {
            matriz[raposas[i].pos.lin][raposas[i].pos.col] = VAZIO_COD;
        }

        if (pos == 0)
        {
            nova_pos[i] = matriz[raposas[i].pos.lin - 1][raposas[i].pos.col];
            matriz[raposas[i].pos.lin - 1][raposas[i].pos.col] = RAPOSA_COD;
            raposas[i].pos.lin = raposas[i].pos.lin - 1;
        }
        else if (pos == 1)
        {
            nova_pos[i] = matriz[raposas[i].pos.lin][raposas[i].pos.col + 1];
            matriz[raposas[i].pos.lin][raposas[i].pos.col + 1] = RAPOSA_COD;
            raposas[i].pos.col = raposas[i].pos.col + 1;
        }
        else if (pos == 2)
        {
            nova_pos[i] = matriz[raposas[i].pos.lin + 1][raposas[i].pos.col];
            matriz[raposas[i].pos.lin + 1][raposas[i].pos.col] = RAPOSA_COD;
            raposas[i].pos.lin = raposas[i].pos.lin + 1;
        }
        else if (pos == 3)
        {
            nova_pos[i] = matriz[raposas[i].pos.lin][raposas[i].pos.col - 1];
            matriz[raposas[i].pos.lin][raposas[i].pos.col - 1] = RAPOSA_COD;
            raposas[i].pos.col = raposas[i].pos.col - 1;
        }

        raposas[i].fome = raposas[i].fome + 1;
        raposas[i].ger = raposas[i].ger + 1;
    }
    verificarRaposas(raposas, nova_pos, tamanho, lin, col, matriz);
}
