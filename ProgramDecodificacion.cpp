#include <iostream>
#include <cstring>
#include "OperacionesPrograma.h"
#define OPT '0'

using namespace std;
int main(int argc, char *argv[])
{
    cout << "Este Programa sirve para Realizar la Decodificacion de un Archivo de Texto Codificado Entregado por el Usuario y guardarlo en un Archivo de Texto." << endl;
    cout << "Por favor, Ingrese Paso a Paso los Siguientes Datos:\n1. El Nombre del Archivo de Texto a Decodificar.\n2. Semilla con la cual se separaron los grupos de Bits (Entero > 0 y Entero < 9).\n3. Nombre del Archivo en que se guardara el Texto Decodificado.\n4. El metodo de Decodificacion (1 (Decodificar segun Cantidad 1s y 0s), 2 (Decodificar Rotando Bits)).\nNOTA: De no entregarse los datos en este orden, no recibiras el resultado esperado." << endl << endl;

    short int semilla; bool Correr = true; int filas; long int limite;
    char** TextoArchiv_; unsigned char* Textend;

    if (argc == 5){
        for (int casos = 1; casos <= 4; casos++){
            switch (casos) {
            case 2:
                if (strlen(argv[casos]) > 1 || strlen(argv[casos]) == 0 || argv[casos][0] < '1' || argv[casos][0] > '8'){
                    cout << "La Semilla que has ingresado no es Valida." << endl;
                    Correr = false;
                } else{
                    semilla = (argv[casos][0]-48);
                }
                break;
            case 4:
                if (strlen(argv[casos]) > 1 || strlen(argv[casos]) == 0 || (argv[casos][0] != '1' && argv[casos][0] != '2')){
                    cout << "El Metodo de Codificacion que has ingresado no es Valido." << endl;
                    Correr = false;
                }
                break;
            }
        }

        if (!Correr){
            return 1;
        } else{
            TextoArchiv_ = Lectura(argv[1], filas, semilla, limite);
            if (argv[4][0] == '1'){
                Decodificacion_1(TextoArchiv_, semilla, filas, limite);
            } else{
                Decodificacion_2(TextoArchiv_, semilla, filas, limite);
            }
            Textend = ArregloEsc_(TextoArchiv_, semilla, filas, OPT, limite);
            Escritura(argv[3], Textend, filas);
        }
    } else{
        cout << "No entregaste suficientes Argumentos.\n";
        return 1;
    }
    return 0;
}
