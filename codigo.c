#include <stdio.h>

int obtenerEvento(int evento)
{
    return evento;
}

void aumentar(int *contador)
{
    (*contador)++;
}

void mostrarRegistro(int *equipos, int *eventos, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        printf("Equipo: %d  Evento: %d\n",
               *(equipos + i), *(eventos + i));
    }
}

int main()
{
    int equipos[20] =
    {
        0, 1, 0, 2, 1,
        1, 3, 2, 0, 1,
        3, 1, 2, 2, 3,
        0, 1, 3, 2, 1
    };

    int eventos[20] =
    {
        0, 1, 0, 2, 1,
        2, 3, 2, 0, 1,
        1, 1, 0, 1, 2,
        0, 2, 3, 1, 2
    };

    int matriz[4][4] = {0};

    for (int i = 0; i < 20; i++)
    {
        int columna = obtenerEvento(eventos[i]);

        aumentar(&matriz[equipos[i]][columna]);
    }

    printf("\nREGISTRO DE EVENTOS\n");

    mostrarRegistro(equipos, eventos, 20);

    printf("\nMATRIZ\n");

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", matriz[i][j]);
        }

        printf("\n");
    }

    printf("\nDETECCION\n");

    for (int i = 0; i < 4; i++)
    {
        int intentosFallidos = matriz[i][1] + matriz[i][2];

        printf("Equipo %d: %d intentos fallidos - ",
               i, intentosFallidos);

        if (intentosFallidos > 3)
        {
            printf("Sospechoso\n");
        }
        else
        {
            printf("Normal\n");
        }
    }

    return 0;
}
