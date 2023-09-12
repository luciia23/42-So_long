#ifndef GAME_H
# define GAME_H

#include "../mlx/mlx.h"
#include "../libft/libft.h"

# include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
# include <sys/time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "key.h"
#include "files.h"
#include "animation.h"


#define NUM_MAPS 4
#define TILE_SIZE 64

#define MAX_SOUNDS 100
#define MAX_MUSIC 100

enum directions  {
	EAST,
	WEST,
	UP,
	DOWN,
};

typedef struct s_vector {
    int x;
    int y;
    int z;
}               t_vector;

#include "sprite.h"

typedef enum e_bool {
	false,
	true
}	t_bool;

typedef struct s_options {
    int start;
    int end_won;
    int end_failed;
}               t_options;

typedef struct s_actions {
	t_bool	key_up;	// UP Arrow or W
	t_bool	key_down;	// DOWN Arroy or S
	t_bool	key_left; 	// KEY_W Arrow or A
	t_bool	key_right;	// KEY_S Arrow or d
	t_bool	key_space;	// KEY_SPACE
	t_bool	key_p;	// KEY_P
}		t_actions;

typedef struct s_music
{
    int music;
    int coin_sound;
    int door_sound;
    int game_over_sound;
    int victory_sound;
}               t_music;

typedef struct t_vars {
  int frameCount, timerFPS, lastFrame, fps, lastTime;
  int setFPS;
  SDL_Point mouse;
  const Uint8 *keystates;
  Uint32 mousestate;
  SDL_Event event;
  int running;
  Mix_Chunk* sounds[MAX_SOUNDS];
  int sounds_size;
  Mix_Music* music[MAX_MUSIC];
  int music_size;
  int volume;
}              t_vars;

typedef struct s_window{
    void        *win;
    t_vector    size;
}               t_window;

typedef struct s_map {
    t_vector    size;
    char        **coords;
    int         total_collec;
    char        *array[NUM_MAPS];
}               t_map;

typedef struct s_player
{
    t_sprite    walk_back;
    t_sprite    walk_front;
    t_sprite    walk_left;
    t_sprite    walk_right;
    t_sprite    flincker_front;
}               t_player;

typedef struct s_enemy
{
    t_sprite    walk_back;
    t_sprite    walk_front;
    t_sprite    walk_left;
    t_sprite    walk_right;
    int         move1;
    int         move2;
}               t_enemy;

typedef struct s_directions
{
    int             east;
    int             west;
    int             up;
    int             down;
}               t_directions;

typedef struct s_game{
    void            *mlx;
    t_window        window;
    t_options       options;
    t_map           map;
    t_map           maps[NUM_MAPS];
    t_vars          vars_sound;
    t_music         music;
    t_collection    collection;
    t_actions       actions;
    t_image         *img;
    t_player        player;
    t_enemy         enemy;
    t_directions    directions;
    int             current_map;
    int             moving;
    int             moving_enemy1;
    int             moving_enemy2;
    int             collec;
    int             count_enemy;
    int             arrow_position;
}               t_game;

typedef struct s_update_params
{
    t_list *list;
    t_game *game;
} t_update_params;


t_window    ft_new_window(void *mlx, int width, int height, char *title);
// INIT FUCTIONS
void    map_init(t_game *game);
void    search_sprite(t_game *game);
void    search_enemy(t_game *game);
void    search_enemy2(t_game *game);
void    collection_init(t_game *game);
void    init_slice(t_game *game);
// DRAW FUNCTIONS
void	draw_map(t_game *game, t_image *coin);
void draw_img(t_game *game, t_image *coin,int x, int y);

// GAME OPTIONS
void    new_game(t_game *game);
int    game_over(t_game *game);
int end_game(t_game *game);
void    reset_game(t_game *game);
void    resume_game(t_game *game);

// HOOKS
int     on_key_press(int keycode, t_game *game);
int     on_key_release(int keycode, t_game *game);
void	ft_input(int key, t_game *game);

//ANIMATION FUNCTION
void update_animation(void * ptr1, void * ptr2, void * ptr3, void * ptr4, void * ptr5);
int     update(t_game * game);

//ENT
void add_ent_from_file_to_game(t_game * game, char * path);

//FREE MEMORY
void    free_sprites(t_game *game);
void free_maps(t_game *game);

//SCORE
void    update_score(t_game *game);
t_font	load_score_font(t_game *game);
void    free_score(t_game *g);

//SOUND & MUSIC

void	init_sound(t_vars *vars);

void init(t_vars *vars);
void game_sound(t_game *game);
void input(t_vars *vars);
void quit(t_vars *vars);
void loop(t_vars *vars);

int loadMusic(const char* filename, t_vars *vars);
int loadSound(const char* filename, t_vars *vars);
void    init_music(t_game *game);
void setVolume(int v, t_vars *vars);
int playMusic(int m, t_vars *vars);
int playSound(int s, t_vars *vars);
int initMixer(t_vars *vars);
void quitMixer(t_vars *vars);
void togglePlay();




#endif