#include "game.h"

void    collection_init(t_game *game)
{
    game->collection.bg_down = new_file_img(BG_IMG, game->mlx);
    game->collection.bg_total_black = new_img(960, 832, game->mlx);
    game->collection.total_bg = new_file_img(BG_TOTAL, game->mlx);
    game->collection.won = new_file_img(WON_IMG, game->mlx);
    game->collection.game_over = new_file_img(FAILED_IMG, game->mlx);
    game->collection.restart = new_file_img(RESTART_IMG, game->mlx);
    game->collection.exit = new_file_img(EXIT, game->mlx);
    game->collection.arrow_up = new_file_img(ARROW_IMG, game->mlx);
    game->collection.arrow = new_file_img(ARROW_IMG, game->mlx);
    game->collection.arrow_down = new_file_img(ARROW_IMG, game->mlx);
    game->collection.logo = new_file_img(LOGO_IMG, game->mlx);
    game->collection.player_one = new_sprite("juan", WALK_FRONT, game->mlx);
    game->collection.enemy1 = new_sprite("pepe", MOVE_BACK, game->mlx);
    game->collection.enemy2 = new_sprite("cuco2", MOVE_BACK, game->mlx);
    game->collection.coin = new_sprite("coin", COIN_IMG, game->mlx);
    game->collection.score_font = load_score_font(game);

      //ISLAND
    game->collection.island.bottom = new_file_img(BORDER_BOTTOM_IMG, game->mlx);
    game->collection.island.top = new_file_img(BORDER_TOP_IMG, game->mlx);
    game->collection.island.left = new_file_img(BORDER_LEFT_IMG, game->mlx);
    game->collection.island.right = new_file_img(BORDER_RIGHT_IMG, game->mlx);
	game->collection.island.k_curve = new_file_img(BORDER_DOWNLEFT_IMG, game->mlx);
	game->collection.island.w_curve = new_file_img(BORDER_UPLEFT_IMG, game->mlx);
	game->collection.island.a_curve = new_file_img(BORDER_UPRIGHT_IMG, game->mlx);
	game->collection.island.j_curve = new_file_img(BORDER_DOWNRIGHT_IMG, game->mlx);
    game->collection.island.sand = new_file_img(SAND_IMG, game->mlx);
    game->collection.island.water = new_file_img(WATER_IMG, game->mlx);
    game->collection.island.star = new_file_img(STAR_IMG, game->mlx);
    game->collection.island.boat = new_file_img(BOAT_IMG, game->mlx);

    //FILD
    game->collection.field.bush = new_file_img(WALL_IMG, game->mlx);
    game->collection.field.floor = new_file_img(FLOOR_IMG, game->mlx);
    game->collection.field.flower_blue = new_file_img(FLOWER_BLUE_IMG, game->mlx);
    game->collection.field.flower_red = new_file_img(FLOWER_RED_IMG, game->mlx);
    game->collection.field.flower_star = new_file_img(FLOWER_STAR_IMG, game->mlx);
    game->collection.field.ladder = new_file_img(EXIT_IMG, game->mlx);
    game->collection.field.rock = new_file_img(ROCK_IMG, game->mlx);

    //FOREST
    game->collection.forest.floor = new_file_img(FLOOR_FOREST_IMG, game->mlx);
    game->collection.forest.tree = new_file_img(TREE_IMG, game->mlx);
    game->collection.forest.mushroom = new_file_img(SETA_IMG, game->mlx);
    game->collection.forest.rock = new_file_img(ROCK_IMG, game->mlx);
    game->collection.forest.ladder = new_file_img(EXIT_IMG, game->mlx);
    
    //CASTLE
    game->collection.castle.floor = new_file_img(FLOOR_CASTLE_IMG, game->mlx);
    game->collection.castle.wall_top = new_file_img(WALL_TOP_IMG, game->mlx);
    game->collection.castle.wall_bottom = new_file_img(WALL_BOTTOM_IMG, game->mlx);
    game->collection.castle.infill_wall = new_file_img(INFILL_WALL_IMG, game->mlx);
    game->collection.castle.hatch = new_file_img(HATCH_IMG, game->mlx);
    game->collection.castle.ladder = new_file_img(LADDER_IMG, game->mlx);
    game->collection.castle.torch = new_file_img(TORCH_IMG, game->mlx);
    game->collection.castle.candle = new_file_img(CANDLE_IMG, game->mlx);
}

void init_slice(t_game *game)
{   /*                             SLICE PLAYER                                 */
    //PARPADEO QUIETO
    sprite_slice slice = (sprite_slice) {0, 0, 64, 64};
    sprite_slice moneda = (sprite_slice) {0, 0, 32, 32};
    game->player.flincker_front = new_sprite("STOP", FLINCKER_FRONT, game->mlx);
    ft_lstadd_back(&game->player.flincker_front.animations, ft_lstnew(slice_sprite(game->player.flincker_front, slice, 3, 3, PLAYER, game->mlx)));
    //ANDAR HACIA ADELANTE
    game->player.walk_front = new_sprite("WALK_DOWN", WALK_FRONT, game->mlx);
    ft_lstadd_back(&game->player.walk_front.animations, ft_lstnew(slice_sprite(game->player.walk_front, slice, 7, 0, PLAYER, game->mlx)));
    //ANDAR HACIA ATRAS
    game->player.walk_back = new_sprite("WALK_UP", WALK_BACK, game->mlx);
    ft_lstadd_back(&game->player.walk_back.animations, ft_lstnew(slice_sprite(game->player.walk_back, slice, 7, 0, PLAYER,game->mlx)));
    //ANDAR HACIA LA DERECHA
    game->player.walk_right = new_sprite("WALK_RIGTH", WALK_RIGHT, game->mlx);
    ft_lstadd_back(&game->player.walk_right.animations, ft_lstnew(slice_sprite(game->player.walk_right, slice, 7, 0, PLAYER, game->mlx)));
    //ANDAR HACIA LA IZQUIERDA
    game->player.walk_left = new_sprite("WALK_LEFT", WALK_LEFT, game->mlx);
    ft_lstadd_back(&game->player.walk_left.animations, ft_lstnew(slice_sprite(game->player.walk_left, slice, 7, 0, PLAYER, game->mlx)));

    /*                             SLICE CUCO                                  */
    //MOVIMIENTO HACIA ADELANTE
    game->enemy.walk_front = new_sprite("MOVE_FRONT", MOVE_FRONT, game->mlx);
    ft_lstadd_back(&game->enemy.walk_front.animations, ft_lstnew(slice_sprite(game->enemy.walk_front, slice, 6, 0, ENEMY, game->mlx)));
    //MOVIMIENTO HACIA ATRAS
    game->enemy.walk_back = new_sprite("MOVE_BACK", MOVE_BACK, game->mlx);
    ft_lstadd_back(&game->enemy.walk_back.animations, ft_lstnew(slice_sprite(game->enemy.walk_back, slice, 6, 0, ENEMY, game->mlx)));
    //MOVIMIENTO A LA DERECHA
    game->enemy.walk_right = new_sprite("MOVE_RIGHT", MOVE_RIGHT, game->mlx);
    ft_lstadd_back(&game->enemy.walk_right.animations, ft_lstnew(slice_sprite(game->enemy.walk_right, slice, 6, 0, ENEMY, game->mlx)));
    //MOVIMIENTO A LA IZQUIERDA
    game->enemy.walk_left = new_sprite("MOVE_LEFT", MOVE_LEFT, game->mlx);
    ft_lstadd_back(&game->enemy.walk_left.animations, ft_lstnew(slice_sprite(game->enemy.walk_left, slice, 6, 0, ENEMY, game->mlx)));
    /*                              MONEDA                                      */
    ft_lstadd_back(&game->collection.coin.animations, ft_lstnew(slice_sprite(game->collection.coin, moneda, 6, 0, OBJ, game->mlx)));
}

void    search_sprite(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.size.y)
    {
        j = 0;
        while (game->map.coords[i][j])
        {
            if (game->map.coords[i][j] == 'P')
            {
                game->collection.player_one.pos.x = j * TILE_SIZE;
                game->collection.player_one.pos.y = i * TILE_SIZE;
            }
            j++;
        }
        i++;
    }
}

void    search_enemy(t_game *game) {
    int i;
    int j;

    i = 0;
    while (i < game->map.size.y)
    {
        j = 0;
        while (game->map.coords[i][j])
        {
            if (game->map.coords[i][j] == 'D')
            {
                game->collection.enemy1.pos.x = j * TILE_SIZE;
                game->collection.enemy1.pos.y = i * TILE_SIZE;
            }
            j++;
        }
        i++;
    }
}

void    search_enemy2(t_game *game) {
    int i;
    int j;

    i = 0;
    while (i < game->map.size.y)
    {
        j = 0;
        while (game->map.coords[i][j])
        {
            if (game->map.coords[i][j] == 'd')
            {
                game->collection.enemy2.pos.x = j * TILE_SIZE;
                game->collection.enemy2.pos.y = i * TILE_SIZE;
            }
            j++;
        }
        i++;
    }
}