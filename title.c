#include "socketmonster.h"
#include "socketdata.h"

void title(){
  SDL_Surface* title;
  SDL_Rect rect,scr_rect;
  SDL_Event event;
  int exit_prg = 0;

  title = SDL_LoadBMP("soketmonster_title.bmp");

  SDL_SetVideoMode(title->w,title->h,32,SDL_HWSURFACE);

  rect.x = 0;
  rect.y = 0;
  rect.w = title->w;
  rect.h = title->h;

  scr_rect.x = 0;
  scr_rect.y = 0;
  draw(title, &rect, &scr_rect);

  while(exit_prg == 0){
    if(SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_KEYDOWN:
	switch(event.key.keysym.sym){
	case SDLK_SPACE:
	  exit_prg = 1;
	  break;
	case SDLK_ESCAPE:
	  exit_prg = 1;
	  break;
	default:
	  break;
	}
      }
    }
    SDL_Delay(1);
  }
  
  SDL_FreeSurface(title);

  SDL_Quit();



}
