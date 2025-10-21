#include <iostream>
#include "OperacionesPrograma.h"

using namespace std;

int main()
{
    char Acceso; short int cont; char* Cedula, Clave;
    char** sudo;
    cout << "Bienvenido a Nuestra Aplicacion de Acceso Bancario, CoinApp!!\nA continuación, Elige una de las Siguientes Opciones para Acceder al Sistema.\n(A) - Para Ingresar como Usuario Administrador.\n(B) - Para Acceder como Cliente.\nOpcion a Elegir: ";
    cin >> Acceso;

    while ((Acceso != 'A' && Acceso != 'B')){
        cout << "Opción no Valida. Intenta Nuevamente: ";
        cin >> Acceso;
    }

    if (Acceso == 'A'){
        cout << "Ingresa la Clave Asignada para los Usuarios Administradores: ";
        cin >> Clave;
    } else{
        cout << "Ingresa tu Numero de Documento: ";
        cin >> Cedula;
        cout << "Ingresa tu Clave: ";
        cin >> Clave;
    }

    bool Ingreso;
    do{
        Ingreso = IngresoSistem(sudo, Cedula, Clave, Acceso);
    }
    return 0;
}
