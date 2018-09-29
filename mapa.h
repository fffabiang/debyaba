#define MAX_NOM 30
#define MAX_FRASE 100

/*Nodo de arista*/
typedef struct arista{
	int id;
	int peso;
	struct arista* next;
}TArista;

/*Nodo de vertice*/
typedef struct vertice{
	int id;
	char lugar[MAX_NOM];
	int posX;
	int posY;
	TNodeCand* cand; //puntero a un candidato
	TTienda* tienda; //puntero a una tienda
	TArista* aristaFirst; //primera arista
	TArista* aristaLast;  //ultima arista
	struct vertice* next; //siguiente vertice
}TVertice; 

/*Mapa*/
typedef struct mapa{
	int numVertices;
	TVertice* verticeFirst; //primer vertice
	TVertice* verticeLast; //ultimo vertice
}TMapa;


void Mapa_CrearVacio(TMapa* mapa);
void Mapa_ImprimirNodosAlrededor(TMapa*,int);
TVertice* Mapa_ExisteVertice(TMapa*,int);
void Mapa_Imprimir(TMapa*);
void Mapa_InsertarArista(TMapa*,int,int,int);
void Mapa_InsertarTienda(TMapa*,TTienda*,int);
void Mapa_InsertarCandidato(TMapa*,TNodeCand*,int);
void Mapa_InsertarVertice(TMapa*,int,int,int);
int Mapa_ExisteArista(TMapa*,int,int);
int Mapa_VerificarExisteVertice(TMapa*,int);
void Mapa_ImprimirMapaGrafico(TMapa*);
int Mapa_HayCandidato(TVertice*);
int Mapa_QuedanCandidatos(TMapa*);
void Mapa_EliminarCandidato(TMapa*,int);
int Mapa_NumeroCandidatos(TMapa*);

