// ACTIVIDAD ADA GRAFOS 2020-2021
// AUTORES: JORGE DEL CASTILL GÓMEZ Y PEDRO DEL CASTILLO GÓMEZ

#include "Grafo.h"

/* Constructor
 * Post : {Crea/inicializa la instancia de la clase}
 * Return: Retorna Objeto Grafo
 */
Grafo::Grafo() {

	ocupadas = 0;

	//Inicialización del conjunto de vértices y matrices.
	for (int i = 0; i < MAX; i++) {
		this->Cjtovertices[i] = "";
		for (int j = 0; j < MAX; j++) {
			this->P[i][j] = -1;
			this->Pprim[i][j] = -1;
			if (i != j) {
				this->MatAdyacencia[i][j] = 9999;
				this->MatExpMin[i][j] = 9999;
			} else {
				this->MatAdyacencia[i][j] = 0;
				this->MatExpMin[i][j] = 0;
			}
		}
	}

	CargarDatos();

	cout << "MATRIZ DE ADYACENCIA" << endl;
	MostrarDatos(this->MatAdyacencia);

}

/* Carga todos los datos del fichero de entrada y ejecuta los algoritmos
 * Return: Crea un log de salida con todos los datos obtenidos tras la ejecucion de los algoritmos
 */
void Grafo::CargarDatos() {
	string num, nodo1, nodo2, coste;

	//Declaración y apertura del flujo de entrada al fichero
	ifstream fEnt;
	fEnt.open("conexiones.in");
	bool fin = false;
	ofstream fSal;
	fSal.open("datos.out");

	if (fEnt.is_open() && fSal.is_open()) {
		while (!fEnt.eof() && !fin) {
			getline(fEnt, num);
			int n = atoi(num.c_str());
			//Lectura conexiones eduroam
			for (int i = 0; i < n; i++) {
				getline(fEnt, num);
				this->Cjtovertices[i] = num;
			}
			getline(fEnt, num);
			int u = atoi(num.c_str());
			//Lectura conexiones Disp
			for (int i = 0; i < u; i++) {
				getline(fEnt, num);
				this->Cjtovertices[n + i] = num;
			}
			this->ocupadas = n + u;

			getline(fEnt, num);
			int d = atoi(num.c_str());
			for (int i = 0; i < d; i++) {
				getline(fEnt, nodo1, ' ');
				getline(fEnt, nodo2, ' ');
				getline(fEnt, coste);

				int fila = posicionVertice(nodo1);
				int col = posicionVertice(nodo2);

				if (fila != -1 && col != -1) {
					insertarCoste(fila, col, atof(coste.c_str()));
				} else {
					cout << "ERROR: NOT FOUND " << endl;
				}
			}

			getline(fEnt, num);
			int p = atoi(num.c_str());
			Floyd();
			prim();
			FloydParaPrim();
			string resultadoPrim = "";

			for (int i = 0; i < p; i++) {
				getline(fEnt, nodo1, ' ');
				getline(fEnt, nodo2);
				fSal << nodo1 << " ";
				//cout << nodo1 <<" ";
				int v1 = posicionVertice(nodo1);
				int v2 = posicionVertice(nodo2);
				Camino(v1, v2, fSal);
				//Camino devuelve un string
				resultadoPrim = resultadoPrim + nodo1 + " " + Camino2(v1, v2) + nodo2 + " " + to_string(this->MatCosteMinimoPrim[v1][v2]) + "\n";
				fSal << nodo2 << " " << this->MatCosteMinimo[v1][v2] << endl;

			}
			fSal << " " << endl;		//PRIMERA LINEA EN BLANCO
			fSal << resultadoPrim << endl;
			fin = true;
		}

	} else {
		cout << "ERROR." << endl;

	}
	fSal.close();
	fEnt.close();
}

/* Muestra una matriz por consola.
 * Parámetro: La matriz que se quiere mostrar.
 * Complejidad: O(N^2)
 */
void Grafo::MostrarDatos(float matriz[][MAX]) {
	cout << setw(4) << endl;
	cout << endl;
	for (int i = 0; i < this->ocupadas; i++) {
		cout << this->Cjtovertices[i] << setw(8);
		for (int j = 0; j < this->ocupadas; j++) {
			cout << matriz[i][j] << setw(10);
		}
		cout << endl;
		cout << "           " << endl;
	}
}

/* Devuelve la posicion de un vertice en el conjunto de vertices dado su nombre (string)
 * Post : {Devuelve la posición del vertice}
 * Parámetro: El nombre del vertice tipo string
 * Return: La posicion del vertice en el vector o -1 si no lo encuentra.
 * Complejidad: O(N)
 */
int Grafo::posicionVertice(string nodo) {
	for (int i = 0; i < this->ocupadas; i++) {
		if (this->Cjtovertices[i] == nodo) {
			return i;
		}
	}
	return -1;
}

/* Actualiza una celda de la matriz de adyacencia.
 * PRE : {La matriz de adyacencia debe existir}
 * Parámetro: La fila y columna de la matriz y el coste a actualizar.
 * Complejidad: O(1)
 */
void Grafo::insertarCoste(int fila, int col, float coste) {
	this->MatAdyacencia[fila][col] = coste;
	this->MatAdyacencia[col][fila] = coste;
}

/* Método que copia la matriz de adyacencia en la de costes minimos
 * PRE : {La matriz de adyacencia debe existir}
 * Complejidad: O(N^2)
 */
void Grafo::copiarMatrizAdy() {
	for (int i = 0; i < this->ocupadas; i++) {
		for (int j = 0; j < this->ocupadas; j++) {
			this->MatCosteMinimo[i][j] = this->MatAdyacencia[i][j];
		}
	}
}

/* Algoritmo de Floyd
 * Post : {Actualiza la matriz de costes minimos}
 * Complejidad: O(N^3)
 */
void Grafo::Floyd() {
	copiarMatrizAdy();
	for (int k = 0; k < this->ocupadas; k++) {
		for (int i = 0; i < this->ocupadas; i++) {
			for (int j = 0; j < this->ocupadas; j++) {
				if (this->MatCosteMinimo[i][k] + this->MatCosteMinimo[k][j] < this->MatCosteMinimo[i][j]) {
					this->MatCosteMinimo[i][j] = this->MatCosteMinimo[i][k] + this->MatCosteMinimo[k][j];
					this->P[i][j] = k;
				}
			}
		}
	}
}

/* Imprime el camino entre dos vertices.
 * Post : {Escribe en el fichero de salida los nodos por los que se pasa para llegar desde el vertice1 al vertice2}
 * Parámetro: Los dos vertices y un flujo de salida como parámetro de entrada/salida.
 * Complejidad:O(N)
 */
void Grafo::Camino(int vertice1, int vertice2, ofstream &fSal) {
	int k = this->P[vertice1][vertice2];
	if (k != -1) {
		Camino(vertice1, k, fSal);
		fSal << this->Cjtovertices[k] << " ";
		Camino(k, vertice2, fSal);
	}
}

/* Algoritmo de PRIM
 * Post : {Genera un arbol de expansion minima}
 * Complejidad: O(n log(n))
 */
void Grafo::prim() {

	string visitados[this->ocupadas];
	int incrementador = 1;
	string v, u;
	float x = 9999;
	//Inicialización del vector
	for (int i = 0; i < this->ocupadas; i++) {
		visitados[i] = "";
	}

	//Elegir un vertice cualquiera
	visitados[0] = this->Cjtovertices[0];

	while (visitados[this->ocupadas - 1] == "") {
		aristaMinima(u, v, x, visitados); // Selecciona la arista mínima

		//Inserción de la arista
		this->MatExpMin[posicionVertice(u)][posicionVertice(v)] = x;
		this->MatExpMin[posicionVertice(v)][posicionVertice(u)] = x;

		//Añade el vertice al conjunto de visitados
		visitados[incrementador] = v;
		x = 9999;
		incrementador++;

		// cout << "Encontrada" << endl;
	}
}

/* Selecciona la artista mínima dado un conjunto de vertices que no genere ciclos.
 * Parámetro: vertices y peso de la arista como parametros de e/s, y un conjunto de vertices visitados.
 * Complejidad: O(N^2)
 */
void Grafo::aristaMinima(string &u, string &v, float &x, string visitados[]) {

	for (int i = 0; i < this->ocupadas && visitados[i] != ""; i++) {
		for (int j = 0; j < this->ocupadas; j++) {
			if (this->MatAdyacencia[posicionVertice(visitados[i])][j] < x && !pertenece(visitados, j) && posicionVertice(visitados[i]) != j) {
				x = this->MatAdyacencia[posicionVertice(visitados[i])][j];
				u = visitados[i];
				v = this->Cjtovertices[j];
			}
		}
	}
}

/* Comprueba la existencia de un vertice en el vector.
 * Parámetro: El vertice a buscar y el conjunto de vertices visitados.
 * Return: Retorna 'true' si lo encuentra, 'false' en caso contrario.
 * Complejidad: O(N)
 */
bool Grafo::pertenece(string visitados[], int v) {
	string vertice = this->Cjtovertices[v];
	for (int i = 0; i < this->ocupadas && visitados[i] != ""; i++) {
		if (visitados[i] == vertice)
			return true;
	}
	return false;
}

/* Método que copia la matriz de expansion minima en la de coste minimo de prim
 * PRE : {La matriz de expansion minima debe existir}
 * Complejidad: O(N^2)
 */
void Grafo::copiarMatrizExpMin() {
	for (int i = 0; i < this->ocupadas; i++) {
		for (int j = 0; j < this->ocupadas; j++) {
			this->MatCosteMinimoPrim[i][j] = this->MatExpMin[i][j];
		}
	}
}


/* Algoritmo de Floyd
 * Post : {Actualiza la matriz de costes minimos}
 * Complejidad: O(N^3)
 */
void Grafo::FloydParaPrim() {
	//Copiamos la matriz
	copiarMatrizExpMin();

	//Algoritmo de Floyd
	for (int k = 0; k < this->ocupadas; k++) {
		for (int i = 0; i < this->ocupadas; i++) {
			for (int j = 0; j < this->ocupadas; j++) {
				if (this->MatCosteMinimoPrim[i][k] + this->MatCosteMinimoPrim[k][j] < this->MatCosteMinimoPrim[i][j]) {
					this->MatCosteMinimoPrim[i][j] = this->MatCosteMinimoPrim[i][k] + this->MatCosteMinimoPrim[k][j];
					this->Pprim[i][j] = k;
				}
			}
		}
	}
}

/* Imprime el camino entre dos vertices.
 * Post : {Escribe en el fichero de salida los nodos por los que se pasa para llegar desde el vertice1 al vertice2}
 * Parámetro: Los dos vertices.
 * Return: Devuelve un string que contiene el camino.
 * Complejidad:O(N)
 */
string Grafo::Camino2(int vertice1, int vertice2) {
	int k = this->Pprim[vertice1][vertice2];
	if (k != -1) {
		return Camino2(vertice1, k) + " " + this->Cjtovertices[k] + " " + Camino2(k, vertice2);
	}
	return "";
}

// DESTRUCTOR
Grafo::~Grafo() {

}

