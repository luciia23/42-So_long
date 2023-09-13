#include "game.h"

int start(t_game *game, int argc, char *argv[])
{
    if (!valid_file(argc, argv[1]))
        return (0);
    map_init(game, argv[1]);
    //inicializar todo
    //map_init haciendo los checks
    //comenzar juego --> game_init
            // mlx_init
            //new_window
    if (!valid_map(game->map))
        return (0);
    return (1);
}

int main(int argc, char *argv[])
{
    t_game  game;

    if (!start(&game, agrc, argv))
        return (0);
    return (0);
}