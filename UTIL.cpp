#include "UTIL.h"
#include "global.h"
#include "Constants.h"

bool init()
{
    bool success = true;
    if ( !SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "Failed to initializes\n";
        success = false;
    }
    else
    {
        //Set texture filltering to linear
        SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1");


        gWindow = SDL_CreateWindow( "Tic tac toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if ( gWindow == NULL )
        {
            std::cout << "Failed to create window\n";
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if ( gRenderer == NULL )
            {
                std::cout << "Renderer could not be create! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if ( !( IMG_Init ( imgFlags ) & imgFlags ) )
                {
                    std::cout << "SDL image could not initialize! SDL_image Error: " << IMG_GetError() << std:: endl;
                    success = false;
                }

                if ( TTF_Init() == -1 )
                {
                    std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    if ( !gSpriteClip[ PRESSING_BOX ].loadFromFile( "empty.png" ) )
    {
        std::cout << "Failed to load empty box texture!\n";
        success = false;
    }
    if ( !gSpriteClip[ X_TICKED_BOX ].loadFromFile( "x.png" ) )
    {
        std::cout << "Failed to load X ticked box texture!\n";
        success = false;
    }
    if ( !gSpriteClip[ O_TICKED_BOX ].loadFromFile( "o.png" ) )
    {
        std::cout << "Failed to load O ticked box texture!\n";
        success = false;
    }

    gFont = TTF_OpenFont( "SuperMario85Mari.ttf", 90);
    if ( gFont == NULL )
    {
        std::cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        success = false;
    }
    else
    {
        SDL_Color textColor = { 0, 0, 0};
        if ( !textTexture.loadFromRenderedText( "Tic tac toe", textColor ) )
        {
            std::cout << "Failed to render text texture! \n";
            success = false;
        }
    }

    int PosX = (SCREEN_WIDTH - BOARD_EDGE_LENGTH)/2, PosY = (SCREEN_HEIGHT - BOARD_EDGE_LENGTH)/2;
    gBox[ 0 ].setPosition( PosX, PosY);
    gBox[ 1 ].setPosition( PosX + BOX_EDGE_LENGTH, PosY);
    gBox[ 2 ].setPosition( PosX + BOX_EDGE_LENGTH * 2, PosY);
    gBox[ 3 ].setPosition( PosX, PosY + BOX_EDGE_LENGTH);
    gBox[ 4 ].setPosition( PosX + BOX_EDGE_LENGTH, PosY + BOX_EDGE_LENGTH );
    gBox[ 5 ].setPosition( PosX + BOX_EDGE_LENGTH * 2, PosY + BOX_EDGE_LENGTH);
    gBox[ 6 ].setPosition( PosX, PosY + BOX_EDGE_LENGTH * 2);
    gBox[ 7 ].setPosition( PosX + BOX_EDGE_LENGTH, PosY + BOX_EDGE_LENGTH * 2);
    gBox[ 8 ].setPosition( PosX + BOX_EDGE_LENGTH * 2, PosY + BOX_EDGE_LENGTH * 2);
    return success;
}

void close()
{
    SDL_DestroyWindow( gWindow );
    SDL_DestroyRenderer( gRenderer );
    gWindow = NULL;
    gRenderer = NULL;

    for (int i = 0; i < TOTAL_BOX; ++i)
    {
        gSpriteClip[ i ].free();
    }
}
