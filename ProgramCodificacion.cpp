#include <iostream>
#include <cstring>
#include "OperacionesPrograma.h"
#define OPT '1'

using namespace std;
int main(int argc, char *argv[])
{
    cout << "Este Programa sirve para Realizar la Codificacion de un Texto Entregado por el Usuario y guardarlo en un Archivo de Texto." << endl;
    cout << "Por favor, Ingrese Paso a Paso los Siguientes Datos:\n1. El Texto a Codificar.\n2. Semilla con la cual se separaran los grupos de Bits (Entero > 0 y Entero < 9).\n3. Nombre del Archivo en que se guardará el Texto Codificado.\n4. El metodo de Codificacion (1 (Codificar según Cantidad 1s y 0s), 2 (Codificar Rotando Bits)).\nNOTA: De no entregarse los datos en este orden, no recibirás el resultado esperado." << endl << endl;

    short int semilla; bool Correr = true; int filas; long int limite;
    char** Texto; unsigned char* TextoEscrib;

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
            Texto = Arreglo_(argv[1], semilla, filas);
            cout << filas << " ";
            limite = (filas*semilla) - ((filas*semilla)%8 + 1);
            if (argv[4][0] == '1'){
                Texto = Codificacion_1(Texto, semilla, filas, limite);
            } else{
                Codificacion_2(Texto, semilla, filas, limite);
            }
            cout << filas << " ";
            TextoEscrib = ArregloEsc_(Texto, semilla, filas, OPT, limite);
            cout << filas;
            Escritura(argv[3], TextoEscrib, filas);
        }
    } else{
        cout << "No entregaste suficientes Argumentos.\n";
        return 1;
    }

    return 0;
}
