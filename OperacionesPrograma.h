#ifndef OPERACIONESPROGRAMA_H
#define OPERACIONESPROGRAMA_H

char** Arreglo_(char* phrase, short int semilla, int& filas, long int& limite);
char** Codificacion_1(char** Arreglo_bits, short int semilla, int filas, long int limitador);
void Codificacion_2(char** Arreglo_bits, short int semilla, int filas, long int limit);
char** Lectura(char* url, int& letras, short int semilla, long int& limite);
void Escritura(char* endfile, unsigned char* TexCodif, int filas);
void Decodificacion_1(char** TextCodif, short int semilla, int filas, long int limitador);
void Decodificacion_2(char** TextCodif, short int semilla, int filas, long int limitador);
unsigned char* ArregloEsc_(char** TextCodif, short int semilla, int& filas, unsigned char Tarea, long int limitador);
bool IngresoSistem(char* Cedula, char* Clave, char* Saldo, char OPT, int& posusuario, int& lineas);
bool VerifReg(char* Clave, char* Cedula);
void Descuento(char* Saldo, long int Restar, char Accion);
void Escribirnewdates(char* Clave, char* Cedula, char* Saldo, char Acceso, int pos, int lineas);
void Transacciones(char Accion, long int resultado, long int Resta);
void Traspass(char* Auxiliar, char* Arreglo, short int tam);
void LimpiarTerminal();
void Dec_Banco();
void Cod_Banco(char Acceso);

#endif // OPERACIONESPROGRAMA_H
