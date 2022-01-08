#ifndef HEADERS_H
#define HEADERS_H

//Definición de constantes a utilizar:
#define PRINCIPIANTE 5 //tamaño del tablero nivel 1
#define AVANZADO 7  //tamaño del tablero nivel 2
#define VETERANO 9 //tamaño del tablero nivel 3
#define ALCANCEFLECHA 5 //numero de casilleros que alcanca la flecha
#define JUGADORES 10 //cantidad máxima de jugadores a ingresar al sistema
#define PALABRA 15  //tamaño máximo del nombre, apellido y alias
#define CI 8 //cantidad de digitos de la cedula
#define GAMES 5 //cantidad de partidas a contabilizar

//Definición de estructuras:

typedef struct{ //estructura que almacena una fecha
    int dia;
    int mes;
    int anio;
}date;

typedef struct{ //estructura que almacena una cadena de caracteres y su largo
    char letra[PALABRA];
    int largo;
}word;

typedef struct{ //almacena una cedula de identidad y su largo
    int cedula[CI];
    int largoCi;
}id;

typedef struct{ //estructura que almacena los jugadores registrados del juego
    word alias;
    word nombre;
    word apellido;
    id cedula;
    date fecha_nacimiento;
    char status; //A = Activo // I = Inactivo
}player;

typedef struct{//estructura que almacena los datos de las partidas jugadas
    date fecha_partida;
    word aliasJ1;
    word aliasJ2;
    int winsJ1;
    int winsJ2;
}game;

//Prototipos de las funciones:

//Muestra las opciones del menú principal
int opciones_menu();

//Muestra las opciones del menú de gestión de usuarios
int opciones_usuarios();

//Muestra las opciones del menú de consultas
int opciones_consultas();

//Solicita al usuario el ingreso de una palabra de hasta 15 caracteres como máximo
word pedir_palabra();

//Solicita el año de nacimiento del jugador en formato(dd-mm-aaaa)
date pedir_fecha();

//Solicita una cedula de jugador de 8 digitos, sin puntos ni guiones
id pedir_cedula();

//Función que comprueba que se haya ingresado una fecha valida
int validar_fecha(date birthdate);

//Función que verifica si la cedula ingresada de un jugador es válida
int validar_ci(id document);

//busca si hay algun jugador con el mismo alias ingresado, falso retorna -1. De lo contrario retorna la pos del jugador
int buscar_jugador(player jugadores[], int pos_players, word alias_aux);

//retorna 0 si encuentra un alias igual al auxiliar o retorna 1 si no encuentra igualdad
int comparar_alias(word alias, word alias_aux);

//Solicita los datos de un jugador y los guarda en el arreglo de tipo player
void registrar_jugador(player players[], int *pos_players);

//Solicita el alias de un jugador y si existe, lo marca como inactivo
void baja_jugador(player players[], int pos_players);

//Solicita al usuario si desea guardar los cambios en la modificación de usuario
char save_confirm();

//Solicita al usuario que ingrese alias de un jugador, y si existe, permite modificar sus datos
void modificar_jugador(player players[], int pos_players);

//Imprime en pantalla una cedula recibida por párametro
void mostrar_cedula(id document);

//Imprime en pantalla una cadena de caracteres recibida por párametro
void mostrar_palabra(word cadena);

//Muestra una lista de los jugadores activos con sus respectivos datos
void player_list(player players[], int pos_players);

//Imprime en pantalla una fecha recibida por parámetro
void mostrar_fecha(date fecha);

//Muestra las victorias de cada jugador en una partida
void mostrar_resultado(int winsJ1, int winsJ2);

//Muestra un listado con las partidas disputadas durante la ejecución del programa
void games_list(game partidas[], int pos_games);

//Solicita el alias de un jugador y si existe, muestra un listado con las partidas que ha disputado
void games_list_by_player(player players[], int pos_players, game partidas[], int pos_games);

//Retorna 0 si las dos fechas son iguales, de lo contrario retorna 1
int comparar_fecha(date fecha, date fecha_aux);

//Solicita una fecha y muestra todas las partidas disputadas en dicha fecha
void games_list_by_date(game partidas[], int pos_games);

//Solicita al usuario elegir el nivel de la partida a jugar
int select_lvl();

//Inicializa el tablero con espacios en blanco y coloca los jugadores, luego los árboles en posiciones random.
void plantar_bosque(int dimensiones, char tablero[][dimensiones]);

//Imprime en pantalla el contenido del tablero del bosque
void mostrar_bosque(int dimensiones, char tablero[][dimensiones]);

//Refresca tablero si el usuario indica que algún jugador está encerrado por árboles
void refrescar_tablero(int dimensiones, char tablero[][dimensiones]);

//Solicita al usuario que indique los jugadores que disputaran el encuentro y cual moverá primero
int elegir_jugador_inicial(game partidas[], int pos_games);

//solicita que se ingrese la dirección en la que moverse o disparar
char solicitar_direccion();

//Permite mover al jugador 1 y define cual es un movimiento válido y cual no.
void movimientosJ1(word aliasJ1, int dimensiones, char tablero[][dimensiones], int pos_jugadores[][2]);

//Permite mover al jugador 2 y define cual es un movimiento válido y cual no.
void movimientosJ2(word aliasJ2, int dimensiones, char tablero[][dimensiones], int pos_jugadores[][2]);

//Permite que cualquiera de los dos jugadores puedan disparar una flecha
int disparar_flecha(int jugador, word aliasJ1, word aliasJ2, int dimensiones, char tablero[][dimensiones], int pos_jugadores[][2]);

//Pregunta a los jugadores si desean moverse o disparar.
void acciones_disponibles(int jugador, word aliasJ1, word aliasJ2, int dimensiones, char tablero[][dimensiones], int pos_jugadores[][2], int *jugador_herido);

//Gestiona los rounds, y las victorias de cada jugador.
void jugar_turnos(int jugador, game partidas[], int pos_games, int dimensiones,char tablero[][dimensiones], int pos_jugadores[][2]);

//muestra las victorias en cada turno
void mostrar_marcador(game partidas[], int pos_games);

//Muestra el ganador y cartel de fin de la partida
void quien_gana(game partidas[], int pos_games);

//Solicita al usuario que ingrese los alias de los jugadores que van a disputar el encuentro
void elegir_alias_game(player jugadores[], int pos_players, game partidas[], int pos_games, int *jugadores_cargados);

//Desarrollo de la partida
void jugar_partida(player jugadores[], int pos_players, game partidas[], int *pos_games);

//muestra mensaje cuando finaliza el programa
void despedida();

//solicita al usuario que ingrese enter para continuar
void pausa();

#endif