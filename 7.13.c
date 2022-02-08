#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
                        made by Santiago Martín Correa
*/
void repartir( int mazo[][13], const char*palos[], const char*carta[], int cantidadCartas, int jugador );
void mezclar( int mazo[][13] );
int determinarJuego( int mazo[][13], int jugador);
void valorMano( int numero );

int determinarJuegoPtr( int mazo[][13], int *ptrJuego , int jugador ); // prototipo con pointer
void valorManoPtr( int *numero );   // prototipo con pointer

int main(void)
{
        const char *palos[4] = { "Corazones", "Trebol", "Picas", "Diamantes" };

        const char *carta[13] = { "As", "Dos", "Tres", "Cuatro", "Cinco", "Seis",
                                    "Siete", "Ocho", "Nueve", "Diez", "Sota", "Caballo", "Rey" };

        int mazo[4][13] = { 0 };

        srand( time( NULL ) );

        mezclar( mazo );

        int jugador0 = 0;
        int juego1 = 0;
        int *ptrJuego1 = NULL;
        ptrJuego1 = &juego1;

        repartir( mazo, carta, palos, 5, jugador0 );
        determinarJuegoPtr( mazo, ptrJuego1, jugador0 );
        valorManoPtr( ptrJuego1);
        //valorMano( determinarJuego( mazo, jugador0 ) );

        printf("\n");

        int jugador1 = 1;
        int juego2 = 0;
        int *ptrJuego2 = NULL;
        ptrJuego2 = &juego2;

        repartir( mazo, carta, palos, 5, jugador1 );
        determinarJuegoPtr( mazo, ptrJuego2, jugador1 );
        valorManoPtr( ptrJuego2);
        //valorMano( determinarJuego( mazo, jugador1 ) );

        printf("\n");

        //  determinar ganador
        if( *ptrJuego1 == *ptrJuego2 )
            printf("Es un empate\n");
        else if( *ptrJuego1 > *ptrJuego2)
            printf("Ganador Jugador 1\n");
        else
            printf("Ganador Jugador 2\n");

        return 0;
}

void mezclar( int mazo[][13] )
{
    int palo, carta;
    for ( int i = 1; i <= 52; i++)
    {
        do{
            palo = rand() % 4;
            carta = rand() % 13;
        }while( mazo[palo][carta] != 0);

        mazo[palo][carta] = i;
    }
}

void repartir( int mazo[][13], const char*carta[], const char*palos[], int cantidadCartas, int jugador )
{
    printf("Mano Jugador %d\n", jugador + 1);
    for ( int i = (1 + jugador*5); i <= (cantidadCartas + jugador*5); i++)
    {
        for( int j = 0; j < 4; j++ ) // por cada palo
        {
            for( int w = 0; w < 13; w++)
            {
                if( mazo[j][w] == i)
                    printf("Carta %d \t %6s de %-9s\n", i, carta[w], palos[j]);

            }
        }
    }
}


int determinarJuego( int mazo[][13], int jugador)
{
    int escaleraReal( int mazo[][13], int jugador );
    if ( escaleraReal(mazo, jugador) == 1 )
    {
        return 7;
    }

    int poker( int mazo[][13], int jugador );
    if ( poker(mazo, jugador) == 1 )
    {
        return 6;
    }

    int color( int mazo[][13], int jugador );
    if ( color(mazo, jugador) == 1 )
    {
        return 5;
    }

    int piernaOfull( int mazo[][13], int jugador );
    if ( piernaOfull(mazo, jugador) == 2 )
    {
        return 4;
    }
    else if ( piernaOfull(mazo, jugador) == 1 )
    {
        return 3;
    }

    int pares( int mazo[][13], int jugador );
    if ( pares(mazo, jugador) == 2 )
    {
        return 2;
    }
    else if ( pares(mazo, jugador) == 1 )
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

int escaleraReal( int mazo[][13], int jugador )
{
    int cantidad = 0;

    for( int j = 0; j < 4; j++ ) // por cada palo
    {
        for( int w = 0; w < 13; w++)
        {
            if( mazo[j][w] == (1 + jugador*5) || mazo[j][w] == (2 + jugador*5) || mazo[j][w] == (3 + jugador*5) || mazo[j][w] == (4 + jugador*5) || mazo[j][w] == (5 + jugador*5) ) // si encuentra la carta del mismo palo
            {
                cantidad++;
            }
            else
            {
                cantidad = 0;
            }
        }
        if ( cantidad == 5) // si 5 son consecutivas, escalera del mismo palo
        {
            return 1;
        }
    }
    return 0;
}// fin funcion escalera real

int poker( int mazo[][13], int jugador )
{
    for( int j = 0; j < 13; j++ ) // por cada numero de carta
    {
        int cantidad = 0;

        for( int w = 0; w < 4; w++) // por cada palo
        {
            if( mazo[w][j] == (1 + jugador*5) || mazo[w][j] == (2 + jugador*5) || mazo[w][j] == (3 + jugador*5) || mazo[w][j] == (4 + jugador*5) || mazo[w][j] == (5 + jugador*5) ) // si encuentra la carta del mismo numero
            {
                cantidad++;
            }
        }
        if ( cantidad == 4) // si tiene poker
        {
            return 1;
        }
    }
    return 0;
} // fin funcion poker

int color( int mazo[][13], int jugador )
{
    for( int j = 0; j < 4; j++ ) // por cada palo
    {
        int cantidad = 0;

        for( int w = 0; w < 13; w++)
        {
            if( mazo[j][w] == (1 + jugador*5) || mazo[j][w] == (2 + jugador*5) || mazo[j][w] == (3 + jugador*5) || mazo[j][w] == (4 + jugador*5) || mazo[j][w] == (5 + jugador*5) ) // si encuentra la carta del mismo palo
            {
                cantidad++;
            }
        }
        if ( cantidad == 5) // si 5 son del mismo palo
        {
            return 1;
        }
    }
    return 0;
}// fin funcion escalera real

int piernaOfull( int mazo[][13], int jugador )
{
    int par = 0;
    int trio = 0;

    for( int j = 0; j < 13; j++ ) // por cada numero de carta
    {
        int cantidad = 0;

        for( int w = 0; w < 4; w++) // por cada palo
        {
            if( mazo[w][j] == (1 + jugador*5) || mazo[w][j] == (2 + jugador*5) || mazo[w][j] == (3 + jugador*5) || mazo[w][j] == (4 + jugador*5) || mazo[w][j] == (5 + jugador*5) ) // si encuentra la carta del mismo numero
            {
                cantidad++;
            }
        }
        if ( cantidad == 3) // si tiene poker
        {
            trio++;
        }
        else if( cantidad == 2 )
        {
            par++;
        }
    }
    if( trio == 1 && par == 1)  // si tiene full
        return 2;
    else if ( trio == 1 )       // si tiene pierna
        return 1;
    else                        // si no tiene ni full ni pierna
        return 0;
} // fin funcion pierna

int pares( int mazo[][13], int jugador )
{
    int pares = 0;
    for( int j = 0; j < 13; j++ ) // por cada numero de carta
    {
        int cantidad = 0;

        for( int w = 0; w < 4; w++) // por cada palo
        {
            if( mazo[w][j] == (1 + jugador*5) || mazo[w][j] == (2 + jugador*5) || mazo[w][j] == (3 + jugador*5) || mazo[w][j] == (4 + jugador*5) || mazo[w][j] == (5 + jugador*5) ) // si encuentra la carta del mismo numero
            {
                cantidad++;
            }
        }
        if ( cantidad == 2) // si tiene par
        {
            pares++;
        }
    }
    return pares;
} // fin funcion pares


void valorMano( int numero )
{
    switch (numero)
    {
        case 7:
            printf("\nTenes una Escalera Real\n");
            break;
        case 6:
            printf("\nTenes Poker\n");
            break;
        case 5:
            printf("\nTenes Color\n");
            break;
        case 4:
            printf("\nTenes Full\n");
            break;
        case 3:
            printf("\nTenes una Pierna\n");
            break;
        case 2:
            printf("\nTenes un Par Doble\n");
            break;
        case 1:
            printf("\nTenes un Par\n");
            break;
        case 0:
            printf("\nNo tenes ninguna combinacion\n");
            break;
        default:
            break;
    }
}


void valorManoPtr( int *numero )
{
    switch (*numero)
    {
        case 7:
            printf("\nTenes una Escalera Real\n");
            break;
        case 6:
            printf("\nTenes Poker\n");
            break;
        case 5:
            printf("\nTenes Color\n");
            break;
        case 4:
            printf("\nTenes Full\n");
            break;
        case 3:
            printf("\nTenes una Pierna\n");
            break;
        case 2:
            printf("\nTenes un Par Doble\n");
            break;
        case 1:
            printf("\nTenes un Par\n");
            break;
        case 0:
            printf("\nNo tenes ninguna combinacion\n");
            break;
        default:
            break;
    }
}

int determinarJuegoPtr( int mazo[][13], int *ptrJuego, int jugador  )
{
    int escaleraReal( int mazo[][13], int jugador );
    if ( escaleraReal(mazo, jugador) == 1 )
    {
        (*ptrJuego) = 7;
    }

    int poker( int mazo[][13], int jugador );
    if ( poker(mazo, jugador) == 1 )
    {
        (*ptrJuego) = 6;
    }

    int color( int mazo[][13], int jugador );
    if ( color(mazo, jugador) == 1 )
    {
        (*ptrJuego) = 5;
    }

    int piernaOfull( int mazo[][13], int jugador  );
    if ( piernaOfull(mazo, jugador) == 2 )
    {
        (*ptrJuego) = 4;
    }
    else if ( piernaOfull(mazo, jugador) == 1 )
    {
        (*ptrJuego) = 3;
    }

    int pares( int mazo[][13], int jugador );
    if ( pares(mazo, jugador) == 2 )
    {
        (*ptrJuego) = 2;
    }
    else if ( pares(mazo, jugador) == 1 )
    {
        (*ptrJuego) = 1;
    }
    else
    {
        (*ptrJuego) = 0;
    }

}
