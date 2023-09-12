#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

void    init_music(t_game *game)
{
    game->music.music = loadMusic(MUSIC, &game->vars_sound);
    game->music.coin_sound = loadSound(COIN_SOUND, &game->vars_sound);
    game->music.door_sound = loadSound(DOOR_SOUND, &game->vars_sound);
    game->music.game_over_sound = loadSound(GAME_OVER_SOUND, &game->vars_sound);
    game->music.victory_sound = loadSound(VICTORY_SOUND, &game->vars_sound);
}

void game_sound(t_game *game) {
    init(&game->vars_sound);
    initMixer(&game->vars_sound);
    init_music(game);
    playMusic(game->music.music, &game->vars_sound);
}

void	init_sound(t_vars *vars)
{
	vars->frameCount = 0;
	vars->timerFPS = 0;
	vars->lastFrame = 0;
	vars->fps = 0;
	vars->lastTime = 0;
	vars->setFPS = 60;
	vars->keystates = NULL;
	vars->running = 0;
	vars->sounds_size = 0;
	vars->music_size = 0;
}

void init(t_vars *vars) {
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_Init(SDL_INIT_EVERYTHING);
  vars->running = 1;
}

void input(t_vars *vars) {
  vars->keystates = SDL_GetKeyboardState(NULL);
  while (SDL_PollEvent(&vars->event)) {
    if (vars->event.type == SDL_QUIT)
      vars->running = 0;
  }
  vars->mousestate = SDL_GetMouseState(&vars->mouse.x, &vars->mouse.y);
}


void  quit(t_vars *vars) {
  vars->running = 0;
  SDL_Quit();
}

void loop(t_vars *vars) {
  vars->lastFrame = SDL_GetTicks();
  if (vars->lastFrame >= (vars->lastTime + 1000)) {
    vars->lastTime = vars->lastFrame;
    vars->fps = vars->frameCount;
    vars->frameCount = 0;
  }
  input(vars);
}

int loadMusic(const char* filename, t_vars *vars) {
    Mix_Music *m = NULL;
    m = Mix_LoadMUS(filename);
    if(m == NULL) {
        printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
        vars->running = 0;
        return -1;
    }
    vars->music[vars->music_size++] = m;
    return vars->music_size-1;
}

int loadSound(const char* filename, t_vars *vars) {
    Mix_Chunk *m = NULL;
    m = Mix_LoadWAV(filename);
    if(m == NULL) {
        printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
        vars->running = 0;
        return -1;
    }
    vars->sounds[vars->sounds_size++] = m;
    return vars->sounds_size-1;
}

void setVolume(int v, t_vars *vars) {
    vars->volume = (MIX_MAX_VOLUME * v) / 100;
}

int playMusic(int m, t_vars *vars) {
    if(Mix_PlayingMusic() == 0) {
        Mix_Volume(1, vars->volume);
        Mix_PlayMusic(vars->music[m], -1);
    }
    return 0;
}

int playSound(int s, t_vars *vars) {
    Mix_Volume(-1, vars->volume);
    Mix_PlayChannel(-1, vars->sounds[s], 0);
    return 0;
}

int initMixer(t_vars *vars) {
    if(Mix_Init(MIX_INIT_MP3) < 0) {
        printf("SDL_Mixer couldnt init. Err: %s\n", Mix_GetError());
        return -1;
    }
    if(SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL couldnt init. Err: %s\n", SDL_GetError());
        return -1;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer couldnt init. Err: %s\n", Mix_GetError());
        return -1;
    }
    setVolume(80, vars);
    return 0;
}

void quitMixer(t_vars *vars) {
    for(int s=0; s<vars->sounds_size; s++) {
        Mix_FreeChunk(vars->sounds[s]);
    }
    for(int s=0; s<vars->music_size; s++) {
        Mix_FreeMusic(vars->music[s]);
    }
    Mix_Quit();
}

void togglePlay() {
    if(Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
}
