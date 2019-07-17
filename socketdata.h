#ifndef _SOCKETDATA_H_
#define _SOCKETDATA_H_


#include<stdio.h>
#include<string.h>
#include "SDL.h"


typedef struct Skill{
  char name[30];
  int way;
  int power;
  int type;
  int acc;
  SDL_Surface* image;
}Skill;

typedef struct Monster{
  char name[20];
  int status[6];
  int type[2];
  struct Skill myskill[4];
  SDL_Surface* mimage;
  SDL_Surface* yimage;
  SDL_Surface* detail;
}Monster;

      

#endif /* _SOCKETDATA_H_*/
