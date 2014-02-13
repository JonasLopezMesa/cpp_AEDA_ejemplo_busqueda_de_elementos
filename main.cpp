#include "Clases.h"

int main () {

	string h;
	int x;
	//cout << "1" << endl;
	char r[] = "archivo.txt";
	//cout << "" << endl;
	sll lista;
	//cout << "3" << endl;
	lista.read(r);
	cout << "SE HA CARGADO EL ARCHIVO: archivo.txt" << endl;
	cout << "..." << endl;
	cout << "LISTA DE VECTORES: " << endl;
	cout << "______________________________" << endl;

	lista.imprimir();
	cout << endl;
	cout << "Introduzca el elemento que quiera buscar: " << endl;
	cin >> x;
	lista.buscar(x);
	lista.~sll();
	
	cout << endl;
	cout << "¿Desea ordenar las listas?: [si][no] " << endl << endl;
	cin >> h;
	if (h == "si") {
		char n[] = "archivo2.txt";
		sll lista2;
		lista2.read(n);
		cout << "SE HA CARGADO EL ARCHIVO: archivo2.txt" << endl;
		cout << "LISTA DESORDENADA:  " << endl;
		lista2.imprimir();
		lista2.ordenar();
		cout << endl;
		cout << "LISTA ORDENADA:  " << endl;
		lista2.imprimir();
	}
	else {
		cout << "Adios" << endl;
	}
	return 0;
	
}
