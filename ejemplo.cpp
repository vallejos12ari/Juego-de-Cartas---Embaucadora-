#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;

//FUNCIONES QUE SE USARAN A LO LARGO DEL JUEGO
void ronda2(int &puntajeJ1R1, int &puntajeJ2R1,string &embaucadora);
int obtenerAnchoConsola();
void imprimirTextoCentrado(const string& texto);
void mezclarEmbaucadora(string &embaucadora);
void cambioDeEmbaucadora(char respuestaCambioEmb,bool &primeraVueltaR2);



struct Carta
{
    string nombre;
    int valor;
    string figura;
};

bool banderaPrimeraConfirmacion = false;
Carta manoJugadorUno[5];
Carta manoJugadorDos[5];
int cantRepeticiones = 0;
int cantRepeticionesJ2R1 = 0;
int puntajeEmbaucadoraJ1R1 = 0;
int puntajeEmbaucadoraJ2R1 = 0;
int puntajeJ1R1 = 0;
int puntajeJ2R1 = 0;
int indexJ1R1 = 0;
int indexJ2R1 = 0;
Carta vectorJ1Ronda1[5] = {};
Carta vectorJ2Ronda1[5] = {};
int indexJ1R1Emb = 0;
int indexJ2R1Emb = 0;
Carta vectorJ1Ronda1Emb[5] = {};
Carta vectorJ2Ronda1Emb[5] = {};
string embaucadora = "";


void restarPuntosEmb(int &puntajeJ1R1, int puntajeJ2R1)
{



}


void ronda2(int &puntajeJ1R1, int &puntajeJ2R1, string &embaucadora)
{

    char respuestaJ1R2;
    char respuestaJ2R2;
    bool restarPuntajeJ1R2=false;
    bool restarPuntajeJ2R2=false;

};


//identifica el sistema operativo windows
//si la macro no esta definida da un error
//ifdef es una directiva  del preprocesador que se usa para saber si la macro esta definida
//win32 es una macro, una api que se utiliza para compilar apps de escritorio de windoes
#ifdef _WIN32
int obtenerAnchoConsola()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
//linux-mac
#else
int obtenerAnchoConsola()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
#endif

//funcion para centrar los textos
void imprimirTextoCentrado(const string& texto)
{
    int anchoConsola = obtenerAnchoConsola();
    int longitudTexto = texto.length();
    int espaciosParaCentrar = (anchoConsola - longitudTexto) / 2;

    for (int i = 0; i < espaciosParaCentrar; ++i)
    {
        cout << " ";
    }
    cout << texto << endl;
}

//funcion para mezclar las cartas
void mezclarCartas(Carta cartas[], int size)
{
    srand(static_cast<unsigned int>(time(0)));

    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(cartas[i], cartas[j]);
    }
}

//funcion para mezclar la embaucadora
void mezclarEmbaucadora(string &embaucadora)
{
    string figuras[4] = {"Corazón", "Diamante", "Pica", "Trébol"};
    srand(static_cast<unsigned int>(time(0)));
    int indiceAleatorio = rand() % 4;
    embaucadora = figuras[indiceAleatorio];
}

int main()
{
    setlocale(LC_ALL, "");

    char respuesta;
    char respuestaEmbJ1;
    char respuestaEmbJ2;
    bool negacionEmbJ1R1 = false;
    bool negacionEmbJ2R1 = false;

    //Mazo ordenado
    Carta cartasTotal[20] =
    {
        {"10 de Diamante", 10, "Diamante"}, {"J de Diamante", 11, "Diamante"}, {"Q de Diamante", 12, "Diamante"}, {"K de Diamante", 15, "Diamante"}, {"A de Diamante", 20, "Diamante"}, {"10 de Pica", 10, "Pica"}, {"J de Pica", 11, "Pica"}, {"Q de Pica", 12, "Pica"}, {"K de Pica", 15, "Pica"}, {"A de Pica", 20, "Pica"}, {"10 de Trébol", 10, "Trébol"}, {"J de Trébol", 11, "Trébol"}, {"Q de Trébol", 12, "Trébol"}, {"K de Trébol", 15, "Trébol"}, {"A de Trébol", 20, "Trébol"}, {"10 de Corazón", 10, "Corazón"}, {"J de Corazón", 11, "Corazón"}, {"Q de Corazón", 12, "Corazón"}, {"K de Corazón", 15, "Corazón"}, {"A de Corazón", 20, "Corazón"}
    };

    imprimirTextoCentrado("MAZO ORDENADO:");
    cout<<endl<<endl;
    for (int x = 0; x < 20; x++)
    {
        imprimirTextoCentrado(cartasTotal[x].nombre + " - Valor: " + to_string(cartasTotal[x].valor));
    }

    imprimirTextoCentrado("");

    do
    {
        if (banderaPrimeraConfirmacion == true)
        {
            cout<<endl<<endl;
            imprimirTextoCentrado("Desea mezclar las cartas otra vez? S/N");
            cin >> respuesta;
        }
        else
        {
            imprimirTextoCentrado("Desea mezclar las cartas? S/N");
            cin >> respuesta;
        }
        if (respuesta == 'S' || respuesta == 's')
        {
            banderaPrimeraConfirmacion = true;
            imprimirTextoCentrado("Respuesta confirmada");

            //mazo mezclado
            mezclarCartas(cartasTotal, 20);

            imprimirTextoCentrado("");

            imprimirTextoCentrado("MAZO MEZCLADO:");
            cout<<endl<<endl;
            // se imprimen las cartas mezcladas
            for (int x = 0; x < 20; x++)
            {
                imprimirTextoCentrado(cartasTotal[x].nombre + " - Valor: " + to_string(cartasTotal[x].valor) + " - Figura: " + cartasTotal[x].figura);
            }
        }
        else if (respuesta == 'N' || respuesta == 'n')
        {
            imprimirTextoCentrado("Respuesta NO confirmada");
        }
        else
        {
            imprimirTextoCentrado("Respuesta invalida");
        }
    }
    while (respuesta != 'N' && respuesta != 'n');



    imprimirTextoCentrado("");
    imprimirTextoCentrado("");
    imprimirTextoCentrado("+--------------------------------------------------+");
    imprimirTextoCentrado("|                                                  |");
    imprimirTextoCentrado("|             Empezamos con la RONDA 1             |");
    imprimirTextoCentrado("|                                                  |");
    imprimirTextoCentrado("+--------------------------------------------------+");
    imprimirTextoCentrado("");

    imprimirTextoCentrado("Repartiendo cartas a cada jugador:");
    imprimirTextoCentrado("---------------------------------------------------");

    for (int x = 0; x < 5; x++)
    {
        manoJugadorUno[x] = cartasTotal[x];
    }

    for (int x = 0; x < 5; x++)
    {
        manoJugadorDos[x] = cartasTotal[x + 5];
    }

    imprimirTextoCentrado(" JUGADOR 1 : " + to_string(puntajeJ1R1) + " (puntos)");
    cout<<endl<<endl;

    for (int x = 0; x < 5; x++)
    {
        imprimirTextoCentrado(manoJugadorUno[x].nombre + " - Valor: " + to_string(manoJugadorUno[x].valor) + " - Figura: " + manoJugadorUno[x].figura);
    }
    imprimirTextoCentrado("---------------------------------------------------");

    imprimirTextoCentrado(" JUGADOR 2 : " + to_string(puntajeJ2R1)+ " (puntos)");
    cout<<endl<<endl;

    for (int x = 0; x < 5; x++)
    {
        imprimirTextoCentrado(manoJugadorDos[x].nombre + " - Valor: " + to_string(manoJugadorDos[x].valor) + " - Figura: " + manoJugadorDos[x].figura);
    }
    cout<<endl<<endl;
    imprimirTextoCentrado("---------------------------------------------------");

    mezclarEmbaucadora(embaucadora);
    imprimirTextoCentrado("La carta embaucadora es: " + embaucadora);
    imprimirTextoCentrado("---------------------------------------------------");

    imprimirTextoCentrado("");
    imprimirTextoCentrado("+*******+");
    imprimirTextoCentrado("|                                                  |");
    imprimirTextoCentrado("|               Puntajes obtenidos:                |");
    imprimirTextoCentrado("|                                                  |");
    imprimirTextoCentrado("+*******+");

    imprimirTextoCentrado("");
    imprimirTextoCentrado("*****");
    imprimirTextoCentrado("+                           +");
    imprimirTextoCentrado("+     Jugador 1: ROSS       +");
    imprimirTextoCentrado("+                           +");
    imprimirTextoCentrado("*****");

    for (int x = 0; x < 5; x++)
    {
        if (manoJugadorUno[x].figura == embaucadora)
        {
            cantRepeticiones++;
            puntajeEmbaucadoraJ1R1 = puntajeEmbaucadoraJ1R1 + manoJugadorUno[x].valor;
            vectorJ1Ronda1Emb[indexJ1R1Emb] = manoJugadorUno[x];
            indexJ1R1Emb++;
        }
        else
        {
            puntajeJ1R1 = puntajeJ1R1 + manoJugadorUno[x].valor;
            vectorJ1Ronda1[indexJ1R1] = manoJugadorUno[x];
            indexJ1R1++;
        }

        if (manoJugadorDos[x].figura == embaucadora)
        {
            puntajeEmbaucadoraJ2R1 = puntajeEmbaucadoraJ2R1 + manoJugadorDos[x].valor;
            vectorJ2Ronda1Emb[indexJ2R1Emb] = manoJugadorDos[x];
            indexJ2R1Emb++;
        }
        else
        {
            puntajeJ2R1 = puntajeJ2R1 + manoJugadorDos[x].valor;
            vectorJ2Ronda1[indexJ2R1] = manoJugadorDos[x];
            indexJ2R1++;
        }
    }

    imprimirTextoCentrado("Las cartas NO embaucadas son:");

    for (int x = 0; x < indexJ1R1; x++)
    {
        imprimirTextoCentrado(vectorJ1Ronda1[x].nombre + " (" + to_string(vectorJ1Ronda1[x].valor) + ")");
    }

    imprimirTextoCentrado("*****");
    imprimirTextoCentrado(" PUNTAJE: " + to_string(puntajeJ1R1) + " (puntos ganados)");
    imprimirTextoCentrado("*****");
    cout <<endl;

    imprimirTextoCentrado("¿Desea ver las cartas embaucadas del Jugador 1? S/N");

    do
    {
        cin >> respuestaEmbJ1;

        if (respuestaEmbJ1 == 'S' || respuestaEmbJ1 == 's')
        {
            imprimirTextoCentrado("Respuesta confirmada");
            cout <<endl;

            if (indexJ1R1Emb == 0)
            {
                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("     El Jugador 1 no tiene ninguna carta embaucada     ");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("~~~~~~~~");

                negacionEmbJ1R1 = true;
            }
            else if (indexJ1R1Emb == 1)
            {
                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("     El Jugador 1 tiene " + to_string(indexJ1R1Emb) + " carta embaucada    ");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("~~~~~~~~");

                cout <<endl;
                imprimirTextoCentrado("La carta embaucada es:");

                for (int x = 0; x < indexJ1R1Emb; x++)
                {
                    imprimirTextoCentrado( vectorJ1Ronda1Emb[x].nombre + " (" + to_string(vectorJ1Ronda1Emb[x].valor) + ")");
                }
                cout <<endl;

                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("PUNTOS PERDIDOS: " + to_string(puntajeEmbaucadoraJ1R1));
                imprimirTextoCentrado("~~~~~~~~");

                negacionEmbJ1R1 = true;
            }
            else
            {
                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("     El Jugador 1 tiene " + to_string(indexJ1R1Emb) + " cartas embaucada     ");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("~~~~~~~~");

                imprimirTextoCentrado("Las cartas embaucadas son:");

                for (int x = 0; x < indexJ1R1Emb; x++)
                {
                    imprimirTextoCentrado("                  " + vectorJ1Ronda1Emb[x].nombre + " (" + to_string(vectorJ1Ronda1Emb[x].valor) + ")");
                }

                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("                 PUNTOS PERDIDOS: " + to_string(puntajeEmbaucadoraJ1R1));
                imprimirTextoCentrado("~~~~~~~~");

                negacionEmbJ1R1 = true;
            }
        }
        else if (respuestaEmbJ1 == 'N' || respuestaEmbJ1 == 'n')
        {
            imprimirTextoCentrado("Respuesta NO confirmada");
            cout <<endl;
            negacionEmbJ1R1 = true;
        }
        else
        {
            imprimirTextoCentrado("Respuesta inválida.");
            cout <<endl;
            imprimirTextoCentrado("Intente nuevamente.");
            cout <<endl;
            imprimirTextoCentrado("¿Desea ver las cartas embaucadas y los puntos perdidos del Jugador 1? S/N");
        }
    }
    while (negacionEmbJ1R1 == false);
    cout <<endl;

    // Puntaje Jugador 2

    imprimirTextoCentrado("");
    imprimirTextoCentrado("*****");
    imprimirTextoCentrado("+                           +");
    imprimirTextoCentrado("+     Jugador 2: CHANDLER   +");
    imprimirTextoCentrado("+                           +");
    imprimirTextoCentrado("*****");

    cout  << endl;

    imprimirTextoCentrado("Las cartas NO embaucadas son:");


    for (int x = 0; x < indexJ2R1; x++)
    {
        imprimirTextoCentrado( vectorJ2Ronda1[x].nombre + " (" + to_string(vectorJ2Ronda1[x].valor) + ")");
    }

    imprimirTextoCentrado("*****");
    imprimirTextoCentrado(" PUNTAJE: " + to_string(puntajeJ2R1) + " (puntos ganados)");
    imprimirTextoCentrado("*****");
    cout <<endl;

    imprimirTextoCentrado("¿Desea ver las cartas embaucadas del Jugador 2? S/N");


    do
    {
        cin >> respuestaEmbJ2;

        if (respuestaEmbJ2 == 'S' || respuestaEmbJ2 == 's')
        {
            imprimirTextoCentrado("Respuesta confirmada");
            cout <<endl;

            if (indexJ2R1Emb == 0)
            {
                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("     El Jugador 2 no tiene ninguna carta embaucada     ");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("~~~~~~~~");

                negacionEmbJ2R1 = true;
            }
            else if (indexJ2R1Emb == 1)
            {
                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("     El Jugador 2 tiene " + to_string(indexJ2R1Emb) + " carta embaucada    ");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("~~~~~~~~");

                cout <<endl;
                imprimirTextoCentrado("La carta embaucada es:");

                for (int x = 0; x < indexJ2R1Emb; x++)
                {
                    imprimirTextoCentrado( vectorJ2Ronda1Emb[x].nombre + " (" + to_string(vectorJ2Ronda1Emb[x].valor) + ")");
                }
                cout <<endl;

                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("PUNTOS PERDIDOS: " + to_string(puntajeEmbaucadoraJ2R1));
                imprimirTextoCentrado("~~~~~~~~");

                negacionEmbJ2R1 = true;
            }
            else
            {
                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("     El Jugador 2 tiene " + to_string(indexJ2R1Emb) + " cartas embaucada     ");
                imprimirTextoCentrado("|                                                            |");
                imprimirTextoCentrado("~~~~~~~~");

                imprimirTextoCentrado("Las cartas embaucadas son:");

                for (int x = 0; x < indexJ2R1Emb; x++)
                {
                    imprimirTextoCentrado("                  " + vectorJ2Ronda1Emb[x].nombre + " (" + to_string(vectorJ2Ronda1Emb[x].valor) + ")");
                }

                imprimirTextoCentrado("~~~~~~~~");
                imprimirTextoCentrado("                 PUNTOS PERDIDOS: " + to_string(puntajeEmbaucadoraJ2R1));
                imprimirTextoCentrado("~~~~~~~~");

                negacionEmbJ2R1 = true;
            }
        }
        else if (respuestaEmbJ2 == 'N' || respuestaEmbJ2 == 'n')
        {
            imprimirTextoCentrado("Respuesta NO confirmada");
            cout <<endl;
            negacionEmbJ2R1 = true;
        }
        else
        {
            imprimirTextoCentrado("Respuesta inválida.");
            cout <<endl;
            imprimirTextoCentrado("Intente nuevamente.");
            cout <<endl;
            imprimirTextoCentrado("¿Desea ver las cartas embaucadas y los puntos perdidos del Jugador 2? S/N");
        }
    }
    while (negacionEmbJ2R1 == false);
    cout <<endl;

    ronda2(puntajeJ1R1, puntajeJ2R1,embaucadora);


    imprimirTextoCentrado("Fin del programa");

    return 0;
}
