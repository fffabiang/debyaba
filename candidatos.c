#include "game.h"

/*FUNCIONES PARA NODO CANDIDATO*/

/*Inicializacion de candidato*/
void init_cand(TNodeCand* cand,int id){
	TListaFrases *lista=(TListaFrases*)malloc(sizeof(TListaFrases));
	init_list_frases(lista);
	if (id==1){
		cand->id=1;
		strcpy(cand->nombre,"Keiko Fujimori");
		strcpy(cand->partido,"Fuerza Popular");
		cand->dinero=60000000;
		cand->votosNece=10000;
		construir_lista_frases(lista,"frases_keiko.txt");
		cand->lista=lista;
		return;
	}
	if (id==2){
		cand->id=2;
		strcpy(cand->nombre,"PPK");
		strcpy(cand->partido,"Peruanos Por El Kambio");
		cand->dinero=1000;
		cand->votosNece=7000;
		construir_lista_frases(lista,"frases_ppk.txt");
		cand->lista=lista;
		return;
	}
	if (id==3){
		cand->id=3;
		strcpy(cand->nombre,"Alan Garcia");
		strcpy(cand->partido,"APRA");
		cand->dinero=1000;
		cand->votosNece=8000;
		construir_lista_frases(lista,"frases_alan.txt");
		cand->lista=lista;
		return;
	}
	if (id==4){
		cand->id=4;
		strcpy(cand->nombre,"Alfredo Barney");
		strcpy(cand->partido,"Accion Popular");
		cand->dinero=1000;
		cand->votosNece=6000;
		construir_lista_frases(lista,"frases_barney.txt");
		cand->lista=lista;
		return;
	}
	if (id==5){
		cand->id=5;
		strcpy(cand->nombre,"Cesitar Acunia");
		strcpy(cand->partido,"Alianza");
		cand->dinero=1000;
		cand->votosNece=5000;
		construir_lista_frases(lista,"frases_acunia.txt");
		cand->lista=lista;
		return;
	}
	if (id==6){
		cand->id=6;
		strcpy(cand->nombre,"Popi Olivera");
		strcpy(cand->partido,"Frente Esperanza");
		cand->dinero=1000;
		cand->votosNece=7000;
		construir_lista_frases(lista,"frases_popi.txt");
		cand->lista=lista;
		return;
	}
}

//Imprimir info de un candidato (menos sus frases)
void print_node_cand_info(TNodeCand *cand){
	printf("%s\n",cand->nombre);
	printf("%8s Partido = %s\n"," ",cand->partido);
	printf("%8s Dinero Inicial = %d\n"," ",cand->dinero);
}

/*FUNCIONES PARA LISTA DE CANDIDATOS*/

//Inicializar lista de candidatos
void init_list_cand(TListaCand* list){
    list->first = NULL;
    list->last = NULL;	
}

//Esta vacia la lista de candidatos?
int is_empty_list_cand(TListaCand* list){
    if(list->first==NULL && list->last==NULL)
        return 1;
    return 0;
}

//Finalizar lista de candidatos
void finalize_list_cand(TListaCand* list){
    TNodeCand* aux = list->first;
    while(aux!=NULL){
        list->first = aux->next;
        free(aux);
        aux = list->first;
    }
}

//Insertar candidato al inicio de la lista
void insert_list_cand_first(TListaCand* list, int id){
    TNodeCand* node = (TNodeCand*)malloc(sizeof(TNodeCand));
	init_cand(node,id);
    node->next = NULL;
    if(is_empty_list_cand(list)){
        list->first = node;
        list->last = node;
    }else{
        node->next = list->first;
        list->first = node;
    }
}

//Tamaño de la lista de candidatos
int size_list_cand(TListaCand* list){
    TNodeCand* aux = list->first;
    int counter=0;
    while(aux!=NULL){
        counter++;
        aux = aux->next;
    }
    return counter;
}

//Insertar candidato al final de la lista
void insert_list_cand_final(TListaCand* list, int id){
    TNodeCand* node = (TNodeCand*)malloc(sizeof(TNodeCand));
	init_cand(node,id);
    node->next = NULL;
    if(is_empty_list_cand(list)){
        list->first = node;
        list->last = node;
    }else{
        list->last->next=node;
        list->last=node;
	}
}

//Imprimir la lista de candidatos
void print_list_cand(TListaCand* list){
    TNodeCand* aux = list->first;
	while(aux!=NULL){
		printf("%8s %d - "," ",aux->id);
        print_node_cand_info(aux);
		printf("\n");
		//print_list_frases(aux->lista);
        aux = aux->next;
    }
}

//Validar id candidato
int idValido(TListaCand*  lista,int opc){
	TNodeCand* ptr=lista->first;
	while (ptr!=NULL){
		if (ptr->id==opc)return 1;
		ptr=ptr->next;
	}
	return 0;
}

//Buscar el nombre de un candidato, dado un numero de id
void lista_buscar_nombre(TListaCand* lista,int id,char nombre[]){
	TNodeCand* aux=lista->first;
	while (aux->id!=id){
		aux=aux->next;
	}
	strcpy(nombre,aux->nombre);
}

