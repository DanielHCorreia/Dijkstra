#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <limits> 

using namespace std;

typedef struct vertice {
	vector<int> vizinhos;
	vector<int> custo;
}vertice;

vertice grafo[10010];

void conectar(int indice, int custo, int vizinho) { //função para ligar o indice ao um de seus vizinhos (i.e, ligar um vertice ao outro)

	grafo[indice].vizinhos.push_back(vizinho);

	grafo[indice].custo.push_back(custo);

}

int Dijkstra(int origem, int destino, int quantidade) {

	int valor[10010]; //array de valores;
	bool visitado[10010]; //Known
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > minHeap;
	pair<int, int> custoIndice; //par suporte para entrar na heap (variavel auxiliar)

	valor[origem] = 0; //caso base

	custoIndice = make_pair(valor[origem], origem); // criando o par e atribuindo

	minHeap.push(custoIndice); //colocando na heap

	for (int i = 1; i <= quantidade; i++) {//varrendo todas as posições
		visitado[i] = false;
		if (i != origem) {

			valor[i] = 200010; //preenchendo com ""infinito"".

		}
	}

	//fim caso base  e preenchimento;

	int auxIndice;

	while (!minHeap.empty()) { //Enquanto a minHeap não estiver vazia, então continue no While;

		auxIndice = minHeap.top().second; //Guardando o indice que sai da minHeap (menor custo da heap(topo));

		minHeap.pop(); // retirando o elemento do topo da minHeap
		visitado[auxIndice] = true; //como retirei o elemento da minHeap, então marco visitado com true;

		if (destino == auxIndice) {
			return valor[destino];
		}

		for (int i = 0; i<grafo[auxIndice].vizinhos.size(); i++) { //repetir para cada vizinho de auxIndice

			if (valor[grafo[auxIndice].vizinhos[i]] > grafo[auxIndice].custo[i] + valor[auxIndice] && visitado[grafo[auxIndice].vizinhos[i]] == false) { //caso tenha um caminho melhor

				valor[grafo[auxIndice].vizinhos[i]] = (grafo[auxIndice].custo[i] + valor[auxIndice]);

				custoIndice = make_pair(valor[grafo[auxIndice].vizinhos[i]], grafo[auxIndice].vizinhos[i]);
				minHeap.push(custoIndice); // Colocando na heap;
			}

		}
	}

	return -1;//forever alone
}

int main() {
	int testes;
	int quantidade;
	string nomes[10010];
	int numeroDeVizinhos;
	int custo, m = 1, vizinho = 0;
	int nCaminhos;
	int origem = 0, destino = 0;
	string O, D;

	scanf("%d", &testes);

	for (int f = 0; f<testes; f++) {

		scanf("%d", &quantidade); //número de vertices

		for (m = 1; m <= quantidade; m++) {
			cin >> nomes[m];

			scanf("%d", &numeroDeVizinhos);

			for (int g = 0; g<numeroDeVizinhos; g++) {

				scanf("%d", &vizinho);

				scanf("%d", &custo);

				conectar(m, custo, vizinho); //passando para a função   
			}
		}

		scanf("%d", &nCaminhos);

		for (int j = 0; j<nCaminhos; j++) {

			cin >> O;
			cin >> D;

			for (int i = 1; i <= quantidade && (origem == 0 || destino == 0); i++) { //Caminhando pelo array de string

				if (!nomes[i].compare(O)) { //Achando o Indice da Origem
					origem = i;
				}

				if (!nomes[i].compare(D)) { //Achando o indice do destino
					destino = i;

				}
			}

			printf("%d\n", Dijkstra(origem, destino, quantidade)); //imprimindo o resultado na tela;

			origem = 0;
			destino = 0;
		}

		for (int a = 1; a <= quantidade; a++) { //zerei todo o grafo para se reescrito novamente.

			grafo[a].vizinhos.clear();
			grafo[a].custo.clear();

		}

	}//f

	return 0;
}
