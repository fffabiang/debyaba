/*Registro de jugador*/
typedef struct jugador{
	TVertice* posicion;
	TNodeCand* cand;
}TJugador;

void init_player(TJugador*);
void player_print_posicion(TJugador*);
void player_print_info_cand(TJugador*);
void player_print_dondeVisitar(TMapa*,TJugador*);
int player_visitar_valido(TMapa*,TJugador*,int);
void player_visitar_lugar(TMapa*,TJugador*,int);
void elegir_candidato(TJugador*,TListaCand*,int);
void player_print_X(TJugador*);
void player_elegir_candidato(TJugador*,TListaCand*,int);
void player_print_dinero(TJugador*);
int player_esta_en_tienda(TJugador*);