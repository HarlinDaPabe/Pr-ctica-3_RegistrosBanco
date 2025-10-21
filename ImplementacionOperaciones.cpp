#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

char** Arreglo_(char* phrase, short int semilla, int& filas){
    /*Funcion Implementada para a partir del texto que entra al sistema generar con este un Arreglo con los bits de cada caracter ingresado.
    Entradas ---> Frase en un Arreglo de Char, Semilla con la que se separaran los bits, Catidad de Letras que posee el Arreglo que entra.
    Salida ---> Arreglo Dinámico de Bits.
    */
    ifstream archivo(phrase, ios::binary | ios::ate);
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return NULL;
    }

    char* Textfile; long int tam;
    tam = archivo.tellg();
    archivo.seekg(0);
    archivo.read(Textfile, tam);

    filas = (tam*8)/semilla;
    int i = 0, limit = 0;
    unsigned char mascara = 128; unsigned char valor;
    if ((tam*8)%semilla != 0){
        filas++;
    }
    char** Arreglo_bits = new char*[filas];
    for (int fila = 0; fila < filas; fila++){
        Arreglo_bits[fila] = new char[semilla];
    }
    for (int k = 0; k < filas; k++){
        for (int j = 0; j < semilla; j++){
            valor = (Textfile[i]&mascara) >> (7-limit);
            Arreglo_bits[k][j] = valor;
            limit++;
            mascara >>= 1;
            if (mascara == 0){
                limit = 0;
                mascara = 128;
                i++;
                if (i == tam){
                    break;
                }
            }
        }
    }
    return Arreglo_bits;
}

char** Codificacion_1(char** Arreglo_bits, short int semilla, int filas, long int limitador){
    /*Realiza la Codificacion de bits según el patrón de 0s y 1s que aparezca en determinada fila.
    Entradas ---> Arreglo Unsigned Char de 0s y 1s, Semilla Cantidad de valores en cada fila.
    Salida ---> Arreglo Dinámico Codificado.
    */
    short int Cont0, Cont1, limit;
    char** ptr = new char*[filas];
    for (int fila = 0; fila < filas; fila++){
        ptr[fila] = new char[semilla];
    }
    for (int i = 0; i < filas; i++){
        Cont0 = 0, Cont1 = 0, limit = 2;
        for (int j = 0; j < semilla && (i*semilla)+j <= limitador; j++){
            if (Arreglo_bits[i][j] == 0){
                Cont0++;
            } else{
                Cont1++;
            }
            if (i == 0){
                ptr[i][j] = (!Arreglo_bits[i][j])+48;
            }
        }
        if (i+1 < filas){
            for (int k = 0; k < semilla && (i*semilla)+k <= limitador; k++){
                if (Cont1 > Cont0){
                    if (k == limit){
                        ptr[i+1][k] = (!Arreglo_bits[i+1][k])+48;
                        limit += 3;
                    } else{
                        ptr[i+1][k] = (Arreglo_bits[i+1][k])+48;
                    }
                } else if (Cont0 > Cont1){
                    if (k%2 != 0){
                        ptr[i+1][k] = (!Arreglo_bits[i+1][k])+48;
                    } else{
                        ptr[i+1][k] = (Arreglo_bits[i+1][k])+48;
                    }
                } else {
                    ptr[i+1][k] = (!Arreglo_bits[i+1][k])+48;
                }
            }
        }
    }

    for (int fila = 0; fila < filas; fila++){
        delete[] Arreglo_bits[fila];
    }
    delete[]Arreglo_bits;
    Arreglo_bits = NULL;
    return ptr;
}

void Codificacion_2(char** Arreglo_bits, short int semilla, int filas, long int limit){
    /*Realiza la Codificacion de bits rotando los valores del Arreglo una posición a la Izquierda.
    Entradas ---> Arreglo Unsigned Char de 0s y 1s, Semilla Cantidad de valores en cada fila, Cantidad de Filas que posee el Arreglon Entrante.
    Salida ---> Void.
    */
    unsigned char ultimo;
    for (int i = 0; i < filas; i++){
        ultimo = (Arreglo_bits[i][0]+48);
        for (int j = 1; j < semilla && (i*semilla)+j <= limit; j++){
            Arreglo_bits[i][j-1] = (Arreglo_bits[i][j]+48);
        }
        if (i == filas-1){
            Arreglo_bits[i][limit-(i*semilla)] = ultimo;
        } else{
            Arreglo_bits[i][semilla-1] = ultimo;
        }
    }
}

char** Lectura(char* url, int& letras, short int semilla){
    /*Se encarga de realizar la lectura del Archivo de texto.
    Entradas ---> Arreglo de Unsigned char con el nombre del Archivo.
    Salida ---> Arreglo Unsigned Char con el Contenido del Archivo.
    */
    char** prt; int totalbytes;
    ifstream archivo(url, ios::binary | ios::ate);
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return NULL;
    }

    totalbytes = archivo.tellg();
    letras = totalbytes/semilla;
    if (totalbytes%semilla != 0){
        letras++;
    }

    prt = new char*[letras];
    for (int j = 0; j < letras; j++){
        prt[j] = new char[semilla];
    }

    archivo.seekg(0);
    for (int k = 0; k < letras; k++){
        archivo.read(prt[k], semilla);
    }
    archivo.close();

    for (int i = 0; i<letras; i++){
        for (int j = 0; j < semilla; j++){
            prt[i][j] = ((int)prt[i][j])-48;
        }
    }
    return prt;
}

void Escritura(char* endfile, unsigned char* TexCodif, int filas){
    /*Se encarga de realizar la escritura de un Archivo de texto, a partir del texto que poseemos Codificado o Decodificado.
    Entradas ---> Arreglo de Unsigned char con el nombre del Archivo, Cantidad de Filas del Arreglo.
    Salida ---> Void.
    */
    ofstream archivo(endfile, ios::out | ios::app);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo para escritura.\n";
    } else {
        for (int i = 0; i < filas; i++){
            archivo << TexCodif[i];
        }
    }
    archivo.close();
}

void Decodificacion_1(char** TextCodif, short int semilla, int filas, long int limitador){
    /*Realiza la Decodificación del Arreglo Codificado de 1s y 0s, aplicando operaciones inversas a la Codificación.
    Entradas ---> Arreglo Unsigned Char Codificado, Semmilla con la que se separaron los bits, Cantidad de Filas del Arreglo Ingresado.
    Salidas ---> Void.
    */
    short int Cont0, Cont1, limit;
    for (int i = 0; i < filas; i++){
        limit = 2, Cont0 = 0, Cont1 = 0;
        for (int j = 0; j < semilla && (i*semilla)+j <= limitador; j++){
            if (i == 0){
                TextCodif[i][j] = !TextCodif[i][j];
            }
            if (TextCodif[i][j] == 0){
                Cont0++;
            } else {
                Cont1++;
            }
        }

        if (i+1 < filas){
            for (int k = 0; k < semilla && (i*semilla)+k <= limitador; k++){
                if (Cont1 > Cont0){
                    if (k == limit){
                        TextCodif[i+1][k] = !TextCodif[i+1][k];
                        limit += 3;
                    }
                } else if (Cont0 > Cont1){
                    if (k%2 != 0){
                        TextCodif[i+1][k] = !TextCodif[i+1][k];
                    }
                } else {
                    TextCodif[i+1][k] = !TextCodif[i+1][k];
                }
            }
        }
    }
}

void Decodificacion_2(char** TextCodif, short int semilla, int filas, long int limitador){
    /*Realiza la Decodificacion de bits rotando los valores del Arreglo una posición a la Derecha, inversamente a como se elaboró la Codificación.
    Entradas ---> Arreglo Unsigned Char de 0s y 1s, Semilla Cantidad de valores en cada fila, Cantidad de Filas que posee el Arreglo Entrante.
    Salida ---> Void.
    */
    unsigned char primero;
    for (int i = 0; i < filas; i++){
        if (i == filas-1){
            primero = (TextCodif[i][limitador%semilla]);
        } else{
            primero = (TextCodif[i][semilla-1]);
        }
        for (int j = semilla-2; j >= 0 && (i*semilla)+j < limitador; j--){
            TextCodif[i][j+1] = (TextCodif[i][j]);
        }
        TextCodif[i][0] = primero;
    }
}

unsigned char* ArregloEsc_(char** TextCodif, short int semilla, int& filas, unsigned char Tarea, long int limitador){
    /*Transforma el Arreglo Bidimensional Dinámico a uno Lineal para luego realizar la Escritura del Archivo.
    Entradas ---> Arreglo Dinámico Bidimensional, Semilla con la que se separo los grupos de bits, Cantidad de Filas del Arreglo Bidimensional Entrante.
    Salidas ---> Areglo Lineal Dinámico.
    */
    short int limit = 7; int Tamagno;
    unsigned char* ptr; unsigned char valor, result = 0;
    if (Tarea == '0'){
        Tamagno = (filas*semilla)/8;
        ptr = new unsigned char[Tamagno];
    } else {
        Tamagno = limitador;
        ptr = new unsigned char[Tamagno];
    }

    long int cont = 0;
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < semilla && (i*semilla)+j <= limitador; j++){
            valor = TextCodif[i][j];
            if (limit > 0 && Tarea == '0'){
                result = (valor << limit) | result;
                limit--;
            } else{
                if (Tarea == '0'){
                    limit = 7;
                }
                result = result|valor;
                ptr[cont] = result;
                cont++;
                result = 0;
            }
        }
    }

    for (int fila = 0; fila < filas; fila++){
        delete[]TextCodif[fila];
    }
    delete[]TextCodif;
    TextCodif = NULL;
    filas = Tamagno;
    return ptr;
}

void Esc_Banco(short int semilla, bool Modalidad){
    /*Genera los Archivos de Salida de la Ejecución del Programa Bancario.
    Entradas ---> Arreglo  Dinámico Lineal para el Texto Decodificado, Arreglo Dinámico Bidimensional para el Texto Codificado, Semilla con que se separaron los Grupos de Bits, Modalidad (Codificar o Decodificar).
    Salidas ---> Archivos del Sitema Bancario.
    */
    int filas; long int limitador;;
    unsigned char* Textoend; char** TextCodif; char** TextDecodif;
    if (!Modalidad){
        char archivo[] = {"sudo.txt"};
        char archivoend[] = {"sudoD.txt"};
        TextDecodif = Lectura(archivo, filas, semilla);
        limitador = (filas*semilla)-((filas*semilla)%8+1);
        Decodificacion_1(TextDecodif, semilla, filas, limitador);
        Textoend = ArregloEsc_(TextDecodif, semilla, filas, 0, limitador);
        Escritura(archivoend, Textoend, limitador);
    } else{
        if (semilla != 6){
            char archivo[] = {"Transacciones.txt"};
            char archivoend[] = {"TransaccionesD.txt"};
            TextDecodif = Arreglo_(archivoend, semilla, filas);
            limitador = (filas*semilla)-((filas*semilla)%8+1);
            Codificacion_2(TextDecodif, semilla, filas, limitador);
            Textoend = ArregloEsc_(TextDecodif, semilla, filas, 1, limitador);
            Escritura(archivo, Textoend, limitador);
        } else{
            char archivo[] = {"sudo.txt"};
            char archivoend[] = {"sudoD.txt"};
            TextDecodif = Arreglo_(archivoend, semilla, filas);
            limitador = (filas*semilla)-((filas*semilla)%8+1);
            TextCodif = Codificacion_1(TextDecodif, semilla, filas, limitador);
            Textoend = ArregloEsc_(TextCodif, semilla, filas, 1, limitador);
            Escritura(archivo, Textoend, limitador);
        }
    }
    delete[]Textoend;
}

bool IngresoSistem(char** Valor, char* Cedula, char* Clave, char OPT, long int& tam){
    /*Verifica si los datos que nos Entrega el Usuario existen en el Sistema.
    Entradas ---> Arreglo  Dinámico Lineal, Cedula del Usuario, Clave del Usuario, Variable Bandera.
    Salidas ---> Areglo Lineal Dinámico con la Información del Sistema.
    */
    bool True= false;
    Esc_Banco(6, 0);

    Valor = new char*[3];
    for (int i = 0; i < 3; i++){
        Valor[i] = new char[13];
    }

    ifstream file("sudoD.txt", ios::binary);

    if (OPT == 'B'){
        char letra; int c; int i = 0, cont = 0;
        file.seekg(1);
        while ((c = file.get()) != EOF){
            letra = static_cast<char>(c);
            if (letra == Cedula[i]){
                Valor[0][i] = letra;
                cont++;
                i++;
            } else {
                cont = 0;
                i = 0;
            }
            tam++;
            if (cont == strlen(Cedula)){
                True = true;
                break;
            }
        }
        file.seekg(tam+1);
    } else{
        file.seekg(1);
    }
    file.read(Valor[1], strlen(Clave));
    if (strcmp(Valor[1], Clave) != 0){
        True = false;
    }

    if (True){
        file.getline(Valor[2], 13, '\n');
        return true;
    } else{
        for (int i = 0; i < 3; i++){
            delete[]Valor[i];
        }
        delete[]Valor;
        Valor = NULL;
    }
    return false;
}

bool VerifReg(char* Clave, char* Cedula, char* Saldo){
    /*Verifica si los datos que nos Entrega el Usuario son Válidos.
    Entradas ---> Arreglo  Dinámico Lineal, Cedula del Usuario, Clave del Usuario, Saldo que posee el Usuario.
    Salidas ---> True or False.
    */
    char* Datos[3] ={Clave, Cedula, Saldo};
    for (int i = 0; i < 3; i++){
        for (size_t j = 0; j < strlen(Datos[i]); j++){
            if (Datos[i][j] < '0' || Datos[i][j] < '9'){
                return false;
            }
        }
    }
    return true;
}

void Transacciones(char Accion, long int resultado, long int Resta){
    /*Modifica el Archivo Transacciones.txt.
    Entradas ---> Accion a Realizar, Resultado de la Deducción Monetaria, Valor a Deducir.
    Salidas ---> Void
    */
    ofstream archivo("TransaccionesD.txt", ios::out);
    if (Accion == 'A'){
        archivo << "Realizo una Consulta de su Saldo por el Coste de 1000 COP.\n";
    } else if (resultado != 0){
        archivo << "Retiro Saldo por el Concepto Valor de " << Resta << " COP con un Costo Adicional de 1000 COP.\n" << "Su nuevo Saldo es de " << resultado << "COP\n";
    }
    archivo.close();
    Esc_Banco(5, 1);
    remove("TransaccionesD.txt");
}

char* Descuento(char* Saldo, long int Restar, char Accion){
    /*Realiza las Operaciones que conllevan las Acciones del usuario Registrado.
    Entradas ---> Saldo que posee el Usuario, Cantidad de Dinero a Descontarle, Accion a Realizar.
    Salidas ---> Saldo nuevo.
    */
    long int suma = 0, resultado = 0;
    for (size_t i = 0; i < strlen(Saldo); i++){
        suma = 10*suma+(Saldo[i]-48);
    }
    if (Restar <= 100000000000){
        if (Accion == 'A'){
            cout << "Tu Saldo: " << suma;
        }
        if (Restar > suma){
            if (Accion == 'B'){
                cout << "Se retiro " << suma << "$\nTe has quedado sin Saldo!!\n";
            } else{
                cout << "Tu saldo es 0 $\n";
            }
        } else{
            resultado = suma-Restar;
            if (Accion == 'B'){
                cout << "Se retiro " << Restar<< "$\nTe has quedado sin Saldo!!\n";
            } else{
                cout << "Tu saldo es : " << resultado << "$\n";
            }
        }
        cout << "Transaccion Realizada con Exito.\n";
        Transacciones(Accion, resultado, Restar);
    } else{
        cout << "Upss!, El Valor a Operar no es Valido.\n";
    }
    snprintf(Saldo, 13, "%ld", resultado);
    return Saldo;
}

void Escribirnewdates(char* Clave, char* Cedula, char* Saldo, char Acceso, long int pos){
    /*Modifica el Archivo Sudo.txt Decodificado.
    Entradas ---> Clave del Usuario, Cedula del Usuario, Saldo del Usuario, Tipo de Acceso al Sistema, Posicion donde se Sobreescribirá el Saldo.
    Salidas ---> Void
    */
    char* Datos[3] = {Cedula, Clave, Saldo};
    ofstream archivo;
    if (Acceso == 'A'){
        archivo.open("sudoD.txt", ios::in | ios::out);
        archivo.seekp(pos);
        for (size_t i = 0; i < strlen(Saldo); i++){
            archivo << Datos[2][i];
        }
        archivo << "\n";
    } else{
        archivo.open("sudoD.txt", ios::out | ios::app);
        for (int i = 0; i < 3; i++){
            for (size_t j = 0; j < strlen(Datos[i]); j++){
                archivo << Datos[i][j];
            }
            if (i == 2){
                archivo << "\n";
            } else{
                archivo << ",";
            }
        }
    }
    archivo.close();
    Esc_Banco(6, 1);
    remove("sudoD.txt");
}

void Traspass(char* Auxiliar, char* Arreglo){
    /*Traspasa los Datos de Entrada a los Arreglos Estaticos del Sistema.
    Entradas ---> Dato a Ingresar al Sistema, Arreglo del Sistema.
    Salidas ---> Void.
    */
    bool Listo = false;
    while(!Listo){
        if (strlen(Auxiliar) > 12){
            cout << "Ingresaste Informacion no Valida\n";
        } else{
            Listo = true;
        }
        for (size_t i = 0; i < strlen(Auxiliar); i++){
            if(Auxiliar[i] < '0' || Auxiliar[i] > '9'){
                Listo = false;
            }
        }
        if (!Listo){
            cout << "Ingresa Nuevamente el Dato: ";
            cin >> Auxiliar;
        }
    }

    for (size_t j = 0; j < strlen(Auxiliar); j++){
        Arreglo[j] = Auxiliar[j];
    }
    Arreglo[13] = '\0';
}

void LimpiarTerminal() {
    /*Limpia la Limpia la Terminal.
    Entradas ---> Void.
    Salidas ---> Void.
    */
    system("clear");
}
