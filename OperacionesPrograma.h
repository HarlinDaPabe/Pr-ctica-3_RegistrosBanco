#ifndef OPERACIONESPROGRAMA_H
#define OPERACIONESPROGRAMA_H

char** Arreglo_(char* phrase, short int semilla, int& filas);
char** Codificacion_1(char** Arreglo_bits, short int semilla, int filas, long int limitador);
void Codificacion_2(char** Arreglo_bits, short int semilla, int filas, long int limit);
char** Lectura(char* url, int& letras, short int semilla);
void Escritura(char* endfile, unsigned char* TexCodif, int filas);
void Decodificacion_1(char** TextCodif, short int semilla, int filas, long int limitador);
void Decodificacion_2(char** TextCodif, short int semilla, int filas, long int limitador);
unsigned char* ArregloEsc_(char** TextCodif, short int semilla, int& filas, unsigned char Tarea, long int limitador);
void Esc_Banco(short int semilla, bool Modalidad);
bool IngresoSistem(char** Valor, char* Cedula, char* Clave, char OPT, long int& cont);
bool VerifReg(char* Clave, char* Cedula, char* Saldo);
char* Descuento(char* Saldo, long int Restar, char Accion);
void Escribirnewdates(char* Clave, char* Cedula, char* Saldo, char Acceso, long int pos);
void Transacciones(char Accion, long int resultado, long int Resta);
void Traspass(char* Auxiliar, char* Arreglo);
void LimpiarTerminal();

#endif // OPERACIONESPROGRAMA_H
