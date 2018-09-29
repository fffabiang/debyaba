#include "game.h"

//Inicializar un jugador
void init_player(TJugador* player){
	player->posicion=NULL;
	player->cand=NULL;
}

//Imprime la posicion actual del jugador
void player_print_posicion(TJugador* player){
	printf("Tu posicion actual es %d!\n",player->posicion->id);
}

//Imprime una X en el mapa grafico senialando la posicion del jugador
void player_print_X(TJugador* player){
	gotoxy(player->posicion->posX,player->posicion->posY);
	printf("X");
}

//Imprime el dinero del jugador en la pantalla
void player_print_dinero(TJugador* player){
	gotoxy(87,9);
	colorear(240);printf("Tu dinero = ");
	colorear(252);printf("%d",player->cand->dinero);
	colorear(240);printf(" monedillas");
}

//Imprimir la informacion de un candidato
void player_print_info_cand(TJugador* player){
	printf("%s de ",player->cand->nombre);
	printf("%s\n",player->cand->partido);
}

//Imprimir los lugares que se pueden visitar (lugares alrededor del jugador)
void player_print_dondeVisitar(TMapa* mapa,TJugador* player){	
	Mapa_ImprimirNodosAlrededor(mapa,player->posicion->id);		
}

//Verificar si es valido visitar un lugar
int player_visitar_valido(TMapa* mapa, TJugador* player,int numLugar){
	if (Mapa_VerificarExisteVertice(mapa,numLugar)&&Mapa_ExisteArista(mapa,player->posicion->id,numLugar))return 1;
	else return 0;
}

//Mover la posicion del jugador
void player_visitar_lugar(TMapa* mapa,TJugador* player,int numLugar){
	TVertice *nuevoLugar=Mapa_ExisteVertice(mapa,numLugar);
	player->posicion=nuevoLugar;
}

//Asignar un candidato a un jugador
void player_elegir_candidato(TJugador* player,TListaCand* lista,int opc){
	TNodeCand* ptr=lista->first;
	while (ptr!=NULL){
		if (ptr->id==opc){
			player->cand=ptr;
			return;
		}
		ptr=ptr->next;
	}
}

//Verificar si hay una tienda en la posicion del jugador
int player_esta_en_tienda(TJugador* player){
	if (player->posicion->tienda==NULL)return 0;
	else return 1;
}
