#include "UTIL.h"
#include "LButton.h"
#include "Constants.h"
#include "global.h"

int main( int argc, char * args[])
{
    //Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle button events
					for( int i = 0; i < 9; ++i )
					{
						gBox[ i ].handleEvent( &e );
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				textTexture.render( (SCREEN_WIDTH - textTexture.getWidth() ) /2, 5 );

                for (int i = 0; i < 9; ++i)
                {
                    SDL_Rect dRect = gBox[ i ].getRect();
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                    SDL_RenderDrawRect( gRenderer,  &dRect);
                }

                for (int i = 0; i < 9; ++i)
                {
                    gBox[ i ].render();
                }
                SDL_RenderPresent( gRenderer );

                if ( gBox[ 0 ].getTick() == gBox[ 1 ].getTick() && gBox[ 1 ].getTick() == gBox[ 2 ].getTick() && gBox[ 0 ].getTick() != 'N'||
                    gBox[ 3 ].getTick() == gBox[ 4 ].getTick() && gBox[ 4 ].getTick() == gBox[ 5 ].getTick() && gBox[ 3 ].getTick() != 'N'||
                    gBox[ 6 ].getTick() == gBox[ 7 ].getTick() && gBox[ 7 ].getTick() == gBox[ 8 ].getTick() && gBox[ 6 ].getTick() != 'N'||
                    gBox[ 0 ].getTick() == gBox[ 3 ].getTick() && gBox[ 3 ].getTick() == gBox[ 6 ].getTick() && gBox[ 0 ].getTick() != 'N'||
                    gBox[ 1 ].getTick() == gBox[ 4 ].getTick() && gBox[ 4 ].getTick() == gBox[ 7 ].getTick() && gBox[ 1 ].getTick() != 'N'||
                    gBox[ 2 ].getTick() == gBox[ 5 ].getTick() && gBox[ 5 ].getTick() == gBox[ 8 ].getTick() && gBox[ 2 ].getTick() != 'N'||
                    gBox[ 0 ].getTick() == gBox[ 4 ].getTick() && gBox[ 4 ].getTick() == gBox[ 8 ].getTick() && gBox[ 0 ].getTick() != 'N'||
                    gBox[ 2 ].getTick() == gBox[ 4 ].getTick() && gBox[ 4 ].getTick() == gBox[ 6 ].getTick() && gBox[ 2 ].getTick() != 'N')
                        if ( gTick == 'O' )
                        {
                            std::cout << "Player 2 win" << std::endl;
                            quit = true;
                        }
                        else
                        {
                            std::cout << "Player 1 win" << std::endl;
                            quit = true;
                        }
                        bool gameend = true;
                        for (int i = 0; i < 9; ++i )
                        {
                            if ( gBox[ i ].getTick() == 'N' )
                                gameend = false;
                        }

                        if (gameend)
                        {
                            std::cout << "Game draw" << std::endl;
                            quit = true;
                        }
			}
		}
	}

	//Free resources and close SDL
	close();
	return 0;
}
