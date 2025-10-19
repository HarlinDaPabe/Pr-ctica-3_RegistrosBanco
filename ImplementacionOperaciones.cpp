#include "OperacionesPrograma.h"
#include <iostream>
#include <fstream>
using namespace std;

unsigned char** Arreglo_(unsigned char* phrase, short int semilla, int letras, int& filas){
    /*Funcion Implementada para a partir del texto que entra al sistema generar con este un Arreglo con los bots de cada caracter ingresado.
    Entradas ---> Frase en un Arreglo de Char, Semilla con la que se separaran los bits, Catidad de Letras que posee el Arreglo que entra.
    Salida ---> Arreglo de Bits.
    */
    filas = (letras*8)/semilla;
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

unsigned char** Codificacion_1(unsigned char** Arreglo_bits, short int semilla, int filas){
    /*Realiza la Codificacion de bits según el patrón de 0s y 1s que aparezca en determinada fila.
    Entradas ---> Arreglo Unsigned Char de 0s y 1s, Semilla Cantidad de valores en cada fila.
    Salida ---> Arreglo Codificado.
    */
    short int Cont0, Cont1, limit;
    unsigned char** ptr = new unsigned char*[filas];
    for (int fila = 0; fila < filas; fila++){
        ptr[fila] = new unsigned char[semilla];
    }
    for (int i = 0; i < filas; i++){
        Cont0 = 0, Cont1 = 0, limit = 2;
        for (int j = 0; j < semilla; j++){
            if (Arreglo_bits[i][j] == 0){
                Cont0++;
            } else{
                Cont1++;
            }
            if (i == 0){
                ptr[i][j] = !Arreglo_bits[i][j];
            }
        }
        if (i+1 < filas){
            for (int k = 0; k < semilla; k++){
                if (Cont1 > Cont0){
                    if (k == limit){
                        ptr[i+1][k] = !Arreglo_bits[i+1][k];
                        limit += 3;
                    }
                } else if (Cont0 > Cont1){
                    if (k%2 != 0){
                        ptr[i+1][k] = !Arreglo_bits[i+1][k];
                    }
                } else {
                    ptr[i+1][k] = !Arreglo_bits[i+1][k];
                }
            }
        }
    }
    return ptr;
}

void Codificacion_2(unsigned char** Arreglo_bits, short int semilla, int filas){
    /*Realiza la Codificacion de bits rotando los valores del Arreglo una posición a la Izquierda.
    Entradas ---> Arreglo Unsigned Char de 0s y 1s, Semilla Cantidad de valores en cada fila.
    Salida ---> void
    */
    unsigned char ultimo;
    for (int i = 0; i < filas; i++){
        ultimo = Arreglo_bits[i][0];
        for (int j = 1; j < semilla; j++){
            Arreglo_bits[i][j-1] = Arreglo_bits[i][j];
        }
        Arreglo_bits[i][semilla-1] = ultimo;
    }
}

unsigned char* Lectura(char* url, int& letras){
    /*Se encarga de realizar la lectura del Archivo de texto.
    Entradas ---> Arreglo de Unsigned char con el nombre del Archivo.
    Salida ---> Arreglo Unsigned Char con el Contenido del Archivo.
    */
    unsigned char* prt;
    ifstream archivo(url, ios::binary | ios::ate);
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return NULL;
    }

    letras = archivo.tellg();
    prt = new unsigned char[letras];

    archivo.seekg(0);
    archivo.read(reinterpret_cast<char*>(prt), letras);
    archivo.close();
    return prt;
}

void Escritura(char* endfile, unsigned char** TexCodif, short int semilla, int filas){
    /*Se encarga de realizar la escritura de un Archivo de texto, a partir del texto que poseemos Codificado.
    Entradas ---> Arreglo de Unsigned char con el nombre del Archivo, Cantidad de Filas del Arreglo.
    Salida ---> Void
    */
    ofstream archivo(endfile, ios::out | ios::app);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo para escritura.\n";
    } else {
        for (int i = 0; i < filas; i++){
            for (int j = 0; j < semilla; j++){
                archivo << (int)TexCodif[i][j];
            }
        }
    }
    archivo.close();
}
