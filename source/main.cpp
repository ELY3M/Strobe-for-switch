#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <switch.h>

#define A         0
#define B         1
#define X         2
#define Y         3
#define LSTICK    4
#define RSTICK    5
#define LBUMPER   6
#define RBUMPER   7
#define LTRIGGER  8
#define RTRIGGER  9
#define PLUS      10
#define MINUS     11
#define DPADL     12
#define DPADU     13
#define DPADR     14
#define DPADD     15


void NavyScreen(int w, int h, SDL_Window *window, SDL_Renderer *renderer) {

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect f = {0, 0, w, h};
    SDL_RenderFillRect(renderer, &f);
	SDL_RenderPresent(renderer);
	
}

void CyanScreen(int w, int h, SDL_Window *window, SDL_Renderer *renderer) {

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect f = {0, 0, w, h};
    SDL_RenderFillRect(renderer, &f);
	SDL_RenderPresent(renderer);
	
}

void BlackScreen(int w, int h, SDL_Window *window, SDL_Renderer *renderer) {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect f = {0, 0, w, h};
    SDL_RenderFillRect(renderer, &f);
	SDL_RenderPresent(renderer);
	
}


void GreenScreen(int w, int h, SDL_Window *window, SDL_Renderer *renderer) {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect f = {0, 0, w, h};
    SDL_RenderFillRect(renderer, &f);
	SDL_RenderPresent(renderer);
	
}


void GlowScreen(int w, int h, SDL_Window *window, SDL_Renderer *renderer) {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 213, 236, 153, 255);
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect f = {0, 0, w, h};
    SDL_RenderFillRect(renderer, &f);
	SDL_RenderPresent(renderer);
	
}

void WhiteScreen(int w, int h, SDL_Window *window, SDL_Renderer *renderer) {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect f = {0, 0, w, h};
    SDL_RenderFillRect(renderer, &f);
	SDL_RenderPresent(renderer);
	
}



void Strobe(int w, int h, SDL_Window *window, SDL_Renderer *renderer) {
	

CyanScreen(w, h, window, renderer);
BlackScreen(w, h, window, renderer);
GreenScreen(w, h, window, renderer);
GlowScreen(w, h, window, renderer);
WhiteScreen(w, h, window, renderer);
NavyScreen(w, h, window, renderer);	

} 

int main(int argc, char *argv[])
{
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int done = 0, i = 0, w = 1280, h = 720;

    // mandatory at least on switch, else gfx is not properly closed
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        return -1;
    }

    // create an SDL window (OpenGL ES2 always enabled)
    // when SDL_FULLSCREEN flag is not set, viewport is automatically handled by SDL (use SDL_SetWindowSize to "change resolution")
    // available switch SDL2 video modes :
    // 1920 x 1080 @ 32 bpp (SDL_PIXELFORMAT_RGBA8888)
    // 1280 x 720 @ 32 bpp (SDL_PIXELFORMAT_RGBA8888)
    window = SDL_CreateWindow("sdl2_gles2", 0, 0, w, h, 0);
    if (!window) {
        SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // create a renderer (OpenGL ES2)
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // open CONTROLLER_PLAYER_1 and CONTROLLER_PLAYER_2
    // when railed, both joycons are mapped to joystick #0,
    // else joycons are individually mapped to joystick #0, joystick #1, ...
    // https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L45
    for (int i = 0; i < 2; i++) {
        if (SDL_JoystickOpen(i) == NULL) {
            SDL_Log("SDL_JoystickOpen: %s\n", SDL_GetError());
            SDL_Quit();
            return -1;
        }
    }

    while (!done) {
		
	while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_JOYBUTTONDOWN:
			if (event.jbutton.button == X)
            {
			

			for(i = 0; i < 100; i++)
			{
			Strobe(w, h, window, renderer);
			}
		
		
            }
			
            if (event.jbutton.button == A)
            {
               CyanScreen(w, h, window, renderer);
            }
			
			if (event.jbutton.button == B)
            {
               BlackScreen(w, h, window, renderer);
            }

			
			if (event.jbutton.button == Y)
            {
               GlowScreen(w, h, window, renderer);
            }
			
			//dpad
			if (event.jbutton.button == DPADU)
            {
               CyanScreen(w, h, window, renderer);
            }			
			if (event.jbutton.button == DPADL)
            {
               GlowScreen(w, h, window, renderer);
            }			
			if (event.jbutton.button == DPADR)
            {
               GreenScreen(w, h, window, renderer);
            }
			if (event.jbutton.button == DPADD)
            {
               NavyScreen(w, h, window, renderer);
            }			
			
			
			if (event.jbutton.button == PLUS)
            {
               done = 1;
            }
            break;
        }
    }		
		

        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_RenderClear(renderer);
		
		//GlowScreen(w, h, window, renderer);
		//SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}







