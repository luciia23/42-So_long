# include "game.h"

int    error(char *msg)
{
    printf("\033[0;31m" " Error\n    %s\n" "\033[0m", msg);
    return (0);
}