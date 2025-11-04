#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <sstream>
#define SEMILLA 7

using namespace std;

char** Arreglo_(char* phrase, short int semilla, int& filas, long int& limite){
    /*Funcion Implementada para a partir del texto que entra al sistema generar con este un Arreglo con los bits de cada caracter ingresado.
    Entradas ---> Frase en un Arreglo de Char, Semilla con la que se separaran los bits, Catidad de Letras que posee el Arreglo que entra.
    Salida ---> Arreglo Dinámico de Bits.
    */
    ifstream archivo(phrase, ios::binary | ios::ate);
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return NULL;
    }
    size_t tam = archivo.tellg();
    limite = tam*8;
    char Textfile[tam];

    archivo.seekg(0);
    archivo.read(Textfile, tam);
    filas = limite/semilla;
    int i = 0, limit = 0;
    unsigned char mascara = 128; unsigned char valor;
    if (limite%semilla != 0){
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
        for (int j = 1; j < semilla && (i*semilla)+j < limit; j++){
            Arreglo_bits[i][j-1] = (Arreglo_bits[i][j]+48);
        }
        if (i == filas-1){
            Arreglo_bits[i][(limit-1)-(i*semilla)] = ultimo;
        } else{
            Arreglo_bits[i][semilla-1] = ultimo;
        }
    }
}

char** Lectura(char* url, int& letras, short int semilla, long int& limite){
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
    limite = totalbytes;
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
    delete[]TexCodif;
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
            primero = (TextCodif[i][limitador%semilla-1]);
        } else{
            primero = (TextCodif[i][semilla-1]);
        }
        for (int j =  i != filas-1 && semilla%2 != 0? semilla-2:limitador%semilla-2; j >= 0 && (i*semilla)+j < limitador; j--){
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
        Tamagno = limitador/8;
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

void Dec_Banco(){
    /*Genera un Archivo con la Informacion del sudo.txt Decodificada.
    Entradas ---> Void.
    Salidas ---> Void.
    */
    char** Lectur; unsigned char* Lectura_Lineal; int filas; long int limite; char filebeg[] = {'s','u','d','o','.','t','x','t'}, filend[] = {'s','u','d','o','D','.','t','x','t'};
    Lectur = Lectura(filebeg, filas, SEMILLA, limite);
    Decodificacion_1(Lectur, SEMILLA, filas, limite);
    Lectura_Lineal = ArregloEsc_(Lectur, SEMILLA, filas, '0', limite);
    Escritura(filend, Lectura_Lineal, filas);
}

void Cod_Banco(char Acceso){
    /*Genera un Archivo con la Informacion de las Transacciones Codificada.
    Entradas ---> Tipo de Usuario que Ingreso al Sistema.
    Salidas ---> Void.
    */
    char** Lectur; unsigned char* Lectura_Lineal; int filas; long int limite; char filebeg[] = {'T','r','a','n','s','a','c','c','i','o','n','e','s', 'D','.','t','x','t'}, filend[] = {'T','r','a','n','s','a','c','c','i','o','n','e','s','.','t','x','t'};
    char filend1[] = {'s','u','d','o','.','t','x','t'}, filebeg1[] = {'s','u','d','o','D','.','t','x','t'};
    if (Acceso == 'B'){
        Lectur = Arreglo_(filebeg, SEMILLA, filas, limite);
        Codificacion_2(Lectur, SEMILLA, filas, limite);
        Lectura_Lineal = ArregloEsc_(Lectur, SEMILLA, filas, '1', limite);
        Escritura(filend, Lectura_Lineal, filas);
        remove(filebeg);
    } else{
        Lectur = Arreglo_(filebeg1, SEMILLA, filas, limite);
        Lectur = Codificacion_1(Lectur, SEMILLA, filas, limite);
        Lectura_Lineal = ArregloEsc_(Lectur, SEMILLA, filas, '1', limite);
        Escritura(filend1, Lectura_Lineal, filas);
        remove(filebeg1);
    }
}

void Traspass(char* Auxiliar, char* Arreglo, short int tam){
    /*Traspasa los Datos de Entrada a los Arreglos del Sistema.
    Entradas ---> Dato a Ingresar al Sistema, Arreglo del Sistema.
    Salidas ---> Void.
    */
    bool Listo = false; short int cont = 0;
    while(!Listo){
        for (size_t i = 0; i < strlen(Auxiliar); i++){
            if(Auxiliar[i] >= '0' && Auxiliar[i] <= '9'){
                Listo = true;
            } else if (tam == 24 && Auxiliar[i] == '.' && i != 0){
                if (cont < 1){
                    cont++;
                    Listo = true;
                } else{
                    Listo = false;
                }
            } else{
                Listo = false;
                break;
            }
        }
        if (!Listo){
            cout << "Ingresa Nuevamente el Dato: ";
            cin.getline(Auxiliar, 30);
        }
    }

    for (int j = 0; j < tam; j++){
        Arreglo[j] = Auxiliar[j];
    }
    Arreglo[tam] = '\0';
}

bool IngresoSistem(char* Cedula, char* Clave, char* Saldo, char OPT, int& posusuario, int& lineas){
    /*Verifica si los datos que nos Entrega el Usuario existen en el Sistema.
    Entradas ---> Arreglo  Dinámico Lineal, Cedula del Usuario, Clave del Usuario, Variable Bandera.
    Salidas ---> True or False.
    */
    Dec_Banco();
    posusuario = 0;
    ifstream file ("sudoD.txt", ios::in);short int cont = 0; size_t tam;
    char* clave = new char[25]; char* text = new char[100];
    if (OPT == 'A'){
        delete[] text;
        file.seekg(20);
        file.getline(clave, 6, '\n');
        file.close();
        if (strcmp(clave, Clave) == 0){
            delete[] clave;
            return true;
        } else{
            delete[] clave;
            return false;
        }
    } else{
        while (cont < 2){
            file.getline(text, 100);
            cont++;
        }
        tam = file.tellg();
        lineas = cont;
        cont = 0;
        while (file.getline(text, 100)){
            cont++;
        }
        lineas += cont;
        file.clear();
        file.seekg(tam-1);

        bool Encontrado = false; int i = 0;
        while (file.getline(text, 100) && i < cont){
            posusuario++;
            Encontrado = true;
            stringstream seg (text);
            seg.getline(clave, 25, '-');
            if (strcmp(clave, Cedula) != 0){
                Encontrado = false;
            }
            seg.getline(clave, 25, '-');
            if (strcmp(clave, Clave) != 0){
                Encontrado = false;
            }
            seg.getline(clave, 25, '\n');
            if (Encontrado){
                for (size_t i = 0; i < strlen(clave); i++){
                    Saldo[i] = clave[i];
                }
            }
            i++;
        }
        file.close();
        delete[] clave;
        if (Encontrado){
            delete[] text;
            return true;
        } else{
            posusuario = -1;
            delete[] text;
            return false;
        }
    }
    return true;
}

bool VerifReg(char* Clave, char* Cedula){
    /*Verifica si los datos que nos Entrega el Usuario son Válidos, y que no se repitan en el s istema.
    Entradas ---> Arreglo  Dinámico Lineal, Cedula del Usuario, Clave del Usuario, Saldo que posee el Usuario.
    Salidas ---> True or False.
    */
    char text[100]; char frase[25]; short int cont = 0; bool repeat = true;
    ifstream sudo("sudoD.txt", ios::in);
    while (cont < 2){
        sudo.getline(text, 100, '\n');
        cont++;
    }
    while (sudo.getline(text, 100, '\n')){
        stringstream linea(text);
        linea.getline(frase, 25, '-');
        if (strcmp(Cedula, frase) == 0){
            repeat = false;
        }
        linea.getline(frase, 25, '-');
        if (strcmp(Clave, frase) == 0){
            repeat = false;
        }
    }
    sudo.close();
    return repeat;
}

void Transacciones(char Accion, long int resultado, long int Resta){
    /*Modifica el Archivo Transacciones.txt.
    Entradas ---> Accion a Realizar, Resultado de la Deducción Monetaria, Valor a Deducir.
    Salidas ---> Void
    */
    ofstream archivo("TransaccionesD.txt", ios::out);
    if (Accion == 'A' && resultado != 0){
        archivo << "Realizo una Consulta de su Saldo por el Coste de 1000 COP.\n";
    } else if (resultado != 0){
        archivo << "Retiro Saldo por el Concepto Valor de " << Resta-1000 << " COP con un Costo Adicional de 1000 COP.\nSu nuevo Saldo es de " << resultado << "COP\n";
    }
    archivo.close();
}

void Descuento(char* Saldo, long int Restar, char Accion){
    /*Realiza las Operaciones que conllevan las Acciones del usuario Registrado.
    Entradas ---> Saldo que posee el Usuario, Cantidad de Dinero a Descontarle, Accion a Realizar.
    Salidas ---> Saldo nuevo.
    */
    float resultado = 0.0f;
    Restar += 1000;
    if (Restar >= atof(Saldo)){
        if (Accion == 'B' && atof(Saldo) != 0){
            cout << "Se retiro " << atof(Saldo) << "$\nTe has quedado sin Saldo!!\n";
        } else{
            cout << "Tu saldo es 0 $\n";
        }
    } else{
        resultado = atof(Saldo) - Restar;
        if (Accion == 'B'){
            cout << "Se retiro " << float(Restar) << "$\n";
        } else{
            cout << "Tu saldo es : " << float(resultado) << "$\n";
        }
    }
    cout << "Transaccion Realizada con Exito.\n";
    Transacciones(Accion, resultado, Restar);
    snprintf(Saldo, 25, "%.2f", float(resultado));
    Cod_Banco('B');
    remove("TransaccionesD.txt");
}

void Escribirnewdates(char* Clave, char* Cedula, char* Saldo, char Acceso, int pos, int lineas){
    /*Modifica el Archivo sudo.txt Decodificado.
    Entradas ---> Clave del Usuario, Cedula del Usuario, Saldo del Usuario, Tipo de Acceso al Sistema, Posicion donde se Sobreescribirá el Saldo.
    Salidas ---> Void
    */
    char* Datos[3] = {Cedula, Clave, Saldo};
    fstream archivo;
    if (Acceso == 'A'){
        archivo.open("sudoD.txt", ios::out | ios::app);
        for (int i = 0; i < 3; i++){
            for (size_t j = 0; j < strlen(Datos[i]); j++){
                archivo << Datos[i][j];
            }
            if (i != 2){
                archivo << "-";
            } else{
                archivo << "\n";
            }
        }
    } else{
        archivo.open("sudoD.txt", ios::in);
        int cont = 0; char text_[100];
        char* texto[lineas];
        while (cont < lineas){
            char* text = new char[100];
            archivo.getline(text, 100, '\n');
            texto[cont] = text;
            cont++;
        }
        archivo.close();
        remove("sudoD.txt");
        archivo.open("sudoD.txt", ios::out);
        for (int i = 0; i < lineas; i++){
            stringstream frase(texto[i]);
            frase.getline(text_, 25, '-');
            if (strcmp(text_, Cedula) == 0){
                archivo << Cedula << '-' << Clave << '-' << Saldo << '\n';
            } else {
                archivo << texto[i] << '\n';
            }
        }
        for (int i = 0; i < lineas; i++){
            delete[] texto[i];
        }
    }
    archivo.close();
    Cod_Banco('A');
    remove("sudoD.txt");
}

void LimpiarTerminal() {
    /*Limpia la Limpia la Terminal.
    Entradas ---> Void.
    Salidas ---> Void.
    */
    system("cls");
}
