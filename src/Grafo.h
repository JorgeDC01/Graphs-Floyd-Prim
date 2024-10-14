// ACTIVIDAD ADA GRAFOS 2020-2021
// AUTORES: JORGE DEL CASTILL GÓMEZ Y PEDRO DEL CASTILLO GÓMEZ

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip> // Libreria para mostrar mostrar por consola con espaciado adeacuado.
using namespace std;

static const int MAX = 20;

class Grafo {

	string Cjtovertices[MAX]; // Conjunto de Vertices del grafo
	float MatAdyacencia[MAX][MAX]; // Matriz de Adyacencia
	float MatCosteMinimo[MAX][MAX]; // Matriz de costes minimos
	int P[MAX][MAX]; // Matriz de existencia de caminos
	int ocupadas;

	float MatExpMin[MAX][MAX]; // Matriz usada tras PRIM
	float MatCosteMinimoPrim[MAX][MAX]; // Matriz usada tras PRIM
	int Pprim[MAX][MAX]; // Matriz de existencia de caminos tras PRIM

public:

	Grafo();

	void CargarDatos(); //Carga todos los datos del fichero y ejectuta los algoritmos.
	int posicionVertice(string nodo); //Calcula la posicion del vector que ocupa un vertice dado su nombre
	void insertarCoste(int fila, int col, float coste); //Inserta un elemento en la matriz
	void MostrarDatos(float matriz[][MAX]); // Muestra la matriz
	void copiarMatrizAdy(); //Copia la matriz de adyacencia
	void Floyd(); //Algoritmo de  Floyd
	void Camino(int vertice1, int vertice2, ofstream &fSal); // Devuelve el camino tras aplicar FLOYD
	void prim();
	void aristaMinima(string &u, string &v, float &x, string visitados[]); //Calcula la arista minima de un conjunto de vertices
	bool pertenece(string visitados[], int v); //Devuelve 'true' si el vertice pertence al vector, 'false' en caso contrario.
	void copiarMatrizExpMin(); // Copia la matriz MatExpMin
	void FloydParaPrim(); // Algoritmo de Floyd enfocado a devolver el camino tras aplicar PRIM
	string Camino2(int vertice1, int vertice2); // Devuelve el camino tras aplicar PRIM

	~Grafo();

};

#endif /* GRAFO_H_ */

