#include "socketmonster.h"
#include"socketdata.h"

void loop(int mySocket);


int main(int argc, char *argv[]){
  init();
  int sv_port = DEFAULT_PORT_NUMBER;
  int sv_Socket;
  //int i,j;
  
  /* ソケットの生成とアドレス付け */
  sv_Socket = socket_and_bind(sv_port);
  
  /* for(i=0;i<=14;i++){
     printf("%s    \t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",monster[i].name,monster[i].status[0],monster[i].status[1],monster[i].status[2],monster[i].status[3],monster[i].status[4],monster[i].status[5],monster[i].type[0],monster[i].type[1]);
     
     for(j=0;j<=3;j++){
     printf("%s\t%d\t%d\t%d\t%d\n",monster[i].myskill[j].name,monster[i].myskill[j].way,monster[i].myskill[j].power,monster[i].myskill[j].type,monster[i].myskill[j].acc);
     
     }
     putchar('\n');
     } */
  
  /* 対戦処理開始 */
  loop(sv_Socket);
  
  /* ソケットを閉じる */
  close(sv_Socket);
  return 0;
}


void loop(int mySocket){
  int d = 0;/*ダメージ用変数*/
  int i = 0;/*行動順決定用の変数*/
  int Messenger; /* 誰がメッセージを送っているか判別するための数字,0か1をとる */
  int H; /*HP交換用変数*/
  Monster catchMonster; /* 送られてきたモンスター情報を一旦格納 */
  struct sockaddr_in youraddr[2];
  struct sockaddr_in tmp_addr;
  Monster nowMonster[2]; /*場に出ているモンスター情報を格納*/
  Skill nowSkill[2]; /* 選択した技の情報を格納 */ 
  int lost_Monster[2]={}; /*勝敗判定用*/
  char name[2][MAX_MSG];/*名前格納用*/
  char buffer[MAX_MSG]; /*メッセージ読み出し用*/
  char cmd[MAX_MSG]; /* 行動読み出し用 */
  char charskill[MAX_MSG]; /* 技読み出し用 */
  char charmonster[MAX_MSG]; /* 交換先読み出し用 */
  enum battle_state battle = NO_INF;
  enum choice_state choice = NO_CHANGE;

  
  /*接続処理*/
  /*一人目接続*/
  receive_message(mySocket,buffer,&youraddr[0]);
  strcpy(name[0],buffer);
  
  /* 二人目接続 */
  receive_message(mySocket,buffer,&youraddr[1]);
  strcpy(name[1],buffer);
  
  /* 接続完了メッセージ送信 */
  send_message(mySocket,name[1],&youraddr[0]);
  send_message(mySocket,name[0],&youraddr[1]);

  /*歩調を合わせるための送受信*/
  receive_message(mySocket,buffer,&tmp_addr);
  receive_message(mySocket,buffer,&tmp_addr);
  send_message(mySocket,name[1],&youraddr[0]);
  send_message(mySocket,name[0],&youraddr[1]);
  
  /*互いの場に出ているモンスターをサーバーに保存*/
  catchMonster = receive_Monster(mySocket,&tmp_addr); /*受信*/
  Messenger = disuser(&tmp_addr,&youraddr[0]); /*誰が送ったのか判別*/
  nowMonster[Messenger] = catchMonster;
  
  
  /*もう一方に対して同じ操作を行う*/
  catchMonster = receive_Monster(mySocket,&tmp_addr);
  Messenger = disuser(&tmp_addr,&youraddr[0]);
  nowMonster[Messenger] = catchMonster;
  //puts("catched");
  
  /*初期情報の送信*/
  send_Monster(mySocket,nowMonster[0],&youraddr[1]);
  
  send_Monster(mySocket,nowMonster[1],&youraddr[0]);
  
  while(1){
    /*終了判定*/
    if(lost_Monster[0] == 3 || lost_Monster[1] == 3){
      send_message(mySocket,"fin",&youraddr[0]);
      
      send_message(mySocket,"fin",&youraddr[1]);
      
      /*勝敗判定*/
      if(lost_Monster[0] == 3){
	send_message(mySocket,"lose",&youraddr[0]);
	
	send_message(mySocket,"win",&youraddr[1]);
      }
      else{
	send_message(mySocket,"win",&youraddr[0]);
	
	send_message(mySocket,"lose",&youraddr[1]);
      }
      break;
    }
    else{
      /*続行を送信*/
      send_message(mySocket,"continue",&youraddr[0]);
      
      send_message(mySocket,"continue",&youraddr[1]);

      if(nowMonster[0].status[0] <= 0){
	nowMonster[0] = receive_Monster(mySocket,&youraddr[0]);
	send_Monster(mySocket,nowMonster[0],&youraddr[1]);
	/*クライアント側で処理が終了するまで待機*/
	receive_message(mySocket,buffer,&tmp_addr);
      }
      if(nowMonster[1].status[0] <= 0){
	nowMonster[1] = receive_Monster(mySocket,&youraddr[1]);
	send_Monster(mySocket,nowMonster[1],&youraddr[0]);
	/*クライアント側で処理が終了するまで待機*/
	receive_message(mySocket,buffer,&tmp_addr);
      }


      /*情報受信準備完了*/
      send_message(mySocket,"comeon",&youraddr[0]);
      
      send_message(mySocket,"comeon",&youraddr[1]);

      /*互いの場に出ているモンスター情報をサーバーで更新*/
      catchMonster = receive_Monster(mySocket,&tmp_addr); /*受信*/
      Messenger = disuser(&tmp_addr,&youraddr[0]); /*誰が送ったのか判別*/
      nowMonster[Messenger] = catchMonster;
      
      
      /*もう一方に対して同じ操作を行う*/
      catchMonster = receive_Monster(mySocket,&tmp_addr);
      Messenger = disuser(&tmp_addr,&youraddr[0]);
      nowMonster[Messenger] = catchMonster;

      send_message(mySocket,"catched",&youraddr[0]);
      
      send_message(mySocket,"catched",&youraddr[1]);

      if(nowMonster[0].status[0] <= 0){
	lost_Monster[0]++;
	/*サーバーとクライアントの歩調を合わせる*/
	receive_message(mySocket,buffer,&tmp_addr);

	receive_message(mySocket,buffer,&tmp_addr);

	if(lost_Monster[0] == 3){

	  send_message(mySocket,"fin",&youraddr[0]);
      
	  send_message(mySocket,"fin",&youraddr[1]);

	  send_message(mySocket,"lose",&youraddr[0]);
	
	  send_message(mySocket,"win",&youraddr[1]);

	}else{

	  send_message(mySocket,"continue",&youraddr[0]);
	  send_message(mySocket,"continue",&youraddr[1]);
	  
	  nowMonster[0] = receive_Monster(mySocket,&youraddr[0]);
	  
	  send_Monster(mySocket,nowMonster[0],&youraddr[1]);
	  
	  /*クライアント側で処理が終了するまで待機*/
	  receive_message(mySocket,buffer,&tmp_addr);
	}
      }
      if(nowMonster[1].status[0] <= 0){
	lost_Monster[1]++;
	
	receive_message(mySocket,buffer,&tmp_addr);
	
	receive_message(mySocket,buffer,&tmp_addr);
	
	if(lost_Monster[0] == 3){
	  
	  send_message(mySocket,"fin",&youraddr[0]);
	  
	  send_message(mySocket,"fin",&youraddr[1]);
	  
	  send_message(mySocket,"lose",&youraddr[0]);
	  
	  send_message(mySocket,"win",&youraddr[1]);
	  
	}else{
	  
	  send_message(mySocket,"continue",&youraddr[0]);
	  
	  send_message(mySocket,"continue",&youraddr[1]);

	  nowMonster[1] = receive_Monster(mySocket,&youraddr[1]);

	  send_Monster(mySocket,nowMonster[1],&youraddr[0]);
	  /*クライアント側で処理が終了するまで待機*/
	  receive_message(mySocket,buffer,&tmp_addr);
	}
      }

      /*情報受信準備完了*/
      send_message(mySocket,"comeon",&youraddr[0]);
      
      send_message(mySocket,"comeon",&youraddr[1]);

      /*互いの場に出ているモンスター情報をサーバーで更新*/
      catchMonster = receive_Monster(mySocket,&tmp_addr); /*受信*/
      Messenger = disuser(&tmp_addr,&youraddr[0]); /*誰が送ったのか判別*/
      nowMonster[Messenger] = catchMonster;
      
      
      /*もう一方に対して同じ操作を行う*/
      catchMonster = receive_Monster(mySocket,&tmp_addr);
      Messenger = disuser(&tmp_addr,&youraddr[0]);
      nowMonster[Messenger] = catchMonster;

      send_message(mySocket,"catched",&youraddr[0]);
      
      send_message(mySocket,"catched",&youraddr[1]);
      
      switch(battle){
	
      case NO_INF:
	/*行動情報を受信*/
	
	receive_message(mySocket,buffer,&tmp_addr);
	
	/*送信相手を判別*/
	Messenger = disuser(&tmp_addr,&youraddr[0]);
	
	sscanf(buffer,"%s",cmd);
	/*技を選択した場合*/
	if(strcmp("skill",cmd) == 0){
	  sscanf(buffer,"skill %s",charskill); /*技情報の読み出し*/
	  nowSkill[Messenger] = get_skill(charskill);/*技情報の格納*/
	  
	  /*交換を選択した場合*/
	}else if(strcmp("change",cmd) == 0){
	  sscanf(buffer,"change %s %d",charmonster,&H);/*名前、HPの読み出し*/
	  nowMonster[Messenger] = get_monster(charmonster);/*モンスター情報格納*/
	  nowMonster[Messenger].status[0] = H;
	  
	  /*二人とも交換の場合と一人だけ交換の場合
	    （どちらが交換するかも含めて）の判別を行う*/
	  if(Messenger == 0)
	    choice = ONE_CHANGE;
	  else
	    choice = TWO_CHANGE;
	}
	battle = ONE_INF;
	/*一人目の情報収集完了*/
      case ONE_INF:
	/*行動情報を受信*/
	
	receive_message(mySocket,buffer,&tmp_addr);
	
	/*送信相手を判別*/
	Messenger = disuser(&tmp_addr,&youraddr[0]);
	
	sscanf(buffer,"%s",cmd);

	/*技を選択した場合*/
	if(strcmp("skill",cmd) == 0){
	  sscanf(buffer,"skill %s",charskill); /*技情報の読み出し*/
	  nowSkill[Messenger] = get_skill(charskill);/*技情報の格納*/
	  
	  /*交換を選択した場合*/
	}else if(strcmp("change",cmd) == 0){
	  sscanf(buffer,"change %s %d",charmonster,&H);/*名前、HPの読み出し*/
	  nowMonster[Messenger] = get_monster(charmonster);/*モンスター情報格納*/
	  nowMonster[Messenger].status[0] = H;
	  
	  /*二人とも交換の場合と一人だけ交換の場合
	    （どちらが交換するかも含めて）の判別を行う*/
	  if(Messenger == 0){
	    
	    if(choice == TWO_CHANGE)
	      choice = DBL_CHANGE;
	    
	    else 
	      choice = ONE_CHANGE;
	  }
	  else{
	    
	    if(choice == ONE_CHANGE)
	      choice = DBL_CHANGE;
	    
	    else
	      choice = TWO_CHANGE;
	  }
	  
	}
	battle = TWO_INF;
	/*情報収集完了*/
      case TWO_INF:
	
	send_Monster(mySocket,nowMonster[0],&youraddr[1]);
	
	send_Monster(mySocket,nowMonster[1],&youraddr[0]);
	
	/*技、交換のやり取り開始*/
	switch(choice){
	  
	case NO_CHANGE:
	  
	  /*素早さによる行動順判定　同速の場合は確率判定*/
	  if(nowMonster[0].status[5] > nowMonster[1].status[5])
	    i = 0;
	  else if(nowMonster[0].status[5] < nowMonster[1].status[5])
	    i = 1;
	  else if(50 <= rand()%100)
	    i = 0;
	  else
	    i = 1;


	  if(i == 0){
	    /*ダメージ計算*/
	    d = damage(nowSkill[0],&nowMonster[0],nowMonster[1]);
	    /*ダメージ送信*/
	    send_damage(mySocket,d,nowMonster[0],nowSkill[0],&youraddr[0],&youraddr[1]);
	    //printf("d = %d\n",d);
	    nowMonster[1].status[0] -= d;

	    /*とんぼがえりの判定 交換*/
	    if(strcmp(nowSkill[0].name,"とんぼがえり") == 0){
	      /*味方が全員死んでいない場合は交換判定*/
	      if(lost_Monster[0] < 2){
		/*お前が変えるんやで*/
		send_message(mySocket,"mychange",&youraddr[0]);
		/*あいつがかわるんやで*/
		send_message(mySocket,"yourchange",&youraddr[1]);
		
		nowMonster[0] =  receive_Monster(mySocket,&tmp_addr);
		
		send_Monster(mySocket,nowMonster[0],&youraddr[1]);
		
	      }
	    }
	    
	    /*先に食らった方のHPが0でなければ続行*/
	    if(nowMonster[1].status[0] > 0){
	      
	      d = damage(nowSkill[1],&nowMonster[1],nowMonster[0]);
	      send_damage(mySocket,d,nowMonster[1],nowSkill[1],&youraddr[1],&youraddr[0]);
	      //printf("d = %d\n",d);
	      nowMonster[0].status[0] -= d;

	    /*とんぼがえりの判定 交換*/
	      if(strcmp(nowSkill[1].name,"とんぼがえり") == 0){

		if(lost_Monster[0] < 2){
		  
		  send_message(mySocket,"mychange",&youraddr[1]);
		  
		  send_message(mySocket,"yourchange",&youraddr[0]);
		  
		  nowMonster[1] =  receive_Monster(mySocket,&tmp_addr);
		  
		  send_Monster(mySocket,nowMonster[1],&youraddr[0]);
		  
		}
	      }
	      
	      if(nowMonster[0].status[0] <= 0)
		lost_Monster[0]++;
	    }
	    else
	      lost_Monster[1]++;
	  }
	  /*素早さの上下が逆だった場合の処理*/
	  else{
	    
	    d = damage(nowSkill[1],&nowMonster[1],nowMonster[0]);

	    send_damage(mySocket,d,nowMonster[1],nowSkill[1],&youraddr[1],&youraddr[0]);
	    nowMonster[0].status[0] -= d;
	    
	    /*とんぼがえりの判定 交換*/
	    if(strcmp(nowSkill[1].name,"とんぼがえり") == 0){

	      if(lost_Monster[0] < 2){

		send_message(mySocket,"mychange",&youraddr[1]);

		send_message(mySocket,"yourchange",&youraddr[0]);

		nowMonster[1] =  receive_Monster(mySocket,&tmp_addr);

		send_Monster(mySocket,nowMonster[1],&youraddr[0]);

	      }
	    }
	    
	    if(nowMonster[0].status[0] > 0){
	      
	      d = damage(nowSkill[0],&nowMonster[0],nowMonster[1]);
	      
	      send_damage(mySocket,d,nowMonster[0],nowSkill[0],&youraddr[0],&youraddr[1]);
	      nowMonster[1].status[0] -= d;
	      
	      if(strcmp(nowSkill[0].name,"とんぼがえり") == 0){

		if(lost_Monster[0] < 2){
		  send_message(mySocket,"mychange",&youraddr[0]);

		  send_message(mySocket,"yourchange",&youraddr[1]);

		  nowMonster[0] =  receive_Monster(mySocket,&tmp_addr);

		  send_Monster(mySocket,nowMonster[0],&youraddr[1]);

		}
	      }
		
	      if(nowMonster[1].status[0] <= 0)
		lost_Monster[1]++;
	    }
	    else
	      lost_Monster[0]++;
	  }
	  send_message(mySocket,"end",&youraddr[0]);
	  send_message(mySocket,"end",&youraddr[1]);
	  break;
	case ONE_CHANGE:
	  
	  d = damage(nowSkill[1],&nowMonster[1],nowMonster[0]);
	  send_damage(mySocket,d,nowMonster[1],nowSkill[1],&youraddr[1],&youraddr[0]);
	  nowMonster[0].status[0] -= d;
	  
	  if(nowMonster[0].status[0] <= 0)
	    lost_Monster[0]++;
	  choice = NO_CHANGE;
	  send_message(mySocket,"end",&youraddr[0]);
	  send_message(mySocket,"end",&youraddr[1]);
	  
	  break;
	  
	case TWO_CHANGE:
	  
	  d = damage(nowSkill[0],&nowMonster[0],nowMonster[1]);
	  send_damage(mySocket,d,nowMonster[0],nowSkill[0],&youraddr[0],&youraddr[1]);
	  nowMonster[1].status[0] -= d;
	  
	  if(nowMonster[1].status[0] <= 0)
	    lost_Monster[1]++;
	  choice = NO_CHANGE;
	  send_message(mySocket,"end",&youraddr[0]);
	  send_message(mySocket,"end",&youraddr[1]);
	  
	  break;
	  
	case DBL_CHANGE:
	  
	  choice = NO_CHANGE;
	  send_message(mySocket,"end",&youraddr[0]);
	  send_message(mySocket,"end",&youraddr[1]);
	  
	  break;
	}
	//send_condition(mySocket,nowMonster[0],nowMonster[1],&youraddr[0],&youraddr[1]);
	battle = NO_INF;
	break;
      }
    }
  }
}
