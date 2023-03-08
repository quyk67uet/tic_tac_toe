#ifndef LBUTTON_H_
#define LBUTTON_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstring>
#include "Constants.h"

class LTexture
{
public:
    LTexture();
    ~LTexture();

    int getWidth();
    int getHeight();

    bool loadFromFile( std::string path );
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    void render(int x, int y, SDL_Rect* clip = NULL);
    void free();
    void setColor( Uint8 r, Uint8 g, Uint8 b );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );

private:
    SDL_Texture * mTexture;

    int mWidth, mHeight;
};

class LButton
{
public:
    LButton();

    void setPosition( int x, int y);

    void handleEvent( SDL_Event* e );

    void render();

    SDL_Rect getRect();

    char getTick();
private:
    SDL_Rect mPosition;

    LBox mCurrentSpite;

    char tick;

    bool gTicked;
};

#endif // LBUTTON__H_
