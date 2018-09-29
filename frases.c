#include "game.h"
#define MAX_STR 255
#define MAX_PESO 9

//Inicializar la lista de frases
void init_list_frases(TListaFrases* list){
    list->first = NULL;
    list->last = NULL;
}

//Finalizar la lista de frases
void finalize_list_frases(TListaFrases* list){
    TNodeFrase* aux = list->first;

    while(aux!=NULL){
        list->first = aux->next;
        free(aux);
        aux = list->first;
    }
}

//Esta vacia la lista?
int is_empty_list_frases(TListaFrases* list){
    if(list->first==NULL && list->last==NULL)
        return 1;
    return 0;
}

//Insertar al inicio de una lista de frases
void insert_list_first_frases(TListaFrases* list, char frase[],int peso,int enem){
    TNodeFrase* node = (TNodeFrase*)malloc(sizeof(TNodeFrase));
    strcpy(node->frase,frase);
	node->peso=peso;
	node->enem=enem;
    node->next = NULL;

    if(is_empty_list_frases(list)){
        list->first = node;
        list->last = node;
    }else{
        node->next = list->first;
        list->first = node;
    }
}

//Tamanio de una lista de frases
int size_list_frases(TListaFrases* list){
    TNodeFrase* aux = list->first;
    int counter=0;
    while(aux!=NULL){
        counter++;
        aux = aux->next;
    }
    return counter;
}

//Insertar al final de una lista de frases
void insert_list_final_frases(TListaFrases* list, char frase[],int peso,int enem){
    TNodeFrase* node = (TNodeFrase*)malloc(sizeof(TNodeFrase));
    strcpy(node->frase,frase);
	node->peso=peso;
    node->next = NULL;
	node->enem=enem;
    if(is_empty_list_frases(list)){
        list->first = node;
        list->last = node;
    }else{
        list->last->next=node;
        list->last=node;
    }
}

//Imprimir una lista de frases
void print_list_frases(TListaFrases* list){
    TNodeFrase* aux = list->first;
	int cont=1;
    while(aux!=NULL){
        printf(" %d - %s\n",cont,aux->frase);
		cont++;
        aux = aux->next;
    }
}

//Imprimir una lista de frases en el menu
void print_list_frases_menu(TListaFrases* list){
    TNodeFrase* aux = list->first;
	int cont=1;
    while(aux!=NULL){
        printf("  %d - %s\n",cont,aux->frase);
		cont++;
        aux = aux->next;
    }
}

//Devolver el peso de una frase
int retornarPeso(TListaFrases* list,int num,int IdEnem){
	TNodeFrase* aux=list->first;
	int i=1;
	while (i<num){
		aux=aux->next;
		i++;
	}
	if (aux->enem==0||aux->enem==IdEnem)return aux->peso;
	else return 1; //se sube 1 voto si la frase no concuerda contra quien la usaste
}

//Devolver una frase
void retornarFrase(TListaFrases* list,int num,char frase[]){
	TNodeFrase* aux=list->first;
	int i=1;
	while (i<num){
		aux=aux->next;
		i++;
	}
	strcpy(frase,aux->frase);	
}

//Eliminar una frase en la posicion "num" de la lista
void eliminar_list_frases(TListaFrases *L, int num){   
    if (!is_empty_list_frases(L)){
        TNodeFrase *ptrActual = L->first;
        TNodeFrase *ptrAnt = NULL;
		int cont=1;
        while (ptrActual != NULL ){
            if (cont==num)break;
			else{
				ptrAnt = ptrActual;
				ptrActual = ptrActual->next;
				cont++;
			}
        }
        if (ptrActual != NULL){// Lo encontró
            // Es el primer elemento de la lista
            if (ptrAnt == NULL){ // ptrActual == L->inicio
                L->first = L->first->next;
            }
            // Es el último elemento
            if (ptrActual->next == NULL){ // ptrActual == L->fin
                if (ptrAnt != NULL) ptrAnt->next = NULL;
                L->last = ptrAnt;
            }else{
            // Es un elemento del medio
                if (ptrAnt != NULL) ptrAnt->next = ptrActual->next;
            }
            free(ptrActual);
            //(L->numElem)--;
        }
    }
}

/*Se construye una lista de frases a partir de una ruta de archivo de texto, por ejemplo una ruta:"frases_julio.txt"*/
void construir_lista_frases(TListaFrases* lista,char ruta[]){
	FILE *file;
	file=fopen(ruta,"r");
	char linea[MAX_FRASE];
	while(fgets(linea,MAX_STR,file)){
		int i=0;
		int posLin=0;
		//Obtener frase
		char frase[MAX_FRASE];
		while (linea[posLin]!=','){
			frase[i]=linea[posLin];
			i++;
			posLin++;
		}
		posLin++;
		frase[i]=0;
		//Obtener peso
		char numero[MAX_PESO];
		i=0;
		while (linea[posLin]!=','){
			numero[i]=linea[posLin];
			i++;
			posLin++;
		}
		numero[i]=0;
		posLin++;
		//Obtener enemigo
		char enem=linea[posLin];
		int valor=enem -'0';
		insert_list_final_frases(lista,frase,atoi(numero),valor);
	}
	fclose(file);	
}