#include "socketmonster.h"
#include "socketdata.h"

#define MESSAGE_LEFT 0
#define MESSAGE_TOP 400

int selectMonsternumber[3]; /*選ぶモンスターの番号*/

typedef struct position{
  SDL_Surface* image;
  int x;
  int y;
} POSITION;

int nom[15]; /*モンスターを乱数で番号で当てる時の一時判定用*/


int select_draw(SDL_Surface *image, SDL_Rect *rect1, SDL_Rect *rect2,int n);
int monster_select(SDL_Surface* image);
int display(SDL_Surface* image,SDL_Rect* scr_rect,SDL_Rect* dst_rect);
int select_show_message(int position,SDL_Surface* image,int* mymonster);
void user_shine(int monsternumber);

void select_monster(Monster selectmonster[3]){
  int i,j,now,n=0;
  SDL_Surface *selectimage[MONSTER_NUMBER];//,*video_surface;
  SDL_Rect rect[15], scr_rect[15];//,rect_tmp[15];
  SDL_Surface* arrow;
  SDL_Rect select_rect,select_scr_rect,select_rect_tmp;
  SDL_Surface* status_detail[MONSTER_NUMBER];
  SDL_Rect status_rect[15],status_scr_rect;
  SDL_Event event;
  int exit_prg = 0; 
  POSITION sokemon[15];/*モンスターの位置を指定している*/
  int dn = 0; /*データ登録個数*/
  for(n=0;n<3;n++){
    selectMonsternumber[n] = 15;
  }
  n = 0;
  
  
  SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32,SDL_HWSURFACE);
  
  
  //画像の読み込み
  selectimage[0] = SDL_LoadBMP("azmou.bmp");
  selectimage[1] = SDL_LoadBMP("kbgn.bmp");
  selectimage[2] = SDL_LoadBMP("bsyam.bmp");
  selectimage[3] = SDL_LoadBMP("rgraj.bmp");
  selectimage[4] = SDL_LoadBMP("jkin.bmp");
  selectimage[5] = SDL_LoadBMP("sndas.bmp");
  selectimage[6] = SDL_LoadBMP("hgner.bmp");
  selectimage[7] = SDL_LoadBMP("bomnd.bmp");
  selectimage[8] = SDL_LoadBMP("tdzrg.bmp");
  selectimage[9] = SDL_LoadBMP("bngrs.bmp");
  selectimage[10] = SDL_LoadBMP("mtgrs.bmp");
  selectimage[11] = SDL_LoadBMP("sanit.bmp");
  selectimage[12] = SDL_LoadBMP("hssm.bmp");
  selectimage[13] = SDL_LoadBMP("nyrbn.bmp");
  selectimage[14] = SDL_LoadBMP("gnga.bmp");
  selectimage[15] = SDL_LoadBMP("krbt.bmp");
  selectimage[16] = SDL_LoadBMP("ydrn.bmp");
  selectimage[17] = SDL_LoadBMP("rzdn.bmp");
  selectimage[18] = SDL_LoadBMP("hrkrs.bmp");
  selectimage[19] = SDL_LoadBMP("kiryu.bmp");
  selectimage[20] = SDL_LoadBMP("hdin.bmp");
  selectimage[21] = SDL_LoadBMP("prskt.bmp");
  selectimage[22] = SDL_LoadBMP("nknn.bmp");
  selectimage[23] = SDL_LoadBMP("gkkg.bmp");
  selectimage[24] = SDL_LoadBMP("nno.bmp");
  selectimage[25] = SDL_LoadBMP("nnfa.bmp");
  selectimage[26] = SDL_LoadBMP("ktt.bmp");
  selectimage[27] = SDL_LoadBMP("sndr.bmp");
  selectimage[28] = SDL_LoadBMP("drpon.bmp");
  selectimage[29] = SDL_LoadBMP("tbtb.bmp");
  selectimage[30] = SDL_LoadBMP("ykno.bmp");
  selectimage[31] = SDL_LoadBMP("sbrdn.bmp");
  selectimage[32] = SDL_LoadBMP("pkt.bmp");
  selectimage[33] = SDL_LoadBMP("bkhn.bmp");
  selectimage[34] = SDL_LoadBMP("rtos.bmp");
  selectimage[35] = SDL_LoadBMP("mrkrs.bmp");


  for(i=0 ;i < MONSTER_NUMBER;i++){
    status_detail[i] = monster[i].detail;
  }

  srand((unsigned) time(NULL));


  while(dn < 15){
    n = rand() % MONSTER_NUMBER;
    for(j=0;;j++){
      if(j < dn){
	if(nom[j] == n)
	  break;
      }else{
	nom[j] = n;
	dn++;
	break;
      }
    }
  }
      

  for(i=0;i<15;i++)
    sokemon[i].image = selectimage[nom[i]];

  
  //画像の矩形情報設定
  for(i=0;i<15;i++){
    rect[i].x = 0;
    rect[i].y = 0;
    rect[i].w = sokemon[i].image->w;
    rect[i].h = sokemon[i].image->h;
    status_rect[i].x = 0;
    status_rect[i].y = 0;
    status_rect[i].w = status_detail[nom[i]]->w;
    status_rect[i].h = status_detail[nom[i]]->h;
    SDL_SetColorKey(status_detail[nom[i]], SDL_SRCCOLORKEY, SDL_MapRGB(status_detail[nom[i]]->format, 0, 0, 0));
  }

  for(j=0;j<3;j++){
    for(i=0;i<5;i++){
      //89 = 画像サイズ(64)+行間(25)
      sokemon[j*5+i].x = (WINDOW_WIDTH/2 - 210) + 89 * i;
      sokemon[j*5+i].y = 30 + 89 * j;
    }
  }
  
  //画像配置位置情報の設定
  for(i=0;i<15;i++){
    scr_rect[i].x = sokemon[i].x;
    scr_rect[i].y = sokemon[i].y;
  }
  
  //選択キー
  arrow = SDL_LoadBMP("arrow.bmp");
  SDL_SetColorKey(arrow, SDL_SRCCOLORKEY, SDL_MapRGB(arrow->format, 0, 0, 0));

  status_scr_rect.x = 350;
  status_scr_rect.y = 300;

  
  //矩形情報設定
  select_rect.x = 0;
  select_rect.y = 0;
  select_rect.w = arrow->w;
  select_rect.h = arrow->h;
  //選択キー位置情報の設定
  select_scr_rect.x = 90;
  select_scr_rect.y = 54;
  //描画
  select_draw(arrow, &select_rect, &select_scr_rect,1);
  select_draw(status_detail[nom[0]],&status_rect[0],&status_scr_rect,0);
  //サーフェスの複写
  for(i=0;i<15;i++){
    SDL_BlitSurface(sokemon[i].image, &rect[i], SDL_GetVideoSurface(), &scr_rect[i]);
  }
  //サーフェスフリップ
  SDL_Flip(SDL_GetVideoSurface());
  
  select_rect_tmp = select_scr_rect;

  n=0;
  
  /* イベントループ */
  while(exit_prg == 0){	
    if(SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_KEYDOWN:
	switch(event.key.keysym.sym){
	case SDLK_UP:
	  select_rect_tmp.y -= 89;
	  break;
	case SDLK_DOWN:
	  select_rect_tmp.y += 89;
	  break;
	case SDLK_RIGHT:
	  select_rect_tmp.x += 89;
	  break;
	case SDLK_LEFT:
	  select_rect_tmp.x -= 89;
	  break;
	case SDLK_ESCAPE:
	case SDLK_x:
	  break;
	case SDLK_SPACE:
	case SDLK_z:
	  now = (select_rect_tmp.x-90)/89+ 5*(select_rect_tmp.y-54)/89;
	  if(now != selectMonsternumber[0] && now != selectMonsternumber[1] && now != selectMonsternumber[2])
	    select_show_message(now,monster[nom[now]].mimage,&selectMonsternumber[n]);
	  if(selectMonsternumber[n] != 15){
	    n++;
	    //printf("%d",n);
	    if(n > 2){
	      exit_prg = 1;
	    }   
	    break;
	    /*case SDLK_q:
	    for(i=0;i<MONSTER_NUMBER;i++){
	      SDL_FreeSurface(selectimage[i]);
	    }
	    
	    SDL_FreeSurface(arrow);

	    SDL_Quit();
	    exit(1);
	    break;*/
	  default:
	    break;
	  }
	}
	
	/* 移動可能範囲の判定 */
	if(select_rect_tmp.x >= 89 
	   && select_rect_tmp.x + select_rect.w <=  500 
	   && select_rect_tmp.y >= 30 
	   && select_rect_tmp.y + select_rect.h <= 270){
	  
	  select_scr_rect = select_rect_tmp;
	  //nowはポケモン番号
	  now =(select_rect_tmp.x-90)/89+ 5*(select_rect_tmp.y-54)/89;
	  /* 描画 */
	  select_draw(arrow, &select_rect, &select_scr_rect,1);
	  select_draw(status_detail[nom[now]],&status_rect[now],&status_scr_rect,0);
	  //サーフェスの複写
	  for(i=0;i<15;i++){
	    SDL_BlitSurface(sokemon[i].image, &rect[i], SDL_GetVideoSurface(), &scr_rect[i]);
	    
	      /*else{
	      rect_tmp[i].x = rect[i].x; rect_tmp[i].y = rect[i].y;
	      rect_tmp[i].w = image[i]->w + 10; rect_tmp[i].h = image[i]->h + 10;
	      video_surface = image[i];	      
	      SDL_FillRect(video_surface, &rect_tmp[i], SDL_MapRGB(video_surface->format, 255,0,0 ));
	      SDL_BlitSurface(image[i], &rect[i], SDL_GetVideoSurface(), &scr_rect[i]);
	      }*/
	  }
	
	  //サーフェスフリップ
	  SDL_Flip(SDL_GetVideoSurface());
	  
	}
	else {
	  select_rect_tmp = select_scr_rect;
	}
	break;
      default:
	break;
      }
    }
    SDL_Delay(1);
  }
  
  
  
  for(i=0;i<MONSTER_NUMBER;i++){
    SDL_FreeSurface(selectimage[i]);
  }
  
  SDL_FreeSurface(arrow);

  for(n=0;n<3;n++){
    selectmonster[n] = monster[nom[selectMonsternumber[n]]];
  }

  SDL_Quit();
  
}

int select_draw(SDL_Surface *a_image, SDL_Rect *rect1, SDL_Rect *rect2,int n){
  SDL_Rect window_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_Surface *video_surface;
  
  video_surface = SDL_GetVideoSurface();
  
  /* 背景色塗りつぶし */
  if(n == 1){
  SDL_FillRect(video_surface, &window_rect, SDL_MapRGB(video_surface->format, 255,255,255 ));
  }
 
  /* サーフェスの複写 */
  SDL_BlitSurface(a_image, rect1, video_surface, rect2);
  
	/* サーフェスフリップ */
  SDL_Flip(video_surface);
  
  return 0;
}

int display(SDL_Surface *image, SDL_Rect *src_rect, SDL_Rect *dst_rect){
	SDL_Surface *video_surface = SDL_GetVideoSurface();

	/* サーフェスの複写 */
	SDL_BlitSurface(image, src_rect, video_surface, dst_rect);

	return 0;
}
 
void user_shine(int monsternumber){
  SDL_Surface* text[3];
  SDL_Surface* foruser;
  SDL_Rect t_scr_rect[3],t_rect[3];
  SDL_Rect f_scr_rect,f_rect;

  //printf("%d\n",monsternumber);

  if(monsternumber == 0){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「かぞくを まもるため ドリルのように するどい ツノで たたかう。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"つのドリルが当たれば強い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ひらいしんで電気タイプが無効。", black);

  }

  if(monsternumber == 1){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「カビが はえていても くさっていても だいじょうぶ。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"HPが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"あついしぼうでほのお、こおりがききづらい。", black);

  }

  if(monsternumber == 2){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「きょうてきに であうと てくびから ほのおを ふきだす。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"こうげきが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ピンチになるとほのおタイプの技の威力が上がる。", black);

  }

  if(monsternumber == 3){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「ふとい うでの ひとふりで あいてを たたきのめす。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"きもくない。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ピンチになるとみずタイプの技の威力が上がる。", black);

  }

  if(monsternumber == 4){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「ジャングルの なかでは てきなしの つよさ。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"とくこうとすばやさが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ピンチになるとくさタイプの技の威力が上がる。", black);

  }

  if(monsternumber == 5){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「でんきを あやつる でんせつの とりポケモン。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"強い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"プレッシャーには特に意味はない。", black);

  }

  if(monsternumber == 6){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「じょうぶな あごで がんせきを かみくだき すすむ」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"ぼうぎょが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"一撃必殺が無効。アズマオウを倒せ。", black);

  }

  if(monsternumber == 7){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「ゆめにまで みた つばさが やっと はえてきた。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"強い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"いかくで相手のこうげきを下げられる。", black);

  }

  if(monsternumber == 8){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「ぶあつい しぼうが てきの こうげきを はねかえす。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"HPが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"あついしぼうでほのお、こおりがききづらい。", black);

  }

  if(monsternumber == 9){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「かたうでを うごかしただけで やまをくずし じひびきを おこす。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"強い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"すなおこしで砂嵐を起こすことができる。", black);

  }

  if(monsternumber == 10){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「スーパーコンピュータなみの ちのう。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"強い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"クリアボディにより能力値が下がらない。", black);

  }

  if(monsternumber == 11){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「いのちがけで しんらいする トレーナーを まもろうとする。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"とくこうが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"もらいびでほのおタイプが無効。", black);

  }


  if(monsternumber == 12){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「ハサミで とらえたものは どんなに かたくても こなごなに くだく。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"こうげきが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ピンチになるとむしタイプの技の威力が上がる。", black);

  }

  if(monsternumber == 13){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「きょうじんな きんにくを もつ。 」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"HPが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ちょすいでみずタイプが無効。", black);

  }

  if(monsternumber == 14){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「とつぜん さむけが するのは ゲンガーが あらわれたからだ。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"すばやさが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ふゆうで地面タイプが無効。", black);

  }

  if(monsternumber == 15){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「はやく しずかに とんで えものに きづかれず しのびよる。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"とにかく速い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"最速であり、それ以外の長所はない。", black);

  }

  if(monsternumber == 16){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「シェルダーの どくそが しみこみ いたさを かんじなくなった。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"HPとぼうぎょが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"さいせいりょくで交代時にHPが回復する。", black);

  }

  if(monsternumber == 17){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「つよい あいてを もとめて そらを とびまわる。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"格好いい。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ピンチになるとほのおタイプの技の威力が上がる。", black);

  }

  if(monsternumber == 18){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「じまんの ツノで あいてを なげとばす。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"こうげきが速い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ピンチになるとむしタイプの技の威力が上がる。", black);
  }

  if(monsternumber == 19){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「16じかんで ちきゅうを 1しゅうできる。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"強い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"マルチスケイルによりもっと強くなる。", black);

  }

  if(monsternumber == 20){
    
    text[0] = TTF_RenderUTF8_Blended(messagefont,"「あらゆる ちょうのうりょくを つかいこなす。」", black);
    
    text[1] = TTF_RenderUTF8_Blended(messagefont,"とくこうが高い。", black);
    
    text[2] = TTF_RenderUTF8_Blended(messagefont,"マジックガードで何かから守られている。", black);
    
  }

 if(monsternumber == 21){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「ちゅうごくでは ほうしを かんぽうやくに する。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"キノコ。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"キノコが本体で虫が寄生されている。", black);

  }

 if(monsternumber == 22){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「ぬけがらが たましいを やどした。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"HPが1しかない。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ふしぎなまもりでほとんどの技が無効。", black);

  }

 if(monsternumber == 23){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「にんじゃのように しんしゅつきぼつ。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"強い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"作者の気合いの塊なのでぜひ使ってほしい。", black);

  }

 if(monsternumber == 24){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「からだは いつも ぬめっている。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"HPが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"特性ちょすいでみずタイプが無効。", black);

  }

 if(monsternumber == 25){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「きもちを やわらげる はどうを おくりこむ。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"可愛い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"１つの技しか打てないけど可愛いし強い。", black);

  }

 if(monsternumber == 26){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「あいてを ゆだんさせ おおきな あごで がぶり。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"可愛い。強い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"なぜかメガ進化後の能力値を持っている。", black);

  }

 if(monsternumber == 27){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「たましいを すいとって もやす。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"とくこうが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"かげふみで相手のソケモンを逃げられなくする。", black);

  }

 if(monsternumber == 28){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「ツメは じどうしゃを スクラップにする はかいりょく。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"むしタイプはない。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"でも特性は、むしのしらせ。", black);

  }

 if(monsternumber == 29){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「おそわれないように いわの したに こもって じっとしている。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"ぼうぎょととくぼうが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"一撃必殺が無効。", black);

  }

 if(monsternumber == 30){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「べつめい アイスモンスター。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"白透過すると透けるバグがある。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ゆきふらしであられを降らせられる。", black);

  }

 if(monsternumber == 31){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「いっしゅんで うみへ ひきずりこむ。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"電気ウナギ。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ふゆうで地面タイプが無効。", black);

  }

 if(monsternumber == 32){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"1位 ゲッコウガ", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"2位 アルセウス", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"3位 ミュウ", black);

  }

 if(monsternumber == 33){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「もえあがる ばくふうは すべてを やきつくすぞ。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"@DJ_HMKのリクエスト。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ピンチになるとほのおタイプの技の威力が上がる。", black);

  }

 if(monsternumber == 34){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「あらそいを きらう やさしい ポケモンだ。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"強い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"ふゆうで地面タイプが無効。", black);

  }

 if(monsternumber == 35){

    text[0] = TTF_RenderUTF8_Blended(messagefont,"「せかいいち うつくしい ポケモン。」", black);

    text[1] = TTF_RenderUTF8_Blended(messagefont,"HPが高い。", black);

    text[2] = TTF_RenderUTF8_Blended(messagefont,"何かの条件を満たすととくこうが2倍になる。", black);

  }

 foruser = monster[monsternumber].detail;
 
 f_scr_rect.x = 250;
 f_scr_rect.y = 120;
 f_rect.x = 0;
 f_rect.y = 0;
 f_rect.w = foruser->w;
 f_rect.h = foruser->h;
 SDL_SetColorKey(foruser, SDL_SRCCOLORKEY, SDL_MapRGB(foruser->format, 0, 0, 0));
 SDL_BlitSurface(foruser,&f_rect,SDL_GetVideoSurface(),&f_scr_rect);

 
 
 t_scr_rect[0].x = 30;
 t_scr_rect[0].y = 20;
 t_scr_rect[1].x = 30;
 t_scr_rect[1].y = 40;
 t_scr_rect[2].x = 30;
 t_scr_rect[2].y = 60;
 
 int k;

 for(k=0;k<3;k++){
  t_rect[k].x = 0;
  t_rect[k].y = 0;
  t_rect[k].w = text[k]->w;
  t_rect[k].h = text[k]->h;
  SDL_BlitSurface(text[k],&t_rect[k],SDL_GetVideoSurface(),&t_scr_rect[k]);
 }



}


   
int select_show_message(int position,SDL_Surface* image,int* mymonster){
  SDL_Surface *q_text,*a_text,*monster;
  SDL_Rect mons_rect,mons_scr_rect;//mons_rect_tmp;
  SDL_Rect a_rect, a_scr_rect,q_rect,q_scr_rect;//a_rect_tmpq_rect_tmp;
  SDL_Event event;
  //int ret,
  int close_msg = 0;
  const char* q_message = "このモンスターでいいですか？";
  const char* a_message = "Y or N";
  SDL_Rect window_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_Surface *video_surface;
  
  video_surface = SDL_GetVideoSurface();


  SDL_FillRect(video_surface, &window_rect, SDL_MapRGB(video_surface->format, 255,255,255 ));

  //モンスター画像
  monster = image;
  mons_rect.x = 0;
  mons_rect.y = 0;
  mons_rect.w = monster->w;
  mons_rect.h = monster->h;
  mons_scr_rect.x = 50;
  mons_scr_rect.y = 120;
  SDL_SetColorKey(monster, SDL_SRCCOLORKEY, SDL_MapRGB(monster->format, 255, 255, 255));

  display(monster,&mons_rect,&mons_scr_rect);


  q_text = TTF_RenderUTF8_Blended(messagefont, q_message, black);

  q_rect.x=0;q_rect.y=0;q_rect.w=q_text->w;q_rect.h=q_text->h;

  q_scr_rect.x = 20; q_scr_rect.y =400;

  a_text = TTF_RenderUTF8_Blended(messagefont, a_message, black);

  a_rect.x=0;a_rect.y=0;a_rect.w=a_text->w;a_rect.h=a_text->h;

  a_scr_rect.x = 20; a_scr_rect.y =420;

  //update_messagerect(q_text,q_message,&q_rect,&q_scr_rect,20,400);
 
  /* サーフェスの複写 */
  display(q_text, &q_rect, &q_scr_rect);
  display(a_text, &a_rect, &a_scr_rect);

  /*モンスターを説明するための関数*/
  user_shine(nom[position]);

  /* サーフェスフリップ */
  SDL_Flip(SDL_GetVideoSurface());
  
  /* メッセージが閉じるまで、元のイベントループには戻らない */
  while(close_msg == 0){	
    if(SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_KEYDOWN:
	switch(event.key.keysym.sym){
	case SDLK_y:
	  *mymonster = position;
	  close_msg = 1;
	  break;
	case SDLK_n:
	  *mymonster = 15;
	  close_msg = 1;
	  break;
	default:
	  break;
	}
	break;
      default:
	break;
      }
    }
    SDL_Delay(1);
  }
  
  SDL_FreeSurface(q_text);
  SDL_FreeSurface(a_text);
  
  return 0;
}  


  
