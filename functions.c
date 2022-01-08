#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"

int opciones_menu(){
    int opcion = 0;
    printf("╔════════════════╗\n");
    printf("║ Menú principal ║\n");
    printf("╚════════════════╝\n");
    printf("  1. Gestionar usuarios\n");
    printf("  2. Consultas\n");
    printf("  3. Jugar\n");
    printf("  4. Salir\n");
    do{
        printf("Ingresa una opción(1..4): ");
        scanf("%d", &opcion);
        if (opcion < 1 || opcion > 4){
            printf("La opción que has ingresado no es válida. Inténtalo otra vez.\n");
        }
    }
    while(opcion < 1 || opcion > 4);
    system("clear");
    return opcion;
}

int opciones_usuarios(){
    int opcion = 0;
    system("clear");
    printf("╔═════════════════════════════╗\n");
    printf("║ Menú de Gestión de Usuarios ║\n");
    printf("╚═════════════════════════════╝\n");
    printf("  1. Alta de jugador\n");
    printf("  2. Baja de jugador\n");
    printf("  3. Modificación de jugador\n");
    printf("  0. Volver al menú principal\n");
    do{
        printf("Ingresa una opción(0..3): ");
        scanf("%d", &opcion);
        if (opcion < 0 || opcion > 3){
            printf("La opción que has ingresado no es válida. Inténtalo otra vez.\n");
        }
    }
    while(opcion < 0 || opcion > 3);
    system("clear");
    return opcion;
}

int opciones_consultas(){
    int opcion = 0;
    system("clear");
    printf("╔═══════════════════╗\n");
    printf("║ Menú de consultas ║\n");
    printf("╚═══════════════════╝\n");
    printf("  1. Listado de jugadores\n");
    printf("  2. Listado de todas las partidas\n");
    printf("  3. Listado de partidas por jugador\n");
    printf("  4. Listado de partidas por fecha\n");
    printf("  0. Volver al menú principal\n");
    do{
        printf("Ingresa una opción(0..4): ");
        scanf("%d", &opcion);
        if (opcion < 0 || opcion > 4){
            printf("La opción que has ingresado no es válida. Inténtalo otra vez.\n");
        }
    }
    while(opcion < 0 || opcion > 4);
    system("clear");
    return opcion;
}

word pedir_palabra(){
    word palabra;
    palabra.largo = 0;
    for(int i = 1; i <= PALABRA && (palabra.letra[i-1]=getchar())!='\n'; i++){
        palabra.largo += 1;
    }
    return palabra;
}

date pedir_fecha(){
    date birthdate;
    int fecha_valida;
    do{
    scanf("%d-%d-%d", &birthdate.dia, &birthdate.mes, &birthdate.anio);
    fecha_valida = validar_fecha(birthdate);
    }
    while(fecha_valida != 1);
    return birthdate;
}

id pedir_cedula(){
    id document;
    int ci_valida;

    getchar();  //absorbe salto de linea de la selección de opción en menú
    do{
        document.largoCi = 0;
        for(int i = 1; i <= CI && (document.cedula[i-1]=getchar())!=10; i++){
            document.cedula[i-1] -= 48;
            document.largoCi += 1;
        }
        ci_valida = validar_ci(document); //si la cedula no es válida se pide ingresar una nueva
    }
    while(ci_valida != 1);
    return document;
}

int validar_fecha(date birthdate){
    int fecha_valida = 1;
    if(birthdate.anio > 2021){
        fecha_valida = 3;
    }
    else if(birthdate.anio < 1900){
        fecha_valida = 4;
    }

    switch(birthdate.mes){
        case 2:
            if(birthdate.dia > 28){
            fecha_valida = 2;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if(birthdate.dia > 30){
                fecha_valida = 2;
            }
            break;

        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(birthdate.dia > 31){
                fecha_valida = 2;
            }
            break;

        default:
            fecha_valida = 0;

    }
    if(fecha_valida == 0){
        printf("El mes que ingresaste no es válido. Ingresa fecha nuevamente: ");
    }
    else if(fecha_valida == 2){
        printf("El dia que ingresaste no es válido. Ingresa fecha nuevamente: ");
    }
    else if(fecha_valida == 3){
        printf("¿Acaso vienes del futuro?. Ingresa fecha nuevamente: ");
    }
    else if(fecha_valida == 4){
        printf("No se acepta un año inferior al 1900. Ingresa fecha nuevamente: ");
    }
    else{
        printf("La fecha es válida.\n");
    }
    return fecha_valida;
}

int validar_ci(id document){
    int multiplicador[] = {2, 9, 8, 7, 6, 3, 4};
    int resultado = 0;
    int suma = 0;
    int resto = 0;
    int dig_verif = 0;
    int ci_valida;

    if(document.largoCi == CI){
        for(int i = 0; i < CI-1; i++){
            resultado = multiplicador[i] * document.cedula[i];
            suma += resultado;
        }
        resto = suma % 10;
        dig_verif = (10 - resto) % 10;
        if(document.cedula[CI-1] == dig_verif){
            printf("CI válida.\n");
            ci_valida = 1; //cedula de identidad válida
        }
        else{
            printf("Digito verificador inválido. Intente nuevamente: ");
            getchar();
            ci_valida = 0; //cedula inválida
        }
    }
    else{
        printf("CI incompleta. Intente nuevamente: ");
        ci_valida = 0; //cedula inválida
    }
    return ci_valida;
}

int buscar_jugador(player jugadores[], int pos_players, word alias_aux){
    int i;
    for(i = 0; i < pos_players; i++){
        if(comparar_alias(jugadores[i].alias, alias_aux) == 0){
            return i;
        }
    }
    return -1; //si no se encuentra jugador con el mismo alias que "alias_aux"
}

int comparar_alias(word alias, word alias_aux){
    int i, c_iguales = 0;
    if(alias.largo != alias_aux.largo){ //compara los largos de ambos alias
        return 1; //si son diferentes retorna 1
    }
    else{
        for(i = 0; i < alias.largo; i++){ //recorre todas las posiciones de los alias
            if(alias.letra[i] == alias_aux.letra[i]){//compara cada caracter de ambos alias
                c_iguales++; //contador de caracteres iguales
            }
        }
        if(c_iguales == alias.largo){
            return 0;//si hay tantos caracteres iguales como el largo de los alias quiere decir que se encontró igualdad
        }
        else{
            return 1;
        }
    }
}

void registrar_jugador(player players[], int *pos_players){
    word alias_aux;
    int existe_jugador;
    system("clear");
    printf("Jugador %d\n", *pos_players+1);
    printf("\nAlias: ");
    alias_aux = pedir_palabra();
    existe_jugador = buscar_jugador(players, *pos_players, alias_aux);
    if(existe_jugador != -1 && players[existe_jugador].status == 'I'){
        players[existe_jugador].status = 'A';
        printf("Jugador inactivo, se colocó como activo nuevamente.\n");
    }
    else if(existe_jugador != -1 && players[existe_jugador].status == 'A'){
    printf("El alias ingresado ya existe.\n");
    }
    else{//si no se encuentra un jugador con el alias ingresado previamente, se procede a ingresar los datos
        players[*pos_players].alias = alias_aux;
        printf("\nNombre: ");
        players[*pos_players].nombre = pedir_palabra();
        printf("\nApellido: ");
        players[*pos_players].apellido = pedir_palabra();
        printf("\nFecha de nacimiento con el siguiente formato dd-mm-aaaa: ");
        players[*pos_players].fecha_nacimiento = pedir_fecha();
        printf("\nCedula sin puntos ni guión: ");
        players[*pos_players].cedula = pedir_cedula();
        //Al registrar jugador su estado se convierte en Activo
        players[*pos_players].status = 'A';
        *pos_players += 1;
        getchar();
    }
    pausa();
}

void baja_jugador(player players[], int pos_players){
    word alias_aux;
    int existe_jugador;
    system("clear");
    printf("Baja de jugadores\n");
    printf("\nIngresa un alias: ");
    alias_aux = pedir_palabra();
    existe_jugador = buscar_jugador(players, pos_players, alias_aux);
    if(existe_jugador == -1){
        printf("No existe un jugador con el alias ingresado.\n");
    }
    else{
        if(players[existe_jugador].status == 'I'){
            printf("Este jugador ya fue dado de baja.\n");
        }
        else{
            players[existe_jugador].status = 'I';
            printf("Se ha dado de baja al jugador con éxito.\n");
        }
    }
    pausa();
}

char save_confirm(){
    char letra;
    printf("\n¿Deseas guardar los datos ingresados?\n");
    printf(" S - Si, guardar datos.\n");
    printf(" N - No, descartar datos.\n");
    printf("Ingresa letra(S/N): ");
    do{
        letra = getchar();
    }
    while(letra != 'S' && letra != 's' && letra != 'N' && letra != 'n');
    return letra;
}

void modificar_jugador(player players[], int pos_players){
    word alias;
    word aux_name;
    word aux_lastname;
    date aux_birthdate;
    id aux_identity;
    int existe_jugador;
    char save_data;
    system("clear");
    printf("Modificación de jugadores\n");
    printf("\nIngresa un alias: ");
    alias = pedir_palabra();
    existe_jugador = buscar_jugador(players, pos_players, alias);
    if(existe_jugador == -1){
        printf("No existe un jugador con el alias ingresado.\n");
    }
    else{
        printf("\nNombre: ");
        aux_name = pedir_palabra();
        printf("\nApellido: ");
        aux_lastname = pedir_palabra();
        printf("\nFecha de nacimiento con el siguiente formato dd-mm-aaaa: ");
        aux_birthdate = pedir_fecha();
        printf("\nCedula sin puntos ni guión: ");
        aux_identity = pedir_cedula();
        save_data = save_confirm();
        if(save_data == 'N' || save_data == 'n'){
            printf("\nSe han descartado los cambios.\n");
            getchar();
        }
        else{
            players[existe_jugador].nombre = aux_name;
            players[existe_jugador].apellido = aux_lastname;
            players[existe_jugador].fecha_nacimiento = aux_birthdate;
            players[existe_jugador].cedula = aux_identity;
            printf("\nSe han modificado los datos del jugador con éxito.\n");
            getchar();
        }
    }
    pausa();
}

void mostrar_cedula(id document){
    for(int i = 0; i < CI; i++){
        printf("%d", document.cedula[i]);
    }
}

void mostrar_palabra(word cadena){
    for(int i = 0; i < cadena.largo; i++){
        printf("%c", cadena.letra[i]);
    }
}

void player_list(player players[], int pos_players){
    int i;
    system("clear");
    printf("Listado de Jugadores\n\n");
    for(i = 0; i < pos_players; i++){
        if(players[i].status == 'A'){
            printf("Jugador %d", i+1);
            printf(" -> ");
            mostrar_cedula(players[i].cedula);
            printf(" -> ");
            mostrar_palabra(players[i].nombre);
            printf(" -> ");
            mostrar_palabra(players[i].apellido);
            printf(" -> ");
            mostrar_palabra(players[i].alias);
            printf("\n");
        }
    }
    if(pos_players == 0){
        printf("No hay jugadores registrados en el sistema aún.\n");
    }
        pausa();
}

void games_list_by_player(player players[], int pos_players, game partidas[], int pos_games){
    int i, existe_jugador, cant_alias = 0;
    word alias;
    system("clear");
    printf("Listado de partidas por jugador\n\n");
    if(pos_games == 0){
        printf("No hay partidas registradas en el sistema aún.\n");
    }
    else{
        printf("Ingresa el alias de un jugador: ");
        alias = pedir_palabra();
        existe_jugador = buscar_jugador(players, pos_players, alias);
        printf("\n");
        if(existe_jugador == -1){
            printf("No existe un jugador con el alias ingresado.\n");
        }
        else{
            for(i = 0; i < pos_games; i++){
                if(comparar_alias(partidas[i].aliasJ1, alias) == 0 || comparar_alias(partidas[i].aliasJ2, alias) == 0){
                    printf("Partida Nro: %d", i+1);
                    printf(" | Fecha: ");
                    mostrar_fecha(partidas[i].fecha_partida);
                    printf(" | J1: ");
                    mostrar_palabra(partidas[i].aliasJ1);
                    printf(" | J2: ");
                    mostrar_palabra(partidas[i].aliasJ2);
                    printf(" | Resultado: ");
                    mostrar_resultado(partidas[i].winsJ1, partidas[i].winsJ2);
                    printf("\n");
                    cant_alias++;
                }
            }

            if(cant_alias == 0){
                printf("El jugador ingresado no ha jugado ninguna partida.\n");
            }
        }
    }
    pausa();
}

int comparar_fecha(date fecha, date fecha_aux){
	if(fecha.anio == fecha_aux.anio){
		if(fecha.mes == fecha_aux.mes){
			if(fecha.dia == fecha_aux.dia){
				return 0;
			}
			else{
				return 1;
			}
		}
		else{
			return 1;
		}
	}
	else{
		return 1;
	}
}

void games_list_by_date(game partidas[], int pos_games){
    int i, cant_partidas = 0;
    date aux_date;
    system("clear");
    printf("Listado de partidas por fecha\n\n");
    if(pos_games == 0){
        printf("No hay partidas registradas en el sistema aún.\n");
    }
    else{
        printf("Ingresa una fecha: ");
        aux_date = pedir_fecha();
        printf("\n");

        for(i = 0; i < pos_games; i++){
            if(comparar_fecha(partidas[i].fecha_partida, aux_date) == 0){
                printf("Partida Nro: %d", i+1);
                printf(" | Fecha: ");
                mostrar_fecha(partidas[i].fecha_partida);
                printf(" | J1: ");
                mostrar_palabra(partidas[i].aliasJ1);
                printf(" | J2: ");
                mostrar_palabra(partidas[i].aliasJ2);
                printf(" | Resultado: ");
                mostrar_resultado(partidas[i].winsJ1, partidas[i].winsJ2);
                printf("\n");
                cant_partidas++;
            }
        }
        if(cant_partidas == 0){
            printf("No se disputó ningun encuentro en la fecha ingresada.\n");
        }
        getchar();
    }
    pausa();
}

void mostrar_fecha(date fecha){
    printf("%d-%d-%d", fecha.dia, fecha.mes, fecha.anio);
}

void mostrar_resultado(int winsJ1, int winsJ2){
    printf("%d-%d", winsJ1, winsJ2);
}

void games_list(game partidas[], int pos_games){
    int i;
    system("clear");
    printf("Listado de partidas\n\n");
    for(i = 0; i < pos_games; i++){
        printf("Partida Nro: %d", i+1);
        printf(" | Fecha: ");
        mostrar_fecha(partidas[i].fecha_partida);
        printf(" | J1: ");
        mostrar_palabra(partidas[i].aliasJ1);
        printf(" | J2: ");
        mostrar_palabra(partidas[i].aliasJ2);
        printf(" | Resultado: ");
        mostrar_resultado(partidas[i].winsJ1, partidas[i].winsJ2);
        printf("\n");
    }
    if(pos_games == 0){
        printf("No hay partidas registradas en el sistema aún.\n");
    }
    pausa();
}

int select_lvl(){
    int lvl = -1;
    system("clear");
    while(lvl != 1 && lvl != 2 && lvl != 3 && lvl != 0){
        printf("Dependiendo el nivel que elijas, serán las dimensiones del tablero a jugar.\n\n");
        printf("Opciones disponibles:\n");
        printf("  1. Principiante\n");
        printf("  2. Avanzado\n");
        printf("  3. Veterano\n");
        printf("  0. Volver al menú principal\n");
        printf("Ingresa una opción(0..3): ");
        scanf("%d", &lvl);
    }
    system("clear");
    return lvl;
}

void plantar_bosque(int dimensiones, char tablero[][dimensiones]){
    srand(time(NULL));
    int yrand, xrand;


    //Se inicializa el tablero con espacios en blanco en cada posición
    for (int linea=0; linea<dimensiones; linea++){
        for(int columna=0; columna<dimensiones; columna++){
            tablero[linea][columna] = ' ';
        }
    }

    //Posición inicial de los jugadores.
    tablero[dimensiones-1][0] = '1';
    tablero[0][dimensiones-1] = '2';

    //Posicionamiento de árboles
    for(int i = 0; i < dimensiones; i++){
        do{
        yrand = rand() % (dimensiones);
        xrand = rand() % (dimensiones);
        }
        while((yrand == dimensiones -2 && xrand == 0)||(yrand == 0 && xrand == dimensiones-2));
            if(tablero[yrand][xrand] != '1' && tablero[yrand][xrand] != '2' && tablero[yrand][xrand] != 'x'){
                tablero[yrand][xrand] = 'x';
            }
            else{
                i--;
            }
    }
}

void mostrar_bosque(int dimensiones, char tablero[][dimensiones]){
     int linea, columna;
        printf("     ");
        for(columna = 1; columna<=dimensiones; columna++){
            printf(" %c  ", columna+64);
        }
        printf("\n");
        for(linea=0; linea<dimensiones; linea++){
            printf("%d   ", linea+1);
            for(columna=0; columna<dimensiones; columna++){
                printf("| %c ", tablero[linea][columna]);
            }
            printf("|\n");
        }
}

void refrescar_tablero(int dimensiones, char tablero[][dimensiones]){
   int bloqueado = 2;
    do{
        printf("\n¿Hay algún jugador encerrado por árboles?\n");
        printf("  1. Si, generar nuevo bosque\n");
        printf("  2. No, continuar con el juego\n");
        printf("Ingresa una opción: ");
        scanf("%d", &bloqueado);
        if(bloqueado == 1){
            system("clear");
            plantar_bosque(dimensiones, tablero);
            mostrar_bosque(dimensiones, tablero);
        }
    }
    while(bloqueado != 2);
    system("clear");
}

int elegir_jugador_inicial(game partidas[], int pos_games){
    int player = 0;
    printf("Selecciona que jugador debe mover primero. \n");
    do{
        printf("Opciones:\n");
        printf("  1. ");
        mostrar_palabra(partidas[pos_games].aliasJ1);
        printf("\n  2. ");
        mostrar_palabra(partidas[pos_games].aliasJ2);
        printf("\nIngresa opción(1/2): ");
        scanf("%d", &player);
        if(player != 1 && player != 2){
            printf("Ingresa una opción válida\n");
        }
    }
    while(player != 1 && player != 2);
    return player;
}

char solicitar_direccion(){
    char direccion = ' ';
    printf("\n  w. Arriba\n");
    printf("  a. Izquierda\n");
    printf("  s. Abajo\n");
    printf("  d. Derecha\n");
    printf("Opción(w/a/s/d): ");
    do{
        scanf(" %c", &direccion);
        if(direccion!='w' && direccion!='a' && direccion!='s' && direccion!='d'){
            printf("Ingresa una opción válida: ");
        }
    }
    while(direccion!='w' && direccion!='a' && direccion!='s' && direccion!='d');
    return direccion;
}

void movimientosJ1(word aliasJ1, int dimensiones, char tablero[][dimensiones], int pos_jugadores[][2]){
    char direccion = ' ';
    int movimiento_invalido;
    int y_temp=0, x_temp=0;
    do{
        system("clear");
        mostrar_bosque(dimensiones, tablero);
        printf("\n¿En que dirección deseas moverte ");
        mostrar_palabra(aliasJ1);
        printf(" ?");
        direccion = solicitar_direccion();
        movimiento_invalido = 0;

        //pos_jugadores[2][2] = {{(dimensiones-1), 0}, {0, (dimensiones-1)}};
        y_temp = pos_jugadores[0][0];
        x_temp = pos_jugadores[0][1];

        switch(direccion){
            case 'w':
                pos_jugadores[0][0]--;
                break;
            case 'a':
                pos_jugadores[0][1]--;
                break;
            case 's':
                pos_jugadores[0][0]++;
                break;
            case 'd':
                pos_jugadores[0][1]++;
                break;
        }
        if((pos_jugadores[0][0]>=0) && (pos_jugadores[0][0]<dimensiones) && (pos_jugadores[0][1]>=0) && (pos_jugadores[0][1]<dimensiones)){
            if((tablero[pos_jugadores[0][0]][pos_jugadores[0][1]] != 'x') && (tablero[pos_jugadores[0][0]][pos_jugadores[0][1]]) != '2'){
                tablero[pos_jugadores[0][0]][pos_jugadores[0][1]] = '1';
                tablero[y_temp][x_temp] = ' ';
                system("clear");
                mostrar_bosque(dimensiones, tablero);
                mostrar_palabra(aliasJ1);
                printf(" se desplazó hacia la casilla: (%c, %d) \n", pos_jugadores[0][1]+65, pos_jugadores[0][0]+1);
            }
            else{
                pos_jugadores[0][0] = y_temp;
                pos_jugadores[0][1] = x_temp;
                printf("No puedes moverte a donde se encuentre un árbol o tu oponente, ingresa un movimiento válido.\n");
                movimiento_invalido=1;
                printf("\nPresiona ENTER para continuar.\n");
                getchar();
                getchar();
            }
        }
        else{
            pos_jugadores[0][0] = y_temp;
            pos_jugadores[0][1] = x_temp;
            printf("No puedes salir del bosque, ingresa un movimiento válido.\n");
            movimiento_invalido=1;
            printf("\nPresiona ENTER para continuar.\n");
            getchar();
            getchar();
        }
    }
    while(movimiento_invalido==1);
}

void movimientosJ2(word aliasJ2, int dimensiones, char tablero[][dimensiones], int pos_jugadores[][2]){
    char direccion;
    int y_temp=0, x_temp=0;
    int movimiento_invalido;

    do{
        system("clear");
        mostrar_bosque(dimensiones, tablero);
        printf("\n¿En que dirección deseas moverte ");
        mostrar_palabra(aliasJ2);
        printf(" ?");
        direccion = solicitar_direccion();
        movimiento_invalido = 0;

        //int pos_jugadores[2][2] = {{(dimensiones-1), 0}, {0, (dimensiones-1)}};
        y_temp = pos_jugadores[1][0];
        x_temp = pos_jugadores[1][1];

        switch(direccion){
            case 'w':
                pos_jugadores[1][0]--;
                break;
            case 'a':
                pos_jugadores[1][1]--;
                break;
            case 's':
                pos_jugadores[1][0]++;
                break;
            case 'd':
                pos_jugadores[1][1]++;
                break;
        }
        if((pos_jugadores[1][0]>=0) && (pos_jugadores[1][0]<dimensiones) && (pos_jugadores[1][1]>=0) && (pos_jugadores[1][1]<dimensiones)){
            if((tablero[pos_jugadores[1][0]][pos_jugadores[1][1]] != 'x') && (tablero[pos_jugadores[1][0]][pos_jugadores[1][1]] != '1')){
                tablero[pos_jugadores[1][0]][pos_jugadores[1][1]] = '2';
                tablero[y_temp][x_temp] = ' ';
                system("clear");
                mostrar_bosque(dimensiones, tablero);
                mostrar_palabra(aliasJ2);
                printf(" se desplazó hacia la casilla: (%c, %d) \n",pos_jugadores[1][1]+65, pos_jugadores[1][0]+1);
            }
            else {
                pos_jugadores[1][0] = y_temp;
                pos_jugadores[1][1] = x_temp;
                printf("No puedes moverte a donde se encuentre un árbol o tu oponente, ingresa un movimiento válido.\n");
                movimiento_invalido=1;
                printf("\nPresiona ENTER para continuar.\n");
                getchar();
                getchar();
            }
        }
        else{
            pos_jugadores[1][0] = y_temp;
            pos_jugadores[1][1] = x_temp;
            printf("No puedes salir del bosque, ingresa un movimiento válido.\n");
            movimiento_invalido=1;
            printf("\nPresiona ENTER para continuar.\n");
            getchar();
            getchar();
        }
    }
    while(movimiento_invalido==1);
}

int disparar_flecha(int jugador, word aliasJ1, word aliasJ2, int dimensiones, char tablero[][dimensiones], int pos_jugadores[][2]){
    char direccion = ' ';
    int pos_flecha[2][2];
    int flechazo;
    int mensaje = 0;
    int jugador_herido = 0;

    system("clear");
    mostrar_bosque(dimensiones, tablero);
    printf("\n¿En que dirección deseas disparar ");
    mostrar_palabra(aliasJ1);
    printf(" ?");
    direccion = solicitar_direccion();

    //Se iguala la posición de la flecha a la posición de los jugadores al momento de disparar
    pos_flecha[0][0] = pos_jugadores[0][0];//posición y de J1
    pos_flecha[0][1] = pos_jugadores[0][1];//posición x de J1
    pos_flecha[1][0] = pos_jugadores[1][0];//posición y de J2
    pos_flecha[1][1] = pos_jugadores[1][1];//posición x de J2

    switch (jugador){
        case 1: { //J1 dispara a J2
            for(flechazo = 0; flechazo < ALCANCEFLECHA; flechazo++){
                switch(direccion){
                    case 'w':
                        pos_flecha[0][0]--;
                        break;
                    case 'a':
                        pos_flecha[0][1]--;
                        break;
                    case 's':
                        pos_flecha[0][0]++;
                        break;
                    default:
                        pos_flecha[0][1]++;
                }
                if((pos_flecha[0][0]>=0) && (pos_flecha[0][0]<dimensiones) && (pos_flecha[0][1]>=0) && (pos_flecha[0][1]<dimensiones)){
                    if(tablero[pos_flecha[0][0]][pos_flecha[0][1]]=='x'){
                        mensaje = 1;
                        flechazo = ALCANCEFLECHA;
                    }
                    else if(tablero[pos_flecha[0][0]][pos_flecha[0][1]]=='2'){
                        mensaje = 4;
                        flechazo = ALCANCEFLECHA;
                    }
                    else if(flechazo == ALCANCEFLECHA-1){
                        if(tablero[pos_flecha[0][0]][pos_flecha[0][1]]==' '){
                            mensaje = 2;
                        }
                        else if(tablero[pos_flecha[0][0]][pos_flecha[0][1]]=='x'){
                            mensaje = 1;
                        }
                        else if(tablero[pos_flecha[0][0]][pos_flecha[0][1]]=='2'){
                            mensaje = 4;
                        }
                    }
                }
                else{
                    mensaje = 3;
                }
            }
        }
            break;
        default:{//J2 dispara a J1
            for(flechazo = 0; flechazo < ALCANCEFLECHA; flechazo++){
                switch(direccion){
                    case 'w':
                        pos_flecha[1][0]--;
                        break;
                    case 'a':
                        pos_flecha[1][1]--;
                        break;
                    case 's':
                        pos_flecha[1][0]++;
                        break;
                    default:
                        pos_flecha[1][1]++;
                }
                if((pos_flecha[1][0]>=0) && (pos_flecha[1][0]<dimensiones) && (pos_flecha[1][1]>=0) && (pos_flecha[1][1]<dimensiones)){
                    if(tablero[pos_flecha[1][0]][pos_flecha[1][1]]=='x'){
                        mensaje = 1;
                        flechazo = ALCANCEFLECHA;
                    }
                    else if(tablero[pos_flecha[1][0]][pos_flecha[1][1]]=='1'){
                        mensaje = 5;
                        flechazo = ALCANCEFLECHA;
                    }
                    else if(flechazo == ALCANCEFLECHA-1){
                        if(tablero[pos_flecha[1][0]][pos_flecha[1][1]]==' '){
                            mensaje = 2;
                        }
                        else if(tablero[pos_flecha[1][0]][pos_flecha[1][1]]=='x'){
                            mensaje = 1;
                        }
                        else if(tablero[pos_flecha[1][0]][pos_flecha[1][1]]=='1'){
                            mensaje = 5;
                        }
                    }
                }
                else{
                    mensaje = 3;
                }
            }
        }
    }
    if(mensaje==1){
        system("clear");
        mostrar_bosque(dimensiones, tablero);
        printf("\nLa flecha impactó contra un árbol.\n");
        jugador_herido = 0;
    }
    else if(mensaje==2){
        system("clear");
        mostrar_bosque(dimensiones, tablero);
        printf("\nEse fue un tiro deplorable, la flecha no impactó en ningún lado.\n");
        jugador_herido = 0;
    }
    else if(mensaje==3){
        system("clear");
        mostrar_bosque(dimensiones, tablero);
        printf("\nTendrías que afinar la puntería, ese disparo se salió del bosque.\n");
        jugador_herido = 0;
    }
    else if(mensaje==4){
        system("clear");
        printf("¡BOOM! La flecha le dio de lleno a ");
        mostrar_palabra(aliasJ2);
        printf("\n");
        jugador_herido = 2;
    }
    else if(mensaje==5){
        system("clear");
        printf("¡BOOM! La flecha le dio de lleno a ");
        mostrar_palabra(aliasJ1);
        printf("\n");
        jugador_herido = 1;
    }
    return jugador_herido;
}

void acciones_disponibles(int jugador, word aliasJ1, word aliasJ2, int dimensiones, char tablero[][dimensiones], int pos_jugadores[][2], int *jugador_herido){
    int accion = 0;
    while(accion!=1 && accion!=2 && accion!=3){
        printf("¿Que deseas hacer?\n");
        printf("  1. Moverte\n");
        printf("  2. Disparar\n");
        printf("  3. Rendirte\n");
        printf("Ingresa opción: ");
        scanf("%d", &accion);
        if(accion!=1 && accion!=2 && accion!=3){
            printf("Ingresa una opción válida.\n");
        }
    }

    switch(jugador){
        case 1:
            if(accion == 1){
                movimientosJ1(aliasJ1, dimensiones, tablero, pos_jugadores);
            }
            else if(accion == 2){
                *jugador_herido = disparar_flecha(jugador, aliasJ1, aliasJ2, dimensiones, tablero, pos_jugadores);
            }
            else{
                *jugador_herido = 6; //se rinde el jugador 1
            }

            break;
        default:
            if(accion == 1){
                movimientosJ2(aliasJ2, dimensiones, tablero, pos_jugadores);
            }
            else if(accion == 2){
                *jugador_herido = disparar_flecha(jugador, aliasJ1, aliasJ2, dimensiones, tablero, pos_jugadores);
            }
            else{
                *jugador_herido = 7; //se rinde el jugador 2
            }

    }
}

void jugar_turnos(int jugador, game partidas[], int pos_games, int dimensiones,char tablero[][dimensiones], int pos_jugadores[][2]){
    int jugador_herido = 0;
    while(jugador_herido == 0){
        if(jugador == 1){
            printf("Es el turno de ");
            mostrar_palabra(partidas[pos_games].aliasJ1);
            printf("(1)\n\n");
            acciones_disponibles(jugador, partidas[pos_games].aliasJ1, partidas[pos_games].aliasJ2, dimensiones, tablero, pos_jugadores, &jugador_herido);
            jugador=2;
        }
        else if(jugador == 2){
            printf("Es el turno de ");
            mostrar_palabra(partidas[pos_games].aliasJ2);
            printf("(2)\n\n");
            acciones_disponibles(jugador, partidas[pos_games].aliasJ1, partidas[pos_games].aliasJ2, dimensiones, tablero, pos_jugadores, &jugador_herido);
            jugador=1;
        }
    }

    if(jugador_herido == 2){
        printf("El ganador del turno es: ");
        mostrar_palabra(partidas[pos_games].aliasJ1);
        printf("\n");
        partidas[pos_games].winsJ1 += 1;
    }
    else if(jugador_herido == 1){
        printf("El ganador del turno es: ");
        mostrar_palabra(partidas[pos_games].aliasJ2);
        printf("\n");
        partidas[pos_games].winsJ2 += 1;
    }
    else if(jugador_herido == 6){ //rendición de jugador 1
        system("clear");
        mostrar_palabra(partidas[pos_games].aliasJ1);
        printf(" se ha rendido\n");
        partidas[pos_games].winsJ2 = 2;
    }

    else if(jugador_herido == 7){ //rendición de jugador 2
        system("clear");
        mostrar_palabra(partidas[pos_games].aliasJ2);
        printf(" se ha rendido\n");
        partidas[pos_games].winsJ1 = 2;
    }

}

void mostrar_marcador(game partidas[], int pos_games){
    printf("\n\n");
    mostrar_palabra(partidas[pos_games].aliasJ1);
    printf(": %d",partidas[pos_games].winsJ1);
    printf("\n");
    mostrar_palabra(partidas[pos_games].aliasJ2);
    printf(": %d",partidas[pos_games].winsJ2);
    printf("\n\n\nPresiona ENTER para continuar.");
    getchar();
    getchar();
    system("clear");
}

void quien_gana(game partidas[], int pos_games){
    if(partidas[pos_games].winsJ1 == 2){
        printf("¡");
        mostrar_palabra(partidas[pos_games].aliasJ1);
        printf(" se lleva la victoria de la partida!\n");
    }
    else if(partidas[pos_games].winsJ2 == 2){
        printf("¡");
        mostrar_palabra(partidas[pos_games].aliasJ2);
        printf(" se lleva la victoria de la partida!\n");
    }

    printf("\n        ╔═══════════╗");
    printf("\n        ║ GAME OVER ║");
    printf("\n        ╚═══════════╝\n");
    printf("\nPresiona ENTER para continuar. ");
    getchar();
    system("clear");

}

void elegir_alias_game(player jugadores[], int pos_players, game partidas[], int pos_games, int *jugadores_cargados){
    word alias_aux;
    int existe_jugador;
    system("clear");

    printf("Indica el alias del jugador 1: ");
    alias_aux = pedir_palabra();
    existe_jugador = buscar_jugador(jugadores, pos_players, alias_aux);
    if(existe_jugador == -1){
        printf("No existe un jugador con el alias ingresado.\n");
    }
    else{
        if(jugadores[existe_jugador].status == 'I'){
            printf("El jugador seleccionado no está disponible.\n");
        }
        else{
            partidas[pos_games].aliasJ1 = alias_aux;
            *jugadores_cargados = 1;
        }
    }

    if(*jugadores_cargados == 1){
        printf("Indica el alias del jugador 2: ");
        alias_aux = pedir_palabra();
        existe_jugador = buscar_jugador(jugadores, pos_players, alias_aux);
        if(existe_jugador == -1){
            printf("No existe un jugador con el alias ingresado.\n");
        }
        else{
            if(jugadores[existe_jugador].status == 'I'){
                printf("El jugador seleccionado no está disponible.\n");
            }
            else{
                partidas[pos_games].aliasJ2 = alias_aux;
                *jugadores_cargados = 2;
            }
        }
    }
}

void jugar_partida(player jugadores[], int pos_players, game partidas[], int *pos_games){
    int dimensiones = 0;
    int nivel = 0;
    int jugador = 0;
    int jugadores_cargados = 0;
    partidas[*pos_games].winsJ1 = 0;
    partidas[*pos_games].winsJ2 = 0;

    elegir_alias_game(jugadores, pos_players, partidas, *pos_games, &jugadores_cargados);
    if(jugadores_cargados == 2){
        nivel = select_lvl();   //el retorno de la función queda almacenado en la variable nivel
        switch(nivel){  //Con base en el nivel elegido, se determina las dimensiones del bosque a jugar
            case 1:
                dimensiones = PRINCIPIANTE;
                break;
            case 2:
                dimensiones = AVANZADO;
                break;
            case 3:
                dimensiones = VETERANO;
                break;
        }
        if(nivel != 0){
            char tablero[dimensiones][dimensiones];//se define una matriz con las dimensiones del nivel elegido

            printf("¿Que día es hoy? Ingresa la fecha con este formato(dd-mm-aaaa): ");
            partidas[*pos_games].fecha_partida = pedir_fecha();
            pausa();
            getchar();
            system("clear");

            plantar_bosque(dimensiones, tablero);
            mostrar_bosque(dimensiones, tablero);
            //si se genera un bosque que impida a los jugadores encontrarse, se puede refrescar el tablero
            refrescar_tablero(dimensiones, tablero);

            //el usuario selecciona que jugador mueve primero en cada turno
            jugador = elegir_jugador_inicial(partidas, *pos_games);

            //Desarrollo de la partida
            while(partidas[*pos_games].winsJ1 < 2 && partidas[*pos_games].winsJ2 < 2){ //contador de rounds
                system("clear");
                mostrar_bosque(dimensiones, tablero);
                //se guardan las posiciones iniciales de los jugadores en una matriz de 2x2
                int pos_jugadores[2][2] = {{(dimensiones-1), 0}, {0, (dimensiones-1)}};
                jugar_turnos(jugador, partidas, *pos_games, dimensiones, tablero, pos_jugadores);
                mostrar_marcador(partidas, *pos_games);
                if(jugador == 1){
                    jugador = 2;
                }
                else{
                    jugador = 1;
                }
                if(partidas[*pos_games].winsJ1 < 2 && partidas[*pos_games].winsJ2 < 2){
                    plantar_bosque(dimensiones, tablero);   //se arma el bosque con los jugadores y sus árboles
                    mostrar_bosque(dimensiones, tablero);
                    //si se genera un bosque que impida a los jugadores encontrarse, se puede refrescar el tablero
                    refrescar_tablero(dimensiones, tablero);
                }
            }//si alguno de los dos jugadores tiene 2 victorias, se termina la partida
            quien_gana(partidas, *pos_games);
            *pos_games += 1; //al finalizar la partida, se incrementa el contador de partidas jugadas
        }
    }
    else{
        printf("\n*SUGERENCIA*: Revisa la lista de jugadores activos en el sistema.\n");
        pausa();
        system("clear");
    }
}

void despedida(){
    printf("Has decidido salir\n");
    printf("\nGracias por jugar \"Arqueros en el bosque\".\n");
}

void pausa(){
    printf("\nPresiona ENTER para continuar.");
    getchar();
}
