#include "socketmonster.h"
#include"socketdata.h"


int socket_and_bind(int port){
  int mySocket;
  struct sockaddr_in myAddr;
  if((mySocket = socket(PF_INET,SOCK_DGRAM,0)) < 0){
    printf("socket failed!!");
    exit(1);
  }
  bzero((char *)&myAddr,sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myAddr.sin_port = htons(port);
  bind(mySocket,(struct sockaddr *)&myAddr,sizeof(myAddr));
  return mySocket;
}

void get_server_addr(const char *name,struct sockaddr_in *p_addr){
  struct hostent* pHostent;
  if((pHostent = gethostbyname(name)) == NULL){
    printf("gethost failed!!");
    exit(1);
  }
  else{
    bzero((char *)p_addr,sizeof(struct sockaddr_in));
    p_addr->sin_family = AF_INET;
    p_addr->sin_port = htons(DEFAULT_PORT_NUMBER);
    bcopy(pHostent->h_addr,(char*)&(p_addr->sin_addr.s_addr),pHostent->h_length);
  }
  
}

void send_message(int mySocket,char *buffer,struct sockaddr_in *p_addr){
  //送信失敗したら全体の処理も終了させる。
  int sentlen;
  //printf("send:  %s\n",buffer);
  sentlen = sendto(mySocket, buffer, strlen(buffer), 0, (struct sockaddr *)p_addr, sizeof(*p_addr));
  if(sentlen < 0)
    exit(1);
}

void receive_message(int mySocket,char *buf,struct sockaddr_in *fromaddr){
  int msglength;
  socklen_t addrlength = sizeof(*fromaddr);
  //受信失敗したら全体の処理も終了させる。
  if((msglength = recvfrom(mySocket , buf , MAX_MSG , 0 ,(struct sockaddr *)fromaddr , &addrlength )) < 0)
    exit(1);
  buf[msglength]= '\0';
  //printf("receive: %s\n",buf);
}

void send_Monster(int mySocket,Monster sendmonster,struct sockaddr_in *p_addr){
  char buffer[MAX_MSG];
  //printf("%s %d %d %d %d %d %d\n",sendmonster.name,sendmonster.status[0],sendmonster.status[1],sendmonster.status[2],sendmonster.status[3],sendmonster.status[4],sendmonster.status[5]);
  sprintf(buffer,"%s %d %d %d %d %d %d",sendmonster.name,sendmonster.status[0],sendmonster.status[1],sendmonster.status[2],sendmonster.status[3],sendmonster.status[4],sendmonster.status[5]);
  //printf("\n time:send %s ",buffer);
  send_message(mySocket,buffer,p_addr);
}

Monster get_monster(char *str){
  int i;
  for(i=0;i<MONSTER_NUMBER;i++){
    if(strcmp(str,monster[i].name) == 0)
    return monster[i];
  }
  return monster[0];
}

Skill get_skill(char *str){
  int i;
  for(i=0;i<SKILL_NUMBER;i++){
    if(strcmp(str,skill[i].name) == 0)
      return skill[i];
  }
  return skill[0];
}

Monster receive_Monster(int mySocket,struct sockaddr_in *p_addr){
  char buffer[MAX_MSG],name[MAX_MSG];
  int H,A,B,C,D,S;
  Monster receivemonster;
  receive_message(mySocket,buffer,p_addr);
  sscanf(buffer,"%s %d %d %d %d %d %d",name,&H,&A,&B,&C,&D,&S);
  //printf("time:receive %s %d\n",name,receivemonster.status[0]);
  receivemonster = get_monster(name);
  receivemonster.status[0] = H;
      receivemonster.status[1] = A;
      receivemonster.status[2] = B;
      receivemonster.status[3] = C;
      receivemonster.status[4] = D;
      receivemonster.status[5] = S;
      //printf("time:catch %s %d\n",receivemonster.name,receivemonster.status[0]);
  return receivemonster;
}

int disuser(struct sockaddr_in *tmp_addr,struct sockaddr_in *p_addr){
  int ms;
  /*送信相手の検証*/
  if(tmp_addr->sin_port == p_addr->sin_port 
     && tmp_addr -> sin_addr.s_addr == p_addr -> sin_addr.s_addr )
    ms = 0;
  else 
    ms = 1;
  return ms;
}

void send_skill(int mySocket,Skill useskill,struct sockaddr_in *p_addr){
  char buffer[MAX_MSG];
  sprintf(buffer,"skill %s",useskill.name);
  send_message(mySocket,buffer,p_addr);
}

void send_change(int mySocket,Monster monster,struct sockaddr_in *p_addr){
  char buffer[MAX_MSG];
  sprintf(buffer,"change %s %d",monster.name,monster.status[0]);
  send_message(mySocket,buffer,p_addr);
}


void send_damage(int mySocket,int da,Monster amonster,Skill askill,struct sockaddr_in *a_addr,struct sockaddr_in *b_addr){
  char abuffer[MAX_MSG];
  char bbuffer[MAX_MSG];
  sprintf(abuffer,"%s %d %d",askill.name,da,0);
  sprintf(bbuffer,"%s %d %d",askill.name,da,1);
  send_message(mySocket,abuffer,a_addr);
  send_message(mySocket,bbuffer,b_addr);
}

void send_condition(int mySocket,Monster amonster,Monster bmonster,struct sockaddr_in *a_addr,struct sockaddr_in *b_addr){
  char abuffer[MAX_MSG];
  char bbuffer[MAX_MSG];
  if(amonster.status[0] <= 0)
    amonster.status[0] =0;
  if(bmonster.status[0] <= 0)
    bmonster.status[0] =0;
  sprintf(abuffer,"%d %d",amonster.status[0],bmonster.status[0]);
  sprintf(bbuffer,"%d %d",bmonster.status[0],amonster.status[0]);
  //printf("%s \n %s \n",abuffer,bbuffer);
  send_message(mySocket,abuffer,a_addr);
  send_message(mySocket,bbuffer,b_addr);
}

void receive_condition(int mySocket,Monster *myMonster,Monster *yourMonster,struct sockaddr_in *p_addr){
  char buffer[MAX_MSG];
  int myH,youH;
  receive_message(mySocket,buffer,p_addr);
  sscanf(buffer,"%d %d",&myH,&youH);
  myMonster->status[0] = myH;
  yourMonster->status[0] = youH;
}

int draw(SDL_Surface *image, SDL_Rect *rect1, SDL_Rect *rect2){
  SDL_Rect window_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_Surface *video_surface;
  
  video_surface = SDL_GetVideoSurface();
  
  /* 背景色塗りつぶし */
  SDL_FillRect(video_surface, &window_rect, SDL_MapRGB(video_surface->format, 255,255,255 ));
  
  /* サーフェスの複写 */
  SDL_BlitSurface(image, rect1, video_surface, rect2);
  
	/* サーフェスフリップ */
  SDL_Flip(video_surface);
  
  return 0;
}
