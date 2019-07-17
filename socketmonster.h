#ifndef _SOCKETMONSTER_H_
#define _SOCKETMONSTER_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<unistd.h>
#include<netdb.h>
#include"socketdata.h"
#include "SDL.h"
#include "SDL_ttf.h"

#define DEFAULT_PORT_NUMBER 6000
#define MAX_MSG 1024

//データの数
#define MONSTER_NUMBER 36
#define SKILL_NUMBER 67
 
//ウインドウ設定
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

//メッセージ位置情報設定
#define MESSAGE_Rect_x 20
#define MESSAGE_Rect_y 400 //480-80

//フォント設定
#define NAME_FONT_NAME "NotoSansMonoCJKjp-Bold.otf"
#define NAME_FONT_SIZE 24
#define MESSAGE_FONT_NAME "ipag-mona.ttf"
#define MESSAGE_FONT_SIZE 18

//交換画面表示位置設定
#define csx0 50
#define csy0 50
#define csx1 400
#define csy1 50
#define cdx0 0
#define cdy0 200
#define cdx1 640/2
#define cdy1 200

//選択肢表示位置設定
#define slx 303
#define sly 480-92

//技説明表示位置
#define skx 3
#define sky 480-92

//自モンスター表示位置設定
#define mmx 70
#define mmy 280 //480-90-110 /*これを基準に個別に調整を加える*/
#define mmy0 280+8
#define mmy1 280+10 
#define mmy2 280 
#define mmy3 280 
#define mmy4 280 
#define mmy5 280+10 
#define mmy6 280 
#define mmy7 280
#define mmy8 280 
#define mmy9 280
#define mmy10 280+27
#define mmy11 280
#define mmy12 280 
#define mmy13 280+10 
#define mmy14 280+5 
#define mmy15 280 
#define mmy16 280+10
#define mmy17 280 
#define mmy18 280 
#define mmy19 280 
#define mmy20 280 
#define mmy21 280 
#define mmy22 280 
#define mmy23 280 
#define mmy24 280+5 
#define mmy25 280 
#define mmy26 280 
#define mmy27 280 
#define mmy28 280 
#define mmy29 280+10 
#define mmy30 280
#define mmy31 280 
#define mmy32 280 
#define mmy33 280 
#define mmy34 280 
#define mmy35 280


//相手モンスター表示位置設定
#define ymx 440 //640-200
#define ymy 50 


#define mnx 350 /*自モンスター名前位置x*/
#define mny 230  /*自モンスター名前位置y*/
#define mhgx 350 /*自モンスターHPゲージ位置x*/
#define mhgy 270 /*自モンスターHPゲージ位置y*/

#define ynx 20 /*相手モンスター名前位置x*/
#define yny 10 /*相手モンスター名前位置y*/
#define yhgx 20 /*相手モンスターHPゲージ位置x*/
#define yhgy 50 /*相手モンスターHPゲージ位置y*/

/*HP(数字表記)設定*/
#define mhx 350 
#define mhy 300


//SDL描写情報構造体
typedef struct{
  SDL_Surface* image;
  SDL_Rect rect;
  SDL_Rect scr_rect;
}pic;

/*天候設定用列挙体*/
enum weather{
  normal,
  sandstorm,
  hailstone,
};

/*キー操作決定時、キャンセル時設定用*/
enum select_state{
  decided, 
  canceled,
  choosing,
  };

/*何を選択しているかの状態を示す変数*/
enum what_select{
  choose_command = 0,
  choose_skill = 1,
  choose_monster = 2,
};

enum battle_state{
  NO_INF, /* 情報収集中 */
  ONE_INF,
  TWO_INF,/* 2人の情報あり */
};

enum choice_state{
  NO_CHANGE, /*交換なし*/
  ONE_CHANGE, /*person1交換*/
  TWO_CHANGE, /*person2交換*/
  DBL_CHANGE, /* 両方交換 */
};

extern double AandD[19][19];/*相性を決める*/
extern Skill skill[SKILL_NUMBER];
Monster monster[MONSTER_NUMBER];
Monster nl;

TTF_Font* namefont; /*ポケモン名前表示フォント*/
TTF_Font* messagefont; /*メッセージ表示用フォント*/

extern SDL_Color black;
extern SDL_Color blue;
extern SDL_Color white;
extern SDL_Color salmon;
extern SDL_Color orangered;

pic myhp;/*自HPゲージ*/
pic yourhp;/*相手HPゲージ*/
pic background; //背景
pic message_window; //メッセージウィンドウ
pic nowmymonster_pic;/*自モンスター画像表示用*/
pic nowyourmonster_pic;/*相手モンスター画像表示用*/
pic nowskill_pic;/*自モンスター技画像表示用*/
pic skillselect[4];//技選択用
pic commandselect[4];//行動選択用
      
void init();
int socket_and_bind(int port);
void get_server_addr(const char *name,struct sockaddr_in *p_addr);
void send_message(int mySocket,char *buffer,struct sockaddr_in *p_addr);
void receive_message(int mySocket,char *buf,struct sockaddr_in *fromaddr);
void send_Monster(int mySocket,Monster sendmonster,struct sockaddr_in *p_addr);
struct Monster get_monster(char *str);
struct Skill get_skill(char *str);
struct Monster receive_Monster(int mySocket,struct sockaddr_in *p_addr);
int disuser(struct sockaddr_in *tmp_addr,struct sockaddr_in *p_addr);
void send_skill(int mySocket,Skill useskill,struct sockaddr_in *p_addr);
void send_change(int mySocket,Monster monster,struct sockaddr_in *p_addr);
int  damage(Skill askill,Monster* amonster,Monster bmonster);
void send_damage(int mySocket,int da,Monster amonster,Skill askill,struct sockaddr_in *a_addr,struct sockaddr_in *b_addr);
void send_condition(int mySocket,Monster amonster,Monster bmonster,struct sockaddr_in *a_dddr,struct sockaddr_in *b_addr);
void receive_condition(int mySocket,Monster *myMonster,Monster *yourMonster,struct sockaddr_in *p_addr);
int draw(SDL_Surface *image, SDL_Rect *rect1, SDL_Rect *rect2);
void title();
void select_monster(Monster selectmonster[3]);
void battle_blit_Init();
void show_message(TTF_Font* font,const char *msg,int x,int y,SDL_Color color);
void show_battle_message(char *message);
void adjust_high(Monster justmonster);
void Mymonster_draw(int h,Monster drawmonster);
void Yourmonster_draw(Monster drawmonster);
void show_weather(enum weather weather);
int judge_characteristic(enum weather* weather,char hisname[MAX_MSG],Monster* amonster,Monster* bmonster);
void command_draw(int k,int m,Monster skillmonster);
void battlesituation_draw(int h,Monster mymonster,Monster yourmonster);
void damage_weather(enum weather weather,Monster* Monster0,Monster* Monster1,char name0[MAX_MSG],char name1[MAX_MSG]);
enum select_state change_monster_select(Monster* nmr,Monster number0,Monster number1);
enum what_select select_whatdo(int *sc,int *nowm,int maxH[3],Monster *nowMonster,Monster myMonster[3],Monster yourMonster);
int show_efficiency(int d,Skill askill,Monster bmonster);
void win_draw();
void lose_draw();
void sfs();


#endif /* _SOCKETMONSTER_H_ */
