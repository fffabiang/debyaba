#define MAX_NOM 30
#define MAX_FRASE 100

/*Nodo de frase*/
typedef struct nodefrase{
	char frase[MAX_FRASE];
	int peso;
	struct nodefrase* next;
	int enem; 
}TNodeFrase;
/*Cada frase posee:
-Frase = descripcion
-Peso = numero de votos que se gana
-Enem = hacia quien esta dirigida la frase...
	Si es...
		0 = neutral
		1 = keiko
		2 = ppk 
		3 = alan
		4 = barne
		5 = acuña
		6 = popi*/
		
/*Lista de frases*/
typedef struct ListaFrase{
    TNodeFrase* first;
    TNodeFrase* last;
}TListaFrases;

void init_list_frases(TListaFrases*);
void finalize_list_frases(TListaFrases*);
int is_empty_list_frases(TListaFrases*);
void insert_list_first_frases(TListaFrases*, char[],int,int);
int size_list_frases(TListaFrases*);
void insert_list_final_frases(TListaFrases*, char[],int,int);
void print_list_frases(TListaFrases*);
int retornarPeso(TListaFrases*,int,int);
void retornarFrase(TListaFrases*,int,char[]);
void eliminar_list_frases(TListaFrases*,int);
void construir_lista_frases(TListaFrases*,char[]);
void print_list_frases_menu(TListaFrases*);