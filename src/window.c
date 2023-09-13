# include "game.h"

int ft_close()
{
    exit(0);
}

t_window    ft_new_window(void *mlx, int width, int height, char *title)
{
    t_window    window = {0};
    
    window.win = mlx_new_window(mlx, width, height, title);
    mlx_hook(window.win, 17, 0, ft_close, 0);
    return (window);
}