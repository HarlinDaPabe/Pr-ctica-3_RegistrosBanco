#ifndef OPERACIONESPROGRAMA_H
#define OPERACIONESPROGRAMA_H

char** Arreglo_(char* phrase, short int semilla, int letras, int& filas);
char** Codificacion_1(char** Arreglo_bits, short int semilla, int filas, long int limitador);
void Codificacion_2(char** Arreglo_bits, short int semilla, int filas, long int limit);
char** Lectura(char* url, int& letras, short int semilla);
void Escritura(char* endfile, unsigned char* TexCodif, int filas);
void Decodificacion_1(char** TextCodif, short int semilla, int filas, long int limitador);
void Decodificacion_2(char** TextCodif, short int semilla, int filas, long int limitador);
unsigned char* ArregloEsc_(char** TextCodif, short int semilla, int& filas, unsigned char Tarea, long int limitador);
void Esc_Banco(char* TextDecodif, char** Texto, short int semilla, bool Modalidad, char* archivo);
bool IngresoSistem(char** Valor, char* Cedula, char* Clave, char OPT);

#endif // OPERACIONESPROGRAMA_H
