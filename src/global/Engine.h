#ifndef ENGINE_H
#define ENGINE_H

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#define STR_ERR_BUFFER_SIZE 128
#define STR_PATH_BUFFER_SIZE 255

#define TEXTURE_FOLDER "images"
#define MUSIC_FOLDER "music"
#define SOUND_FOLDER "sounds"
#define FONT_FOLDER "fonts"

#define MUSIC_FREQUENCY 44100

#define WINDOW_WIDTH 1280.0
#define WINDOW_HEIGHT 720.0

typedef struct _Font {
  SDL_Texture *texture;
  int charsLen;
  char *chars;
  int *widthList;
  SDL_Rect *rectList;
  SDL_Point *offsetList;

  int kerningPairsLen;
  struct {
    char ch[2];
  } *kerningPairs;
  int *kerningValues;
} Font;

typedef struct {
  /* Graphics */
  SDL_Window *win;
  SDL_Renderer *render;
  SDL_Texture **textures;
  unsigned int texturesLen;

  float scale_x;
  float scale_y;

  Font **fonts;
  unsigned int fontsLen;

  bool fullScr;

  /* Scores */

  /* Sound and Music */
  float volMus;
  float volSnd;

  Mix_Music *music;
  unsigned int soundsLen;
  Mix_Chunk **sounds;
  unsigned int soundsSfxLen;
  Mix_Chunk **soundsSfx;
} Engine;

extern Engine engine;

void Engine_PushError(const char *, const char *);
void Engine_PushErrorCode(const char *, int);
void Engine_PushErrorFile(const char *, const char *);
void Engine_PushErrorFileCode(const char *, int);

int Engine_Init();
void Engine_Destroy();

/* === Graphics === */
int Engine_CreateWindow(const char *, int, int);
SDL_Texture *Engine_TextureLoad(const char *);
int Engine_TexturesLoad(const char **, int);
SDL_Texture *Engine_GetTextureSDL(unsigned int);

/* Font */
Font *Engine_FontLoad(const char *);
int Engine_FontsLoad(const char **, int);
void Engine_FontFree(Font *);

/* Drawing */
void Engine_DrawTexture(unsigned int, float, float);
void Engine_DrawTextureWithRot(unsigned int, float, float, float);
void Engine_DrawTextureSDL(SDL_Texture *, float, float);
void Engine_DrawTextScale(const char *, unsigned int, float, float, float);
void Engine_DrawText(const char *, unsigned int, float, float);
int Engine_GetTextWidth(const char *str, unsigned int fontID);
void Engine_DrawTextExt(const char *str, int fontID, SDL_Color color,
                        bool drawShadow, bool center, float x, float y);
void Engine_DrawTextExtScale(const char *str, int fontID, float scale,
                             SDL_Color color, bool drawShadow, bool center,
                             float x, float y);

/* === Sound and Music === */
int Engine_MusicLoad(const char *);

Mix_Chunk *Engine_SoundLoad(const char *);
Mix_Chunk *Engine_SoundSfxLoad(const char *);
int Engine_SoundsLoad(const char **, uint32_t);
int Engine_SoundsSfxLoad(const char **, uint32_t);
Mix_Chunk *Engine_GetSoundSample(uint32_t);

void Engine_PlayMusic(uint32_t);
void Engine_StopMusic();
void Engine_PlaySound(uint32_t);
void Engine_StopSound(uint32_t);
void Engine_PlaySoundSfxPitch(int, float);
void Engine_StopSoundSfx(int);

void Engine_GetMousePos(int *mx, int *my);

int Engine_SaveSettings();
int Engine_LoadSettings();

int randInt(const int, const int);
float fsign(float x);
float lerp(float start, float end, float val);

#endif
