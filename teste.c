int teste(int matriz[][])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d\n", matriz[i][j]);
        }
    }
}

int main(int argc, char const *argv[])
{
    int m[10][10];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            m[i][j] = i + j;
        }
    }

    teste(m);
    return 0;
}
