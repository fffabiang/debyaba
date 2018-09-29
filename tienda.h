#define MAX_NOM 30
#define MAX_FRASE 100

/*Nodo de Tienda*/
typedef struct nodeTienda{
	int precio;
	struct nodeTienda* left;
	struct nodeTienda* right;
	TListaFrases* lista;
}TNodeTienda;

/*Registro de tienda*/
typedef struct tienda{
	char nombre[MAX_NOM];
	int num;
	TNodeTienda* root;
}TTienda;

void init_tienda(TTienda*);
void finalize_subtienda(TNodeTienda*);
void finalize_tienda(TTienda*);
int search_node(TNodeTienda*,int);
int search_tree(TTienda*,int);
void insert_nodeTienda(TNodeTienda*,TNodeTienda*);
void buscar_y_agregar(TNodeTienda*,char[],int,int,int);
void insert_tienda(TTienda*,char[],int,int,int);
int tienda_valor_min(TTienda*);
int tienda_valor_max(TTienda*);
int tienda_buscarnumfrases(TTienda*,int);
int tienda_buscarnumfrases_nodo(TNodeTienda*,int);
void inorder_precios(TNodeTienda*);
void tienda_compra_frase(TNodeCand*,TTienda*,int,int);
void tienda_imprimir_frases(TTienda*,int);