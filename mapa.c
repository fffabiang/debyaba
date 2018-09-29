#include "game.h"

//Crear un mapa vacio
void Mapa_CrearVacio(TMapa* mapa){
	mapa->verticeFirst=NULL;
	mapa->verticeLast=NULL;
	mapa->numVertices=0;
}

//Retornar, si existe, un vertice del mapa para tal id
TVertice* Mapa_ExisteVertice(TMapa* mapa,int idV){
	if (mapa->verticeFirst!=NULL){
		TVertice* ptrRec=mapa->verticeFirst;
		while(ptrRec!=NULL){
			if (ptrRec->id==idV)
				return ptrRec;
			ptrRec=ptrRec->next;
		}
	}	
	return NULL;
}

//Retornar una verificacion si existe un vertice
int Mapa_VerificarExisteVertice(TMapa* mapa,int id){
	if (mapa->verticeFirst!=NULL){
		TVertice* ptrRec=mapa->verticeFirst;
		while (ptrRec!=NULL){
			if (ptrRec->id==id)return 1;
			ptrRec=ptrRec->next;
		}
	}
	return 0;
}

//Verificar si existe una arista
int Mapa_ExisteArista(TMapa* mapa,int idU,int idV){
	TVertice *ptrVert=Mapa_ExisteVertice(mapa,idU);
	if (ptrVert!=NULL){
		TArista *ptrArt=ptrVert->aristaFirst;
		while(ptrArt!=NULL){
			if (ptrArt->id==idV)
				return 1;
			ptrArt=ptrArt->next;
		}
	}
	return 0;
}

//Insertar un nuevo vertice en el mapa
void Mapa_InsertarVertice(TMapa* mapa,int id,int posX,int posY){
	if (Mapa_ExisteVertice(mapa,id)==NULL){
		TVertice *ptrNuevo=malloc(sizeof(TVertice));
		if (ptrNuevo){
			ptrNuevo->id=id;
			ptrNuevo->aristaFirst=NULL;
			ptrNuevo->aristaLast=NULL;
			ptrNuevo->next=NULL;
			ptrNuevo->tienda=NULL;
			ptrNuevo->cand=NULL; 
			ptrNuevo->next=NULL;
			ptrNuevo->posX=posX;
			ptrNuevo->posY=posY;
			if (mapa->verticeFirst==NULL){
				mapa->verticeFirst=ptrNuevo;
			}else{
				mapa->verticeLast->next=ptrNuevo;
			}
			mapa->verticeLast=ptrNuevo;
			mapa->numVertices++;		
		}
	}
}

//Insertar un candidato en el mapa
void Mapa_InsertarCandidato(TMapa* mapa,TNodeCand* cand,int idVertice){
	TVertice *ptrVert=Mapa_ExisteVertice(mapa,idVertice);
	if (ptrVert!=NULL){
		ptrVert->cand=cand;			
	}	
}

//Insertar una tienda en el mapa
void Mapa_InsertarTienda(TMapa* mapa,TTienda* tienda,int idVertice){
	TVertice *ptrVert=Mapa_ExisteVertice(mapa,idVertice);
	if (ptrVert!=NULL){
		ptrVert->tienda=tienda;			
	}
}

//Insertar una arista en el mapa
void Mapa_InsertarArista(TMapa* mapa,int idU,int idV,int peso){
	TVertice *ptrVert=Mapa_ExisteVertice(mapa,idU);
	if (ptrVert!=NULL && Mapa_ExisteVertice(mapa,idV) && !Mapa_ExisteArista(mapa,idU,idV)){
		TArista *ptrNuevo=malloc(sizeof(TArista));
		ptrNuevo->id=idV;
		ptrNuevo->peso=peso;
		ptrNuevo->next=NULL;
		if (ptrVert->aristaFirst==NULL) //si el vertice no tenia aristas
			ptrVert->aristaFirst=ptrNuevo;
		else{ //sino... se agrega al final
			ptrVert->aristaLast->next=ptrNuevo;
		}
		ptrVert->aristaLast=ptrNuevo; //la nueva ultima arista sera ptrNuevo
	}
}

//Imprimir el mapa
void Mapa_Imprimir(TMapa* mapa){
	TVertice* ptrVert=mapa->verticeFirst;
	while (ptrVert!=NULL){
		printf("%d",ptrVert->id);
		TArista *ptrArist=ptrVert->aristaFirst;
		while (ptrArist!=NULL){
			printf(" -> %d",ptrArist->id);
			ptrArist=ptrArist->next;
		}
		printf("\n");
		if (ptrVert->cand!=NULL){
			printf("En el vertice %d esta...\n",ptrVert->id);
			print_node_cand_info(ptrVert->cand);
		}else{
			printf("No hay ningun candidato en este vertice!\n");
		}
		if (ptrVert->tienda==NULL){
			printf("No hay tienda en este vertice!\n");
		}else printf("Hay una tienda!\n");
		printf("\n");
		ptrVert=ptrVert->next;	
	}
}

//Imprimir los nodos alrededor de un vertice y lo que haya en ellos
void Mapa_ImprimirNodosAlrededor(TMapa* mapa,int idV){
	TVertice *ptrVert=Mapa_ExisteVertice(mapa,idV);
	if (ptrVert!=NULL){
		printf("\n");
		TArista *ptrArist=ptrVert->aristaFirst;
		while (ptrArist!=NULL){
			printf("Puedes viajar al lugar %d.\n",ptrArist->id);	
			TVertice *aux=Mapa_ExisteVertice(mapa,ptrArist->id);
			if (aux->cand!=NULL){
				colorear(240);
				printf("%10s %s"," ","Hay un candidato enemigo aqui:");
				colorear(249);
				printf(" %s\n",aux->cand->nombre);
			}else{
				colorear(240);
				printf("%10s %s\n"," ","No hay candidato enemigo aqui.",aux->cand->nombre);
			}
			if (aux->tienda!=NULL){
				colorear(240);
				printf("%10s %s"," ","Hay una tienda aqui:");
				colorear(242);
				printf(" %s\n",aux->tienda->nombre);
			}
			printf("\n");
			colorear(240);
			ptrArist=ptrArist->next;									
		}								
	}
}

//Eliminar un candidato de un lugar del mapa
void Mapa_EliminarCandidato(TMapa* mapa,int idCand){
	TVertice *aux=mapa->verticeFirst;
	while (aux!=NULL){
		TNodeCand* auxCand=aux->cand;
		if (auxCand!=NULL){
			if (auxCand->id==idCand){
				aux->cand=NULL;
				free(auxCand);
				return;
			}
		}
		aux=aux->next;
	}
}

//Verificar si hay un candidato en un lugar
int Mapa_HayCandidato(TVertice* vertice){
	if (vertice->cand!=NULL)return 1;
	else return 0;
}


//Imprimir graficamente el mapa
void Mapa_ImprimirMapaGrafico(TMapa* mapa){
	TVertice* ptrVert=mapa->verticeFirst;
	while (ptrVert!=NULL){
		gotoxy(ptrVert->posX,ptrVert->posY);
		printf("%d",ptrVert->id);
		gotoxy_imprimir_alrededor(ptrVert->posX,ptrVert->posY);
		ptrVert=ptrVert->next;
	}
	colorear(243);
	gotoxy_imprimir_caminos(mapa,8,1,1);
	gotoxy_imprimir_caminos(mapa,1,4,2);
	gotoxy_imprimir_caminos(mapa,4,5,2);
	gotoxy_imprimir_caminos(mapa,1,2,1);
	gotoxy_imprimir_caminos(mapa,5,6,1);
	gotoxy_imprimir_caminos(mapa,6,7,1);
	gotoxy_imprimir_caminos(mapa,2,3,3);
}

//Verificar si quedan candidatos en el mapa
int Mapa_QuedanCandidatos(TMapa* mapa){
	TVertice* ptrVert=mapa->verticeFirst;
	while (ptrVert!=NULL){
		if (ptrVert->cand!=NULL)return 1;
		ptrVert=ptrVert->next;
	}
	return 0;
}

//Retorna cuantos candidatos quedan en el mapa
int Mapa_NumeroCandidatos(TMapa* mapa){
	TVertice* ptrVert=mapa->verticeFirst;
	int contador=0;
	while (ptrVert!=NULL){
		if (ptrVert->cand!=NULL)contador++;
		ptrVert=ptrVert->next;
	}
	return contador;
}