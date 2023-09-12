#include "game.h"

int start(t_game *game, int argc, char *argv[])
{
    if (argc == 1)
        error("mal");
    if (argc > 2)
        error("only the first file will be used");//print warning
    //check extension
    map_init(game, argv[1]);
    //inicializar todo
    //map_init haciendo los checks
    //comenzar juego --> game_init
            // mlx_init
            //new_window
    return (0);
}

int main(int argc, char *argv[])
{
    t_game  game;

    if (!start(&game, agrc, argv))
        return (0);
    return (0);
}