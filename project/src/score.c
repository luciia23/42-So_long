#include "game.h"

void    free_score(t_game *g)
{
	mlx_destroy_image(g->mlx, g->collection.score_font.zero.img_ptr);
	mlx_destroy_image(g->mlx, g->collection.score_font.one.img_ptr);
	mlx_destroy_image(g->mlx, g->collection.score_font.two.img_ptr);
	mlx_destroy_image(g->mlx, g->collection.score_font.three.img_ptr);
	mlx_destroy_image(g->mlx, g->collection.score_font.four.img_ptr);
	mlx_destroy_image(g->mlx, g->collection.score_font.five.img_ptr);
	mlx_destroy_image(g->mlx, g->collection.score_font.six.img_ptr);
	mlx_destroy_image(g->mlx, g->collection.score_font.seven.img_ptr);
	mlx_destroy_image(g->mlx, g->collection.score_font.eight.img_ptr);
	mlx_destroy_image(g->mlx, g->collection.score_font.nine.img_ptr);
}

t_font	load_score_font(t_game *game)
{    
	game->collection.score_font.zero = new_file_img(TEXT_NUMBER_0, game->mlx);
	game->collection.score_font.one = new_file_img(TEXT_NUMBER_1, game->mlx);
	game->collection.score_font.two = new_file_img(TEXT_NUMBER_2, game->mlx);
	game->collection.score_font.three = new_file_img(TEXT_NUMBER_3, game->mlx);
	game->collection.score_font.four = new_file_img(TEXT_NUMBER_4, game->mlx);
	game->collection.score_font.five = new_file_img(TEXT_NUMBER_5, game->mlx);
	game->collection.score_font.six = new_file_img(TEXT_NUMBER_6, game->mlx);
	game->collection.score_font.seven = new_file_img(TEXT_NUMBER_7, game->mlx);
	game->collection.score_font.eight = new_file_img(TEXT_NUMBER_8, game->mlx);
	game->collection.score_font.nine = new_file_img(TEXT_NUMBER_9, game->mlx);
	return(game->collection.score_font);
}

void    put_font(t_game *game, int digit, int x, int y)
{
    t_image font;

    font.img_ptr = NULL;
    if (digit == 0)
        font = game->collection.score_font.zero;
    if (digit == 1)
        font = game->collection.score_font.one;
    if (digit == 2)
        font = game->collection.score_font.two;
    if (digit == 3)
        font = game->collection.score_font.three;
    if (digit == 4)
        font = game->collection.score_font.four;
    if (digit == 5)
        font = game->collection.score_font.five;
    if (digit == 6)
        font = game->collection.score_font.six;
    if (digit == 7)
        font = game->collection.score_font.seven;
    if (digit == 8)
        font = game->collection.score_font.eight;
    if (digit == 9)
        font = game->collection.score_font.nine;
    put_img_to_img(game->collection.bg_down, font,  x, y);
}

void    update_score(t_game *game)
{
    int x = 264;
    int y = 40;
    int i;
    int score;
    int digit;

    i = 0;
    score = game->collec;
    while (i < 4)
    {
        digit = score % 10;
        score /= 10;
        put_font(game, digit, x, y);
        i++;
        x -= TILE_SIZE;
    }
}