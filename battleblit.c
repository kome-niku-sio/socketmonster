#include "socketmonster.h"
#include "socketdata.h"


SDL_Color black = {0x00, 0x00, 0x00};
SDL_Color blue = {0x00, 0x00, 0xff};
SDL_Color white = {0xff, 0xff, 0xff};
SDL_Color salmon = {0xfa,0x80,0x72};
SDL_Color orangered = {0xff,0x45,0x00};

void battle_blit_Init(){
  int cc;
  
  
  //背景の初期化
  background.image = SDL_LoadBMP("battleBG.bmp");
  // 画像の矩形情報設定
  background.rect.x = 0;
  background.rect.y = 0;
  background.rect.w = background.image->w;
  background.rect.h = background.image->h;
  
  // 画像配置位置情報の設定
  background.scr_rect.x = 0;
  background.scr_rect.y = 0;
  
  
  //メッセージウィンドウの初期化
  message_window.image = SDL_LoadBMP("MessageBack-1.bmp");

  SDL_SetColorKey(message_window.image, SDL_SRCCOLORKEY, SDL_MapRGB(message_window.image->format, 255, 255, 255));
  // 画像の矩形情報設定
  message_window.rect.x = 0;
  message_window.rect.y = 0;
  message_window.rect.w = message_window.image->w;
  message_window.rect.h = message_window.image->h;
  
  // 画像配置位置情報の設定
  message_window.scr_rect.x = 0;
  message_window.scr_rect.y = 480-92;

  myhp.image = SDL_LoadBMP("HP.bmp");

  SDL_SetColorKey(myhp.image, SDL_SRCCOLORKEY, SDL_MapRGB(myhp.image->format, 0, 0, 0));
  // 画像の矩形情報設定
  myhp.rect.x = 0;
  myhp.rect.y = 0;
  myhp.rect.w = myhp.image->w;
  myhp.rect.h = myhp.image->h;
  
  // 画像配置位置情報の設定
  myhp.scr_rect.x = mhgx;
  myhp.scr_rect.y = mhgy;

  yourhp.image = SDL_LoadBMP("HP.bmp");

 SDL_SetColorKey(yourhp.image, SDL_SRCCOLORKEY, SDL_MapRGB(yourhp.image->format, 0, 0, 0));
  // 画像の矩形情報設定
  yourhp.rect.x = 0;
  yourhp.rect.y = 0;
  yourhp.rect.w = yourhp.image->w;
  yourhp.rect.h = yourhp.image->h;
  
  // 画像配置位置情報の設定
  yourhp.scr_rect.x = yhgx;
  yourhp.scr_rect.y = yhgy;


  //自モンスター表示の初期化
  nowmymonster_pic.image = SDL_LoadBMP("119_2.bmp");
    // 画像の矩形情報設定
  nowmymonster_pic.rect.x = 0;
  nowmymonster_pic.rect.y = 0;
  nowmymonster_pic.rect.w = nowmymonster_pic.image->w;
  nowmymonster_pic.rect.h = nowmymonster_pic.image->h;
  
  // 画像配置位置情報の設定
  nowmymonster_pic.scr_rect.x = mmx;
  nowmymonster_pic.scr_rect.y = mmy;

  //相手モンスター表示の初期化
  nowyourmonster_pic.image = SDL_LoadBMP("119.bmp");

  // 画像の矩形情報設定
  nowyourmonster_pic.rect.x = 0;
  nowyourmonster_pic.rect.y = 0;
  nowyourmonster_pic.rect.w = nowyourmonster_pic.image->w;
  nowyourmonster_pic.rect.h = nowyourmonster_pic.image->h;
  
  // 画像配置位置情報の設定
  nowyourmonster_pic.scr_rect.x = ymx;
  nowyourmonster_pic.scr_rect.y = ymy;

  
  //技説明表示画像初期設定
    nowskill_pic.image = SDL_LoadBMP("skill00.bmp");

    // 画像の矩形情報設定
  nowskill_pic.rect.x = 0;
  nowskill_pic.rect.y = 0;
  nowskill_pic.rect.w = nowskill_pic.image->w;
  nowskill_pic.rect.h = nowskill_pic.image->h;
  
  // 画像配置位置情報の設定
  nowskill_pic.scr_rect.x = skx;
  nowskill_pic.scr_rect.y = sky;


  //選択肢画像設定
  skillselect[0].image = SDL_LoadBMP("select1.bmp");
  skillselect[1].image = SDL_LoadBMP("select3.bmp");
  skillselect[2].image = SDL_LoadBMP("select2.bmp");
  skillselect[3].image = SDL_LoadBMP("select4.bmp");
  
  for(cc=0;cc<4;cc++){
    // 画像の矩形情報設定
    SDL_SetColorKey(skillselect[cc].image, SDL_SRCCOLORKEY, SDL_MapRGB(skillselect[cc].image->format, 0, 0, 0));
    skillselect[cc].rect.x = 0;
    skillselect[cc].rect.y = 0;
    skillselect[cc].rect.w = skillselect[cc].image->w;
    skillselect[cc].rect.h = skillselect[cc].image->h;
    
    // 画像配置位置情報の設定
    skillselect[cc].scr_rect.x = slx;
    skillselect[cc].scr_rect.y = sly;
  }

  commandselect[0].image  = SDL_LoadBMP("command1.bmp");
  commandselect[1].image  = SDL_LoadBMP("command2.bmp");
  commandselect[2].image  = SDL_LoadBMP("command3.bmp");
  commandselect[3].image  = SDL_LoadBMP("command4.bmp");
  

  
  for(cc=0;cc<4;cc++){
    // 画像の矩形情報設定
SDL_SetColorKey(commandselect[cc].image, SDL_SRCCOLORKEY, SDL_MapRGB(commandselect[cc].image->format, 0, 0, 0));
  
    commandselect[cc].rect.x = 0;
    commandselect[cc].rect.y = 0;
    commandselect[cc].rect.w =commandselect[cc].image->w;
    commandselect[cc].rect.h =commandselect[cc].image->h;
    
    // 画像配置位置情報の設定
    commandselect[cc].scr_rect.x = slx;
    commandselect[cc].scr_rect.y = sly;
  }
  
}

void show_message(TTF_Font* font,const char *msg,int x,int y,SDL_Color color){
  SDL_Surface *image;
  SDL_Rect rect,scr_rect;

  image = TTF_RenderUTF8_Blended(font,msg,color);
  
  /* 画像の矩形情報設定 */
  rect.x = 0;
  rect.y = 0;
  rect.w = image->w;
  rect.h = image->h;
  
  /* 画像配置位置情報の設定 */
  scr_rect.x = x;
  scr_rect.y = y;

  SDL_BlitSurface(image, &rect, SDL_GetVideoSurface(), &scr_rect);
}

void show_battle_message(char *message){
  SDL_BlitSurface(message_window.image,&message_window.rect,SDL_GetVideoSurface(),&message_window.scr_rect);
  
  show_message(messagefont,message,MESSAGE_Rect_x,MESSAGE_Rect_y,black);
}

void adjust_high(Monster justmonster){

  if(strcmp(justmonster.name,monster[0].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy0;

  if(strcmp(justmonster.name,monster[1].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy1;

  if(strcmp(justmonster.name,monster[2].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy2;

  if(strcmp(justmonster.name,monster[3].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy3;

  if(strcmp(justmonster.name,monster[4].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy4;

  if(strcmp(justmonster.name,monster[5].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy5;

  if(strcmp(justmonster.name,monster[6].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy6;

  if(strcmp(justmonster.name,monster[7].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy7;

  if(strcmp(justmonster.name,monster[8].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy8;

  if(strcmp(justmonster.name,monster[9].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy9;

  if(strcmp(justmonster.name,monster[10].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy10;

  if(strcmp(justmonster.name,monster[11].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy11;

  if(strcmp(justmonster.name,monster[12].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy12;

  if(strcmp(justmonster.name,monster[13].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy13;

  if(strcmp(justmonster.name,monster[14].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy14;

  if(strcmp(justmonster.name,monster[15].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy15;

  if(strcmp(justmonster.name,monster[16].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy16;

  if(strcmp(justmonster.name,monster[17].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy17;

  if(strcmp(justmonster.name,monster[18].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy18;

  if(strcmp(justmonster.name,monster[19].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy19;

  if(strcmp(justmonster.name,monster[20].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy20;

  if(strcmp(justmonster.name,monster[21].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy21;

  if(strcmp(justmonster.name,monster[22].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy22;

  if(strcmp(justmonster.name,monster[23].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy23;

  if(strcmp(justmonster.name,monster[24].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy24;

  if(strcmp(justmonster.name,monster[25].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy25;

  if(strcmp(justmonster.name,monster[26].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy26;

  if(strcmp(justmonster.name,monster[27].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy27;

  if(strcmp(justmonster.name,monster[28].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy28;

  if(strcmp(justmonster.name,monster[29].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy29;

  if(strcmp(justmonster.name,monster[30].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy30;

  if(strcmp(justmonster.name,monster[31].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy31;

  if(strcmp(justmonster.name,monster[32].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy32;

  if(strcmp(justmonster.name,monster[33].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy33;

  if(strcmp(justmonster.name,monster[34].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy34;

  if(strcmp(justmonster.name,monster[35].name) == 0)
    nowmymonster_pic.scr_rect.y = mmy35;

}

void Mymonster_draw(int h,Monster drawmonster){
  SDL_Rect H_rect;
  char msg[MAX_MSG];
  SDL_Surface *video_surface;
  nowmymonster_pic.image = drawmonster.yimage;

  video_surface = SDL_GetVideoSurface();

    SDL_SetColorKey(nowmymonster_pic.image, SDL_SRCCOLORKEY, SDL_MapRGB(nowmymonster_pic.image->format, 255, 255, 255));
  
 /*ポケモンごとに高さが違うのでその調整を行う*/

 adjust_high(drawmonster);

  SDL_BlitSurface(nowmymonster_pic.image, &nowmymonster_pic.rect, SDL_GetVideoSurface(), &nowmymonster_pic.scr_rect);

  //自モンスター名前描写
  sprintf(msg,"%s      lv50",drawmonster.name);
  show_message(namefont,msg,mnx,mny,orangered);

  sprintf(msg,"HP  %d     /    %d",drawmonster.status[0],h);
  show_message(namefont,msg,mhx,mhy,black);

  SDL_BlitSurface(myhp.image, &myhp.rect, SDL_GetVideoSurface(), &myhp.scr_rect);

  /*HPゲージの調整*/
  H_rect.x = mhgx + 4 + ((double)drawmonster.status[0]/(double)h) * (myhp.image->w - 8);
  H_rect.y = mhgy + 2;
  H_rect.w = (double)(h - drawmonster.status[0])/(double)h * (myhp.image->w - 8);
  H_rect.h = myhp.image->h - 4;

  SDL_FillRect(video_surface,&H_rect,SDL_MapRGB(video_surface->format,0,0,0));

}

void Yourmonster_draw(Monster drawmonster){
  SDL_Rect H_rect;
  char msg[MAX_MSG];
  nowyourmonster_pic.image = drawmonster.mimage;
  SDL_Surface *video_surface;
  int h;

  h = get_monster(drawmonster.name).status[0];

  video_surface = SDL_GetVideoSurface();

    SDL_SetColorKey(nowyourmonster_pic.image, SDL_SRCCOLORKEY, SDL_MapRGB(nowyourmonster_pic.image->format, 255, 255, 255));
  
  SDL_BlitSurface(nowyourmonster_pic.image, &nowyourmonster_pic.rect, SDL_GetVideoSurface(), &nowyourmonster_pic.scr_rect);

  //相手モンスター名前描写
  sprintf(msg,"%s      lv50",drawmonster.name);
  show_message(namefont,msg,ynx,yny,orangered);

  SDL_BlitSurface(yourhp.image, &yourhp.rect, SDL_GetVideoSurface(), &yourhp.scr_rect);

  /*HPゲージの調整*/
  H_rect.x = yhgx + 4 + ((double)drawmonster.status[0]/(double)h) * (yourhp.image->w - 8);
  H_rect.y = yhgy + 2;
  H_rect.w = (double)(h - drawmonster.status[0])/(double)h * (yourhp.image->w - 8);
  H_rect.h = yourhp.image->h - 4;

  SDL_FillRect(video_surface,&H_rect,SDL_MapRGB(video_surface->format,0,0,0));

}

void show_weather(enum weather weather){
  
  if(weather == sandstorm){

    show_battle_message("すなあらしが吹き荒れている");
    
    SDL_Flip(SDL_GetVideoSurface());
    
    SDL_Delay(2000);

  }

  if(weather == hailstone){

    show_battle_message("あられが降り続いている");
    
    SDL_Flip(SDL_GetVideoSurface());
    
    SDL_Delay(2000);

  }

}


int judge_characteristic(enum weather* weather,char hisname[MAX_MSG],Monster* amonster,Monster* bmonster){
  char msg[MAX_MSG];
  /*amonster = 発動元 bmonster = 発動先*/

  if(strcmp(amonster->name,"ユキノオー") == 0){

    if(*weather != hailstone){

      sprintf(msg,"%sの ユキノオーの ゆきふらし！",hisname);

      show_battle_message(msg);

      SDL_Flip(SDL_GetVideoSurface());
      
      SDL_Delay(2000);

      *weather = hailstone;

      show_weather(*weather);

    }

    return 0;
  }



  if(strcmp(amonster->name,"バンギラス") == 0){

    if(*weather != sandstorm){

      sprintf(msg,"%sの バンギラスの すなおこし！",hisname);

      show_battle_message(msg);

      SDL_Flip(SDL_GetVideoSurface());
      
      SDL_Delay(2000);

      *weather = sandstorm;

      show_weather(*weather);

    }

    return 0;
  }

    
  if(strcmp(amonster->name,"サンダー") == 0){

    sprintf(msg,"%sの サンダーはプレッシャーを放っている!!",hisname);

    show_battle_message(msg);

    SDL_Flip(SDL_GetVideoSurface());

    SDL_Delay(2000);

    return 0;
  }

  if(strcmp(amonster->name,"ボーマンダ") == 0){

    sprintf(msg,"%sの ボーマンダの いかく！",hisname);

    show_battle_message(msg);

    SDL_Flip(SDL_GetVideoSurface());

    if(strcmp(bmonster->name,"メタグロス") == 0){

      SDL_Delay(1000);

      show_battle_message("メタグロスは クリアボディで能力値が下がらない！");

      SDL_Flip(SDL_GetVideoSurface());

      SDL_Delay(2000);

    }else{
      
      SDL_Delay(2000);

      sprintf(msg,"%sの %sの こうげきが下がった！",hisname,bmonster->name);

      bmonster->status[1] = bmonster->status[1] *0.67; 

      show_battle_message(msg);

      SDL_Flip(SDL_GetVideoSurface());

      SDL_Delay(2000);

      /*かちきの判定*/
      if(strcmp(bmonster->name,"ミロカロス") == 0){

	sprintf(msg,"ミロカロスの かちき！特攻がぐーんと上がった！");

	bmonster->status[3] = bmonster->status[3] * 2;

	show_battle_message(msg);
	
	SDL_Flip(SDL_GetVideoSurface());
	
	SDL_Delay(2000);

      }
      
    }
    return 0;
  }
  return 0;
}
      

void command_draw(int k,int m,Monster skillmonster){
  nowskill_pic.image = skillmonster.myskill[k].image;

  SDL_SetColorKey(nowskill_pic.image, SDL_SRCCOLORKEY, SDL_MapRGB(nowskill_pic.image->format, 0, 0, 0));

  if(m == 0)
  SDL_BlitSurface(commandselect[k].image, &commandselect[k].rect, SDL_GetVideoSurface(), &commandselect[k].scr_rect);
  else{
    SDL_BlitSurface(skillselect[k].image, &skillselect[k].rect, SDL_GetVideoSurface(), &skillselect[k].scr_rect);
    SDL_BlitSurface(nowskill_pic.image, &nowskill_pic.rect, SDL_GetVideoSurface(), &nowskill_pic.scr_rect);
  }

}


void battlesituation_draw(int h,Monster mymonster,Monster yourmonster){

  //背景描写
  SDL_BlitSurface(background.image, &background.rect, SDL_GetVideoSurface(), &background.scr_rect);
  
  Mymonster_draw(h,mymonster);
  
  Yourmonster_draw(yourmonster);
  
}

/*天候ダメージ用関数*/
void damage_weather(enum weather weather,Monster* Monster0,Monster* Monster1,char name0[MAX_MSG],char name1[MAX_MSG]){
  char msg[MAX_MSG];
  int maxH[2];

  show_weather(weather);

  /*ダメージ量決定のために最大HPを呼び出しておく*/
  maxH[0] = get_monster(Monster0->name).status[0];
  maxH[1] = get_monster(Monster1->name).status[0];

 //0:なし 1:ノ 2:炎 3:水 4:電 5:草 6:氷 7:格 8:毒 9:地 10:飛 11:超 12:虫 13:岩 14:霊 15:竜 16:悪 17:鋼 18:妖

  /*砂嵐時*/
  /*岩 13 鋼 17 地面 9 以外はダメージを受ける*/
  if(weather == sandstorm){
    /*素早さが早い方が先にダメージを受ける*/
    if(Monster0->status[5] >= Monster1->status[5]){
      
      if(Monster0->type[0] != 13 && Monster0->type[0] != 17 && Monster0->type[0] != 9 && strcmp(Monster0->name,"フーディン") != 0){
	if(Monster0->type[1] != 13 && Monster0->type[1] != 17 && Monster0->type[1] != 9 && strcmp(Monster0->name,"フーディン") != 0){
	  
	  sprintf(msg,"すなあらしが %sの %s をおそう！",name0,Monster0->name);

	  show_battle_message(msg);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);

	  Monster0->status[0] -=  maxH[0]/16;

	  if(Monster0->status[0] < 0)
	    Monster0->status[0] = 0;

	  battlesituation_draw(maxH[0],*Monster0,*Monster1);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	}
      }
      if(Monster1->type[0] != 13 && Monster1->type[0] != 17 && Monster1->type[0] != 9 && strcmp(Monster1->name,"フーディン") != 0){
	if(Monster1->type[1] != 13 && Monster1->type[1] != 17 && Monster1->type[1] != 9 && strcmp(Monster1->name,"フーディン") != 0){
	  sprintf(msg,"すなあらしが %sの %s をおそう！",name1,Monster1->name);
	  
	  show_battle_message(msg);
	  
	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);

	  Monster1->status[0] -=  maxH[1]/16;

	  if(Monster1->status[0] < 0)
	    Monster1->status[0] = 0;

	  battlesituation_draw(maxH[0],*Monster0,*Monster1);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	}
      }
    }else if(Monster1->status[5] > Monster0->status[5]){
      if(Monster1->type[0] != 13 && Monster1->type[0] != 17 && Monster1->type[0] != 9 && strcmp(Monster1->name,"フーディン") != 0){
	if(Monster1->type[1] != 13 && Monster1->type[1] != 17 && Monster1->type[1] != 9 && strcmp(Monster1->name,"フーディン") != 0){
	  sprintf(msg,"すなあらしが %sの %s をおそう！",name1,Monster1->name);
	  
	  show_battle_message(msg);
	  
	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);

	  Monster1->status[0] -=  maxH[1]/16;

	  if(Monster1->status[0] < 0)
	    Monster1->status[0] = 0;

	  battlesituation_draw(maxH[0],*Monster0,*Monster1);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	}
      }
      if(Monster0->type[0] != 13 && Monster0->type[0] != 17 && Monster0->type[0] != 9 && strcmp(Monster0->name,"フーディン") != 0){
	if(Monster0->type[1] != 13 && Monster0->type[1] != 17 && Monster0->type[1] != 9 && strcmp(Monster0->name,"フーディン") != 0){
	  
	  sprintf(msg,"すなあらしが %sの %s をおそう！",name0,Monster0->name);

	  show_battle_message(msg);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);

	  Monster0->status[0] -=  maxH[0]/16;

	  if(Monster0->status[0] < 0)
	    Monster0->status[0] = 0;

	  battlesituation_draw(maxH[0],*Monster0,*Monster1);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	}
      }
    }
  }
  /*霰時*/
  /*氷 6 以外がダメージをうける*/
  if(weather == hailstone){
    /*素早さが早い方が先にダメージを受ける*/
    if(Monster0->status[5] >= Monster1->status[5]){
      
      if(Monster0->type[0] != 6 && strcmp(Monster0->name,"フーディン") != 0){
	if(Monster0->type[1] != 6 && strcmp(Monster0->name,"フーディン") != 0){
	  
	  sprintf(msg,"あられが %sの %s をおそう！",name0,Monster0->name);

	  show_battle_message(msg);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);

	  Monster0->status[0] -=  maxH[0]/16;

	  if(Monster0->status[0] < 0)
	    Monster0->status[0] = 0;

	  battlesituation_draw(maxH[0],*Monster0,*Monster1);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	}
      }
      if(Monster1->type[0] != 6 && strcmp(Monster1->name,"フーディン") != 0){
	if(Monster1->type[1] !=6 && strcmp(Monster1->name,"フーディン") != 0){
	  sprintf(msg,"あられが %sの %s をおそう！",name1,Monster1->name);
	  
	  show_battle_message(msg);
	  
	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);

	  Monster1->status[0] -=  maxH[1]/16;

	  if(Monster1->status[0] < 0)
	    Monster1->status[0] = 0;

	  battlesituation_draw(maxH[0],*Monster0,*Monster1);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	}
      }
    }else if(Monster1->status[5] > Monster0->status[5]){
      if(Monster1->type[0] != 6 && strcmp(Monster1->name,"フーディン") != 0){
	if(Monster1->type[1] != 6 && strcmp(Monster1->name,"フーディン") != 0){
	  sprintf(msg,"あられが %sの %s をおそう！",name1,Monster1->name);
	  
	  show_battle_message(msg);
	  
	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);

	  Monster1->status[0] -=  maxH[1]/16;

	  if(Monster1->status[0] < 0)
	    Monster1->status[0] = 0;

	  battlesituation_draw(maxH[0],*Monster0,*Monster1);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	}
      }
      if(Monster0->type[0] != 6 && strcmp(Monster0->name,"フーディン") != 0){
	if(Monster0->type[1] != 6 && strcmp(Monster0->name,"フーディン") != 0){
	  
	  sprintf(msg,"あられが %sの %s をおそう！",name0,Monster0->name);

	  show_battle_message(msg);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);

	  Monster0->status[0] -=  maxH[0]/16;

	  if(Monster0->status[0] < 0)
	    Monster0->status[0] = 0;

	  battlesituation_draw(maxH[0],*Monster0,*Monster1);

	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	}
      }
    }
  }
}





int show_efficiency(int d,Skill askill,Monster bmonster){
  double e;/*倍率格納用*/
  char msg[MAX_MSG];

  /*ふしぎなまもり判定,ばつぐん未満はダメージ0*/
  if(strcmp(bmonster.name,"ヌケニン") == 0 && AandD[askill.type][bmonster.type[0]] * AandD[askill.type][bmonster.type[1]] <= 1 ){
    show_battle_message("ヌケニンは ふしぎなまもりで ダメージを受けない！");
    return 0;
  }
  
  /*がんじょうの判定 一撃必殺無効*/
  if(strcmp(bmonster.name,"ハガネール") == 0){
    if(strcmp(askill.name,"つのドリル")==0 || strcmp(askill.name,"ぜったいれいど")==0 || strcmp(askill.name,"ハサミギロチン") == 0){
      show_battle_message("ハガネールは がんじょうで 一撃必殺は 効かない！");
      return 0;
    }
  }

  /*技があまえるの場合*/
  if(strcmp(askill.name,"あまえる") == 0){
    show_battle_message("ニンフィア は かわいい！");
    return 0;
  }

  /*技がはねるの場合*/
  if(strcmp(askill.name,"はねる") == 0){
    show_battle_message("アズマオウ は 必死だ！");
    return 0;
  }

  /*ひらいしんの判定 電気無効*/
  if(strcmp(bmonster.name,"ピカチュウ") == 0 && askill.type == 4){
    show_battle_message("ひらいしんで でんきタイプは 効かない！");
    return 0;
  }
  
  /*ひらいしんの判定 電気無効*/
  if(strcmp(bmonster.name,"アズマオウ") == 0 && askill.type == 4){
    show_battle_message("ひらいしんで でんきタイプは 効かない！");
    return 0;
  }

  /*ちょすいの判定 水無効*/
  if(strcmp(bmonster.name,"ヌオー") == 0 && askill.type == 3){
    show_battle_message("ちょすいで みずタイプは 効かない！");
    return 0;
  }

  /*ちょすいの判定 水無効*/
  if(strcmp(bmonster.name,"ニョロボン") == 0 && askill.type == 3){
    show_battle_message("ちょすいで みずタイプは 効かない！");
    return 0;
  }

  /*ふゆうの判定 地面無効*/
  if(strcmp(bmonster.name,"ラティオス") == 0 && askill.type == 9){
    show_battle_message("ふゆうで じめんタイプは 効かない！");
    return 0;
  }

  /*ふゆうの判定 地面無効*/
  if(strcmp(bmonster.name,"シビルドン") == 0 && askill.type == 9){
    show_battle_message("ふゆうで じめんタイプは 効かない！");
    return 0;
  }

  /*ふゆうの判定 地面無効*/
  if(strcmp(bmonster.name,"ゲンガー") == 0 && askill.type == 9){
    show_battle_message("ふゆうで じめんタイプは 効かない！");
    return 0;
  }

  /*もらいびの判定　炎無効*/
  if(strcmp(bmonster.name,"サーナイト") == 0 && askill.type == 2){
    show_battle_message("もらいびで ほのおタイプは 効かない！");
    return 0;
  }

  e =  AandD[askill.type][bmonster.type[0]] * AandD[askill.type][bmonster.type[1]];
  /*ダメージが0の場合*/
  if(d == 0){

    if(e == 0){
      sprintf(msg,"%sには効果がないようだ....",bmonster.name);
      show_battle_message(msg);
    }
    else{
      sprintf(msg,"%sには当たらなかった！",bmonster.name);
      show_battle_message(msg);
    }
  }
  /*一撃必殺の命中時には特殊処理を行う*/
  else if(strcmp(askill.name,"つのドリル")==0 || strcmp(askill.name,"ぜったいれいど")==0 || strcmp(askill.name,"ハサミギロチン") == 0){

    show_battle_message("一　撃　必　殺 ！");

  }
  
  else{

    if(e > 1)
      show_battle_message("効果 は 抜群だ！！");
    
    if(e < 1)
      show_battle_message("効果は 今ひとつ のようだ");
    
  }
  return 0;
}
void win_draw(){
  SDL_Surface* image;
  SDL_Rect rect,scr_rect;
  SDL_Event event;
  int exit_prg = 0;

  image  = SDL_LoadBMP("win_image.bmp");

  SDL_SetVideoMode(image->w,image->h,32,SDL_HWSURFACE);

  rect.x = 0;
  rect.y = 0;
  rect.w = image->w;
  rect.h = image->h;

  scr_rect.x = 0;
  scr_rect.y = 0;

  draw(image, &rect, &scr_rect);

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
  
  SDL_FreeSurface(image);

  SDL_Quit();



}

void lose_draw(){
  SDL_Surface* image;
  SDL_Rect rect,scr_rect;
  SDL_Event event;
  int exit_prg = 0;

  image  = SDL_LoadBMP("lose_image.bmp");

  SDL_SetVideoMode(image->w,image->h,32,SDL_HWSURFACE);

  rect.x = 0;
  rect.y = 0;
  rect.w = image->w;
  rect.h = image->h;

  scr_rect.x = 0;
  scr_rect.y = 0;

  draw(image, &rect, &scr_rect);

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
  
  SDL_FreeSurface(image);

  SDL_Quit();



}

void sfs(){
  int p;

  for(p=0;p<42;p++){
    SDL_FreeSurface(skill[p].image);
  }

  for(p=0;p<15;p++){
    SDL_FreeSurface(monster[p].mimage);
    SDL_FreeSurface(monster[p].yimage);
    SDL_FreeSurface(monster[p].detail);
  }

  
  SDL_FreeSurface(background.image);
  
  SDL_FreeSurface(message_window.image);
  
  for(p=0;p<4;p++){
    SDL_FreeSurface(skillselect[p].image);
    SDL_FreeSurface(commandselect[p].image);
  }
  
}
