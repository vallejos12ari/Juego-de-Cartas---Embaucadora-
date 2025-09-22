#pragma once

void mezclarCartas(std::string valores[], std::string palos[], std::string barajaValores[], std::string barajaPalos[], int cantidadValores, int cantidadPalos, int totalCartas);
void repartirCartas(std::string barajaValores[], std::string barajaPalos[], std::string mazoValoresJ1[], std::string mazoPalosJ1[], std::string mazoValoresJ2[], std::string mazoPalosJ2[], int cantidadPorJugador);
std::string CartaEmbaucadora(std::string palos[], int cantidadPalos);
void mostrarCartas(std::string mazoValores[], std::string mazoPalos[], int cantidad);
int calcularPuntaje(std::string mazoValores[], std::string mazoPalos[], std::string cartaEmbaucadora, int cantidad);
void imprimirPuntajes(std::string mazoValores[], std::string mazoPalos[], std::string cartaEmbaucadora, int cantidad);
