/* -----------------------------------------------------------------------
 PRA1. Processos, pipes i senyals: El 7,5
 Codi font : jugador.c

 Nom complet autor1.  
 Nom complet autor2.  
 ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

char *color_red = "\033[01;31m";
char *color_yellow = "\033[01;33m";
char *color_green = "\033[01;32m";
char *color_end = "\033[00m";

void inicialitzacions()
{
    /* Inicialització nombres aleatoris */
    srand(getpid());
}

/* Codificació cartes: 0:rei, 1:as, 2:2, ..., 7:7, 8:sota, 9:cavall */
/* Per no gestionar decimals, es guarda el valor numèric multiplicat per 2 */

#define NUM_CARTES 10

struct
{
    char *nom;
    int valor;
} cartes[NUM_CARTES] =
    {
        {"rei", 1},
        {"as", 2},
        {"2", 4},
        {"3", 6},
        {"4", 8},
        {"5", 10},
        {"6", 12},
        {"7", 14},
        {"sota", 1},
        {"cavall", 1}};

/* Retorna una carta (enter entre 0 i NUM_CARTES -1) */
int obtenir_carta()
{
    return (rand() % NUM_CARTES);
}

void error(char *m)
{
    write(2, m, strlen(m));
    write(2, "\n", 1);
    exit(0);
}

int main()
{
    int no_fi = TRUE;
    int actual = 0, previ = 0;
    int carta;
    char s[100];

    inicialitzacions();

    while (no_fi)
    {
        carta = obtenir_carta();

        previ = actual;
        actual += cartes[carta].valor;

        sprintf(s,
                "[%d] valor previ=%2.1f, carta rebuda=%s, valor actual=%2.1f\n",
                getpid(), previ / 2.0, cartes[carta].nom, actual / 2.0);

        if (write(1, s, strlen(s)) < 0)
            error("write info. cartes");

        if (actual > 15)
        { /* 15 = 7.5 * 2 */
            sprintf(s, "%s[%d] M'he passat\n%s", color_red, getpid(), color_end);
            no_fi = FALSE;
        }
        else if (actual == 15)
        {
            sprintf(s, "%s[%d] Em planto amb 7.5\n%s", color_green, getpid(), color_end);
            no_fi = FALSE;
        }
        else
        {
            if ((rand() % 3) == 0)
            {
                sprintf(s, "%s[%d] Decideixo plantar-me amb %2.1f\n%s", color_yellow, getpid(), actual / 2.0, color_end);
                no_fi = FALSE;
            }
            else
            {
                sprintf(s, "[%d] Decideixo continuar\n", getpid());
            }
        }
        if (write(1, s, strlen(s)) < 0)
            error("write resultat + decisió");

        /* Per introduir una certa aleatorietat en el temps d'execució dels jugadors */
        sleep(rand() % 2);
    }

    exit(0);
}
