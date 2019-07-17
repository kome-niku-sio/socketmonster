#include "socketmonster.h"
#include "socketdata.h"

void change_select_Init(pic arrow[2],pic change_select_monster[2],pic change_select_detail[2]){

  /*画像の初期化開始*/

  arrow[0].image = SDL_LoadBMP("arrow.bmp");

  SDL_SetColorKey(arrow[0].image, SDL_SRCCOLORKEY, SDL_MapRGB(arrow[0].image->format, 0, 0, 0));

  arrow[0].rect.x = 0;
  arrow[0].rect.y = 0;
  arrow[0].rect.w = arrow[0].image->w;
  arrow[0].rect.h = arrow[0].image->h;

  arrow[0].scr_rect.x = csx0 - arrow[0].image->w;
  arrow[0].scr_rect.y = csy0 - arrow[0].image->h + 64;

  arrow[1].image = SDL_LoadBMP("arrow.bmp");

  SDL_SetColorKey(arrow[1].image, SDL_SRCCOLORKEY, SDL_MapRGB(arrow[1].image->format, 0, 0, 0));

  arrow[1].rect.x = 0;
  arrow[1].rect.y = 0;
  arrow[1].rect.w = arrow[1].image->w;
  arrow[1].rect.h = arrow[1].image->h;

  arrow[1].scr_rect.x = csx1 - arrow[1].image->w;
  arrow[1].scr_rect.y = csy1 - arrow[1].image->h +64;


  SDL_SetColorKey(change_select_monster[0].image, SDL_SRCCOLORKEY, SDL_MapRGB(change_select_monster[0].image->format, 255, 255, 255));

  change_select_monster[0].rect.x = 0;
  change_select_monster[0].rect.y = 0;
  change_select_monster[0].rect.w = change_select_monster[0].image->w;
  change_select_monster[0].rect.h = change_select_monster[0].image->h;

  change_select_monster[0].scr_rect.x = csx0;
  change_select_monster[0].scr_rect.y = csy0;



  SDL_SetColorKey(change_select_monster[1].image, SDL_SRCCOLORKEY, SDL_MapRGB(change_select_monster[1].image->format, 255, 255, 255));

  change_select_monster[1].rect.x = 0;
  change_select_monster[1].rect.y = 0;
  change_select_monster[1].rect.w = change_select_monster[1].image->w;
  change_select_monster[1].rect.h = change_select_monster[1].image->h;

  change_select_monster[1].scr_rect.x = csx1;
  change_select_monster[1].scr_rect.y = csy1;

  SDL_SetColorKey(change_select_detail[0].image, SDL_SRCCOLORKEY, SDL_MapRGB(change_select_detail[0].image->format, 0, 0, 0));

  change_select_detail[0].rect.x = 0;
  change_select_detail[0].rect.y = 0;
  change_select_detail[0].rect.w = WINDOW_WIDTH /2;
  change_select_detail[0].rect.h = change_select_detail[0].image->h;

  change_select_detail[0].scr_rect.x = cdx0;
  change_select_detail[0].scr_rect.y = cdy0;

 SDL_SetColorKey(change_select_detail[1].image, SDL_SRCCOLORKEY, SDL_MapRGB(change_select_detail[1].image->format, 0, 0, 0));

  change_select_detail[1].rect.x = 0;
  change_select_detail[1].rect.y = 0;
  change_select_detail[1].rect.w = WINDOW_WIDTH/2;
  change_select_detail[1].rect.h = change_select_detail[1].image->h;

  change_select_detail[1].scr_rect.x = cdx1;
  change_select_detail[1].scr_rect.y = cdy1;

  /*画像の初期化完了*/
}

void change_draw(int k,pic csm[2],pic arrow[2],pic csd[2]){

  SDL_BlitSurface(background.image, &background.rect, SDL_GetVideoSurface(), &background.scr_rect);
  
  SDL_BlitSurface(csm[0].image, &csm[0].rect, SDL_GetVideoSurface(), &csm[0].scr_rect);
  
  SDL_BlitSurface(csm[1].image, &csm[0].rect, SDL_GetVideoSurface(), &csm[1].scr_rect);
  
  SDL_BlitSurface(csd[0].image, &csd[0].rect, SDL_GetVideoSurface(), &csd[0].scr_rect);
  
  SDL_BlitSurface(csd[1].image, &csd[1].rect, SDL_GetVideoSurface(), &csd[1].scr_rect);

 SDL_BlitSurface(arrow[k].image, &arrow[k].rect, SDL_GetVideoSurface(), &arrow[k].scr_rect);

}


enum select_state change_monster_select(Monster* nmr,Monster number0,Monster number1){
  int cc=0; /*選択中の選択先を示す変数*/
  SDL_Event changeevent;
  Monster monster_status[2];
  pic change_select_monster[2];
  pic change_select_detail[2];
  pic arrow[2];/*矢印、0はmonster[0],1はmonster[1]を示す*/
  enum select_state change_select_state = choosing;
  //pic change_background;

  monster_status[0] = number0;
  monster_status[1] = number1;

  change_select_monster[0].image = number0.mimage;
  change_select_monster[1].image = number1.mimage;

  change_select_detail[0].image = number0.detail;
  change_select_detail[1].image = number1.detail;

  /*eventの初期化を行う*/
  while(SDL_PollEvent(&changeevent)){
  }

  /*画像の配置位置などの設定を行う*/
  change_select_Init(arrow,change_select_monster,change_select_detail);

  /*基本描写*/
  change_draw(cc,change_select_monster,arrow,change_select_detail);

  SDL_Flip(SDL_GetVideoSurface());

  while(change_select_state == choosing){
    if(SDL_PollEvent(&changeevent)){
      switch(changeevent.type){
      case SDL_KEYDOWN:
	switch(changeevent.key.keysym.sym){
	case SDLK_LEFT:
	  if(cc == 1)
	    cc = 0;
	  break;
	case SDLK_RIGHT:
	  if(cc == 0)
	    cc = 1;
	  break;
	  /*決定キー*/
	case SDLK_SPACE:
	case SDLK_RETURN:
	case SDLK_z:
	  change_select_state = decided;
	  break;
	  /*キャンセルキー*/
	case SDLK_ESCAPE:
	case SDLK_x:
	  change_select_state = canceled;
	  break;
	default:
	  break;
	}
	/*決定した場合*/
	if(change_select_state == decided){
	  if(monster_status[cc].status[0] > 0)
	    *nmr = monster_status[cc];
	  else{
	    show_message(messagefont,"そいつは既に死んでるぞ",100,10,salmon);
	    SDL_Flip(SDL_GetVideoSurface());
	    SDL_Delay(1000);
	    change_select_state = choosing;
	  }
	}
	if(change_select_state == choosing){
	  change_draw(cc,change_select_monster,arrow,change_select_detail);
	  
	  SDL_Flip(SDL_GetVideoSurface());
	}
	break;
      default:
	break;
      }
    }
  }
  
  return change_select_state;
  
}

