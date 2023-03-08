#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "UTIL.h"
#include "LButton.h"
#include "Constants.h"

extern SDL_Window * gWindow;

extern SDL_Renderer * gRenderer;

extern TTF_Font * gFont;

extern LButton gBox[ 9 ];

extern LTexture gSpriteClip[ TOTAL_BOX ];

extern char gTick;

extern LTexture textTexture;

#endif // GLOBAL_H_
