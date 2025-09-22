#include <iostream>
#include "logicaJuego.h"
#include <cstdlib>
#include <locale.h>
#include <ctime>

using namespace std;

void mezclarCartas(string valores[], string palos[], string barajaValores[], string barajaPalos[], int cantidadValores, int cantidadPalos, int totalCartas)
{
	srand(time(0));
	int v, p, indice = 0, i;
	int j;
	string tempValor, tempPalo;

	// Genero todas las combinaciones posibles de cartas (valores y palos). 20 en total
	for (v = 0; v < cantidadValores; v++)
	{
		for(p = 0; p < cantidadPalos; p++)
		{
			if (indice < totalCartas)
			{
				barajaValores[indice] = valores[v];
				barajaPalos[indice] = palos[p];
				indice++;
			}
		}
	}

	// Aplico Algoritmo de Fisher-Yates para mezclar
	for(i = totalCartas - 1; i > 0; i--)
	{
		j = rand() % (i + 1); // 0 <= j <= i

		// Realizo el intercambio de valores
		tempValor = barajaValores[i];
		barajaValores[i] = barajaValores[j];
		barajaValores[j] = tempValor;

		tempPalo = barajaPalos[i];
		barajaPalos[i] = barajaPalos[j];
		barajaPalos[j] = tempPalo;
	}

	// https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
}

void repartirCartas(string barajaValores[], string barajaPalos[], string mazoValoresJ1[], string mazoPalosJ1[], string mazoValoresJ2[], string mazoPalosJ2[], int cantidadPorJugador)
{
	int i;
	for (i = 0; i < cantidadPorJugador; i++)
	{
		mazoValoresJ1[i] = barajaValores[i];
		mazoPalosJ1[i] = barajaPalos[i];
		mazoValoresJ2[i] = barajaValores[i + cantidadPorJugador];
		mazoPalosJ2[i] = barajaPalos[i + cantidadPorJugador];
	}
}

string CartaEmbaucadora(string palos[], int cantidadPalos)
{
    srand(time(0));
    int indiceAleatorio = rand() % cantidadPalos;
    return palos[indiceAleatorio];
}

void mostrarCartas(string mazoValores[], string mazoPalos[], int cantidad)
{
	int i;
	for (i = 0; i < cantidad; i++)
	{
		cout << mazoValores[i] + " de " + mazoPalos[i] << endl;
	}
}

int calcularPuntaje(string mazoValores[], string mazoPalos[], string cartaEmbaucadora, int cantidad)
{
    int puntaje = 0, i;
    for (i = 0; i < cantidad; i++)
    {
        if (mazoPalos[i] != cartaEmbaucadora)
        {
            if (mazoValores[i] == "10")
            {
                puntaje += 10;
            }
            else if (mazoValores[i] == "J")
            {
                puntaje += 11;
            }
            else if (mazoValores[i] == "Q")
            {
                puntaje += 12;
            }
            else if (mazoValores[i] == "K")
            {
                puntaje += 15;
            }
            else if (mazoValores[i] == "A")
            {
                puntaje += 20;
            }
        }
    }

    return puntaje;
}

void imprimirPuntajes(string mazoValores[], string mazoPalos[], string cartaEmbaucadora, int cantidad)
{
	bool primerPuntaje = true; // Bandera para saber si es el primer puntaje que se imprime
	for (int i = 0; i < cantidad; i++)
	{
		int puntajeCarta = 0;
		if (mazoPalos[i] != cartaEmbaucadora)
		{
			if (mazoValores[i] == "10")
			{
				puntajeCarta = 10;
			}
			else if (mazoValores[i] == "J")
			{
				puntajeCarta = 11;
			}
			else if (mazoValores[i] == "Q")
			{
				puntajeCarta = 12;
			}
			else if (mazoValores[i] == "K")
			{
				puntajeCarta = 15;
			}
			else if (mazoValores[i] == "A")
			{
				puntajeCarta = 20;
			}
		}
		if (puntajeCarta > 0)
		{
			if (!primerPuntaje) // si no es el primer puntaje imprimo el signo +
			{
				cout << " + ";
			}
			cout << puntajeCarta;
			primerPuntaje = false; // aca deja de ser el primer puntaje
		}
	}
}

