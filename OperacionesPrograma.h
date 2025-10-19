#ifndef OPERACIONESPROGRAMA_H
#define OPERACIONESPROGRAMA_H

unsigned char** Arreglo_(unsigned char* phrase, short int semilla, int letras, int& filas);
unsigned char** Codificacion_1(unsigned char** Arreglo_bits, short int semilla, int filas);
void Codificacion_2(unsigned char** Arreglo_bits, short int semilla, int filas);
unsigned char* Lectura(char* url, int& letras);
void Escritura(char* endfile, unsigned char** TexCodif, short int semilla, int filas);

#endif // OPERACIONESPROGRAMA_H
