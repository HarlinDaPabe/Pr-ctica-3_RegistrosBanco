#include <iostream>
#include "OperacionesPrograma.h"

using namespace std;

int main()
{
    char Acceso, Accion; char Cedula[11]; char Clave[7]; char Saldo[25]; char Auxiliar[30];
    bool Ingreso; int posB, lineas; bool bandera = false;
    while(!bandera){
        short int cont = 0;
        cout << "Bienvenid@ a Nuestra Aplicacion de Acceso Bancario, CoinApp!!\nA continuacion, Elige una de las Siguientes Opciones para Acceder al Sistema.\n(A) - Para Ingresar como Usuario Administrador.\n(B) - Para Acceder como Cliente.\n(y) - Cerrar Programa.\nOpcion a Elegir: ";
        cin >> Acceso;

        while ((Acceso != 'A' && Acceso != 'B' && Acceso != 'y')){
            cout << "Opcion no Valida. Intenta Nuevamente: ";
            cin >> Acceso;
        }
        LimpiarTerminal();
        if (Acceso == 'y'){
            bandera = true;
        } else{
            if (Acceso == 'A'){
                cout << "Ingresa la Clave Asignada para los Usuarios Administradores: ";
                cin.ignore();
                cin.getline(Auxiliar,30);
                Traspass(Auxiliar, Clave, 6);
            } else{
                cout << "Ingresa tu Numero de Cedula: ";
                cin.ignore();
                cin.getline(Auxiliar,30);
                Traspass(Auxiliar, Cedula, 10);
                cout << "Ingresa tu Clave: ";
                cin.getline(Auxiliar,30);
                Traspass(Auxiliar, Clave, 6);
            }

            do{
                Ingreso = IngresoSistem(Cedula, Clave, Saldo, Acceso, posB, lineas);
                cont++;
                if (!Ingreso){
                    if (Acceso == 'A'){
                        cout << "La Clave Ingresada es Incorrecta.\nIntenta Nuevamente: ";
                        cin.getline(Auxiliar,30);
                        Traspass(Auxiliar, Clave, 6);
                    } else{
                        cout << "Los Datos Ingresados no se pudieron encontrar en el Sistema.\nIntenta Nuevamente.\n";
                        cout << "Ingresa tu Numero de Cedula: ";
                        cin.getline(Auxiliar,30);
                        Traspass(Auxiliar, Cedula, 10);
                        cout << "Ingresa tu Clave: ";
                        cin.getline(Auxiliar,30);
                        Traspass(Auxiliar, Clave, 6);
                        cout << Clave;
                    }
                    if (cont > 3){
                        return 1;
                    }
                }
            } while (!Ingreso);
        }

        LimpiarTerminal();
        while (Ingreso){
            cont = 0;
            if (Acceso == 'B'){
                char newSaldo[25];
                cout << "Que Accion deseas realizar?\n(A) - Consultar tu Saldo.\n(B) - Retirar Dinero.\nNOTA: Ten en cuenta que cada transaccion a efectuar conlleva un costo de 1000 COP.\nEleccion: ";
                cin >> Accion;
                while ((Accion != 'A' && Accion != 'B')){
                    cont++;
                    if (cont == 5){
                        cout << "ERROR!! Cantidad de Intentos Agotados. Vuelve Pronto:)\n";
                        return 1;
                    }
                    cout << "Opción no Valida. Intenta Nuevamente: ";
                    cin >> Accion;
                }
                if (Accion == 'B'){
                    cout << "Ingresa la Cantidad de Dinero que deseas Retirar: ";
                    cin.ignore();
                    cin.getline(Auxiliar, 30);
                    Traspass(Auxiliar, newSaldo, 24);
                }
                Descuento(Saldo, atof(newSaldo), Accion);
            } else{
                cout << "Ingresa en Orden los Siguientes Datos:\n1. Cedula.\n2. Clave\n3. Saldo (No Mayor a 9.999.999.998.999$)\n";
                do{
                    cout << "Cedula: ";
                    cin.getline(Auxiliar,30);
                    Traspass(Auxiliar, Cedula, 10);
                    cout << "Clave: ";
                    cin.getline(Auxiliar,30);
                    Traspass(Auxiliar, Clave, 6);
                    cout << "Saldo: ";
                    cin.getline(Auxiliar,30);
                    Traspass(Auxiliar, Saldo, 24);
                    Ingreso = VerifReg(Clave, Cedula);
                    if (!Ingreso){
                        cout << "Has Ingresado Informacion no Valida. Vuelve a Intentarlo.\n";
                    }
                } while (!Ingreso);
            }
            Escribirnewdates(Clave, Cedula, Saldo, Acceso, posB, lineas);
            cout << "¿Deseas cerrar la sesion? (y/n)\nEleccion: ";
            cin >> Accion;
            while ((Accion != 'y' && Accion != 'n')){
                cout << "Opcion no Valida. Intenta Nuevamente: ";
                cin >> Accion;
            }
            if (Accion == 'y'){
                Ingreso = false;
            }
            LimpiarTerminal();
        }
        LimpiarTerminal();
    }
    return 0;
}
