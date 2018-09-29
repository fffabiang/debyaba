#define MAX_NOM 30
#define MAX_FRASE 100

/*Nodo de candidato*/
typedef struct nodeCand{
	char nombre[MAX_NOM];
	int id;
	char partido[MAX_FRASE];
	int dinero;
	int votosNece; //votos necesarios para vencer un candidato
	TListaFrases* lista;
	struct nodeCand* next;
}TNodeCand;

/*Lista de candidatos*/
typedef struct listaPersonaje{
	TNodeCand* first;
	TNodeCand* last;
}TListaCand;

void init_cand(TNodeCand*,int);
void print_node_cand_info(TNodeCand*);
int is_empty_list_cand(TListaCand*);
void finalize_list_cand(TListaCand*);
void insert_list_cand_first(TListaCand*, int);
int size_list_cand(TListaCand*);
void insert_list_cand_final(TListaCand*,int);
void print_list_cand(TListaCand*);
int idValido(TListaCand*,int);
void init_list_cand(TListaCand*);
void lista_buscar_nombre(TListaCand*,int,char[]);