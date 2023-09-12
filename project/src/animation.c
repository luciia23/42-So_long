# include "game.h"
# include <sys/time.h>
//Variables globales la "x" y la "y" las utilizamos para el movimiento de link.
//Variables globales la "i" y la "j" las utilizamos para el movimiento de cuco
int x, y, j, i, k, l;

void	update_directions(t_game *game, enum directions d, int v)
{
	if (d == EAST)
	{
		game->directions.east = v;
		game->moving = v;
	}

	if (d == WEST)
	{
		game->directions.west = v;
		game->moving = v;
	}

	if (d == UP)
	{
		game->directions.up = v;
		game->moving = v;
	}

	if (d == DOWN)
	{
		game->directions.down = v;
		game->moving = v;
	}
}

void	update_player(t_game *game, int y, int x, enum directions d) {
	if (game->map.coords[y][x] == '1' || game->map.coords[y][x] == 'T' || game->map.coords[y][x] == '2' || game->map.coords[y][x] == '3' )
		{
			game->collection.player_one.pos.z = 0;
			game->moving = 0;
		}
        else if(game->map.coords[y][x] == 'E' && game->collec == game->map.total_collec)
        {
            if (game->current_map < NUM_MAPS - 1)
            {
                game->current_map++;	
                game->map = game->maps[game->current_map];
				search_sprite(game);
                search_enemy(game);
				search_enemy2(game);
				game->enemy.move1 = 4;
				game->moving_enemy1 = 0;
				game->enemy.move2 = 4;
				game->moving_enemy2 = 0;
                game->collec = 0;
            }
            else
            {
				game->options.end_won = 1;
				togglePlay();
				playSound(game->music.victory_sound, &game->vars_sound);
				mlx_loop_hook(game->mlx, game_over, game);
            }
        }
		else if (((game->collection.enemy1.pos.x / 64) == (game->collection.player_one.pos.x / 64)
		&& (game->collection.enemy1.pos.y / 64) == (game->collection.player_one.pos.y / 64)) || 
		((game->collection.enemy2.pos.x / 64) == (game->collection.player_one.pos.x / 64)
		&& (game->collection.enemy2.pos.y / 64) == (game->collection.player_one.pos.y / 64)))
		{
			game->options.end_failed = 1;
			togglePlay();
			playSound(game->music.game_over_sound, &game->vars_sound);
			mlx_loop_hook(game->mlx, game_over, game);
		}
		else if (game->map.coords[y][x] == 'C')
		{
			game->collec++;
			playSound(game->music.coin_sound, &game->vars_sound);
			if (game->collec == game->map.total_collec)
				playSound(game->music.door_sound, &game->vars_sound);
			game->map.coords[y][x] = '0';
			update_directions(game, d, 1);
		}
        else
			update_directions(game, d, 1);
}

void	update_enemies(t_game *game, int j, int i, int k) {
	if (k == 0) {
		if (game->map.coords[j][i] == '1' || game->map.coords[j][i] == '2' || game->map.coords[j][i] == '3' 
		|| game->map.coords[j][i] == 'E' || game->map.coords[j][i] == 'T' || game->map.coords[j][i] == 'd')
		{
			game->collection.enemy1.pos.z = 0;
			game->moving_enemy1 = 0;
			game->enemy.move1 = 4;
		}
		else
			game->moving_enemy1 = 1;
	} else if (k == 1) {
		if (game->map.coords[j][i] == '1' || game->map.coords[j][i] == '2' || game->map.coords[j][i] == '3'  
		|| game->map.coords[j][i] == 'E' || game->map.coords[j][i] == 'T' || game->map.coords[j][i] == 'd')
		{
			game->collection.enemy2.pos.z = 0;
			game->moving_enemy2 = 0;
			game->enemy.move2 = 4;
		}
		else if (((game->collection.enemy2.pos.x / 64) == (game->collection.player_one.pos.x / 64)
		&& (game->collection.enemy2.pos.y / 64) == (game->collection.player_one.pos.y / 64)))
		{
			game->options.end_failed = 1;
			togglePlay();
			playSound(game->music.game_over_sound, &game->vars_sound);
			mlx_loop_hook(game->mlx, game_over, game);
		}
		else
			game->moving_enemy2 = 1;
	}
}

void update_animation(void * ptr1, void * ptr2, void * ptr3, void * ptr4, void * ptr5) {
	t_image 	*img1, *img2, *img3, *moneda;
	t_game 		*game;
	t_animation	*a_player, *a_enemy, *a_moneda, *a_enemy2;
	unsigned int en1x, en1y, en2x, en2y;

	game = (t_game *)ptr5;
	a_player = (t_animation *)ptr1;
	a_enemy = (t_animation *)ptr2;
	a_moneda = (t_animation *) ptr3;
	a_enemy2 = (t_animation *) ptr4;
	en1x = game->collection.enemy1.pos.x - game->collection.player_one.pos.x;
	en1y = game->collection.enemy1.pos.y - game->collection.player_one.pos.y;
	en2x = game->collection.enemy2.pos.x - game->collection.player_one.pos.x;
	en2y = game->collection.enemy2.pos.y - game->collection.player_one.pos.y;
	/*					MONEDA					*/
	if (!a_moneda)
		return ;
	if (a_moneda->_tmp_delay++ == a_moneda->delay) {
		a_moneda->_tmp_delay = 0;
		a_moneda->current_frame_num++;
		a_moneda->current_frame_num %= ft_lstsize(a_moneda->frames);
	}
	moneda = (t_image *)ft_lstget(a_moneda->frames, a_moneda->current_frame_num)->content;
	draw_map(game, moneda);
	if(game->collection.player_one.pos.z == 0 && game->actions.key_right && game->moving == 0){
		game->collection.player_one.pos.z = game->collection.player_one.pos.x + 64;
		x = game->collection.player_one.pos.x / 64;
		y = game->collection.player_one.pos.y / 64;
		update_player(game, y, x + 1, EAST);
	}
	if (game->collection.player_one.pos.z == 0 && game->actions.key_left && game->moving == 0) {
		game->collection.player_one.pos.z = game->collection.player_one.pos.x - 64;
		x = game->collection.player_one.pos.x / 64;
		y = game->collection.player_one.pos.y / 64;
		update_player(game, y, x - 1, WEST);
	}
	if (game->collection.player_one.pos.z == 0 && game->actions.key_up && game->moving == 0) {
		game->collection.player_one.pos.z = game->collection.player_one.pos.y - 64;
		x = game->collection.player_one.pos.x / 64;
		y = game->collection.player_one.pos.y / 64;
		update_player(game, y - 1, x, UP);
	}
	if (game->collection.player_one.pos.z == 0 && game->actions.key_down && game->moving == 0) {
		game->collection.player_one.pos.z = game->collection.player_one.pos.y + 64;
		x = game->collection.player_one.pos.x / 64;
		y = game->collection.player_one.pos.y / 64;
		update_player(game, y + 1, x, DOWN);
	}
		
	if (!a_player)
		return ;
	if (a_player->_tmp_delay++ == a_player->delay) {
		a_player->_tmp_delay = 0;
		a_player->current_frame_num++;
		a_player->current_frame_num %= ft_lstsize(a_player->frames);
	}

	if (((game->collection.enemy1.pos.x / 64) == (game->collection.player_one.pos.x / 64)
		&& (game->collection.enemy1.pos.y / 64) == (game->collection.player_one.pos.y / 64)) || 
		((game->collection.enemy2.pos.x / 64) == (game->collection.player_one.pos.x / 64)
		&& (game->collection.enemy2.pos.y / 64) == (game->collection.player_one.pos.y / 64)))
		{
			game->options.end_failed = 1;
			togglePlay();
			playSound(game->music.game_over_sound, &game->vars_sound);
			mlx_loop_hook(game->mlx, game_over, game);
		}

	/*						PLAYER						*/
	img1 = (t_image *)ft_lstget(a_player->frames, a_player->current_frame_num)->content;
	if (game->moving == 1 && game->collection.player_one.pos.x < game->collection.player_one.pos.z && game->directions.east == 1)
	{
		game->collection.player_one.pos.x += 16;
		if (game->collection.player_one.pos.x == game->collection.player_one.pos.z)
		{
			game->collection.player_one.pos.z = 0;
			game->moving = 0;
			game->directions.east = 0;
		}
	}
	if (game->moving == 1 && game->collection.player_one.pos.y < game->collection.player_one.pos.z && game->directions.down == 1) {
		game->collection.player_one.pos.y += 16;
		if (game->collection.player_one.pos.y == game->collection.player_one.pos.z)
		{
			game->collection.player_one.pos.z = 0;
			game->moving = 0;
			game->directions.down = 0;
		}
	}
	if (game->moving == 1 && game->collection.player_one.pos.x > game->collection.player_one.pos.z && game->directions.west == 1) {
		game->collection.player_one.pos.x -= 16;
		if (game->collection.player_one.pos.x == game->collection.player_one.pos.z)
		{
			game->collection.player_one.pos.z = 0;
			game->moving = 0;
			game->directions.west = 0;
		}
	}
	if (game->moving == 1 && game->collection.player_one.pos.y > game->collection.player_one.pos.z && game->directions.up == 1) {
		game->collection.player_one.pos.y -= 16;
		if (game->collection.player_one.pos.y == game->collection.player_one.pos.z)
		{
			game->collection.player_one.pos.z = 0;
			game->moving = 0;
			game->directions.up = 0;
		}
	}
	/*						ENEMY *1					*/
	if (game->enemy.move1 == 0 && game->moving_enemy1 == 0)
	{
		game->collection.enemy1.pos.z = game->collection.enemy1.pos.x + 64;
		i = game->collection.enemy1.pos.x / TILE_SIZE;
		j = game->collection.enemy1.pos.y / TILE_SIZE;
		update_enemies(game, j, i + 1, 0);
	}
	if (game->enemy.move1 == 1 && game->moving_enemy1 == 0)
	{
		game->collection.enemy1.pos.z = game->collection.enemy1.pos.x - 64;
		i = game->collection.enemy1.pos.x / TILE_SIZE;
		j = game->collection.enemy1.pos.y / TILE_SIZE;
		update_enemies(game, j, i - 1, 0);
	}
	if (game->enemy.move1 == 2 && game->moving_enemy1 == 0)
	{
		game->collection.enemy1.pos.z = game->collection.enemy1.pos.y + 64;
		i = game->collection.enemy1.pos.x / TILE_SIZE;
		j = game->collection.enemy1.pos.y / TILE_SIZE;
		update_enemies(game, j + 1, i, 0);
	}
	if (game->enemy.move1 == 3 && game->moving_enemy1 == 0)
	{
		game->collection.enemy1.pos.z = game->collection.enemy1.pos.y - 64;
		i = game->collection.enemy1.pos.x / TILE_SIZE;
		j = game->collection.enemy1.pos.y / TILE_SIZE;
		update_enemies(game, j - 1, i, 0);
	}
	if (!a_enemy)
		return ;
	if (a_enemy->_tmp_delay++ == a_enemy->delay) {
		a_enemy->_tmp_delay = 0;
		a_enemy->current_frame_num++;
		a_enemy->current_frame_num %= ft_lstsize(a_enemy->frames);
	}
	img2 = (t_image *)ft_lstget(a_enemy->frames, a_enemy->current_frame_num)->content;
	if (game->enemy.move1 == 0 && game->moving_enemy1 == 1)
	{
		game->collection.enemy1.pos.x += 8;
		if (game->collection.enemy1.pos.x == game->collection.enemy1.pos.z)
		{
			game->collection.enemy1.pos.z = 0;
			game->moving_enemy1 = 0;
			game->enemy.move1 = 4;
		}
	}
	if (game->enemy.move1 == 1 && game->moving_enemy1 == 1)
	{
		game->collection.enemy1.pos.x -= 8;
		if (game->collection.enemy1.pos.x == game->collection.enemy1.pos.z)
		{
			game->collection.enemy1.pos.z = 0;
			game->moving_enemy1 = 0;
			game->enemy.move1 = 4;
		}
	}
	if (game->enemy.move1 == 2 && game->moving_enemy1 == 1)
	{
		game->collection.enemy1.pos.y += 8;
		if (game->collection.enemy1.pos.y == game->collection.enemy1.pos.z)
		{
			game->collection.enemy1.pos.z = 0;
			game->moving_enemy1 = 0;
			game->enemy.move1 = 4;
		}
	}
	if (game->enemy.move1 == 3 && game->moving_enemy1 == 1)
	{
		game->collection.enemy1.pos.y -= 8;
		if (game->collection.enemy1.pos.y == game->collection.enemy1.pos.z)
		{
			game->collection.enemy1.pos.z = 0;
			game->moving_enemy1 = 0;
			game->enemy.move1 = 4;
		}
	}
	/*						ENEMY *2					*/
	if(game->count_enemy == 2)
	{
		if (game->enemy.move2 == 0 && game->moving_enemy2 == 0)
		{
			game->collection.enemy2.pos.z = game->collection.enemy2.pos.x + 64;
			k = game->collection.enemy2.pos.x / TILE_SIZE;
			l = game->collection.enemy2.pos.y / TILE_SIZE;
			update_enemies(game, l, k + 1, 1);
		}
		if (game->enemy.move2 == 1 && game->moving_enemy2 == 0)
		{
			game->collection.enemy2.pos.z = game->collection.enemy2.pos.x - 64;
			k = game->collection.enemy2.pos.x / TILE_SIZE;
			l = game->collection.enemy2.pos.y / TILE_SIZE;
			update_enemies(game, l, k - 1, 1);
		}
		if (game->enemy.move2 == 2 && game->moving_enemy2 == 0)
		{
			game->collection.enemy2.pos.z = game->collection.enemy2.pos.y + 64;
			k = game->collection.enemy2.pos.x / TILE_SIZE;
			l = game->collection.enemy2.pos.y / TILE_SIZE;
			update_enemies(game, l + 1, k, 1);
		}
		if (game->enemy.move2 == 3 && game->moving_enemy2 == 0)
		{
			game->collection.enemy2.pos.z = game->collection.enemy2.pos.y - 64;
			k = game->collection.enemy2.pos.x / TILE_SIZE;
			l = game->collection.enemy2.pos.y / TILE_SIZE;
			update_enemies(game, l - 1, k, 1);
		}
		if (!a_enemy2)
			return ;
		if (a_enemy2->_tmp_delay++ == a_enemy2->delay) {
			a_enemy2->_tmp_delay = 0;
			a_enemy2->current_frame_num++;
			a_enemy2->current_frame_num %= ft_lstsize(a_enemy2->frames);
		}
		img3 = (t_image *)ft_lstget(a_enemy2->frames, a_enemy2->current_frame_num)->content;
		if (game->enemy.move2 == 0 && game->moving_enemy2 == 1)
		{
			game->collection.enemy2.pos.x += 8;
			if (game->collection.enemy2.pos.x == game->collection.enemy2.pos.z)
			{
				game->collection.enemy2.pos.z = 0;
				game->moving_enemy2 = 0;
				game->enemy.move2 = 4;
			}
		}
		if (game->enemy.move2 == 1 && game->moving_enemy2 == 1)
		{
			game->collection.enemy2.pos.x -= 8;
			if (game->collection.enemy2.pos.x == game->collection.enemy2.pos.z)
			{
				game->collection.enemy2.pos.z = 0;
				game->moving_enemy2 = 0;
				game->enemy.move2 = 4;
			}
		}
		if (game->enemy.move2 == 2 && game->moving_enemy2 == 1)
		{
			game->collection.enemy2.pos.y += 8;
			if (game->collection.enemy2.pos.y == game->collection.enemy2.pos.z)
			{
				game->collection.enemy2.pos.z = 0;
				game->moving_enemy2 = 0;
				game->enemy.move2 = 4;
			}
		}
		if (game->enemy.move2 == 3 && game->moving_enemy2 == 1)
		{
			game->collection.enemy2.pos.y -= 8;
			if (game->collection.enemy2.pos.y == game->collection.enemy2.pos.z)
			{
				game->collection.enemy2.pos.z = 0;
				game->moving_enemy2 = 0;
				game->enemy.move2 = 4;
			}
		}
	}
	if ((en1x < 64 && en1y < 64) || (en2x < 64 && en2y < 64))
	{
		game->options.end_failed = 1;
		togglePlay();
		playSound(game->music.game_over_sound, &game->vars_sound);
		mlx_loop_hook(game->mlx, game_over, game);
	}
	put_img_to_img(game->collection.bg, *img1, game->collection.player_one.pos.x, game->collection.player_one.pos.y);
	put_img_to_img(game->collection.bg, *img2, game->collection.enemy1.pos.x, game->collection.enemy1.pos.y);
	if (game->count_enemy == 2)
		put_img_to_img(game->collection.bg, *img3, game->collection.enemy2.pos.x, game->collection.enemy2.pos.y);
	mlx_put_image_to_window(game->mlx, game->window.win, game->collection.bg.img_ptr, 0, 0);
}

uint64_t timestamp_in_ms(void);
uint64_t update_at = 0;

int	fps = 12;
int p_posx, p_posy, e1_posx, e1_posy, e2_posx, e2_posy;

int	update(t_game * game) {
	if (timestamp_in_ms() - update_at < (uint64_t)(1000 / fps))
		return 0;
	update_at = timestamp_in_ms();
	if (!game)
		return 1;
    loop(&game->vars_sound);
	p_posx = game->collection.player_one.pos.x;
	p_posy = game->collection.player_one.pos.y;
	e1_posx = game->collection.enemy1.pos.x;
	e1_posy = game->collection.enemy1.pos.y;
	e2_posx = game->collection.enemy2.pos.x;
	e2_posy = game->collection.enemy2.pos.y;
	if (ft_strncmp(game->collection.enemy1.name, "pepe", 10) == 0)
		destroy_sprite(game->collection.enemy1, game->mlx);
	if (ft_strncmp(game->collection.player_one.name,"juan", 10) == 0)
		destroy_sprite(game->collection.player_one, game->mlx);
	if (ft_strncmp(game->collection.enemy2.name, "cuco2", 9) == 0)
		destroy_sprite(game->collection.enemy2, game->mlx);
	/*						PLAYER						*/
	if(game->actions.key_right && game->moving == 0) {
		if (ft_strncmp(game->collection.player_one.name,"WALK_RIGTH", 10) != 0)
		{
			game->collection.player_one = game->player.walk_right;
			game->collection.player_one.pos.x = p_posx;
			game->collection.player_one.pos.y = p_posy;
		}
	}
	else if(game->actions.key_left && game->moving == 0) {
		if (ft_strncmp(game->collection.player_one.name,"WALK_LEFT", 9) != 0)
		{
			game->collection.player_one = game->player.walk_left;
			game->collection.player_one.pos.x = p_posx;
			game->collection.player_one.pos.y = p_posy;
		}
	}
	else if(game->actions.key_up && game->moving == 0) {
		if (ft_strncmp(game->collection.player_one.name,"WALK_UP", 7) != 0)
		{
			game->collection.player_one = game->player.walk_back;
			game->collection.player_one.pos.x = p_posx;
			game->collection.player_one.pos.y = p_posy;
		}
	}
	else if(game->actions.key_down && game->moving == 0) {
		if (ft_strncmp(game->collection.player_one.name,"WALK_DOWN", 9) != 0)
		{
			game->collection.player_one = game->player.walk_front;
			game->collection.player_one.pos.x = p_posx;
			game->collection.player_one.pos.y = p_posy;
		}
	}
	else if (!game->actions.key_down && !game->actions.key_up && !game->actions.key_right && !game->actions.key_left && game->moving == 0) {
		if (ft_strncmp(game->collection.player_one.name, "STOP", 6) != 0)
		{
			game->collection.player_one = game->player.flincker_front;
			game->collection.player_one.pos.x = p_posx;
			game->collection.player_one.pos.y = p_posy;
		}
	}
	/*						ENEMY *1					*/
	if (game->moving_enemy1 == 0)
		game->enemy.move1 = rand() % 4;
	if (game->enemy.move1 == 0 && game->moving_enemy1 == 0) {
		if (ft_strncmp(game->collection.enemy1.name, "MOVE_RIGHT", 10) != 0)
        {
            game->collection.enemy1 = game->enemy.walk_right;
			game->collection.enemy1.pos.x = e1_posx;
			game->collection.enemy1.pos.y = e1_posy;
        }
	}
	if (game->enemy.move1 == 1 && game->moving_enemy1 == 0) {
		if (ft_strncmp(game->collection.enemy1.name, "MOVE_LEFT", 9) != 0)
        {
            game->collection.enemy1 = game->enemy.walk_left;
			game->collection.enemy1.pos.x = e1_posx;
			game->collection.enemy1.pos.y = e1_posy;
        }
	}
	if (game->enemy.move1 == 2 && game->moving_enemy1 == 0) {
		if (ft_strncmp(game->collection.enemy1.name, "MOVE_FRONT", 10) != 0)
        {
			game->collection.enemy1 = game->enemy.walk_front;
			game->collection.enemy1.pos.x = e1_posx;
			game->collection.enemy1.pos.y = e1_posy;
        }
	}
	if (game->enemy.move1 == 3 && game->moving_enemy1 == 0) {
		if (ft_strncmp(game->collection.enemy1.name, "MOVE_BACK", 9) != 0)
        {
			game->collection.enemy1 = game->enemy.walk_back;
			game->collection.enemy1.pos.x = e1_posx;
			game->collection.enemy1.pos.y = e1_posy;
        }
	}
		/*						ENEMY *2					*/
	if (game->moving_enemy2 == 0)
		game->enemy.move2 = rand() % 4;
	if (game->enemy.move2 == 0 && game->moving_enemy2 == 0) {
		if (ft_strncmp(game->collection.enemy2.name, "MOVE_RIGHT", 10) != 0)
		{
			game->collection.enemy2 = game->enemy.walk_right;
			game->collection.enemy2.pos.x = e2_posx;
			game->collection.enemy2.pos.y = e2_posy;
		}
	}
	if (game->enemy.move2 == 1 && game->moving_enemy2 == 0) {
		if (ft_strncmp(game->collection.enemy2.name, "MOVE_LEFT", 9) != 0)
		{
			game->collection.enemy2 = game->enemy.walk_left;
			game->collection.enemy2.pos.x = e2_posx;
			game->collection.enemy2.pos.y = e2_posy;
		}
	}
	if (game->enemy.move2 == 2 && game->moving_enemy2 == 0) {
		if (ft_strncmp(game->collection.enemy2.name, "MOVE_FRONT", 10) != 0)
		{
			game->collection.enemy2 = game->enemy.walk_front;
			game->collection.enemy2.pos.x = e2_posx;
			game->collection.enemy2.pos.y = e2_posy;
		}
	}
	if (game->enemy.move2 == 3 && game->moving_enemy2 == 0) {
		if (ft_strncmp(game->collection.enemy2.name, "MOVE_BACK", 9) != 0)
		{
			game->collection.enemy2 = game->enemy.walk_back;
			game->collection.enemy2.pos.x = e2_posx;
			game->collection.enemy2.pos.y = e2_posy;
		}
	}
	//Cuando hagas la imagen del enemigo es añadirla aqui y ver si funciona la animacion
	ft_lstiter_param(game->collection.player_one.animations, game->collection.enemy1.animations, game->collection.coin.animations, game->collection.enemy2.animations, update_animation, game);
	destroy_image(game->collection.bg, game->mlx);
	game->collection.bg = new_img(game->map.size.x * TILE_SIZE, game->map.size.y * TILE_SIZE, game->mlx);
	return 0;
}

uint64_t created_at = 0;

static uint64_t	gettimeofday_ms(void) {
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	timestamp_in_ms(void) {
	if (created_at == 0)
		created_at = gettimeofday_ms();
	return (gettimeofday_ms() - created_at);
}