#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>//setw
#include <algorithm>//Ordena std::
#include <sstream>//Lee std::string facilitando la manipulación de datos
#include <vector>

using namespace std;

//estructura del libro
struct Libro{
    int numero;
    string titulo;
    string autor;
    string editorial;
    int anio;
    int edicion;
    string genero;
    string isbn;
};

const string ARCHIVO_LIBROS = "C:\\Users\\GIANCARLO\\OneDrive\\Escritorio\\LA_BIBLIOTECA_ERRANTE.txt";
const int ANCHO_COLUMNA = 20;//Para controlar la tabla

void verMenuPrin();
void menuAdmon(); 
void menuVis();
void aggLibro();
void modLibro();
void eliminarLibro();
void verPorAutor();
void verPorGenero();
void verPorEdi();
void verPorAnio();
void verTodos();

vector<Libro> leerLibros();
void guardarLibros(const vector<Libro>& libros);
void mostrarLibrosTabla(const vector<Libro>& libros);
void mostrarCabecera();
Libro leerLineaLibro(const string& linea);
string libroAString(const Libro& libro);


int main() {
    verMenuPrin();
    
	return 0;
}

//Menú Principal
void verMenuPrin() {
    int opcion;
    do {
    	cout<<"\n---------------------------------------------------------------\n";
        cout<<"\n\tBIBLIOTECA\n";
        cout<<"\n1. Administracion de libros\n";
        cout<<"2. Visualizacion de libros\n";
        cout<<"3. Salir\n";
        cout<<"\nSeleccione una opcion: ";
        cin>>opcion;
        cin.ignore();

        switch(opcion) {
            case 1:
				menuAdmon();
				break;
            case 2:
				menuVis();
				break;
            case 3:
				cout<<"Saliendo del sistema...\n";
				break;
            default:
				cout<<"Opcion no valida. Intente nuevamente.\n";
        }
    } while(opcion != 3);
}

//Administración de libros
void menuAdmon() {
    int opcion;
    do {
        cout<<"\n\tADMINISTRACION DE LIBROS\n";
        cout<<"\n1. Agregar libro\n";
        cout<<"2. Modificar libro\n";
        cout<<"3. Eliminar libro\n";
        cout<<"4. Volver al menu principal\n";
        cout<<"\nSeleccione una opcion: ";
        cin>>opcion;
        cin.ignore();//Elimina el carácter de nueva línea del búfer.

        switch(opcion) {
            case 1: 
				aggLibro();
				break;
            case 2:
				modLibro();
				break;
            case 3:
				eliminarLibro();
				break;
            case 4:
				break;
            default:
				cout<<"Opcion incorrecta\n";
        }
    } while(opcion != 4);
}

//Menú para visualisar los libros
void menuVis() {
    int opcion;
    do {
        cout<<"\n\tVISUALIZACION DE LIBROS\n";
        cout<<"\n1. Ver todos los libros\n";
        cout<<"2. Buscar por genero\n";
        cout<<"3. Buscar por editorial\n";
        cout<<"4. Buscar por anio de edicion\n";
        cout<<"5. Buscar por autor\n";
        cout<<"6. Volver al menu principal\n";
        cout<<"\nSeleccione una opcion: ";
        cin>>opcion;
        cin.ignore();

        switch(opcion) {
            case 1:
				verTodos();
				break;
            case 2:
				verPorGenero();
				break;
            case 3:
				verPorEdi();
				break;
            case 4:
				verPorAnio();
				break;
            case 5:
				verPorAutor();
				break;
            case 6:
				break;
            default:
				cout<<"Opcion incorrecta\n";
        }
    } while(opcion != 6);
}
//almacena múltiples libros que se leerán desde el archivo
vector<Libro> leerLibros() {
    vector<Libro> libros;
    ifstream archivo(ARCHIVO_LIBROS);//ifstream lee
    string linea;//almacena cada linea del arcivo leída

    while (getline(archivo, linea)) {
        libros.push_back(leerLineaLibro(linea));//Lo agrega a un vector dinámico
    }
    return libros;
}

//lee las líneas del libro(archivo)
Libro leerLineaLibro(const string& linea) {
    Libro libro;
    stringstream ss(linea);//pasa de linea a un flujo de datos
    string temp;//temporales

    getline(ss, temp, '|'); libro.numero = stoi(temp);
    getline(ss, libro.titulo, '|');
    getline(ss, libro.autor, '|');
    getline(ss, libro.editorial, '|');
    getline(ss, temp, '|'); libro.anio = stoi(temp);
    getline(ss, temp, '|'); libro.edicion = stoi(temp);
    getline(ss, libro.genero, '|');
    getline(ss, libro.isbn);

    return libro;
}

void guardarLibros(const vector<Libro>& libros) {
    ofstream archivo(ARCHIVO_LIBROS);
    for (const auto& libro : libros) {//itera los elementos del vector
        archivo<<libroAString(libro)<<endl;//lo convierte a una cadena con formato
    }
}

//El separador entre las partes del libro
string libroAString(const Libro& libro) {
    return to_string(libro.numero) + "|" + libro.titulo + "|" + libro.autor + "|" +
           libro.editorial + "|" + to_string(libro.anio) + "|" + to_string(libro.edicion) + "|" +
           libro.genero + "|" + libro.isbn;
}

//Muestra la cabecera de una tabla
void mostrarCabecera() {
    cout<<left;
    cout<<setw(5)<<"No."<<"|"//define el ancho de las columnas
        <<setw(ANCHO_COLUMNA)<<"Titulo"<<"|"
        <<setw(ANCHO_COLUMNA)<<"Autor"<<"|"
        <<setw(ANCHO_COLUMNA)<<"Editorial"<<"|"
        <<setw(8)<<"Anio"<<"|"
        <<setw(8)<<"Edicion"<<"|"
        <<setw(ANCHO_COLUMNA)<<"Genero"<< "|"
        <<setw(12) << "ISBN"<<endl;
    cout<<string(150, '-')<<endl;
}

//muestra los libros en formato tabular
void mostrarLibrosTabla(const vector<Libro>& libros) {
    if (libros.empty()) {//si libro está vacío
        cout<<"No se encontraron libros.\n";
        return;
    }

    mostrarCabecera();
    cout<<left;
    for(const auto& libro : libros) {
        cout<<setw(5)<<libro.numero<<"|"
            <<setw(ANCHO_COLUMNA)<<(libro.titulo.length() > ANCHO_COLUMNA ? libro.titulo.substr(0, ANCHO_COLUMNA-3) + "..." : libro.titulo) << "|"
            <<setw(ANCHO_COLUMNA)<<(libro.autor.length() > ANCHO_COLUMNA ? libro.autor.substr(0, ANCHO_COLUMNA-3) + "..." : libro.autor) << "|"
            <<setw(ANCHO_COLUMNA)<<(libro.editorial.length() > ANCHO_COLUMNA ? libro.editorial.substr(0, ANCHO_COLUMNA-3) + "..." : libro.editorial) << "|"
            <<setw(8) << libro.anio<<"|"
            <<setw(8) << libro.edicion<<"|"
            <<setw(ANCHO_COLUMNA)<<(libro.genero.length() > ANCHO_COLUMNA ? libro.genero.substr(0, ANCHO_COLUMNA-3) + "..." : libro.genero) << "|"
            <<setw(12) << libro.isbn<<endl;//"?" punteros
    }
}

//Función de menú para agregar Libros
void aggLibro() {
    Libro nuevo;
    vector<Libro> libros = leerLibros();

    nuevo.numero = libros.empty() ? 1 : libros.back().numero + 1;

    cout<<"\n\tAGREGAR NUEVO LIBRO\n";
    cout<<"\nTitulo: "; getline(cin, nuevo.titulo);
    cout<<"Autor: "; getline(cin, nuevo.autor);
    cout<<"Editorial: "; getline(cin, nuevo.editorial);
    cout<<"Anio de edicion: "; cin >> nuevo.anio; cin.ignore();
    cout<<"Edicion: "; cin >> nuevo.edicion; cin.ignore();
    cout<<"Genero literario: "; getline(cin, nuevo.genero);
    cout<<"ISBN: "; getline(cin, nuevo.isbn);

    libros.push_back(nuevo);
    guardarLibros(libros);

    cout<<"\nLibro agregado exitosamente!\n";
}

//Por si se necesita modificar un libro
void modLibro() {
    vector<Libro> libros = leerLibros();
    int numero;

    cout<<"\n\tMODIFICAR LIBRO\n";
    cout<<"Ingrese el numero del libro a modificar: ";
    cin>>numero;
    cin.ignore();

    bool encontrado = false;
    for (auto& libro : libros) {
        if (libro.numero == numero) {
            encontrado = true;
            
			cout<<"\nModificando libro #"<<libro.numero<<" - "<<libro.titulo<<"\n";
            cout<<"Nuevo titulo ["<<libro.titulo<<"]: ";
            
			getline(cin, libro.titulo);
			if (libro.titulo.empty()) getline(cin, libro.titulo);
            	cout<<"Nuevo autor [" << libro.autor << "]: ";
            
			getline(cin, libro.autor);
			if (libro.autor.empty()) getline(cin, libro.autor);
            	cout<<"Nueva editorial [" << libro.editorial << "]: ";
            
			getline(cin, libro.editorial);
			if (libro.editorial.empty()) getline(cin, libro.editorial);
            	cout<<"Nuevo anio [" << libro.anio << "]: ";
            
			string temp; getline(cin, temp);
			if (!temp.empty()) libro.anio = stoi(temp);
            	cout << "Nueva edicion [" << libro.edicion << "]: ";
            
			getline(cin, temp);
			if(!temp.empty()) libro.edicion = stoi(temp);
            	cout<<"Nuevo genero ["<<libro.genero<<"]: ";
            
			getline(cin, libro.genero);
			if(libro.genero.empty()) getline(cin, libro.genero);
            	cout<<"Nuevo ISBN ["<<libro.isbn<<"]: ";
            
			getline(cin, libro.isbn);
			if(libro.isbn.empty()) getline(cin, libro.isbn);

            break;
        }
    }

    if (encontrado) {
        guardarLibros(libros);
        cout<<"\nLibro modificado!\n";
    }
	else {
        cout<<"\nNo se encontro un libro con ese numero.\n";
    }
}

//Por si se quiere eliminar un libro
void eliminarLibro() {
    vector<Libro> libros = leerLibros();
    int numero;

    cout<<"\n\tELIMINAR LIBRO\n";
    cout<<"\nIngrese el numero del libro a eliminar: ";
    cin>>numero;
    cin.ignore();

    auto it = remove_if(libros.begin(), libros.end(), [numero](const Libro& l) {
        return l.numero == numero;
    });

    if (it != libros.end()) {
        libros.erase(it, libros.end());
        guardarLibros(libros);
        cout<<"\nSe elimino el libro\n";
    }
	else {
        cout<<"\nNo se encontro un libro con ese numero.\n";
    }
}

void verPorAutor() {
    string autor;
    cout<<"\n\tVISUALIZAR POR AUTOR\n";
    cout<<"\nIngrese el nombre del autor: ";
    getline(cin, autor);

    vector<Libro> libros = leerLibros();
    vector<Libro> filtrados;

    copy_if(libros.begin(), libros.end(), back_inserter(filtrados), [autor](const Libro& l) {
        return l.autor.find(autor) != string::npos;
    });

    cout<<"\nResultados para autor: "<<autor<<"\n";
    mostrarLibrosTabla(filtrados);
}

void verPorGenero() {
    string genero;
    cout<<"\n\tVISUALIZAR POR GENERO\n";
    cout<<"\nIngrese el genero literario: ";
    getline(cin, genero);

    vector<Libro> libros = leerLibros();//Carga todos los libros
    vector<Libro> filtrados;//Según lo que haya buscado

    copy_if(libros.begin(), libros.end(), back_inserter(filtrados), [genero](const Libro& l) {
        return l.genero.find(genero) != string::npos;//si no se encontró en filtrados
    });

    cout<<"\nResultados para genero: "<<genero << "\n";
    mostrarLibrosTabla(filtrados);
}

void verPorEdi() {
    string editorial;
    cout<<"\ntVISUALIZAR POR EDITORIAL \n";
    cout<<"\nIngrese la editorial: ";
    getline(cin, editorial);

    vector<Libro> libros = leerLibros();
    vector<Libro> filtrados;

    copy_if(libros.begin(), libros.end(), back_inserter(filtrados), [editorial](const Libro& l) {
        return l.editorial.find(editorial) != string::npos;
    });

    cout<<"\nResultados para editorial: "<<editorial<<"\n";
    mostrarLibrosTabla(filtrados);
}

void verPorAnio() {
    int anio;
    cout<<"\n\tVISUALIZAR POR AÑO \n";
    cout<<"\nIngrese el año de edicion: ";
    cin>>anio;
    cin.ignore();

    vector<Libro> libros = leerLibros();
    vector<Libro> filtrados;

    copy_if(libros.begin(), libros.end(), back_inserter(filtrados), [anio](const Libro& l) {
        return l.anio == anio;
    });

    cout << "\nResultados para anio: " << anio << "\n";
    mostrarLibrosTabla(filtrados);
}

void verTodos() {
    vector<Libro> libros = leerLibros();
    cout << "\n\t\tTODOS LOS LIBROS (" << libros.size() << ")\n";
    mostrarLibrosTabla(libros);
}