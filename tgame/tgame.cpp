/*****
Possibly don't use single word variables; makes it difficult to parse through multiword var's that share same word
*****/


//Using SDL, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>


/*** Variables and Enums ***/

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surface constants
enum KeyPressSurfaces   //enum is the alternative to defines: '#define KEY_PRESS_SURFACE_DEFAULT 0', '#define KEY_PRESS_SURFACE_UP 1'
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};


/*** Function Declarations ***/

//Starts up SDL and creates window
bool init();

//Loads surface media
bool loadMediaSurface();   //this loads all media from outside the program

//Loads texture media
bool loadMediaTexture();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );   //loads individual surfaces

SDL_Texture* loadTexture( std::string path );   //loads individual textures


/*** Pointers ***/

//The window we'll be rendering to
SDL_Window* primaryWindow = NULL;

//The surface contained by the window
SDL_Surface* primaryWindowSurface = NULL;

//The window renderer
SDL_Renderer* primaryRenderer = NULL;

//The images that correspond to a keypress
SDL_Surface* KeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* awaitingSurface = NULL;   //holds the image that you want to apply to primaryWindowSurface
				       //images change depending on user input
//Current displayed texture
SDL_Texture* primaryWindowTexture = NULL;


/*** Function Definitions ***/

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )   //calls SDL_Init( SDL_INIT_VIDEO ) and immediately evaluates its return value
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf("Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		primaryWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( primaryWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			primaryRenderer = SDL_CreateRenderer( primaryWindow, -1, SDL_RENDERER_ACCELERATED );
			if ( primaryRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor ( primaryRenderer, 0x00, 0x00, 0x00, 0xff );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if ( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

			//Get window surface
			primaryWindowSurface = SDL_GetWindowSurface( primaryWindow );   //store to variable for reuse
		}
	}

	return success;
}

bool loadMediaSurface()
{
	//Loading success flag
	bool success = true;

	//Load default surface
	KeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "pictures/press.bmp" );
	if( KeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load up surface
	KeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "pictures/up.bmp" );
	if( KeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		printf( "Failed to load up image!\n" );
		success = false;
	}

	//Load down surface
	KeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "pictures/down.bmp" );
	if( KeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
	{
		printf( "Failed to load down image!\n" );
		success = false;
	}

	//Load left surface
	KeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "pictures/left.bmp" );
	if( KeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		printf( "Failed to load left image!\n" );
		success = false;
	}

	//Load right surface
	KeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "pictures/right.bmp" );
	if( KeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
	{
		printf( "Failed to load right image!\n" );
		success = false;
	}

	return success;
}

bool loadMediaTexture()   //maybe eventually create loadMediaPNG
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	primaryWindowTexture = loadTexture( "07_texture_loading_and_rendering/texture.png" );
	if( primaryWindowTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}	

void close()
{
	//Deallocate surfaces
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( KeyPressSurfaces[ i ] );
		KeyPressSurfaces[ i ] = NULL;
	}

	//Destroy window
	SDL_DestroyRenderer( primaryRenderer );
	SDL_DestroyWindow( primaryWindow );
	primaryWindow = NULL;
	primaryRenderer = NULL;

	//Free loaded texture
	SDL_DestroyTexture( primaryWindowTexture );
	primaryWindowTexture = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


/*** Pointer Function Definitions ***/

SDL_Surface* loadSurface( std::string path )   //loads BMPs
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, primaryWindowSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

SDL_Texture* loadTexture( std::string path )   //Load various image formats
{
        //The final texture
        SDL_Texture* newTexture = NULL;

        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == NULL )
        {
                printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        }
        else
	{
        	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface( primaryRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
               	}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}


/*** main ***/

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )   //calls init() and immediately evaluates it
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMediaSurface() )   //calls loadMediaSurface and immediately evaluates it
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			awaitingSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];  //defaults to this surface

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )   //check events, continue if not 0
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//User presses a key
					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							awaitingSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							awaitingSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;

							case SDLK_LEFT:
							awaitingSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							awaitingSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;

							default:
							awaitingSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
				}

				//Apply the current image stretched
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled( awaitingSurface, NULL, primaryWindowSurface, &stretchRect);   //the picture is drawn to the surface...
			
				//Update the surface
				SDL_UpdateWindowSurface( primaryWindow );    //...now put it up for show
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}


/*** Surface-only ***/
/**

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )   //main parameters unused in this program
{
	//The window we'll be rendering to
	SDL_Window* Window = NULL;   
	
	//The surface contained by the window
	SDL_Surface* WindowSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window / initialize Window
		Window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN );
		if( Window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface / initialize surface
			WindowSurface = SDL_GetWindowSurface( Window );   //get surface for window

			//Fill the surface white
			SDL_FillRect( WindowSurface, NULL, SDL_MapRGB(
						WindowSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( Window );
            
            //Hack to get window to stay up
            SDL_Event e;
	    bool quit = false;
	    while( quit == false ){
		    while( SDL_PollEvent( &e )){
			    if( e.type == SDL_QUIT )
				    quit = true;
		    			    }}}}

	//Destroy window
	SDL_DestroyWindow( Window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
**/
