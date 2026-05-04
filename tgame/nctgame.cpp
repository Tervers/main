#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};

bool init();
bool loadSurfaceMedia();

bool loadTextureMedia();

void close();
SDL_Texture* loadTexture( std::string path );

SDL_Surface* loadSurface( std::string path );

SDL_Window* gWindow = NULL;
	
SDL_Renderer* gRenderer = NULL;

SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

SDL_Surface* gCurrentSurface = NULL;

SDL_Surface* gStrechedSurface = NULL;

SDL_Texture* gTextureTexture = NULL;

SDL_Texture* gViewportTexture = NULL;

class LTexture
{
	public:
		LTexture();

		~LTexture();

		bool loadFromFile( std::string path );

		void free();

        void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void render( int x, int y );

        void renderClip( int x, int y, SDL_Rect* clip = NULL );

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};


LTexture gFooTexture;
LTexture gBackgroundTexture;

SDL_Rect gSpriteClips[ 4 ];
LTexture gSpriteSheetTexture;

LTexture gModulatedTexture;

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

bool LTexture::loadFromFile( std::string path )
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::render( int x, int y )
{
	SDL_Rect renderQuad = { x, y, mWidth / 2, mHeight / 2 }; //mWidth,mHeight divided for viewport: rewrite
	SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}

void LTexture::renderClip( int x, int y, SDL_Rect* clip )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    if( clip != NULL )
    {
	renderQuad.w = clip->w;
	renderQuad.h = clip->h;
    }

    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}



bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
		
		gWindow = SDL_CreateWindow( "Tgame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
												SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadSurfaceMedia()
{
	bool success = true;

	gStrechedSurface = SDL_LoadBMP( "media/03/x.bmp" );
	if( gStrechedSurface == NULL )
	{
		printf( "Unable to load surface image %s! SDL Error: %s\n", "media/03/x.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

SDL_Texture* loadTexture( std::string path )
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

bool loadTextureMedia()
{
	bool success = true;

	gTextureTexture = loadTexture( "media/07/texture.png" );
	if( gTextureTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

bool loadViewportMedia()
{
    bool success = true;

    gViewportTexture = loadTexture( "media/09/viewport.png" );
    if( gViewportTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

    return success;
}

SDL_Surface* loadSurface( std::string path )
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

bool loadColorKeyMedia()
{
	bool success = true;

	if( !gFooTexture.loadFromFile( "media/10/foo.png" ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}

	if( !gBackgroundTexture.loadFromFile( "media/10/background.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	return success;
}

bool loadSpriteMedia()
{
    bool success = true;

    if( !gSpriteSheetTexture.loadFromFile( "media/11/dots.png" ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w = 100;
        gSpriteClips[ 0 ].h = 100;

        gSpriteClips[ 1 ].x = 100;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w = 100;
        gSpriteClips[ 1 ].h = 100;

        gSpriteClips[ 2 ].x =   0;
        gSpriteClips[ 2 ].y = 100;
        gSpriteClips[ 2 ].w = 100;
        gSpriteClips[ 2 ].h = 100;

        gSpriteClips[ 3 ].x = 100;
        gSpriteClips[ 3 ].y = 100;
        gSpriteClips[ 3 ].w = 100;
        gSpriteClips[ 3 ].h = 100;
    }

    return success;
}

bool loadModulationMedia()
{
    bool success = true;

    if( !gModulatedTexture.loadFromFile( "media/12/colors.png" ) )
    {
        printf( "Failed to load modulation texture!\n" );
        success = false;
    }

    return success;
}

bool loadKeyPressMedia()
{
	bool success = true;

	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "media/04/press.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load default key press image!\n" );
		success = false;
	}

	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "media/04/up.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		printf( "Failed to load up key press image!\n" );
		success = false;
	}

	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "media/04/down.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN] == NULL )
	{
		printf( "Failed to load down key press image!\n" );
		success = false;
	}

	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "media/04/left.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		printf( "Failed to load left key press image!\n" );
		success = false;
	}

	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "media/04/right.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
	{
		printf( "Failed to load right key press image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	SDL_DestroyTexture( gTextureTexture );
	SDL_DestroyTexture( gViewportTexture );
	gTextureTexture = NULL;
	gViewportTexture = NULL;
	gFooTexture.free();
	gBackgroundTexture.free();
    gSpriteSheetTexture.free();
    gModulatedTexture.free();
	
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = NULL;
	}

	SDL_FreeSurface( gStrechedSurface );
	gStrechedSurface = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadSurfaceMedia() )
		{
			printf( "Failed to load surface media!\n" );
		}
		else if( !loadTextureMedia() )
		{
			printf( "Failed to load texture media!\n" );
		}
        else if( !loadViewportMedia() )
        {
            printf( "Failed to load viewport media!\n" );
        }
		else if( !loadColorKeyMedia() )
		{
			printf( "Failed to load color key media!\n" );
		}
        else if( !loadSpriteMedia() )
        {
            printf("Failed to load sprite media!\n" );
        }
        else if( !loadModulationMedia() )
        {
            printf( "Failed to load modulation media!\n" );
        }
        else if( !loadKeyPressMedia() )
        {
            printf( "Failed to load key press media!\n" );
        }
		else
		{			
			bool quit = false;

			SDL_Event e;

            Uint8 r = 255;
            Uint8 g = 255;
            Uint8 b = 255;

			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_q:
                            r += 32;
                            break;

                            case SDLK_w:
                            g += 32;
                            break;

                            case SDLK_e:
                            b += 32;
                            break;

                            case SDLK_a:
                            r -= 32;
                            break;

                            case SDLK_s:
                            g -= 32;
                            break;

                            case SDLK_d:
                            b -= 32;
                            break;
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;

							default:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
                        }
                    }
				}

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                SDL_Rect topLeftViewport;
                topLeftViewport.x = 0;
                topLeftViewport.y = 0;
                topLeftViewport.w = SCREEN_WIDTH / 2;
                topLeftViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport( gRenderer, &topLeftViewport );
				gBackgroundTexture.render( 0, 0 );

				gFooTexture.render( 120, 95 );

                gBackgroundTexture.setColor( r, g, b );
                gFooTexture.setColor( r, g, b );

                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH / 2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH / 2;
                topRightViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport( gRenderer, &topRightViewport );

                SDL_RenderCopy( gRenderer, gTextureTexture, NULL, NULL );

                gSpriteSheetTexture.renderClip( 0, 0, &gSpriteClips[ 0 ] );

                gSpriteSheetTexture.renderClip( ( SCREEN_WIDTH / 2 ) - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );

                gSpriteSheetTexture.renderClip( 0, ( SCREEN_HEIGHT / 2 ) - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );

                gSpriteSheetTexture.renderClip( ( SCREEN_WIDTH / 2 ) - gSpriteClips[ 3 ].w, ( SCREEN_HEIGHT / 2 ) - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );

                gSpriteSheetTexture.setColor( r, g, b );

                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = SCREEN_HEIGHT / 2;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport( gRenderer, &bottomViewport );

				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );

				SDL_UpdateWindowSurface( gWindow );

                SDL_RenderCopy( gRenderer, gViewportTexture, NULL, NULL );

                SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 };
                SDL_SetRenderDrawColor( gRenderer, 0xff, 0x00, 0x00, 0x7F );
                SDL_RenderFillRect( gRenderer, &fillRect );

                SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 12, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 6 };
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0x7F );
                SDL_RenderDrawRect( gRenderer, &outlineRect );

                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0x7F );
                SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 4, SCREEN_WIDTH, SCREEN_HEIGHT / 4 );

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0x7F );
                for( int i = 9; i < SCREEN_HEIGHT; i += 4 )
                {
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
                }

                gModulatedTexture.setColor( r, g, b );
                gModulatedTexture.render( SCREEN_WIDTH / 2, 0 );

				SDL_RenderPresent( gRenderer );
			}
		}
	}
	close();
	return 0;
}
