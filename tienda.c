#include "game.h"

//Inicializar la tienda
void init_tienda(TTienda* tienda){
	tienda->root=NULL;
	strcpy(tienda->nombre,"La tiendita de Don Johnny");
}

/*//Imprimir los precios en preorden
void preorder(TNodeTienda* node){
    if(node==NULL)
        return;
    printf("%d ", node->precio);
    preorder(node->left);
    preorder(node->right);
}*/

/*//Imprimir los precios en inorden 
void inorder(TNodeTienda* node){
    if(node==NULL)
        return;

    inorder(node->left);
	if (size_list_frases(node->lista)>0){
		printf("Peso = %d\n", node->precio);
		printf("Frases:\n");
		print_list_frases(node->lista);
		printf("\n");
	}
    inorder(node->right);
}*/

//Imprimir los precios inorden del arbol tienda (si tienen frases)
void inorder_precios(TNodeTienda* node){
	if (node==NULL)
		return;
	inorder_precios(node->left);
	if (size_list_frases(node->lista)>0){
		printf("     - %d monedillas\n",node->precio);
	}
	inorder_precios(node->right);
}



/*//Imprimir los precios en postorden
void postorder(TNodeTienda* node){
    if(node==NULL)
        return;

    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->precio);
}*/

//Finalizar la subtienda
void finalize_subtienda(TNodeTienda* n){
    if(n==NULL)
        return;
    finalize_subtienda(n->left);
    finalize_subtienda(n->right);
    free(n);
}

//Finalizar la tienda
void finalize_tienda(TTienda* T){
    if(T->root==NULL)
        return;
    finalize_subtienda(T->root->left);
    finalize_subtienda(T->root->right);
    free(T->root);
    T->root = NULL;
}

//Buscar nodeTienda en la tienda
int search_node(TNodeTienda* node, int x){
    if(node==NULL)
        return 0;

    if(node->precio==x)
        return 1;
    else if(x < node->precio)
            return search_node(node->left, x);
    else
            return search_node(node->right, x);
}

//Buscar un precio x en la tienda
int search_tree(TTienda* T, int x){
    if(T->root==NULL)
        return 0;
    return search_node(T->root, x);
}

//Insertar nuevo nodo en la tienda
void insert_nodeTienda(TNodeTienda* node, TNodeTienda* n){
    if(n->precio < node->precio){ //Insertar en el subarbol izquierdo
        if(node->left==NULL)
            node->left = n;
        else
            insert_nodeTienda(node->left, n);
    }else if(n->precio > node->precio){
        if(node->right == NULL)
            node->right = n;
        else
            insert_nodeTienda(node->right, n);
    }
}

//Buscar e insertar en la lista de frases cuando el peso ya este en el arbol
void buscar_y_agregar(TNodeTienda* node,char frase[],int precio,int peso,int enem){
	if (precio==node->precio){
		insert_list_final_frases(node->lista,frase,peso,enem);
	}else if (precio<node->precio){
		buscar_y_agregar(node->left,frase,precio,peso,enem);
	}else{
		buscar_y_agregar(node->right,frase,precio,peso,enem);
	}
}

//Insertar una frase en la tienda
void insert_tienda(TTienda* T, char frase[],int precio,int peso,int enem){	
	if (search_tree(T,precio)==0){
		TNodeTienda* newNode = (TNodeTienda*)malloc(sizeof(TNodeTienda));
		newNode->precio = precio;
		newNode->left = newNode->right = NULL;
		TListaFrases* lista=(TListaFrases*)malloc(sizeof(TListaFrases));
		init_list_frases(lista);
		insert_list_final_frases(lista,frase,peso,enem);
		newNode->lista=lista;
		if(T->root == NULL){
			T->root = newNode;
			return;
		}
		insert_nodeTienda(T->root, newNode);	
	}else{
		buscar_y_agregar(T->root,frase,precio,peso,enem);
	}
}

//Recursion para buscar el mas a la izquierda
int buscar_min_izquierda(TNodeTienda* node){
	if (node->left==NULL) return node->precio;
	else buscar_min_izquierda(node->left);
}

//Valor minimo de una tienda
int tienda_valor_min(TTienda* T){
	if (T->root==NULL)return 0;
	else return buscar_min_izquierda(T->root);
}

//Recursion para buscar el mas a la derecha
int buscar_max_derecha(TNodeTienda* node){
	if (node->right==NULL) return node->precio;
	else buscar_max_derecha(node->right);
}

//Valor maximo de una tienda
int tienda_valor_max(TTienda* T){
	if (T->root==NULL)return 0;
	else return buscar_max_derecha(T->root);
}

//Imprimir la lista de frases del nodo respectivo
void tienda_imprimir_frases_nodo(TNodeTienda* node, int x){
	if (node->precio==x){
		TNodeFrase* auxFrase=node->lista->first;
		int cont=1;
		while (auxFrase!=NULL){
			char ene[MAX_NOM];
			if (auxFrase->enem==1)strcpy(ene,"Keiko");
			if (auxFrase->enem==2)strcpy(ene,"PPK");
			if (auxFrase->enem==3)strcpy(ene,"Alan");
			if (auxFrase->enem==4)strcpy(ene,"Barney");
			if (auxFrase->enem==5)strcpy(ene,"Acunia");
			if (auxFrase->enem==6)strcpy(ene,"Popi");
			printf("  %d-%s [%s]\n",cont,auxFrase->frase,ene);
			cont++;
			auxFrase=auxFrase->next;
		}
		printf("\n[X] = Util contra el candidato X\n");
	}else if (node->precio>x) tienda_imprimir_frases_nodo(node->left,x);
	else tienda_imprimir_frases_nodo(node->right,x);
}

//Imprimir la lista de frases de un nodo de la tienda (se asume que X sí esta en la tienda)
void tienda_imprimir_frases(TTienda* tienda,int x){
	if (tienda->root==NULL){
		printf("La tienda esta vacia!");
		return;
	}else tienda_imprimir_frases_nodo(tienda->root,x);
}


int tienda_buscarnumfrases_nodo(TNodeTienda* node,int x){
	if (node->precio==x)return size_list_frases(node->lista);
	else if (node->precio>x)return tienda_buscarnumfrases_nodo(node->left,x);
	else return tienda_buscarnumfrases_nodo(node->right,x);
}

//Retornar el numero de frases para un precio en la tienda
int tienda_buscarnumfrases(TTienda* tienda,int x){
	if (tienda->root==NULL){
		return -1;
	}else{
		return tienda_buscarnumfrases_nodo(tienda->root,x);
	}
}

//Comprar la frase de precio "opcPrecio" en posicion "opcNum" de la tienda:
//1.Agregar la frase a la lista de frases del jugador
//2.Restar el dinero correspondiente
void tienda_compra_frase(TNodeCand* cand,TTienda* tienda,int opcPrecio,int opcNum){
	//en auxNodoTienda esta el nodo de la tienda con el valor de precio = "opcPrecio"
	TNodeTienda* auxNodoTienda=tienda->root;
	while (auxNodoTienda->precio!=opcPrecio){
		if (auxNodoTienda->precio>opcPrecio)auxNodoTienda=auxNodoTienda->left;
		else if (auxNodoTienda->precio<opcPrecio)auxNodoTienda=auxNodoTienda->right;
	}
	//en auxFrase esta el nodo frase a agregar a nuestro candidato
	int i=1;
	TNodeFrase* auxFrase=auxNodoTienda->lista->first;
	while (i<opcNum){
		auxFrase=auxFrase->next;
		i++;
	}
	insert_list_final_frases(cand->lista,auxFrase->frase,auxFrase->peso,auxFrase->enem);
	cand->dinero=cand->dinero-opcPrecio;
}
