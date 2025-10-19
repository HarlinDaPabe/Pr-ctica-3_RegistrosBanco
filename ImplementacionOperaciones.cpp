#include "OperacionesPrograma.h"

unsigned char** Arreglo_(unsigned char* phrase, short int semilla, int letras){
    /*Funcion Implementada para a partir del texto que entra al sistema generar con este un Arreglo con los bots de cada caracter ingresado.
    Entradas ---> Frase en un Arreglo de Char, Semilla con la que se separaran los bits, Catidad de Letras que posee el Arreglo que entra.
    Salida ---> Arreglo de Bits.
    */
    int filas = (letras*8)/semilla;
    int i = 0, limit = 0;
    unsigned char mascara = 128; unsigned char valor;
    if (filas%semilla != 0){
        filas++;
    }
    unsigned char** Arreglo_bits = new unsigned char*[filas];
    for (int fila = 0; fila < filas; fila++){
        Arreglo_bits[fila] = new unsigned char[semilla];
    }
    for (int k = 0; k < filas; k++){
        for (int j = 0; j < semilla; j++){
            valor = (phrase[i]&mascara) >> (7-limit);
            Arreglo_bits[k][j] = valor;
            limit++;
            mascara >>= 1;
            if (mascara == 0){
                limit = 0;
                mascara = 128;
                i++;
                if (i == letras){
                    break;
                }
            }
        }
    }
    return Arreglo_bits;
}


