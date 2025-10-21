#include <iostream>
#include "OperacionesPrograma.h"

using namespace std;

int main()
{
    char Acceso, Accion; short int cont = 0; char* Cedula = new char[13]; char* Clave = new char[13]; char* Saldo = new char[13]; char* Auxiliar = new char[15];
    char** sudo = NULL; long int posB; char bandera = '1';
    while(bandera != '0'){
        cout << "Bienvenid@ a Nuestra Aplicacion de Acceso Bancario, CoinApp!!\nA continuación, Elige una de las Siguientes Opciones para Acceder al Sistema.\n(A) - Para Ingresar como Usuario Administrador.\n(B) - Para Acceder como Cliente.\n(y) - Cerrar Programa.\nOpcion a Elegir: ";
        cin >> Acceso;

        while ((Acceso != 'A' && Acceso != 'B' && Acceso != 'y')){
            cout << "Opción no Valida. Intenta Nuevamente: ";
            cin >> Acceso;
        }
        LimpiarTerminal();
        if (Acceso == 'A'){
            cout << "Ingresa la Clave Asignada para los Usuarios Administradores: ";
            cin.ignore();
            cin.getline(Auxiliar,12);
            Traspass(Auxiliar, Clave);
        } else if (Acceso == 'y'){
            bandera = '0';
            delete[]Cedula;
            delete[]Clave;
            delete[]Saldo;
            delete[]Auxiliar;
            return 1;
        } else{
            cout << "Ingresa tu Numero de Documento: ";
            cin.ignore();
            cin.getline(Auxiliar,12);
            Traspass(Auxiliar, Cedula);
            cout << "Ingresa tu Clave: ";
            cin.getline(Auxiliar,12);
            Traspass(Auxiliar, Clave);
        }
        LimpiarTerminal();
        bool Ingreso;

        do{
            Ingreso = IngresoSistem(sudo, Cedula, Clave, Acceso, posB);
            cont++;
            if (cont == 3){
                cout << "Acceso Denegado al Sistema. Gracias por adquirir nuestros Servicios:)\n";
                return 1;
            }
        } while (!Ingreso);

        while (bandera != 'y'){
            cont = 0;
            if (Acceso == 'B'){
                long int newSaldo;
                cout << "¿Que Accion deseas realizar?\n(A) - Consultar tu Saldo.\n(B) - Retirar Dinero.\nEleccion: ";
                cin >> Accion;
                while ((Accion != 'A' && Accion != 'B')){
                    cont++;
                    if (cont == 5){
                        cout << "ERROR!! Cantidad de Intentos Agotados. Vuelve Pronto:)\n";
                        return 1;
                    }
                    cout << "Opción no Valida. Intenta Nuevamente: ";
                    cin >> Acceso;
                }
                if (Accion == 'A'){
                    newSaldo = 1000;
                } else{
                    cin >> newSaldo;
                    newSaldo += 1000;
                }
                Saldo = Descuento(Saldo, newSaldo, Accion);
            } else{
                cout << "Ingresa en Orden los Siguientes Datos:\n1. Cedula.\n2. Clave\n3. Saldo (No Mayor a 9.999.999.998.999$)\n";

                do{
                    cout << "Cedula: ";
                    cin.ignore();
                    cin.getline(Auxiliar,12);
                    Traspass(Auxiliar, Cedula);
                    cout << "Clave: ";
                    cin.getline(Auxiliar,12);
                    Traspass(Auxiliar, Clave);
                    cout << "Saldo: ";
                    cin.getline(Auxiliar,12);
                    Traspass(Auxiliar, Saldo);
                    Ingreso = VerifReg(Clave, Cedula, Saldo);
                    if (!Ingreso){
                        cout << "Has Ingresado Caracteres no Numericos. Vuelve a Intentarlo.\n";
                    }
                } while (!Ingreso);

            }
            Escribirnewdates(Clave, Cedula, Saldo, Acceso, posB);
            cout << "¿Deseas cerrar la sesion? (y/n)\nEleccion: ";
            cin >> Acceso;
            while ((Acceso != 'y' && Acceso != 'n')){
                cout << "Opción no Valida. Intenta Nuevamente: ";
                cin >> Acceso;
            }
            LimpiarTerminal();
        }
    }
    return 0;
}
