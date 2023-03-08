#include "LButton.h"
#include "global.h"

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

int LTexture::getHeight() { return mHeight; }
int LTexture::getWidth() { return mWidth; }

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specifiled path
    SDL_Surface * loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
    {
        std::cout << "Unable to load imae " << path << "! SDL image Error" << IMG_GetError() << std::endl;
    }
    else
    {
        // Set color key
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x00, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if ( newTexture == NULL )
        {
            std::cout << "Unable to create texture from " << path << "!SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface * textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if ( textSurface == NULL )
    {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    else
    {
        //Create texture from surface pixel
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if ( mTexture == NULL )
        {
            std::cout << "Unable to create texture from rendered text! SDL Error: " << TTF_GetError() << std::endl;
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
    }
    return mTexture != NULL;
}

void LTexture::render( int x, int y, SDL_Rect* clip )

{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if ( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad);
}


void LTexture::setColor( Uint8 r, Uint8 g, Uint8 b )
{
    SDL_SetTextureColorMod( mTexture, r, g, b );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::free()
{
    if ( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;
    mPosition.w = BOX_EDGE_LENGTH;
    mPosition.h = BOX_EDGE_LENGTH;

    mCurrentSpite = EMPTY_BOX;

    tick = 'N';

    gTicked = false;
}

void LButton::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e )
{
    //If mouse event happened
    if ( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x,  &y);

        bool inside = true;

        if( x < mPosition.x ||
            x > mPosition.x + BOX_EDGE_LENGTH ||
            y < mPosition.y  ||
            y > mPosition.y + BOX_EDGE_LENGTH )
            inside = false;
        if ( !inside )
        {
            mCurrentSpite =EMPTY_BOX;
        }
        else
        {
            switch( e->type )
            {
            case SDL_MOUSEBUTTONDOWN:
                mCurrentSpite = PRESSING_BOX;
                break;

            case SDL_MOUSEBUTTONUP:
                if ( tick == 'N')
                {
                    tick = gTick;

                    if ( gTick == 'O' )
                        gTick = 'X';
                    else
                        gTick = 'O';
                }
                break;

            }
        }
    }
}

SDL_Rect LButton::getRect()
{
    return mPosition;
}

char LButton::getTick()
{
    return tick;
}

void LButton::render()
{
    if ( tick == 'O' )
    {
        gSpriteClip[ O_TICKED_BOX ].render(mPosition.x, mPosition.y);
        return;
    }
    if ( tick == 'X' )
    {
        gSpriteClip[ X_TICKED_BOX ].render(mPosition.x, mPosition.y );
        return;
    }
    if ( mCurrentSpite != EMPTY_BOX )
        gSpriteClip[ mCurrentSpite ].render( mPosition.x, mPosition.y);
}
