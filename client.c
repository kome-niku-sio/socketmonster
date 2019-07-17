#include "socketmonster.h"
#include "socketdata.h"


void loop(char name[MAX_MSG],int mySocket,struct sockaddr_in svaddr);

int main(int argc,char* argv[]){
  init();
  int mySocket;
  int myPort = 0; //ポート番号自動割当
  char myname[MAX_MSG];/*自分の名前記入用*/
  struct sockaddr_in svaddr;

  //コマンドライン引数確認
  if(argc != 3){
    printf("usage:%s server_name user_name",argv[0]);
    exit(1);
  }
  
  strcpy(myname,argv[2]);
  
  //サーバーアドレスの取得
  get_server_addr(argv[1],&svaddr);
  
  //ソケットの生成
  mySocket = socket_and_bind(myPort);
  
  /*for(i=0;i<=14;i++){
    printf("%s    \t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",monster[i].name,monster[i].status[0],monster[i].status[1],monster[i].status[2],monster[i].status[3],monster[i].status[4],monster[i].status[5],monster[i].type[0],monster[i].type[1]);
    
    for(j=0;j<=3;j++){
    printf("%s\t%d\t%d\t%d\t%d\n",monster[i].myskill[j].name,monster[i].myskill[j].way,monster[i].myskill[j].power,monster[i].myskill[j].type,monster[i].myskill[j].acc);
    
    }
    putchar('\n');
    }*/
  
  
  //対戦処理開始
  loop(myname,mySocket,svaddr);
  
  //ソケットを閉じる
  close(mySocket);
  return 0; 
}


void loop(char myname[MAX_MSG],int mySocket,struct sockaddr_in svaddr){
  Monster myMonster[3]; /*３体選出データ保存用*/
  Monster nowMonster; /*場のモンスター保存用*/
  Monster catchMonster; /*受信モンスター保存用*/
  Monster yourMonster; /*相手の場のモンスター保存用*/
  Skill effect;/*効果判定用*/
  char yourname[MAX_MSG]; /*相手の名前を収録するのに用いる*/
  char buffer[MAX_MSG]; /*基本メッセージ読み出し用*/
  char con[MAX_MSG];
  char command[MAX_MSG];
  char charskill[MAX_MSG]; /*スキル受信に用いる*/
  char winorloss[MAX_MSG]; /*勝敗判定に使う*/
  char battlemessage[MAX_MSG]; /*戦闘時メッセージ表示*/
  int weatherturn = 0;/*天候発動ターン　=0の時はダメージなし*/
  int stopping =0;/*特性発動待機　 =1で待機中*/
  int p;/*便利変数 どうでもいいfor文とかで初期化して使います*/
  int da;/*ダメージ格納用変数*/
  int Messenger; /*0=自分、1=相手*/
  int sc;/*技決定用の変数*/
  int nowm=0; /*現在モンスターの番号*/
  int maxH[3]; /*自モンスター三体のHP最大値*/
  enum weather lastweather = normal; /*一ターン前の天気*/
  enum weather nowweather = normal; /*天候の状態を示す*/
  enum select_state select_state = choosing; /*選択状態を示す*/
  enum what_select what_select = choose_command; /*何を選択しているかを示す*/
  int a=23,b=35,c=34;

  myMonster[0] = monster[a];
  myMonster[1] = monster[b];
  myMonster[2] = monster[c];

  //接続処理
  send_message(mySocket,myname,&svaddr);
  
  //接続完了しているか確認
  receive_message(mySocket,buffer,&svaddr);
  
  strcpy(yourname,buffer);

  SDL_Init(SDL_INIT_EVERYTHING);
  
  //タイトル表示　"ソケットモンスター"←大田君が名付けました！
  title();
  
  //TTF初期化
  TTF_Init();

  //ポケモン名前表示用フォント
  namefont = TTF_OpenFont(NAME_FONT_NAME,NAME_FONT_SIZE);


  //メッセージ表示用フォント
  messagefont = TTF_OpenFont(MESSAGE_FONT_NAME,MESSAGE_FONT_SIZE);

  /*モンスター選択画面*/
  select_monster(myMonster);

  /*対戦画面用画像初期化*/
  battle_blit_Init();

  /*各ポケモンの最大HPを記録　HP表示に使う*/
  for(p=0;p<=2;p++){
    maxH[p] = myMonster[p].status[0];
  }
 
  /*1体目に選んだモンスターを場のモンスターとして記録*/
  nowMonster = myMonster[0];

  //画面起動
  SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32,SDL_HWSURFACE);

  //背景描写
  SDL_BlitSurface(background.image, &background.rect, SDL_GetVideoSurface(), &background.scr_rect);

  SDL_Flip(SDL_GetVideoSurface());

  /*プレイヤー間の歩調を合わせるための送受信*/
  send_message(mySocket,"select",&svaddr);

  receive_message(mySocket,buffer,&svaddr);

  /*目があったらソケモン勝負！*/
  sprintf(battlemessage,"%s が　勝負を仕掛けてきた！！",yourname);

  show_battle_message(battlemessage);

  SDL_Flip(SDL_GetVideoSurface());

  SDL_Delay(2000);
  
  //サーバに先頭のモンスターの情報を送信
  send_Monster(mySocket,nowMonster,&svaddr);

  //繰り出したモンスターの画像を描写
  Mymonster_draw(maxH[nowm],nowMonster);

  //繰り出し時メッセージ描写（これを一つの関数としてまとめてもよい？）
  sprintf(battlemessage,"いけっ！　%s",nowMonster.name);

  show_battle_message(battlemessage);  

  SDL_Flip(SDL_GetVideoSurface());
  
  SDL_Delay(2000);

  
  //相手が場に出したモンスターを受信
  yourMonster = receive_Monster(mySocket,&svaddr);
  
  Yourmonster_draw(yourMonster);

  sprintf(battlemessage,"%s は　%s　を繰り出してきた！",yourname,yourMonster.name);

  show_battle_message(battlemessage);

  SDL_Flip(SDL_GetVideoSurface());
  
  SDL_Delay(2000);

  /*特性発動の判定を行う*/
  /*素早さが早い方の特性が先に発動する 同速の場合は*/
  if(nowMonster.status[5] > yourMonster.status[5]){
    
    judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
    
    judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
    
  }
  else if(nowMonster.status[5] < yourMonster.status[5]){
    
    judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
    
    judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
    
  }else{
	  
    judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
    
    judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
    
  }

  
  while(1){
    /*続行or終了の判断*/
    receive_message(mySocket,buffer,&svaddr);
    sscanf(buffer,"%s",con);
    //printf("con:%s\n",con);
    if(strcmp("fin",con)==0){
      break;
    }
    
    /*ここで天候ダメージ判定を行うと交換して出てきた時に判定が効かない*/
    //damage_weather(nowweather,&nowMonster,&yourMonster,myname,yourname);
    
    /*クライアント側で保存しているデータとサーバーと交換中のデータを同期*/
    for(p=0;p <= 2;p++){
      if(strcmp(nowMonster.name,myMonster[p].name) == 0)
	myMonster[p].status[0] = nowMonster.status[0];
      }
    
    /*どちらかのモンスターが倒れていた場合の処理をSDLで入力*/
    if(nowMonster.status[0] <= 0){
      /*SDLで自分のモンスターの死亡を確認*/
      sprintf(battlemessage,"%s は 倒れた！",nowMonster.name);
      
      show_battle_message(battlemessage);
      
      SDL_Flip(SDL_GetVideoSurface());
      
      SDL_Delay(2000);
      
      
      while(1){
	
	if(nowm == 0)
	  select_state = change_monster_select(&nowMonster,myMonster[1],myMonster[2]);
	else if(nowm == 1)
	  select_state = change_monster_select(&nowMonster,myMonster[0],myMonster[2]);
	else
	  select_state = change_monster_select(&nowMonster,myMonster[0],myMonster[1]);
	
	if(select_state == decided){
	  /*現在モンスターの番号を変更*/
	  for(p=0;p <= 2;p++){
	    if(strcmp(nowMonster.name,myMonster[p].name) == 0)
	      nowm = p;
	  }
	  /*交換情報をサーバに送信*/
	  send_Monster(mySocket,nowMonster,&svaddr);

	  /*交換をSDLで表示*/
	  battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
	  
	  sprintf(battlemessage,"いけっ！　%s",nowMonster.name);
	  
	  show_battle_message(battlemessage);
	  
	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	  
	  /*特性発動*/        
	    judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);

	  
	  break;
	}
      }
      
      /*↑ここまでがSDLを用いた実装部分↑*/
    }
    /*相手のモンスターのHPが0の場合*/    
    if(yourMonster.status[0] <= 0){

      /*まずは倒れたのをSDLで表示*/
      sprintf(battlemessage,"%s の %s は 倒れた！",yourname,yourMonster.name);

      show_battle_message(battlemessage);

      SDL_Flip(SDL_GetVideoSurface());

      SDL_Delay(2000);

      /*サーバから送られてきた相手の交換データを受信*/
      yourMonster = receive_Monster(mySocket,&svaddr);

      /*サーバーの待機を解除*/
      send_message(mySocket,"catched",&svaddr);

      /*受信したデータをSDLで表示*/

      battlesituation_draw(maxH[nowm],nowMonster,yourMonster);

      sprintf(battlemessage,"%s は %s を繰り出してきた！",yourname,yourMonster.name);

      show_battle_message(battlemessage);

      SDL_Flip(SDL_GetVideoSurface());

      SDL_Delay(2000);

      /*特性発動*/
	judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);

    }
    
    //receive_message(mySocket,buffer,&svaddr);
    
    /*サーバー側モンスター情報の更新*/
    //send_Monster(mySocket,nowMonster,&svaddr);
    
    //receive_message(mySocket,buffer,&svaddr);

    /*天候ダメージをここでやる 死亡交換判定をもう一回する必要あり*/
    if(lastweather != nowweather){
      
      weatherturn=0;
      
      lastweather = nowweather;
      
    }else
      weatherturn++;
    
    /*天候ダメージは初ターンは発生しない*/
    if(weatherturn > 0){
      
      damage_weather(nowweather,&nowMonster,&yourMonster,myname,yourname);
      
      
      /*クライアント側で保存しているデータと交換中のデータを同期*/
      for(p=0;p <= 2;p++){
	if(strcmp(nowMonster.name,myMonster[p].name) == 0)
	  myMonster[p].status[0] = nowMonster.status[0];
      }
      
      receive_message(mySocket,buffer,&svaddr);
      
      /*サーバー側モンスター情報の更新*/
      send_Monster(mySocket,nowMonster,&svaddr);
      
      receive_message(mySocket,buffer,&svaddr);
      
      /*どちらかのモンスターが倒れていた場合の処理をSDLで入力*/
      if(nowMonster.status[0] <= 0){
	send_message(mySocket,"ok?",&svaddr);	  
	/*続行or終了の判断*/
	receive_message(mySocket,buffer,&svaddr);
	sscanf(buffer,"%s",con);
	//printf("con:%s\n",con);
	if(strcmp("fin",con)==0){
	  break;
	}
	
	/*SDLで自分のモンスターの死亡を確認*/
	sprintf(battlemessage,"%s は 倒れた！",nowMonster.name);
	
	show_battle_message(battlemessage);
	
	SDL_Flip(SDL_GetVideoSurface());
	
	  SDL_Delay(2000);
	  
	  
	  while(1){
	    
	    if(nowm == 0)
	      select_state = change_monster_select(&nowMonster,myMonster[1],myMonster[2]);
	    else if(nowm == 1)
	      select_state = change_monster_select(&nowMonster,myMonster[0],myMonster[2]);
	    else
	      select_state = change_monster_select(&nowMonster,myMonster[0],myMonster[1]);
	    
	    if(select_state == decided){
	      /*現在モンスターの番号を変更*/
	      for(p=0;p <= 2;p++){
		if(strcmp(nowMonster.name,myMonster[p].name) == 0)
		nowm = p;
	      }
	      /*交換情報をサーバに送信*/
	      send_Monster(mySocket,nowMonster,&svaddr);
	      
	      /*交換をSDLで表示*/
	      battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
	      
	      sprintf(battlemessage,"いけっ！　%s",nowMonster.name);
	      
	      show_battle_message(battlemessage);
	      
	      SDL_Flip(SDL_GetVideoSurface());
	      
	      SDL_Delay(2000);
	      
	      /*特性発動の判定を行う*/
	    if(yourMonster.status[0] > 0)
	      judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
	    else 
	      stopping = 1;
	    
	    break;
	    }
	  }
	  /*↑ここまでがSDLを用いた実装部分↑*/
	  
	}
      /*相手のモンスターのHPが0の場合*/    
      if(yourMonster.status[0] <= 0){

	send_message(mySocket,"ok?",&svaddr);	  
	/*続行or終了の判断*/
	receive_message(mySocket,buffer,&svaddr);
	sscanf(buffer,"%s",con);
	//printf("con:%s\n",con);
	if(strcmp("fin",con)==0){
	  break;
	}

	/*まずは倒れたのをSDLで表示*/
	sprintf(battlemessage,"%s の %s は 倒れた！",yourname,yourMonster.name);
	
	show_battle_message(battlemessage);
	
	SDL_Flip(SDL_GetVideoSurface());
	
	SDL_Delay(2000);
	
	/*サーバから送られてきた相手の交換データを受信*/
	yourMonster = receive_Monster(mySocket,&svaddr);
	
	/*サーバーの待機を解除*/
	send_message(mySocket,"catched",&svaddr);
	
	/*受信したデータをSDLで表示*/
	
	battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
	
	sprintf(battlemessage,"%s は %s を繰り出してきた！",yourname,yourMonster.name);
	
	show_battle_message(battlemessage);
	
	SDL_Flip(SDL_GetVideoSurface());
	
	SDL_Delay(2000);
	
	/*特性発動の判定を行う*/
	if(stopping != 1)
	  judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
	
      }
      
      if(stopping == 1){
	/*特性発動の判定を行う*/
	/*素早さが早い方の特性が先に発動する 同速の場合は*/
	if(nowMonster.status[5] > yourMonster.status[5]){
	  
	  judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
	  
	  judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
	  
	}
	else if(nowMonster.status[5] < yourMonster.status[5]){
	  
	  judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
	  
	  judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
	  
	}else{
	  
	  judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
	  
	  judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
	  
	}
	stopping = 0;
      }
      if(lastweather != nowweather){
	
	weatherturn=0;
	
	lastweather = nowweather;
	
      }else
	weatherturn++;
    }else{
      show_weather(nowweather);

      receive_message(mySocket,buffer,&svaddr);
      
      /*サーバー側モンスター情報の更新*/
      send_Monster(mySocket,nowMonster,&svaddr);
      
      receive_message(mySocket,buffer,&svaddr);
	
	}
    
    receive_message(mySocket,buffer,&svaddr);
    
    /*サーバー側モンスター情報の更新*/
    send_Monster(mySocket,nowMonster,&svaddr);

    receive_message(mySocket,buffer,&svaddr);
    
    /*状況をSDLで表示する*/
    battlesituation_draw(maxH[nowm],nowMonster,yourMonster);

    show_battle_message("どうする？");

    command_draw(0,0,nowMonster);
    
    SDL_Flip(SDL_GetVideoSurface());

    /*行動選択用変数の初期化*/
    //what_select = choose_command;
    sc = 4;
    /*
    i = 0;
    select_state = choosing;
    */

    //eventの蓄積をさけるために関数による処理に変更

    what_select = select_whatdo(&sc,&nowm,maxH,&nowMonster,myMonster,yourMonster);
    /*選択処理開始*/
    /*
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
	    //決定キー
	  case SDLK_SPACE:
	  case SDLK_RETURN:
	  case SDLK_z:
	    select_state = decided;
	    break;
	    //キャンセルキー
	  case SDLK_ESCAPE:
	  case SDLK_x:
	    if(what_select != choose_command)
	      select_state = canceled;
	    break;
	  default:
	    break;
	  }
	  if(select_state == decided){
	    //行動選択画面で決定キーを押した場合
	    if(what_select == choose_command){

	      //たたかう　を選択
	      if(i == 0){
	      what_select = choose_skill;
	      select_state = choosing;
	      }

	      //どうぐ　を選択
	      if(i == 1){
		show_battle_message("道具に頼るな！");
		command_draw(i,what_select,nowMonster);
		select_state = choosing;
	      }  
	      
	      //ソケモン を　選択
	      if(i == 2){
		what_select = choose_monster;

		if(nowm == 0)
		  select_state = change_monster_select(&nowMonster,myMonster[1],myMonster[2]);
		else if(nowm == 1)
		  select_state = change_monster_select(&nowMonster,myMonster[0],myMonster[2]);
		else
		  select_state = change_monster_select(&nowMonster,myMonster[0],myMonster[1]);

		if(select_state == decided){
		  for(p=0;p <= 2;p++){
		    if(strcmp(nowMonster.name,myMonster[p].name) == 0)
		      nowm = p;
		  }
		}
	      }
	      //にげる　を　選択
	      if(i == 3){
		show_battle_message("甘えるな！！");
		sfs();
		SDL_Quit();
		exit(1);
		//デバッグ用
		command_draw(i,what_select,nowMonster);
		select_state = choosing;
	      }
	      SDL_Flip(SDL_GetVideoSurface());

	      if (what_select == choose_command){
		SDL_Delay(500);
		battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
		show_battle_message("どうする？");
		command_draw(i,what_select,nowMonster);
		SDL_Flip(SDL_GetVideoSurface());
	      }

	    }
	    //技選択画面で決定キーを押した場合
	    else if(what_select == choose_skill){
	      if(i == 0)
		sc = 0;
	      if(i == 1)
		sc = 1;
	      if(i == 2)
		sc = 2;
	      if(i == 3)
		sc = 3;
	    }
	  }
	  //キャンセル時
	  if(select_state == canceled){
	    sc = 4;
	    what_select = choose_command;
	    i = 0;
	    battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
	    show_battle_message("どうする？");
	    command_draw(i,what_select,nowMonster);
	    SDL_Flip(SDL_GetVideoSurface());
	    select_state = choosing;
	  }
	  //未決定時
	  else if(select_state == choosing){
	    command_draw(i,what_select,nowMonster);
	    SDL_Flip(SDL_GetVideoSurface());
	  }
	  break;
	default:
	  break;
	}
      }
    }*/

    battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
    show_battle_message("待機中...");
    SDL_Flip(SDL_GetVideoSurface());

    
  /*プレイヤーの行動選択のための処理をSDLで実装する*/
    //Command_select(nowMonster,yourMonster);
    /*↓ここから↓*/
    /*
    printf("choose!yourskill!\n");
    scanf("%d",&i);
    if(i >= 4){
      printf("choose change monster.\n");
      scanf("%d",&j);
      for(p=0;p <= 2;p++){
	if(strcmp(nowMonster.name,myMonster[p].name) == 0)
	  myMonster[p].status[0] = nowMonster.status[0];
      }
      nowMonster = myMonster[j];
    }
    */
    /*↑ここまではSDLによる行動選択処理部分↑*/
    
    if(what_select == choose_skill){
      send_skill(mySocket,nowMonster.myskill[sc],&svaddr);
    }
    else{
      /*この時点でnowMonsterは交換先のモンスターにかわっている*/
      send_change(mySocket,nowMonster,&svaddr);

      battlesituation_draw(maxH[nowm],nowMonster,yourMonster);

      sprintf(battlemessage,"いけっ！　%s",nowMonster.name);

      show_battle_message(battlemessage);

      SDL_Flip(SDL_GetVideoSurface());

      SDL_Delay(2000);
      
    }
    catchMonster = receive_Monster(mySocket,&svaddr);

    if(strcmp(yourMonster.name,catchMonster.name) != 0){

      yourMonster = catchMonster;

      battlesituation_draw(maxH[nowm],nowMonster,yourMonster);

      sprintf(battlemessage,"%s は %s を繰り出してきた！",yourname,yourMonster.name);

      show_battle_message(battlemessage);

      SDL_Flip(SDL_GetVideoSurface());

      SDL_Delay(2000);

      /*こちらも交換していた場合は交換後の特性処理*/
      if(what_select == choose_monster){
	/*素早さが早い方の特性が先に発動する 同速の場合は確率判定*/
	if(nowMonster.status[5] > yourMonster.status[5]){
	  
	  judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
	  
	  judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
	  
	}
	else if(nowMonster.status[5] < yourMonster.status[5]){
	  
	  judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
	  
	  judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
	  
	}else{
	  
	  judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);
	  
	  judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
	  
	}
	
      }else
	judge_characteristic(&nowweather,yourname,&yourMonster,&nowMonster);


    }else if(what_select == choose_monster)
      judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);


    while(1){
      receive_message(mySocket,buffer,&svaddr);
      sscanf(buffer,"%s",command);
      if(strcmp(command,"end") != 0){

	/*とんぼがえりによるポケモンの交換を実装*/
	if(strcmp(command,"mychange") == 0){

	  sprintf(battlemessage,"%s は %s のもとに戻っていく！",nowMonster.name,myname);

	  show_battle_message(battlemessage);
	  
	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	  
	  while(1){
	    
	    if(nowm == 0)
	      select_state = change_monster_select(&nowMonster,myMonster[1],myMonster[2]);
	    else if(nowm == 1)
	      select_state = change_monster_select(&nowMonster,myMonster[0],myMonster[2]);
	    else
	      select_state = change_monster_select(&nowMonster,myMonster[0],myMonster[1]);
	    
	    if(select_state == decided){
	    /*現在モンスターの番号を変更*/
	      for(p=0;p <= 2;p++){
		if(strcmp(nowMonster.name,myMonster[p].name) == 0)
		  nowm = p;
	      }
	      /*サーバーに交換情報を送信*/
	      send_Monster(mySocket,nowMonster,&svaddr);
	      
	      /*交換をSDLで表示*/
	      battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
	      
	      sprintf(battlemessage,"いけっ！　%s",nowMonster.name);
	      
	      show_battle_message(battlemessage);
	      
	      SDL_Flip(SDL_GetVideoSurface());
	      
	      SDL_Delay(2000);
	      
	      /*特性発動を行う*/
	      judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
	      
	      break;
	    }
	  }
	  /*相手ポケモンのとんぼ交換を実装*/
	}else if(strcmp(command,"yourchange") == 0){
	  
	  sprintf(battlemessage,"%sは %sのもとに 戻っていく！",yourMonster.name,yourname);
	  
	  show_battle_message(battlemessage);
	  
	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);
	  
	  /*サーバから送られてきた相手の交換データを受信*/
	  yourMonster = receive_Monster(mySocket,&svaddr);
	  
	  battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
	  
	  sprintf(battlemessage,"%s は %s を繰り出してきた！",yourname,yourMonster.name);
	  
	  show_battle_message(battlemessage);
	  
	  SDL_Flip(SDL_GetVideoSurface());
	  
	  SDL_Delay(2000);

	      /*特性発動を行う*/
	    judge_characteristic(&nowweather,myname,&nowMonster,&yourMonster);
	  
	}
	
	else{
	  
	  sscanf(buffer,"%s %d %d",charskill,&da,&Messenger);
	  effect = get_skill(charskill);
	  
	  /*SDL表示部分今は仮にprintfで実装*/
	  /*messenger == 0 (自分のポケモンが動く時)*/
	  if(Messenger==0){
	    
	    sprintf(battlemessage,"%s の %s !!",nowMonster.name,charskill);
	    
	    show_battle_message(battlemessage);
	    
	    SDL_Flip(SDL_GetVideoSurface());
	    
	    SDL_Delay(2000);

	    if(strcmp(nowMonster.name,"ゲッコウガ") == 0){
	      if(nowMonster.type[0] != effect.type || nowMonster.type[1] != 0){

		nowMonster.type[0] = effect.type;

		nowMonster.type[1] = 0;

		sprintf(battlemessage,"%sの ゲッコウガの へんげんじざい 発動！",myname);

		show_battle_message(battlemessage);

		SDL_Flip(SDL_GetVideoSurface());
		
		SDL_Delay(1000);

		sprintf(battlemessage,"%sの ゲッコウガのタイプが変化する！",myname);

		show_battle_message(battlemessage);

		SDL_Flip(SDL_GetVideoSurface());
		
		SDL_Delay(1000);

	      }
	    }
	    
	    /*HP操作(0以下の場合は0に)*/
	    if(yourMonster.status[0] - da < 0)
	      yourMonster.status[0] = 0;
	    else
	      yourMonster.status[0] -= da;
	    
	    battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
	    
	    SDL_Flip(SDL_GetVideoSurface());
	    
	    SDL_Delay(500);
	    
	    /*効果のメッセージ表示*/
	    show_efficiency(da,effect,yourMonster);
	    
	    SDL_Flip(SDL_GetVideoSurface());
	    
	    SDL_Delay(2000);
	    
	    /*messenger == 1 相手のポケモンが動く時*/
	  }else {
	    
	    sprintf(battlemessage,"%s の %s の %s !!",yourname,yourMonster.name,charskill);
	    
	    show_battle_message(battlemessage);
	    
	    SDL_Flip(SDL_GetVideoSurface());
	    
	    SDL_Delay(2000);

	    if(strcmp(yourMonster.name,"ゲッコウガ") == 0){
	      if(yourMonster.type[0] != effect.type || yourMonster.type[1] != 0){

		yourMonster.type[0] = effect.type;

		yourMonster.type[1] = 0;

		sprintf(battlemessage,"%sの ゲッコウガの へんげんじざい 発動！",yourname);

		show_battle_message(battlemessage);

		SDL_Flip(SDL_GetVideoSurface());
		
		SDL_Delay(1000);

		sprintf(battlemessage,"%sの ゲッコウガのタイプが変化する！",yourname);

		show_battle_message(battlemessage);

		SDL_Flip(SDL_GetVideoSurface());
		
		SDL_Delay(1000);

	      }
	    }
	    
	    if(nowMonster.status[0] - da < 0)
	      nowMonster.status[0] = 0;
	    else
	      nowMonster.status[0] -= da;
	    
	    battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
	    
	    SDL_Flip(SDL_GetVideoSurface());
	    
	    SDL_Delay(1000);
	    
	    /*効果のメッセージ表示*/
	    show_efficiency(da,effect,nowMonster);
	    
	    SDL_Flip(SDL_GetVideoSurface());
	    
	    SDL_Delay(2000);
	    
	  }
	}
      }else
	break;
    }
    //receive_condition(mySocket,&nowMonster,&yourMonster,&svaddr);
  }
  
  /*対戦終了後serverの送信に基づいて勝敗判定を行う*/
  /*この場面もSDLでの処理になるのかもしれない*/
  receive_message(mySocket,buffer,&svaddr);
  sscanf(buffer,"%s",winorloss);
  if(strcmp(winorloss,"win") == 0){
    /*間をおくと味が出る*/
    
    battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
    
    sprintf(battlemessage,"%s の %s は 倒れた！",yourname,yourMonster.name);
    
    show_battle_message(battlemessage);
    
    SDL_Flip(SDL_GetVideoSurface());
    
    SDL_Delay(2000);
    
    battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
    
    show_battle_message("勝敗判定中...");
    
    SDL_Flip(SDL_GetVideoSurface());
    
    SDL_Delay(2000);

    sfs();
    
    SDL_Quit();
   
    win_draw();
    
  }else{

    battlesituation_draw(maxH[nowm],nowMonster,yourMonster);
    
    sprintf(battlemessage,"%s は 倒れた！",nowMonster.name);
    
    show_battle_message(battlemessage);
    
    SDL_Flip(SDL_GetVideoSurface());

    SDL_Delay(1000);

    show_battle_message("勝敗判定中...");

    SDL_Flip(SDL_GetVideoSurface());
    
    SDL_Delay(2000);

    sfs();
    
    SDL_Quit();

    lose_draw();
  }
}


