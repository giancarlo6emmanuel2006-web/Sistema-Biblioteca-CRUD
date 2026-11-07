# Sistema de Gestión de Biblioteca (CRUD)

Programa de consola en C++ para administrar el catálogo de una biblioteca. Los libros se guardan en un archivo de texto (50 libros de ejemplo incluidos).

## Funciones

- Menú principal con modo administrador y modo visitante
- Agregar, modificar y eliminar libros
- Consultar por autor, género, edición o año
- Ver el catálogo completo en formato de tabla
- Persistencia de datos en archivo de texto

## Cómo compilar y ejecutar

Coloca `biblioteca.cpp` y `LA_BIBLIOTECA_ERRANTE.txt` en la misma carpeta.

    g++ biblioteca.cpp -o biblioteca
    ./biblioteca

En Windows:

    g++ biblioteca.cpp -o biblioteca.exe
    biblioteca.exe

## Tecnologías

C++, manejo de archivos (fstream), vectores y estructuras.

## Autores

- José Luis Turcios Santos
- Giancarlo Emmanuel Ortiz Marín
- Hilda Cristina Santizo Contreras

Programación I - Universidad Mariano Gálvez de Guatemala, Sede Santa Lucía Cotzumalguapa (2025)
