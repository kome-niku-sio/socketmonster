#include "socketmonster.h"
#include"socketdata.h"

enum what_select select_whatdo(int *sc,int *nowm,int maxH[3],Monster *nowMonster,Monster myMonster[3],Monster yourMonster){
  Monster *lastMonster;
  SDL_Event event;
  int p;
  int i=0;
  enum select_state select_state = choosing; /*選択状態を示す*/  
  enum what_select what_select = choose_command; /*何を選択しているかを示す*/

  /*eventの初期化を行う*/
  while(SDL_PollEvent(&event)){
  }
  
  /*選択処理開始*/
  while(select_state == choosing){
    if(SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_KEYDOWN:
	switch(event.key.keysym.sym){
	case SDLK_UP:
	  if(i-2 >= 0)
	    i = i-2;
	  break;
	case SDLK_DOWN:
	  if(i+2 <= 3)
	    i = i+2;
	  break;
	case SDLK_LEFT:
	  if(i-1 >= 0)
	    i = i-1;
	  break;
	case SDLK_RIGHT:
	  if(i+1 <= 3)
	    i = i+1;
	  break;
	  /*決定キー*/
	case SDLK_SPACE:
	case SDLK_RETURN:
	case SDLK_z:
	  select_state = decided;
	  break;
	  /*キャンセルキー*/
	case SDLK_ESCAPE:
	case SDLK_x:
	  if(what_select != choose_command)
	    select_state = canceled;
	  break;
	default:
	  break;
	}
	if(select_state == decided){
	  /*行動選択画面で決定キーを押した場合*/
	  if(what_select == choose_command){
	    
	    /*たたかう　を選択*/
	    if(i == 0){
	      what_select = choose_skill;
	      select_state = choosing;
	    }
	    
	    /*どうぐ　を選択*/
	    if(i == 1){
	      show_battle_message("道具に頼るな！");
	      command_draw(i,what_select,*nowMonster);
	      select_state = choosing;
	    }  
	    
	    /*ソケモン を　選択*/
	    if(i == 2){
	      /*かげふみの判定 影踏み発動時は交換不可能*/
	      if(strcmp(yourMonster.name,"シャンデラ") == 0 && strcmp(nowMonster->name,"シャンデラ") != 0){
		show_battle_message("シャンデラのかげふみで 交換できない！");

		SDL_Flip(SDL_GetVideoSurface());

		SDL_Delay(1000);

		select_state = choosing;

	      }else{
		what_select = choose_monster;
		lastMonster = &myMonster[*nowm];
		
		if(*nowm == 0)
		  select_state = change_monster_select(nowMonster,myMonster[1],myMonster[2]);
		else if(*nowm == 1)
		  select_state = change_monster_select(nowMonster,myMonster[0],myMonster[2]);
		else
		  select_state = change_monster_select(nowMonster,myMonster[0],myMonster[1]);
		
		if(select_state == decided){
		  
		  /*再生力の判定 HP1/3回復*/
		  if(strcmp(lastMonster->name,"ヤドラン") == 0){
		    
		    /*最大HPより大きくならないように判定*/
		    if(lastMonster->status[0] + (maxH[*nowm]/3) > maxH[*nowm])
		      lastMonster->status[0] = maxH[*nowm];
		    
		    else
		      lastMonster->status[0] = lastMonster->status[0] + (maxH[*nowm]/3);
		  }
		  /*現在ポケモン番号の変更*/
		  for(p=0;p <= 2;p++){
		    if(strcmp(nowMonster->name,myMonster[p].name) == 0)
		      *nowm = p;
		  }
		}
	      }
	    }
	    /*にげる　を　選択*/
	    if(i == 3){
	      show_battle_message("甘えるな！！");
	      /*sfs();
	      SDL_Quit();
	      exit(1);*/
	      //デバッグ用
	      command_draw(i,what_select,*nowMonster);
	      select_state = choosing;
	    }
	    SDL_Flip(SDL_GetVideoSurface());
	    
	    if (what_select == choose_command){
		SDL_Delay(1000);
		battlesituation_draw(maxH[*nowm],*nowMonster,yourMonster);
		show_battle_message("どうする？");
		command_draw(i,what_select,*nowMonster);
		SDL_Flip(SDL_GetVideoSurface());
	    }
	    
	  }
	  /*技選択画面で決定キーを押した場合*/
	  else if(what_select == choose_skill){
	    if(i == 0)
	      *sc = 0;
	    if(i == 1)
	      *sc = 1;
	    if(i == 2)
	      *sc = 2;
	    if(i == 3)
	      *sc = 3;
      }
      }
	/*キャンセル時*/
	if(select_state == canceled){
	  *sc = 4;
	  what_select = choose_command;
	  i = 0;
	  battlesituation_draw(maxH[*nowm],*nowMonster,yourMonster);
	  show_battle_message("どうする？");
	  command_draw(i,what_select,*nowMonster);
	  SDL_Flip(SDL_GetVideoSurface());
	  select_state = choosing;
	}
	/*未決定時*/
	else if(select_state == choosing){
	  command_draw(i,what_select,*nowMonster);
	  SDL_Flip(SDL_GetVideoSurface());
	}
	break;
      default:
	break;
      }
    }
  }
  return what_select;
}
