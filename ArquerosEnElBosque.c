//Trabajo de laboratorio realizado por Alexis Velázquez y Cristian González
//Estudiantes de tecnólogo en informática de UTEC.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"
#include "functions.c"

//Programa principal
int main()
{
    int opcion = -1;
    int opt_users = 0;
    int opt_queries = 0;
    int pos_players = 0;
    player players[JUGADORES];
    int pos_games = 0;
    game partidas[GAMES];

    printf("Bienvenido al juego: \"Arqueros en el bosque\". \nEsperamos que disfrutes.\n\n");
    while(opcion != 4){
        opcion = opciones_menu();
        while(opcion == 1){  //Gestionar usuario
            opt_users = opciones_usuarios();
            if(opt_users == 1){  //Alta de jugador
                getchar();  //absorbe salto de linea de la selección de opción en menú
                registrar_jugador(players, &pos_players);
            }

            else if(opt_users == 2){  //Baja de jugador
                getchar();
                baja_jugador(players, pos_players);
            }

            else if(opt_users == 3){  //Modificar jugador
                getchar();
                modificar_jugador(players, pos_players);
            }

            else if(opt_users == 0){  //Volver al menú principal
                opcion = 0;
            }
        }

        while(opcion == 2){  //Consultas
            opt_queries = opciones_consultas();
            if(opt_queries == 1){  //Listado de jugadores
                getchar();
                player_list(players, pos_players);
            }

            else if(opt_queries == 2){  //Listado de todas las partidas
                getchar();
                games_list(partidas, pos_games);
            }

            else if(opt_queries == 3){  //Listado de partidas por jugador
                getchar();
                games_list_by_player(players, pos_players, partidas, pos_games);
            }

            else if(opt_queries == 4){  //Listado de partidas por fecha
                getchar();
                games_list_by_date(partidas, pos_games);
            }

            else if(opt_queries == 0){  //Volver al menú principal
                opcion = 0;
            }
        }

        if(opcion == 3){  //desarrollo del juego
            getchar();
            jugar_partida(players, pos_players, partidas, &pos_games);
        }

        else if(opcion == 4){  //Terminar programa
            despedida();
        }
    }
    return 0;
}
