#include "game.h"
#include "windows.h"
#include <time.h>
#define MAX 30
#define MAX_NOMBRE_CAND 30
#define MAX_OPC 100
#define MAX_STR 255
#define MAX_PESO 9

//CONSOLA TAMAÑO VENTANA = 120 x 38
//CONSOLA TAMAÑO BUFFER = 120 X 50 
//CONSOLA FUENTE = LUCIDA CONSOLE 16

void prepararCandidatos(TListaCand* listaCandidatos){
	init_list_cand(listaCandidatos);
	insert_list_cand_final(listaCandidatos,1); 
	insert_list_cand_final(listaCandidatos,2);
	insert_list_cand_final(listaCandidatos,3);
	insert_list_cand_final(listaCandidatos,4);
	insert_list_cand_final(listaCandidatos,5);
	insert_list_cand_final(listaCandidatos,6);
}

void prepararMapa(TMapa* mapa,TTienda* tienda,TJugador* player){
	
	Mapa_CrearVacio(mapa);
	
	//Se insertan los vertices en el mapa
	Mapa_InsertarVertice(mapa,1,53,11); 
	Mapa_InsertarVertice(mapa,2,65,11);
	Mapa_InsertarVertice(mapa,3,73,17);
	Mapa_InsertarVertice(mapa,4,53,17);
	Mapa_InsertarVertice(mapa,5,53,23);
	Mapa_InsertarVertice(mapa,6,65,23);
	Mapa_InsertarVertice(mapa,7,77,23);
	Mapa_InsertarVertice(mapa,8,40,11);
	
	//Se insertan las aristas en el mapa
	Mapa_InsertarArista(mapa,1,2,0);
	Mapa_InsertarArista(mapa,1,4,0);
	Mapa_InsertarArista(mapa,1,8,0);
	Mapa_InsertarArista(mapa,2,3,0);
	Mapa_InsertarArista(mapa,2,1,0);
	Mapa_InsertarArista(mapa,3,2,0);
	Mapa_InsertarArista(mapa,4,1,0);
	Mapa_InsertarArista(mapa,4,5,0);
	Mapa_InsertarArista(mapa,5,4,0);
	Mapa_InsertarArista(mapa,5,6,0);
	Mapa_InsertarArista(mapa,6,5,0);
	Mapa_InsertarArista(mapa,6,7,0);
	Mapa_InsertarArista(mapa,7,6,0);
	Mapa_InsertarArista(mapa,8,1,0);

	//Se colocan los candidatos en el mapa
	int i;
	for (i=1;i<=6;i++){
		TNodeCand* cand=(TNodeCand*)malloc(sizeof(TNodeCand));
		init_cand(cand,i);
		if (i==1)Mapa_InsertarCandidato(mapa,cand,7);
		if (i==2)Mapa_InsertarCandidato(mapa,cand,3);
		if (i==3)Mapa_InsertarCandidato(mapa,cand,6);
		if (i==4)Mapa_InsertarCandidato(mapa,cand,2);
		if (i==5)Mapa_InsertarCandidato(mapa,cand,4);
		if (i==6)Mapa_InsertarCandidato(mapa,cand,5);
	}
	
	//Se coloca la tienda en el mapa
	Mapa_InsertarTienda(mapa,tienda,8);
	
	//Se inicializa la posicion del jugador
	player->posicion=mapa->verticeFirst;
}

void prepararTienda(TTienda* tienda){
	init_tienda(tienda);
	FILE *file;
	file=fopen("frases_tienda.txt","r");
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
		//Obtener precio
		char numero[MAX_PESO];
		i=0;
		while (linea[posLin]!=','){
			numero[i]=linea[posLin];
			i++;
			posLin++;
		}
		posLin++;
		numero[i]=0;
		//obtener peso
		char numero2[MAX_PESO];
		i=0;
		while (linea[posLin]!=','){
			numero2[i]=linea[posLin];
			i++;
			posLin++;
		}
		numero2[i]=0;
		posLin++;		
		//Obtener enemigo
		char enem=linea[posLin];
		int valor=enem -'0';
		insert_tienda(tienda,frase,atoi(numero),atoi(numero2),valor);
	}
	fclose(file);	
}

//Convertir una cadena de caracteres en numeros
int convertirAInt(char opcion[]){
	int i=0;
	char numero[MAX_STR];
	int minNumero='0';
	int maxNumero='9';
	int j=0;
	
	while (i<strlen(opcion)){
		if (opcion[i]<minNumero||opcion[i]>maxNumero)return -1;
		i++;
	}
	i=0;
	while (opcion[i]>=minNumero&&opcion[i]<=maxNumero){
		numero[j]=opcion[i];
		i++;
		j++;
	}
	return atoi(numero);
}

//Funcion donde se realiza la seleccion del candidato por el jugador
void menu_seleccion(TJugador* player,TListaCand* listaCandidatos,TMapa* mapa){
		int flagSelect=0;		
		while (flagSelect==0){
			system("cls");
			imprimir_cabecera_seleccion();
			gotoxy(0,10);
			colorear(241);	
			print_list_cand(listaCandidatos);

			colorear(240);
			printf("%45s %s"," ","Elige:");

			char opcion[MAX_OPC];
			gets(opcion);
			int opc=convertirAInt(opcion);
			if (idValido(listaCandidatos,opc)){
				
				//imprimir logo correspondiente
				FILE *file;
				if (opc==1){
					file=fopen("logo_keiko.txt","r");
					colorear(244);
				}
				if (opc==2){
					file=fopen("logo_ppk.txt","r");
					colorear(243);
				}
				if (opc==3){
					file=fopen("logo_apra.txt","r");
					colorear(252);
				}
				if (opc==4){
					file=fopen("logo_barney.txt","r");
					colorear(241);
				}
				if (opc==5){
					file=fopen("logo_acunia.txt","r");
					colorear(249);
				}
				if (opc==6){
					file=fopen("logo_popi.txt","r");
					colorear(253);
				}
				char linea[255];
				int i=12;
				while(fgets(linea,255,file)){
					gotoxy(65,i);
					i++;
					printf("%s",linea);
				}printf("\n");
				fclose(file);	
				gotoxy(5,36);				
				colorear(240);
				
				
				//confirmacion de seleccion
				char nombre[MAX_NOMBRE_CAND];
				lista_buscar_nombre(listaCandidatos,opc,nombre);
				printf("Vas a eligir a %s.. Segura? [1]Si [2]No:",nombre);
				char opcionConfirmar[MAX_OPC];
				gets(opcionConfirmar);
				int opcConf=convertirAInt(opcionConfirmar);
				
				//si se confirma
				if (opcConf==1){
					player_elegir_candidato(player,listaCandidatos,opc);
					imprimir_eleccion(player);
					//player_mostrar_foto(player);
					Mapa_EliminarCandidato(mapa,opc);
					flagSelect=1;
				}
			}else{
				printf("Opcion no valida.\n");
				system("pause");
			}
		}
}

//Funcion que realiza la jugada del CPU (retorna el peso de la frase que eligio)
int jugadaCPU(TNodeCand* cand,int idPlayer){
	colorear(240);
	int tam=size_list_frases(cand->lista);
	time_t t;
	 /* Intializes random number generator */
	srand((unsigned) time(&t));
	int opcion=(rand() % tam) +1;
	char frase[MAX_FRASE];
	int peso=retornarPeso(cand->lista,opcion,idPlayer);
	retornarFrase(cand->lista,opcion,frase);
	imprimir_uso_frase(cand->id,frase);
	eliminar_list_frases(cand->lista,opcion);
	gotoxy(0,35);
	printf("%s ha aumentado sus votos!\n",cand->nombre);
	return peso;
}

//Funcion donde se realiza el debate... (retorna 1 si ganas o 0 si pierdes)
int debate(TJugador* player,TMapa* mapa){

	system("cls");
	
	colorear(252);
	imprimir_titulo_txt("titulo_debate.txt");

	int maxVotos=player->posicion->cand->votosNece;
	int numVotosJugador=0;
	int numVotosCPU=0;
	
	//mensaje del panelista 
	colorear(240);
	char mensaje[MAX_STR];
	strcpy(mensaje,"Es tu turno");
	imprimir_uso_frase(0,mensaje); 	
	
	//estado actual de los votos
	imprimir_votos_debate(player->cand,numVotosJugador,player->posicion->cand,numVotosCPU);	
	
	if (size_list_frases(player->cand->lista)==0){
		gotoxy(0,34);
		printf("Ya no te quedan frases!\n");
		return 0;
	}	
	
	while (numVotosJugador<maxVotos&&numVotosCPU<maxVotos){
		system("cls");
		//imprimir titulo
		colorear(252);
		imprimir_titulo_txt("titulo_debate.txt");		
		//estado actual de los votos
		imprimir_votos_debate(player->cand,numVotosJugador,player->posicion->cand,numVotosCPU);	
		//mensaje del panelista 
		colorear(240);
		char mensaje[MAX_STR];
		strcpy(mensaje,"Es tu turno");
		imprimir_uso_frase(0,mensaje); 

		if (size_list_frases(player->cand->lista)==0){
			imprimir_uso_frase(0,"Ya no te quedan frases");
			gotoxy(0,36);system("pause");
			return 0;
		}
		
		//imprimir indicadores del debate
		imprimir_votos_debate(player->cand,numVotosJugador,player->posicion->cand,numVotosCPU);	

		//imprimir las frases
		colorear(240);
		gotoxy(0,14);
		printf("Tus frases:\n");
		print_list_frases(player->cand->lista);
		
		int flagTurnoPlayer=0;
		//elegir opcion y continuar...
		printf("\nElige:");
		char opc[MAX];
		gets(opc);
		int opcion=convertirAInt(opc);
		if (opcion<=size_list_frases(player->cand->lista)&&opcion>0){
			char frase[MAX];
			int aumento=retornarPeso(player->cand->lista,opcion,player->posicion->cand->id);
			numVotosJugador=numVotosJugador+aumento;
			retornarFrase(player->cand->lista,opcion,frase);
			imprimir_uso_frase(player->cand->id,frase);
			imprimir_votos_debate(player->cand,numVotosJugador,player->posicion->cand,numVotosCPU);	
			colorear(240);
			gotoxy(0,34);
			printf("Has aumentado tus votos!\n");
			eliminar_list_frases(player->cand->lista,opcion);
			flagTurnoPlayer=1;
			system("pause");
		}else{
			printf("Opcion no valida\n\n");
			system("pause");
		}
		
		//Si es que ganaste...
		if (numVotosJugador>=maxVotos){
			player->cand->dinero=player->cand->dinero+floor(maxVotos/2); //Se gana por debate: maxVotos/2
			Mapa_EliminarCandidato(mapa,player->posicion->cand->id);
			gotoxy(0,34);
			printf("Has alcanzado los %d votos!                    ",maxVotos);
			return 1;
		}

		//turno del CPU
		if (flagTurnoPlayer==1){
			//mensaje del panelista 
			colorear(240);
			char mensaje[MAX_STR];
			strcpy(mensaje,"Es el turno de ");
			strcat(mensaje,player->posicion->cand->nombre);
			imprimir_uso_frase(0,mensaje); 	
			gotoxy(0,35);printf("                                                  ");
			gotoxy(0,36); printf("Espera...                                                         ");
			system("sleep 0.5");
			
			numVotosCPU=numVotosCPU+jugadaCPU(player->posicion->cand,player->cand->id);
			imprimir_votos_debate(player->cand,numVotosJugador,player->posicion->cand,numVotosCPU);	
			gotoxy(0,36);
			system("pause");
		}
	}
	
	//Si gano el CPU
	if (numVotosCPU>=maxVotos){
		return 0;
	}
	
}

//Compra de frases en la tienda
void comprarFrases(TJugador* player){
	int valorMinTienda=tienda_valor_min(player->posicion->tienda);
	int valorMaxTienda=tienda_valor_max(player->posicion->tienda);
	char opcionMin[MAX],opcionMax[MAX];
	int flagGeneralTienda=0;	
	
	while (flagGeneralTienda==0){ //controla cuando estamos o salimos de la "tienda"
		//decoracion
		system("cls");
		imprimir_menu_tiendilla();
		player_print_dinero(player);
		gotoxy(0,8);	
		colorear(240);
		if (player->posicion->tienda->root==NULL){
			printf("Esta tienda esta vacia! :( \n");
			break;
		}
		printf("En esta tienda, tenemos frases que cuestan...\n");
		inorder_precios(player->posicion->tienda->root);
		printf("\n[1]Elegir Precio  [2]Salir\n\nTu opcion:");
		char opcionMenuTienda[MAX_OPC];
		gets(opcionMenuTienda);
		int opcMenuTienda=convertirAInt(opcionMenuTienda);
		if (opcMenuTienda==1){ //Si se eligio comprar una frase
			printf("\nIngresa el precio:");
			char opcionCompra[MAX_OPC];
			gets(opcionCompra);
			int opcPrecio=convertirAInt(opcionCompra);
			if (search_tree(player->posicion->tienda,opcPrecio)){ //si el precio es valido
				int flagComprarFrase=0;
				while (flagComprarFrase==0){ //bucle para este grupo de frases
					system("cls");
					imprimir_menu_tiendilla();
					player_print_dinero(player);
					gotoxy(0,8);
					colorear(240);					
					printf("\nLas frases que cuestan %d monedillas son:\n",opcPrecio);
					tienda_imprimir_frases(player->posicion->tienda,opcPrecio);
					int numFrases=tienda_buscarnumfrases(player->posicion->tienda,opcPrecio);
					printf("\nPuedes: [1]Comprar o [2]Regresar\n\nTu opcion:");
					char opcionCompraFrase[MAX_OPC];
					gets(opcionCompraFrase);
					int opcCompraFrase=convertirAInt(opcionCompraFrase);
					if (opcCompraFrase==1){
						char opcionNum[MAX_OPC];
						printf("Ingresa el # de la frase a comprar:");
						gets(opcionNum);
						int opcNum=convertirAInt(opcionNum);
						if (opcNum>=1&&opcNum<=numFrases){
							if (opcPrecio<=player->cand->dinero){
								//agregar la frase a las del jugador
								tienda_compra_frase(player->cand,player->posicion->tienda,opcPrecio,opcNum);
								printf("Has comprado la frase!\n");								
							}else{
								printf("No tienes suficiente dinero!\n");
							}
							flagComprarFrase=1;//regresar al menu principal de compra
							system("pause");
						}else{
							printf("Indice invalido\n");
							system("pause");
						}
					}else if (opcCompraFrase==2){
						printf("Mira otros precios!\n");
						flagComprarFrase=1; //el usuario ya no quiere ver mas de estas frases
						system("pause");
					}else{
						printf("Opcion invalida!\n");
						system("pause");
					}
				}
			}else{
				printf("El precio no es valido!\n");
				system("pause");
			}
		}else if (opcMenuTienda==2){
			printf("\nHas salido de la tienda!\n");
			system("pause");
			flagGeneralTienda=1;
		}else{
			printf("Esa opcion no es valida!\n");
			system("pause");
		} 
	}
}

int main(){
	
	system("pause");
	
	TJugador player;
	init_player(&player);
	
	TListaCand listaCandidatos;
	prepararCandidatos(&listaCandidatos);
	
	TTienda tienda;
	prepararTienda(&tienda);
	
	TMapa mapa;
	prepararMapa(&mapa,&tienda,&player);

	system("color F0");
	menu_seleccion(&player,&listaCandidatos,&mapa);

	while (1){
		//Si hay un enemigo donde estas...
		if (Mapa_HayCandidato(player.posicion)){
			colorear(249);
			printf("Hay un candidato donde estas!\n");
			printf("Empezara el debate!\n");
			system("pause");
			colorear(240);
			if (debate(&player,&mapa)){
				colorear(252);
				imprimir_uso_frase(0,"Ganaste este debate");
				gotoxy(0,35);
				colorear(240);
				printf("Ha aumentado tu dinero!                                  \n");
				system("pause");
			}else{
				colorear(252);
				imprimir_uso_frase(0,"Ha ganado tu contrincante! Perdiste");
				colorear(240);
				gotoxy(0,36);
				system("pause");
				return 0;
			}
		}
		
		//Si has llegado a una tienda...
		if (player_esta_en_tienda(&player)){
			printf("Has llegado a la tienda!\n");
			system("pause");
			int flagOpcionCompra=0;
			while (flagOpcionCompra==0){
				system("cls");
				imprimir_menu_tiendilla();
				player_print_dinero(&player);
				gotoxy(0,12);	
				colorear(240);				
				printf("Quieres comprar frases? [1]Si [2]No:");				
				char opcionCompra[MAX];
				gets(opcionCompra);
				int opc=convertirAInt(opcionCompra);
				if (opc==1){
					comprarFrases(&player);
					flagOpcionCompra=1;
					player_visitar_lugar(&mapa,&player,1); //te regresa de donde viniste (posicion 1) importante para evitar bucle infinito
				}else if (opc==2){
					printf("Has salido de la tienda!\n");
					flagOpcionCompra=1;
					player_visitar_lugar(&mapa,&player,1); //te regresa de donde viniste (posicion 1) importante para evitar bucle infinito				
					system("pause");
				}else{
					printf("Opcion invalida.\n");
					system("pause");
				}
			}
		}
		
		
		//Se rompe el bucle cuando ya no quedan candidatos (se gana el juego)
		if (Mapa_QuedanCandidatos(&mapa)==0){
			printf("Ya no quedan candidatos en el mapa!\n");
			printf("Has ganado el juego!\n");
			system("pause");
			return 0;
		}		
		
		//menu de juego
		system("color F0");
		system("cls");
		imprimir_detalles_juego(&player,&mapa); //imprime titulo, mapa, posicion, dinero, etc		
		gotoxy(0,21);
		colorear(240);
		player_print_posicion(&player);
		printf("\nQue hacer: [1]Mover [2]Ver Frases\n\nTu opcion:");
		char opcionMenu[MAX_STR];
		gets(opcionMenu);
		int opcMenu=convertirAInt(opcionMenu);
		if (opcMenu==1){
			char opcion[MAX_FRASE];
			printf("Viajar al lugar numero:");gets(opcion);
			int numLugar=convertirAInt(opcion);
			if (player_visitar_valido(&mapa,&player,numLugar)){
				player_visitar_lugar(&mapa,&player,numLugar);
			}else{
				if (numLugar==player.posicion->id)printf("Ya estas en ese lugar!\n");
				else printf("No puedes viajar a ese lugar!\n");
				system("pause");
			}
		}else if (opcMenu==2){
			printf("Tus frases son:\n");
			print_list_frases_menu(player.cand->lista);
			system("pause");
		}else{
			printf("Esa opcion no es valida!\n");
			system("pause");
		}		
	}
	return 0;
}