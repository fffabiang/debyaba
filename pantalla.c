#include "game.h"
#include "windows.h"
#define MAX_NOMBRE_CAND 30
#define MAX_STR 255

//Ubica el cursor de la consola en una posicion (x,y)
void gotoxy(int x,int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hCon,dwPos);
}

//Modifica el texto impreso por consola para que salga en un color (de texto y de fondo) de codigo n
void colorear(int n){
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,n);
}

//Imprimir un TITULO en la parte superior de la pantalla
void imprimir_titulo_txt(char ruta[]){
	FILE *file;
	file=fopen(ruta,"r");
	char linea[255];
	int i=0;
	while(fgets(linea,255,file)){
		int ancho=strlen(linea);
		int pos=round((SIZE_SCREEN-ancho)/2);
		gotoxy(pos,i);
		i++;
		printf("%s",linea);
	}
	printf("\n");
	fclose(file);
}

//Imprimir la cabecera del menu de seleccion de candidato en la pantalla
void imprimir_cabecera_seleccion(){
	colorear(252);
	imprimir_titulo_txt("titulo_juego.txt");
	gotoxy(0,8);
	colorear(242);
	printf("%12s %s"," ","-----------------------------------ELIGE A TU CANDIDATO-----------------------------------\n");
}

//Imprimir en la pantalla de MAPA: el titulo MAPA y la LEYENDA a la derecha de la pantalla
void imprimir_detalles_juego(TJugador* player,TMapa* mapa){
	//MAPA EN LA PANTALLA
	colorear(252);
	imprimir_titulo_txt("titulo_mapa.txt");
	colorear(242);
	gotoxy(2,7); printf("---------------------------------------------------------------------------------------------------------------------");
	Mapa_ImprimirMapaGrafico(mapa);
	
	
	//LEYENDA DE LA DERECHA DE LA PANTALLA
	colorear(242);
	int i; 
	int posYBarra=8;
	int posX=85;
	for (i=posYBarra;i<38;i++){
		gotoxy(posX,i);
		printf("|");
	}
	
	colorear(252);
	player_print_X(player); //imprimir X (posicion del jugador) en el mapa
	player_print_dinero(player); //imprimir dinero del jugador en la pantalla
	int numEne=Mapa_NumeroCandidatos(mapa);
	gotoxy(posX+2,11);
	colorear(240);printf("Quedan "); 
	colorear(252);printf("%d",numEne); //imprimir cuantos candidatos quedan en el mapa
	colorear(240);printf(" enemigos!");
	gotoxy(posX+2,27);
	printf("Remember #1: Solo puedes moverte ");
	gotoxy(posX+2,28);
	printf("a lugares adyacentes!");
	gotoxy(posX+2,30);
	printf("Remember #2: Mientras mas te ");
	gotoxy(posX+2,31);
	printf("alejas necesitaras mas votos");
	gotoxy(posX+2,32);
	printf("para ganar cada debate");
	
	//Indicar que candidatos o tiendas hay en el mapa
	gotoxy(posX+2,13);
	printf("En el mapa:");
	int iniY=14;
	TVertice* aux=mapa->verticeFirst;
	while (aux!=NULL){
		if (aux->cand!=NULL){
			gotoxy(posX+2,iniY);
			printf("  %d = %s",aux->id,aux->cand->nombre);
			iniY++;
		}
		if (aux->tienda!=NULL){
			gotoxy(posX+2,iniY);
			printf("  %d = %s",aux->id,aux->tienda->nombre);
			iniY++;
		}
		aux=aux->next;
	}
}


//Imprimir decoracion alrededor del numero del vertice
void gotoxy_imprimir_alrededor(int x,int y){
	gotoxy(x-2,y);
	printf("|");
	gotoxy(x+2,y);
	printf("|");
	gotoxy(x-1,y-1);
	printf("---");
	gotoxy(x-1,y+1);
	printf("---");
}


//Imprime los caminos (en forma de guiones o barras) entre dos vertices en la pantalla
void gotoxy_imprimir_caminos(TMapa* mapa,int idA,int idB,int dir){
	TVertice* ptrVertA=Mapa_ExisteVertice(mapa,idA);
	TVertice* ptrVertB=Mapa_ExisteVertice(mapa,idB);
	if (dir==1){ //de izquierda a derecha
		int i=ptrVertA->posX + 3;
		while (i<ptrVertB->posX - 2){
			gotoxy(i,ptrVertA->posY);
			printf("-");
			i++;
		}
		return;
	}
	if (dir==2){ //de arriba a abajo
		int i=ptrVertA->posY+2;
		while (i<ptrVertB->posY-1){
			gotoxy(ptrVertA->posX,i);
			printf("|");
			i++;
		}
		return;
	}
	if (dir==3){ //diagonal izq_arrib a der_abajo
		int i=ptrVertA->posX+2;
		int j=ptrVertA->posY+1;
		while (i<=ptrVertB->posX-2||j<=ptrVertB->posY-1){
			gotoxy(i,j);
			printf("\\");
			i++;
			j++;
		}
	}
	if (dir==4){ //diagonal izq_abajo a der_arriba
		int i=ptrVertA->posX+2;
		int j=ptrVertA->posY-1;
		while (i<=ptrVertB->posX-2||j<=ptrVertB->posY+1){
			gotoxy(i,j);
			printf("/");
			i++;
			j++;
		}
	}
}

//Imprimir una foto centrada(de un txt) a partir de una ruta
void imprimir_foto_txt(char ruta[]){
	FILE *file;

	//primero obtener la altura de la foto para poder centrarla en la pantalla
	int altura_foto=0;
	file=fopen(ruta,"r");
	char linea[255];
	while(fgets(linea,255,file)){
		altura_foto++;
	}
	fclose(file);
	
	//imprimir cada linea de la foto
	file=fopen(ruta,"r");	
	colorear(240);
	int espacio_impresion=27; //espacio definido para imprimir la foto
	int posY=round((espacio_impresion-altura_foto)/2);
	int i=8+posY;
	while(fgets(linea,255,file)){
		int ancho=strlen(linea);
		int pos=round((SIZE_SCREEN-ancho)/2);
		gotoxy(pos,i);
		i++;
		printf("%s",linea);		
	}
	fclose(file);
}

//Imprimir el mensaje y la foto del candidato cuando el jugador elige uno!
void imprimir_eleccion(TJugador* player){
	system("cls");
	colorear(252);
	imprimir_titulo_txt("titulo_juego.txt");
	colorear(249);
	char eleccion[120];
	if (player->cand->id == 1){
		strcpy(eleccion," --------------------------------------Has elegido a Keiko Fujimori!-------------------------------------- ");
		int ancho=strlen(eleccion);
		int pos=round((SIZE_SCREEN-ancho)/2);
		gotoxy(pos,7);
		printf("%s",eleccion);
		imprimir_foto_txt("foto_keiko.txt");
	}else if(player->cand->id == 2){
		strcpy(eleccion," --------------------------------------Has elegido a PPK!-------------------------------------- ");		
		int ancho=strlen(eleccion);
		int pos=round((SIZE_SCREEN-ancho)/2);
		gotoxy(pos,7);
		printf("%s",eleccion);
		imprimir_foto_txt("foto_ppk.txt");
	}else if(player->cand->id == 3){
		strcpy(eleccion," --------------------------------------Has elegido a Alan!-------------------------------------- ");		
		int ancho=strlen(eleccion);
		int pos=round((SIZE_SCREEN-ancho)/2);
		gotoxy(pos,7);
		printf("%s",eleccion);
		imprimir_foto_txt("foto_alan.txt");
	}else if(player->cand->id == 4){
		strcpy(eleccion," --------------------------------------Has elegido a Barney!-------------------------------------- ");		
		int ancho=strlen(eleccion);
		int pos=round((SIZE_SCREEN-ancho)/2);
		gotoxy(pos,7);
		printf("%s",eleccion);
		imprimir_foto_txt("foto_barney.txt");
	}else if(player->cand->id == 5){
		strcpy(eleccion," --------------------------------------Has elegido a Cesitar Acunia!-------------------------------------- ");		
		int ancho=strlen(eleccion);
		int pos=round((SIZE_SCREEN-ancho)/2);
		gotoxy(pos,7);
		printf("%s",eleccion);
		imprimir_foto_txt("foto_acunia.txt");
	}else if(player->cand->id == 6){
		strcpy(eleccion," --------------------------------------Has elegido a Popi!-------------------------------------- ");		
		int ancho=strlen(eleccion);
		int pos=round((SIZE_SCREEN-ancho)/2);
		gotoxy(pos,7);
		printf("%s",eleccion);	
		imprimir_foto_txt("foto_popi.txt");		
	}	
	int iniborde=floor((SIZE_SCREEN-strlen(eleccion))/2);
	int i;
	colorear(249);
	for (i=8;i<=34;i++){
		gotoxy(iniborde,i);
		printf("|");
		gotoxy(SIZE_SCREEN-iniborde-2,i);
		printf("|");
	}
	for (i=iniborde+1;i<=SIZE_SCREEN-iniborde-3;i++){
		gotoxy(i,35);
		printf("-");
	}
	gotoxy(5,36);
	colorear(240);
	system("pause");
}

//Imprimir el titulo del juego y la casita (tienda) en la pantalla de la tienda
void imprimir_menu_tiendilla(){
	colorear(252);
	imprimir_titulo_txt("titulo_tienda.txt");
	colorear(242);
	gotoxy(2,7); printf("---------------------------------------------------------------------------------------------------------------------");		
	FILE *file;
	file=fopen("imagen_tienda.txt","r");
	char linea[255];
	int i=12;
	while(fgets(linea,255,file)){
		gotoxy(55,i);
		i++;
		printf("%s",linea);
	}
	fclose(file);	
}

//Imprimir los graficos del debate: el titulo DEBATE, las cajas con los votos respetivos del jugador y el enemigo (CPU)
void imprimir_votos_debate(TNodeCand* candPlayer,int votosPlayer,TNodeCand* candCPU,int votosCPU){
	
	colorear(241); //pintar de azul todos los indicadores

	//Se consigue las dimensiones del titulo para encajar donde se imprimiran los votos
	FILE* file;
	file=fopen("titulo_debate.txt","r");
	char linea[255];
	int altura_titulo=0;
	int ancho_titulo=0;
	while(fgets(linea,255,file)){
		if (ancho_titulo==0)ancho_titulo=strlen(linea);
		altura_titulo++;
	}
	fclose(file);
	int espacio_disponible=round((SIZE_SCREEN-ancho_titulo)/2);
	
	char nombre_jugador[MAX_NOMBRE_CAND];
	strcpy(nombre_jugador,candPlayer->nombre);
	char nombre_enem[MAX_NOMBRE_CAND];
	strcpy(nombre_enem,candCPU->nombre);
	int ancho_box_votos_player=strlen(nombre_jugador)+5;
	int ancho_box_votos_CPU=strlen(nombre_enem)+5;
	//Se asume que hay espacio suficiente para escribir...
	//El nombre del candidato del jugador a la izquierda del titulo DEBATE
	//El nombre del candidato del enemigo a la derecha del titulo DEBATE
	int posX_player=0+round((espacio_disponible-ancho_box_votos_player)/2);
	int posX_CPU=round(SIZE_SCREEN/2)+floor(ancho_titulo/2)+round((espacio_disponible-ancho_box_votos_CPU)/2);
	int posY=round(altura_titulo/2);
	int i;
	
	//Imprimir votos del jugador
	gotoxy(posX_player-1,posY-1);
	printf("|");
	gotoxy(posX_player-1,posY+1);
	printf("|");
	gotoxy(posX_player+ancho_box_votos_player-1,posY-1);
	printf("|");
	gotoxy(posX_player+ancho_box_votos_player-1,posY+1);
	printf("|");	
	gotoxy(posX_player+2,posY-1);
	printf("%s",nombre_jugador);
	gotoxy(posX_player,posY);
	for(i=1;i<ancho_box_votos_player;i++)printf("-");
	gotoxy(posX_player,posY-2);
	for(i=1;i<ancho_box_votos_player;i++)printf("-");	
	gotoxy(posX_player+1,posY+1);
	printf("%d",votosPlayer);
	gotoxy(posX_player,posY+2);
	for(i=1;i<ancho_box_votos_player;i++)printf("-");	
	
	//Imprimir votos del CPU
	gotoxy(posX_CPU-1,posY-1);
	printf("|");
	gotoxy(posX_CPU-1,posY+1);
	printf("|");
	gotoxy(posX_CPU+ancho_box_votos_CPU-1,posY-1);
	printf("|");
	gotoxy(posX_CPU+ancho_box_votos_CPU-1,posY+1);
	printf("|");		
	gotoxy(posX_CPU+2,posY-1);
	printf("%s",nombre_enem);
	gotoxy(posX_CPU,posY);
	for(i=1;i<ancho_box_votos_CPU;i++)printf("-");
	gotoxy(posX_CPU,posY-2);
	for(i=1;i<ancho_box_votos_CPU;i++)printf("-");	
	gotoxy(posX_CPU+1,posY+1);
	printf("%d",votosCPU);	
	gotoxy(posX_CPU,posY+2);
	for(i=1;i<ancho_box_votos_CPU;i++)printf("-");	

	//Imprimir limite
	gotoxy(5,7);
	printf(" ---------------------------------------- Debes llegar a %d votos ---------------------------------------- ",candCPU->votosNece);
}

//Imprimir grafico de uso de frases (foto de candidato + su frase dicha)
void imprimir_uso_frase(int id,char frase[MAX_FRASE]){
	FILE *file;
	//primero se imprime la foto
	if (id==1)file=fopen("debate_keiko.txt","r");
	if (id==2)file=fopen("debate_ppk.txt","r");
	if (id==3)file=fopen("debate_alan.txt","r");
	if (id==4)file=fopen("debate_barney.txt","r");
	if (id==5)file=fopen("debate_acunia.txt","r");
	if (id==6)file=fopen("debate_popi.txt","r");
	if (id==0)file=fopen("debate_federico.txt","r");
	char linea[MAX_STR];
	int posYImagen=14;
	int posXImagen=75;
	while(fgets(linea,MAX_STR,file)){
		gotoxy(posXImagen,posYImagen);
		printf("%s",linea);
		posYImagen++;
	}
	fclose(file);
	
	//ahora se imprime la frase
	int posYFrase=11;
	int posXFrase=62;
	if (strlen(frase)>50)posXFrase=50;
	gotoxy(posXFrase,posYFrase);
	printf("| %s!|",frase);
	int aux=posXFrase+strlen(frase)+4; 
	
	//limpiar restos de frase anterior en la pantalla a la derecha
	while (aux<119){
		gotoxy(aux,posYFrase);
		printf(" ");
		aux++;
	}
	//limpiar restos de frase anterior en la pantalla a la izquierda
	int i=1;
	aux=posXFrase-1;
	gotoxy(aux+1,posYFrase-1);
	printf(" ");
	gotoxy(aux+1,posYFrase+1);
	printf(" ");		
	while (i<=12){
		gotoxy(aux,posYFrase);
		printf(" ");
		gotoxy(aux,posYFrase-1);
		printf(" ");
		gotoxy(aux,posYFrase+1);
		printf(" ");		
		aux--;
		i++;
	}
	
	//se imprime la burbuja alrededor
	gotoxy(posXImagen-1,13);
	printf("%c",92);
	int cont=1;
	aux=posXFrase+1;
	while (cont<strlen(frase)+3){
		gotoxy(aux,posYFrase+1);
		printf("-");
		gotoxy(aux,posYFrase-1);
		printf("-");
		aux++;
		cont++;
	}

	//limpiar restos de frase anterior en la pantalla a la derecha
	while(aux<119){
		gotoxy(aux,posYFrase-1);
		printf(" ");
		gotoxy(aux,posYFrase+1);
		printf(" ");		
		aux++;
	}
	
}
