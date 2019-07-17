#include "socketmonster.h"
#include"socketdata.h"


//0:なし 1:ノ 2:炎 3:水 4:電 5:草 6:氷 7:格 8:毒 9:地 10:飛 11:超 12:虫 13:岩 14:霊 15:竜 16:悪 17:鋼 18:妖
    
double AandD[19][19]={
  //なし/ノ/炎 /水  /電 /草  /氷 /格 /毒 /地  /飛 /超 /虫  /岩 /霊 /竜  /悪 /鋼 /妖　/
  {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},
  {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.5,0.0,1.0,1.0,0.5,1.0},
  {1.0,1.0,0.5,0.5,1.0,2.0,2.0,1.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5,1.0,2.0,1.0},
  {1.0,1.0,2.0,0.5,1.0,0.5,1.0,1.0,1.0,2.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0,1.0,1.0},
  {1.0,1.0,1.0,2.0,0.5,0.5,1.0,1.0,1.0,0.0,2.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,1.0},
  {1.0,1.0,0.5,2.0,1.0,0.5,1.0,1.0,0.5,2.0,0.5,1.0,0.5,2.0,1.0,0.5,1.0,0.5,1.0},
  {1.0,1.0,0.5,0.5,1.0,2.0,0.5,1.0,1.0,2.0,2.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0},
  {1.0,2.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0,0.5,0.5,0.5,2.0,0.0,1.0,2.0,2.0,0.5},
  {1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,0.5,0.5,1.0,1.0,1.0,0.5,0.5,1.0,1.0,0.0,2.0},
  {1.0,1.0,2.0,1.0,2.0,0.5,1.0,1.0,2.0,1.0,0.0,1.0,0.5,2.0,1.0,1.0,1.0,2.0,1.0},
  {1.0,1.0,1.0,1.0,0.5,2.0,1.0,2.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,1.0,1.0,0.5,1.0},
  {1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,2.0,1.0,1.0,0.5,1.0,1.0,1.0,1.0,0.0,0.5,1.0},
  {1.0,1.0,0.5,1.0,1.0,2.0,1.0,0.5,0.5,1.0,0.5,2.0,1.0,1.0,0.5,1.0,2.0,0.5,0.5},
  {1.0,1.0,2.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5,2.0,1.0,2.0,1.0,1.0,1.0,1.0,0.5,1.0},
  {1.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,2.0,1.0,0.5,1.0,1.0},
  {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,0.0},
  {1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,1.0,2.0,1.0,1.0,2.0,1.0,0.5,1.0,0.5},
  {1.0,1.0,0.5,0.5,0.5,1.0,2.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,1.0,0.5,2.0},
  {1.0,1.0,0.5,1.0,1.0,1.0,1.0,2.0,0.5,1.0,1.0,1.0,1.0,1.0,1.0,2.0,2.0,0.5,1.0}
};

Skill skill[SKILL_NUMBER] = {
  { "つのドリル",0,10000,1,30,NULL}, //一撃必殺
  { "はねる",0,0,1,100,NULL},
  { "のしかかり",0,85,1,100,NULL},
  { "かみくだく",0,80,16,100,NULL },
  { "ほのおのパンチ",0,75,2,100,NULL},
  { "かみなりパンチ",0,75,4,100,NULL },
  { "とびひざげり",0,130,7,90,NULL },
  { "フレアドライブ",0,120,2,100,NULL },
  { "どくづき",0,80,8,100,NULL},
  { "いわなだれ",0,75,13,90,NULL},
  { "じしん",0,100,9,100,NULL },
  { "なみのり",1,90,3,100,NULL},
  { "れいとうビーム",1,90,6,100,NULL},
  { "かわらわり",1,75,7,100,NULL},
  { "リーフストーム",1,130,5,90,NULL },
  { "りゅうのはどう",1,85,15,100,NULL },
  { "きあいだま",1,120,7,70,NULL },
  { "かみなり",1,110,4,70,NULL },
  { "ねっぷう",1,95,2,90,NULL },
  { "ドリルくちばし",0,80,10,100,NULL},
  { "シグナルビーム",1,75,12,100,NULL },
  { "アイアンテール",0,100,17,75,NULL },
  { "ほのおのキバ",0,65,2,95,NULL },
  { "ドラゴンクロー",0,80,15,100,NULL },
  { "りゅうせいぐん",1,130,15,90,NULL },
  { "しねんのずつき",0,80,11,90,NULL },
  { "ぜったいれいど",0,10000,6,30,NULL}, //一撃必殺
  { "ストーンエッジ",0,100,13,80,NULL },
  { "れいとうパンチ",0,75,6,100,NULL },
  { "コメットパンチ",0,90,17,90,NULL },
  { "ムーンフォース",1,95,18,100,NULL},
  { "サイコキネシス",1,90,11,100,NULL},
  { "シャドーボール",1,80,14,100,NULL },
  { "エナジーボール",1,90,5,100,NULL },
  { "アイアンヘッド",0,80,17,100,NULL },
  { "むしくい",0,60,12,100,NULL },
  { "つじぎり",0,70,16,100,NULL },
  { "たきのぼり",0,80,3,100,NULL},
  { "インファイト",0,120,7,100,NULL },
  { "じならし",0,60,9,100,NULL },
  { "ヘドロばくだん",1,90,8,100,NULL },
  { "こごえるかぜ",1,55,6,95,NULL },
  { "アクロバット",0,110,10,100,NULL  },
  { "クロスポイズン",0,70,8,100,NULL  },
  { "シザークロス",0,80,12,100,NULL  },
  { "いかりのまえば",0,50,1,90,NULL  },//ダメージはHPの半分
  { "だいもんじ",1,110,2,85,NULL  },
  { "エアスラッシュ",1,75,10,95,NULL  },
  { "ちきゅうなげ",0,50,7,100,NULL  },//50ダメージ固定
  { "メガホーン",0,120,12,85,NULL  },
  { "アクアテール",0,90,3,90,NULL  },
  { "ハサミギロチン",0,10000,1,30,NULL  },//一撃必殺
  { "シャドークロー",0,70,14,100,NULL  },
  { "つばめがえし",0,60,10,100,NULL  },//必中
  { "あくのはどう",1,80,16,100,NULL  },
  { "とんぼがえり",0,70,12,100,NULL  },//交換どうする？
  { "ハイパーボイス",1,90,1,100,NULL  },
  { "あまえる",1,0,18,100,NULL  },
  { "じゃれつく",0,90,18,90,NULL  },
  { "ジャイロボール",0,100,17,100,NULL  },//威力不定技とは？
  { "ふぶき",1,110,6,70,NULL  },
  { "かえんほうしゃ",1,90,2,100,NULL  },
  { "10まんボルト",1,90,4,100,NULL  },
  { "ラスターカノン",1,80,17,100,NULL  },
  { "ボルテッカー",0,120,4,100,NULL  },
  { "ふんか",1,100,2,100,NULL  },//威力不定技とは？
  { "じんつうりき",1,80,11,100,NULL  },
};


void init(){

  skill[0].image = SDL_LoadBMP("skill00.bmp");
  skill[1].image = SDL_LoadBMP("skill01.bmp");
  skill[2].image = SDL_LoadBMP("skill02.bmp");
  skill[3].image = SDL_LoadBMP("skill03.bmp");
  skill[4].image = SDL_LoadBMP("skill04.bmp");
  skill[5].image = SDL_LoadBMP("skill05.bmp");
  skill[6].image = SDL_LoadBMP("skill06.bmp");
  skill[7].image = SDL_LoadBMP("skill07.bmp");
  skill[8].image = SDL_LoadBMP("skill08.bmp");
  skill[9].image = SDL_LoadBMP("skill09.bmp");
  skill[10].image = SDL_LoadBMP("skill10.bmp");
  skill[11].image = SDL_LoadBMP("skill11.bmp");
  skill[12].image = SDL_LoadBMP("skill12.bmp");
  skill[13].image = SDL_LoadBMP("skill13.bmp");
  skill[14].image = SDL_LoadBMP("skill14.bmp");
  skill[15].image = SDL_LoadBMP("skill15.bmp");
  skill[16].image = SDL_LoadBMP("skill16.bmp");
  skill[17].image = SDL_LoadBMP("skill17.bmp");
  skill[18].image = SDL_LoadBMP("skill18.bmp");
  skill[19].image = SDL_LoadBMP("skill19.bmp");
  skill[20].image = SDL_LoadBMP("skill20.bmp");
  skill[21].image = SDL_LoadBMP("skill21.bmp");
  skill[22].image = SDL_LoadBMP("skill22.bmp");
  skill[23].image = SDL_LoadBMP("skill23.bmp");
  skill[24].image = SDL_LoadBMP("skill24.bmp");
  skill[25].image = SDL_LoadBMP("skill25.bmp");
  skill[26].image = SDL_LoadBMP("skill26.bmp");
  skill[27].image = SDL_LoadBMP("skill27.bmp");
  skill[28].image = SDL_LoadBMP("skill28.bmp");
  skill[29].image = SDL_LoadBMP("skill29.bmp");
  skill[30].image = SDL_LoadBMP("skill30.bmp");
  skill[31].image = SDL_LoadBMP("skill31.bmp");
  skill[32].image = SDL_LoadBMP("skill32.bmp");
  skill[33].image = SDL_LoadBMP("skill33.bmp");
  skill[34].image = SDL_LoadBMP("skill34.bmp");
  skill[35].image = SDL_LoadBMP("skill35.bmp");
  skill[36].image = SDL_LoadBMP("skill36.bmp");
  skill[37].image = SDL_LoadBMP("skill37.bmp");
  skill[38].image = SDL_LoadBMP("skill38.bmp");
  skill[39].image = SDL_LoadBMP("skill39.bmp");
  skill[40].image = SDL_LoadBMP("skill40.bmp");
  skill[41].image = SDL_LoadBMP("skill41.bmp");
  skill[42].image = SDL_LoadBMP("skill42.bmp");
  skill[43].image = SDL_LoadBMP("skill43.bmp");
  skill[44].image = SDL_LoadBMP("skill44.bmp");
  skill[45].image = SDL_LoadBMP("skill45.bmp");
  skill[46].image = SDL_LoadBMP("skill46.bmp");
  skill[47].image = SDL_LoadBMP("skill47.bmp");
  skill[48].image = SDL_LoadBMP("skill48.bmp");
  skill[49].image = SDL_LoadBMP("skill49.bmp");
  skill[50].image = SDL_LoadBMP("skill50.bmp");
  skill[51].image = SDL_LoadBMP("skill51.bmp");
  skill[52].image = SDL_LoadBMP("skill52.bmp");
  skill[53].image = SDL_LoadBMP("skill53.bmp");
  skill[54].image = SDL_LoadBMP("skill54.bmp");
  skill[55].image = SDL_LoadBMP("skill55.bmp");
  skill[56].image = SDL_LoadBMP("skill56.bmp");
  skill[57].image = SDL_LoadBMP("skill57.bmp");
  skill[58].image = SDL_LoadBMP("skill58.bmp");
  skill[59].image = SDL_LoadBMP("skill59.bmp");
  skill[60].image = SDL_LoadBMP("skill60.bmp");
  skill[61].image = SDL_LoadBMP("skill61.bmp");
  skill[62].image = SDL_LoadBMP("skill62.bmp");
  skill[63].image = SDL_LoadBMP("skill63.bmp");
  skill[64].image = SDL_LoadBMP("skill64.bmp");
  skill[65].image = SDL_LoadBMP("skill65.bmp");
  skill[66].image = SDL_LoadBMP("skill66.bmp");



  
  
  strcpy(monster[0].name,"アズマオウ");
  
  monster[0].status[0]=187;
  monster[0].status[1]=112;
  monster[0].status[2]=86;
  monster[0].status[3]=76;
  monster[0].status[4]=100;
  monster[0].status[5]=198;

  monster[0].type[0]=3;//みず
  monster[0].type[1]=0;//なし
  
  monster[0].myskill[0]=skill[0];//つのドリル
  monster[0].myskill[1]=skill[1];//はねる
  monster[0].myskill[2]=skill[1];
  monster[0].myskill[3]=skill[1];
  monster[0].mimage = SDL_LoadBMP("119.bmp");
  monster[0].yimage = SDL_LoadBMP("119_2.bmp");
  monster[0].detail = SDL_LoadBMP("monster0.detail.bmp");
  
  
  
  
  strcpy(monster[1].name,"カビゴン");
  
  monster[1].status[0]=267;
  monster[1].status[1]=178;
  monster[1].status[2]=85;
  monster[1].status[3]=85;
  monster[1].status[4]=131;
  monster[1].status[5]=45;

  monster[1].type[0]=1;//ノーマル
  monster[1].type[1]=0;//なし


  monster[1].myskill[0]=skill[2];//のしかかり
  monster[1].myskill[1]=skill[3];//かみくだく
  monster[1].myskill[2]=skill[4];//ほのおのパンチ
  monster[1].myskill[3]=skill[5];//かみなりパンチ

  monster[1].mimage = SDL_LoadBMP("143.bmp");
  monster[1].yimage = SDL_LoadBMP("143_2.bmp");
  monster[1].detail = SDL_LoadBMP("monster1.detail.bmp");


  strcpy(monster[2].name,"バシャーモ");

  monster[2].status[0]=156;
  monster[2].status[1]=189;
  monster[2].status[2]=90;
  monster[2].status[3]=117;
  monster[2].status[4]=90;
  monster[2].status[5]=132;

  monster[2].type[0]=2;//ほのお
  monster[2].type[1]=7;//かくとう

  monster[2].myskill[0]=skill[6];//とびひざげり
  monster[2].myskill[1]=skill[7];//フレアドライブ
  monster[2].myskill[2]=skill[8];//どくづき
  monster[2].myskill[3]=skill[9];//いわなだれ

  monster[2].mimage =SDL_LoadBMP("257.bmp");
  monster[2].yimage =SDL_LoadBMP("257_2.bmp");
  monster[2].detail = SDL_LoadBMP("monster2.detail.bmp");



  strcpy(monster[3].name,"ラグラージ");

  monster[3].status[0]=207;
  monster[3].status[1]=144;
  monster[3].status[2]=110;
  monster[3].status[3]=136;
  monster[3].status[4]=110;
  monster[3].status[5]=72;

  monster[3].type[0]=3;//みず
  monster[3].type[1]=9;//じめん

  monster[3].myskill[0]=skill[10];//じしん
  monster[3].myskill[1]=skill[11];//なみのり
  monster[3].myskill[2]=skill[12];//れいとうビーム
  monster[3].myskill[3]=skill[13];//かわらわり

  monster[3].mimage =SDL_LoadBMP("260.bmp");
  monster[3].yimage =SDL_LoadBMP("260_2.bmp");
  monster[3].detail = SDL_LoadBMP("monster3.detail.bmp");



  strcpy(monster[4].name,"ジュカイン");

  monster[4].status[0]=146;
  monster[4].status[1]=94;
  monster[4].status[2]=85;
  monster[4].status[3]=157;
  monster[4].status[4]=105;
  monster[4].status[5]=189;

  monster[4].type[0]=5;//くさ
  monster[4].type[1]=0;//なし

  monster[4].myskill[0]=skill[14];//リーフストーム
  monster[4].myskill[1]=skill[15];//りゅうのはどう
  monster[4].myskill[2]=skill[16];//きあいだま
  monster[4].myskill[3]=skill[9];//いわなだれ

  monster[4].mimage = SDL_LoadBMP("254.bmp");
  monster[4].yimage = SDL_LoadBMP("254_2.bmp");
  monster[4].detail = SDL_LoadBMP("monster4.detail.bmp");



  strcpy(monster[5].name,"サンダー");

  monster[5].status[0]=197;
  monster[5].status[1]=99;
  monster[5].status[2]=105;
  monster[5].status[3]=194;
  monster[5].status[4]=110;
  monster[5].status[5]=121;

  monster[5].type[0]=4;//でんき
  monster[5].type[1]=10;//ひこう

  monster[5].myskill[0]=skill[17];//かみなり
  monster[5].myskill[1]=skill[18];//ねっぷう
  monster[5].myskill[2]=skill[19];//ドリルくちばし
  monster[5].myskill[3]=skill[20];//シグナルビーム

  monster[5].mimage = SDL_LoadBMP("145.bmp");
  monster[5].yimage =SDL_LoadBMP("145_2.bmp");
  monster[5].detail = SDL_LoadBMP("monster5.detail.bmp");



  strcpy(monster[6].name,"ハガネール");

  monster[6].status[0]=182;
  monster[6].status[1]=150;
  monster[6].status[2]=221;
  monster[6].status[3]=75;
  monster[6].status[4]=85;
  monster[6].status[5]=45;

  monster[6].type[0]=17;//はがね
  monster[6].type[1]=9;//じめん

  monster[6].myskill[0]=skill[10];//じしん
  monster[6].myskill[1]=skill[21];//アイアンテール
  monster[6].myskill[2]=skill[22];//ほのおのキバ
  monster[6].myskill[3]=skill[3];//かみくだく

  monster[6].mimage = SDL_LoadBMP("208.bmp");
  monster[6].yimage = SDL_LoadBMP("208_2.bmp");
  monster[6].detail = SDL_LoadBMP("monster6.detail.bmp");



  strcpy(monster[7].name,"ボーマンダ");

  monster[7].status[0]=170;
  monster[7].status[1]=205;
  monster[7].status[2]=100;
  monster[7].status[3]=131;
  monster[7].status[4]=90;
  monster[7].status[5]=152;

  monster[7].type[0]=15;//ドラゴン
  monster[7].type[1]=10;//ひこう

  monster[7].myskill[0]=skill[23];//ドラゴンクロー
  monster[7].myskill[1]=skill[24];//りゅうせいぐん
  monster[7].myskill[2]=skill[10];//じしん
  monster[7].myskill[3]=skill[25];//しねんのずつき

  monster[7].mimage = SDL_LoadBMP("373.bmp");
  monster[7].yimage = SDL_LoadBMP("373_2.bmp");
  monster[7].detail = SDL_LoadBMP("monster7.detail.bmp");



  strcpy(monster[8].name,"トドゼルガ");

  monster[8].status[0]=217;
  monster[8].status[1]=90;
  monster[8].status[2]=111;
  monster[8].status[3]=161;
  monster[8].status[4]=110;
  monster[8].status[5]=85;

  monster[8].type[0]=3;//みず
  monster[8].type[1]=6;//こおり

  monster[8].myskill[0]=skill[12];//れいとうビーム
  monster[8].myskill[1]=skill[11];//なみのり
  monster[8].myskill[2]=skill[2];//のしかかり
  monster[8].myskill[3]=skill[26];//ぜったいれいど

  monster[8].mimage = SDL_LoadBMP("365.bmp");
  monster[8].yimage =SDL_LoadBMP("365_2.bmp");
  monster[8].detail = SDL_LoadBMP("monster8.detail.bmp");



  strcpy(monster[9].name,"バンギラス");

  monster[9].status[0]=175;
  monster[9].status[1]=204;
  monster[9].status[2]=131;
  monster[9].status[3]=103;
  monster[9].status[4]=180;
  monster[9].status[5]=113;

  monster[9].type[0]=13;//いわ
  monster[9].type[1]=16;//あく


  monster[9].myskill[0]=skill[27];//ストーンエッジ
  monster[9].myskill[1]=skill[3];//かみくだく
  monster[9].myskill[2]=skill[28];//れいとうパンチ
  monster[9].myskill[3]=skill[10];//じしん

  monster[9].mimage = SDL_LoadBMP("248.bmp");
  monster[9].yimage =SDL_LoadBMP("248_2.bmp");
  monster[9].detail = SDL_LoadBMP("monster9.detail.bmp");



  strcpy(monster[10].name,"メタグロス");

  monster[10].status[0]=166;
  monster[10].status[1]=205;
  monster[10].status[2]=151;
  monster[10].status[3]=103;
  monster[10].status[4]=111;
  monster[10].status[5]=111;

  monster[10].type[0]=17;//はがね
  monster[10].type[1]=11;//エスパー

  monster[10].myskill[0]=skill[29];//コメットパンチ
  monster[10].myskill[1]=skill[25];//しねんのずつき
  monster[10].myskill[2]=skill[28];//れいとうパンチ
  monster[10].myskill[3]=skill[10];//じしん

  monster[10].mimage = SDL_LoadBMP("376.bmp");
  monster[10].yimage = SDL_LoadBMP("376_2.bmp");
  monster[10].detail = SDL_LoadBMP("monster10.detail.bmp");



  strcpy(monster[11].name,"サーナイト");

  monster[11].status[0]=144;
  monster[11].status[1]=76;
  monster[11].status[2]=85;
  monster[11].status[3]=194;
  monster[11].status[4]=135;
  monster[11].status[5]=132;

  monster[11].type[0]=11;//エスパー
  monster[11].type[1]=18;//フェアリー

  monster[11].myskill[0]=skill[30];//ムーンフォース
  monster[11].myskill[1]=skill[31];//サイコキネシス
  monster[11].myskill[2]=skill[32];//シャドーボール
  monster[11].myskill[3]=skill[33];//エナジーボール

  monster[11].mimage =SDL_LoadBMP("282.bmp");
  monster[11].yimage =SDL_LoadBMP("282_2.bmp");
  monster[11].detail = SDL_LoadBMP("monster11.detail.bmp");



  strcpy(monster[12].name,"ハッサム");

  monster[12].status[0]=177;
  monster[12].status[1]=200;
  monster[12].status[2]=121;
  monster[12].status[3]=67;
  monster[12].status[4]=100;
  monster[12].status[5]=85;

  monster[12].type[0]=17;//はがね
  monster[12].type[1]=12;//むし

  monster[12].myskill[0]=skill[34];//アイアンヘッド
  monster[12].myskill[1]=skill[35];//むしくい
  monster[12].myskill[2]=skill[36];//つじぎり
  monster[12].myskill[3]=skill[13];//かわらわり

  monster[12].mimage = SDL_LoadBMP("212.bmp");
  monster[12].yimage = SDL_LoadBMP("212_2.bmp");
  monster[12].detail = SDL_LoadBMP("monster12.detail.bmp");



  strcpy(monster[13].name,"ニョロボン");

  monster[13].status[0]=197;
  monster[13].status[1]=161;
  monster[13].status[2]=116;
  monster[13].status[3]=81;
  monster[13].status[4]=110;
  monster[13].status[5]=90;

  monster[13].type[0]=3;//みず
  monster[13].type[1]=7;//かくとう

  monster[13].myskill[0]=skill[37];//たきのぼり
  monster[13].myskill[1]=skill[28];//れいとうパンチ
  monster[13].myskill[2]=skill[38];//インファイト
  monster[13].myskill[3]=skill[39];//じならし

  monster[13].mimage = SDL_LoadBMP("062.bmp");
  monster[13].yimage =SDL_LoadBMP("062_2.bmp");
  monster[13].detail = SDL_LoadBMP("monster13.detail.bmp");



  strcpy(monster[14].name,"ゲンガー");

  monster[14].status[0]=136;
  monster[14].status[1]=76;
  monster[14].status[2]=80;
  monster[14].status[3]=182;
  monster[14].status[4]=95;
  monster[14].status[5]=178;

  monster[14].type[0]=14;//ゴースト
  monster[14].type[1]=8;//どく

  monster[14].myskill[0]=skill[32];//シャドーボール
  monster[14].myskill[1]=skill[40];//ヘドロばくだん
  monster[14].myskill[2]=skill[16];//きあいだま
  monster[14].myskill[3]=skill[41];//こごえるかぜ

  monster[14].mimage = SDL_LoadBMP("094.bmp");
  monster[14].yimage = SDL_LoadBMP("094_2.bmp");
  monster[14].detail = SDL_LoadBMP("monster14.detail.bmp");



  strcpy(monster[15].name,"クロバット");

  monster[15].status[0]=161;
  monster[15].status[1]=142;
  monster[15].status[2]=100;
  monster[15].status[3]=81;
  monster[15].status[4]=100;
  monster[15].status[5]=200;

  monster[15].type[0]=8;//どく
  monster[15].type[1]=10;//ひこう

  monster[15].myskill[0]=skill[42];//アクロバット
  monster[15].myskill[1]=skill[43];//クロスポイズン
  monster[15].myskill[2]=skill[44];//シザークロス
  monster[15].myskill[3]=skill[45];//いかりのまえば

  monster[15].mimage = SDL_LoadBMP("169.bmp");
  monster[15].yimage = SDL_LoadBMP("169_2.bmp");
  monster[15].detail = SDL_LoadBMP("monster15.detail.bmp");





  strcpy(monster[16].name,"ヤドラン");

  monster[16].status[0]=202;
  monster[16].status[1]=85;
  monster[16].status[2]=178;
  monster[16].status[3]=120;
  monster[16].status[4]=101;
  monster[16].status[5]=50;

  monster[16].type[0]=3;//みず
  monster[16].type[1]=11;//エスパー

  monster[16].myskill[0]=skill[12];//れいとうビーム
  monster[16].myskill[1]=skill[11];//なみのり
  monster[16].myskill[2]=skill[31];//サイコキネシス
  monster[16].myskill[3]=skill[46];//だいもんじ

  monster[16].mimage = SDL_LoadBMP("080.bmp");
  monster[16].yimage = SDL_LoadBMP("080_2.bmp");
  monster[16].detail = SDL_LoadBMP("monster16.detail.bmp");




  strcpy(monster[17].name,"リザードン");

  monster[17].status[0]=154;
  monster[17].status[1]=93;
  monster[17].status[2]=98;
  monster[17].status[3]=161;
  monster[17].status[4]=105;
  monster[17].status[5]=167;

  monster[17].type[0]=2;//ほのお
  monster[17].type[1]=10;//ひこう

  monster[17].myskill[0]=skill[46];//だいもんじ
  monster[17].myskill[1]=skill[47];//エアスラッシュ
  monster[17].myskill[2]=skill[15];//りゅうのはどう
  monster[17].myskill[3]=skill[48];//ちきゅうなげ

  monster[17].mimage = SDL_LoadBMP("006.bmp");
  monster[17].yimage = SDL_LoadBMP("006_2.bmp");
  monster[17].detail = SDL_LoadBMP("monster17.detail.bmp");



  strcpy(monster[18].name,"ヘラクロス");

  monster[18].status[0]=156;
  monster[18].status[1]=194;
  monster[18].status[2]=95;
  monster[18].status[3]=54;
  monster[18].status[4]=115;
  monster[18].status[5]=137;

  monster[18].type[0]=12;//むし
  monster[18].type[1]=7;//かくとう

  monster[18].myskill[0]=skill[49];//メガホーン
  monster[18].myskill[1]=skill[38];//インファイト
  monster[18].myskill[2]=skill[10];//じしん
  monster[18].myskill[3]=skill[27];//ストーンエッジ

  monster[18].mimage = SDL_LoadBMP("214.bmp");
  monster[18].yimage = SDL_LoadBMP("214_2.bmp");
  monster[18].detail = SDL_LoadBMP("monster18.detail.bmp");



  strcpy(monster[19].name,"カイリュー");

  monster[19].status[0]=167;
  monster[19].status[1]=204;
  monster[19].status[2]=115;
  monster[19].status[3]=108;
  monster[19].status[4]=120;
  monster[19].status[5]=132;

  monster[19].type[0]=15;//ドラゴン
  monster[19].type[1]=10;//ひこう

  monster[19].myskill[0]=skill[23];//ドラゴンクロー
  monster[19].myskill[1]=skill[10];//じしん
  monster[19].myskill[2]=skill[50];//アクアテール
  monster[19].myskill[3]=skill[13];//かわらわり

  monster[19].mimage = SDL_LoadBMP("149.bmp");
  monster[19].yimage = SDL_LoadBMP("149_2.bmp");
  monster[19].detail = SDL_LoadBMP("monster19.detail.bmp");



  strcpy(monster[20].name,"フーディン");

  monster[20].status[0]=131;
  monster[20].status[1]=63;
  monster[20].status[2]=65;
  monster[20].status[3]=187;
  monster[20].status[4]=115;
  monster[20].status[5]=189;

  monster[20].type[0]=11;//エスパー
  monster[20].type[1]=0;//なし

  monster[20].myskill[0]=skill[31];//サイコキネシス
  monster[20].myskill[1]=skill[32];//シャドーボール
  monster[20].myskill[2]=skill[33];//エナジーボール
  monster[20].myskill[3]=skill[16];//きあいだま

  monster[20].mimage = SDL_LoadBMP("065.bmp");
  monster[20].yimage = SDL_LoadBMP("065_2.bmp");
  monster[20].detail = SDL_LoadBMP("monster20.detail.bmp");



  strcpy(monster[21].name,"パラセクト");

  monster[21].status[0]=167;
  monster[21].status[1]=132;
  monster[21].status[2]=100;
  monster[21].status[3]=80;
  monster[21].status[4]=101;
  monster[21].status[5]=55;

  monster[21].type[0]=12;//むし
  monster[21].type[1]=5;//くさ

  monster[21].myskill[0]=skill[51];//ハサミギロチン
  monster[21].myskill[1]=skill[44];//シザークロス
  monster[21].myskill[2]=skill[43];//クロスポイズン
  monster[21].myskill[3]=skill[13];//かわらわり
 
  monster[21].mimage = SDL_LoadBMP("047.bmp");
  monster[21].yimage = SDL_LoadBMP("047_2.bmp");
  monster[21].detail = SDL_LoadBMP("monster21.detail.bmp");



  strcpy(monster[22].name,"ヌケニン");

  monster[22].status[0]=1;
  monster[22].status[1]=156;
  monster[22].status[2]=65;
  monster[22].status[3]=45;
  monster[22].status[4]=51;
  monster[22].status[5]=60;

  monster[22].type[0]=12;//むし
  monster[22].type[1]=14;//ゴースト

  monster[22].myskill[0]=skill[52];//シャドークロー
  monster[22].myskill[1]=skill[44];//シザークロス
  monster[22].myskill[2]=skill[36];//つじぎり
  monster[22].myskill[3]=skill[53];//つばめがえし
 
  monster[22].mimage = SDL_LoadBMP("292.bmp");
  monster[22].yimage = SDL_LoadBMP("292_2.bmp");
  monster[22].detail = SDL_LoadBMP("monster22.detail.bmp");



  strcpy(monster[23].name,"ゲッコウガ");

  monster[23].status[0]=148;
  monster[23].status[1]=103;
  monster[23].status[2]=87;
  monster[23].status[3]=155;
  monster[23].status[4]=91;
  monster[23].status[5]=191;

  monster[23].type[0]=3;//みず
  monster[23].type[1]=16;//あく

  monster[23].myskill[0]=skill[11];//なみのり
  monster[23].myskill[1]=skill[54];//あくのはどう
  monster[23].myskill[2]=skill[12];//れいとうビーム
  monster[23].myskill[3]=skill[55];//とんぼがえり
 
  monster[23].mimage = SDL_LoadBMP("gkkg-2.bmp");
  monster[23].yimage = SDL_LoadBMP("gkkg-2.bmp");
  monster[23].detail = SDL_LoadBMP("monster23.detail.bmp");



  strcpy(monster[24].name,"ヌオー");

  monster[24].status[0]=202;
  monster[24].status[1]=94;
  monster[24].status[2]=150;
  monster[24].status[3]=85;
  monster[24].status[4]=85;
  monster[24].status[5]=56;

  monster[24].type[0]=3;//みず
  monster[24].type[1]=9;//じめん

  monster[24].myskill[0]=skill[10];//じしん
  monster[24].myskill[1]=skill[12];//れいとうビーム
  monster[24].myskill[2]=skill[27];//ストーンエッジ
  monster[24].myskill[3]=skill[11];//なみのり
 
  monster[24].mimage = SDL_LoadBMP("195.bmp");
  monster[24].yimage = SDL_LoadBMP("195_2.bmp");
  monster[24].detail = SDL_LoadBMP("monster24.detail.bmp");



  strcpy(monster[25].name,"ニンフィア");

  monster[25].status[0]=202;
  monster[25].status[1]=76;
  monster[25].status[2]=85;
  monster[25].status[3]=178;
  monster[25].status[4]=150;
  monster[25].status[5]=81;

  monster[25].type[0]=18;//フェアリー
  monster[25].type[1]=0;//なし

  monster[25].myskill[0]=skill[56];//ハイパーボイス
  monster[25].myskill[1]=skill[57];//あまえる
  monster[25].myskill[2]=skill[57];//あまえる
  monster[25].myskill[3]=skill[57];//あまえる
 
  monster[25].mimage = SDL_LoadBMP("nnfa-2.bmp");
  monster[25].yimage = SDL_LoadBMP("nnfa-2.bmp");
  monster[25].detail = SDL_LoadBMP("monster25.detail.bmp");




  strcpy(monster[26].name,"クチート");

  monster[26].status[0]=157;
  monster[26].status[1]=172;
  monster[26].status[2]=146;
  monster[26].status[3]=67;
  monster[26].status[4]=115;
  monster[26].status[5]=70;

  monster[26].type[0]=17;//はがね
  monster[26].type[1]=18;//フェアリー

  monster[26].myskill[0]=skill[58];//じゃれつく
  monster[26].myskill[1]=skill[34];//アイアンヘッド
  monster[26].myskill[2]=skill[9];//いわなだれ
  monster[26].myskill[3]=skill[13];//かわらわり

  monster[26].mimage = SDL_LoadBMP("303.bmp");
  monster[26].yimage = SDL_LoadBMP("303_2.bmp");
  monster[26].detail = SDL_LoadBMP("monster26.detail.bmp"); 




  strcpy(monster[27].name,"シャンデラ");

  monster[27].status[0]=136;
  monster[27].status[1]=67;
  monster[27].status[2]=110;
  monster[27].status[3]=197;
  monster[27].status[4]=110;
  monster[27].status[5]=145;

  monster[27].type[0]=14;//ゴースト
  monster[27].type[1]=2;//ほのお

  monster[27].myskill[0]=skill[46];//だいもんじ
  monster[27].myskill[1]=skill[32];//シャドーボール
  monster[27].myskill[2]=skill[33];//エナジーボール
  monster[27].myskill[3]=skill[31];//サイコキネシス
 
  monster[27].mimage = SDL_LoadBMP("609.bmp");
  monster[27].yimage = SDL_LoadBMP("609_2.bmp");
  monster[27].detail = SDL_LoadBMP("monster27.detail.bmp");



  strcpy(monster[28].name,"ドラピオン");

  monster[28].status[0]=146;
  monster[28].status[1]=156;
  monster[28].status[2]=130;
  monster[28].status[3]=72;
  monster[28].status[4]=95;
  monster[28].status[5]=147;

  monster[28].type[0]=8;//どく
  monster[28].type[1]=16;//あく

  monster[28].myskill[0]=skill[35];//むしくい
  monster[28].myskill[1]=skill[36];//つじぎり
  monster[28].myskill[2]=skill[43];//クロスポイズン
  monster[28].myskill[3]=skill[9];//いわなだれ
 
  monster[28].mimage = SDL_LoadBMP("452.bmp");
  monster[28].yimage = SDL_LoadBMP("452_2.bmp");
  monster[28].detail = SDL_LoadBMP("monster28.detail.bmp");



  strcpy(monster[29].name,"ツボツボ");

  monster[29].status[0]=127;
  monster[29].status[1]=33;
  monster[29].status[2]=267;
  monster[29].status[3]=27;
  monster[29].status[4]=266;
  monster[29].status[5]=25;

  monster[29].type[0]=12;//むし
  monster[29].type[1]=13;//いわ

  monster[29].myskill[0]=skill[35];//むしくい
  monster[29].myskill[1]=skill[27];//ストーンエッジ
  monster[29].myskill[2]=skill[10];//じしん
  monster[29].myskill[3]=skill[59];//ジャイロボール
 
  monster[29].mimage = SDL_LoadBMP("213.bmp");
  monster[29].yimage = SDL_LoadBMP("213_2.bmp");
  monster[29].detail = SDL_LoadBMP("monster29.detail.bmp");



  strcpy(monster[30].name,"ユキノオー");

  monster[30].status[0]=166;
  monster[30].status[1]=123;
  monster[30].status[2]=95;
  monster[30].status[3]=129;
  monster[30].status[4]=105;
  monster[30].status[5]=112;

  monster[30].type[0]=6;//こおり
  monster[30].type[1]=5;//くさ

  monster[30].myskill[0]=skill[60];//ふぶき
  monster[30].myskill[1]=skill[10];//じしん
  monster[30].myskill[2]=skill[33];//エナジーボール
  monster[30].myskill[3]=skill[16];//きあいだま
 
  monster[30].mimage = SDL_LoadBMP("460.bmp");
  monster[30].yimage = SDL_LoadBMP("460_2.bmp");
  monster[30].detail = SDL_LoadBMP("monster30.detail.bmp");



  strcpy(monster[31].name,"シビルドン");

  monster[31].status[0]=192;
  monster[31].status[1]=183;
  monster[31].status[2]=101;
  monster[31].status[3]=112;
  monster[31].status[4]=100;
  monster[31].status[5]=70;

  monster[31].type[0]=4;//でんき
  monster[31].type[1]=0;//なし

  monster[31].myskill[0]=skill[62];//10まんボルト
  monster[31].myskill[1]=skill[61];//かえんほうしゃ
  monster[31].myskill[2]=skill[63];//ラスターカノン
  monster[31].myskill[3]=skill[15];//りゅうのはどう
 
  monster[31].mimage = SDL_LoadBMP("604.bmp");
  monster[31].yimage = SDL_LoadBMP("604_2.bmp");
  monster[31].detail = SDL_LoadBMP("monster31.detail.bmp");



  strcpy(monster[32].name,"ピカチュウ");

  monster[32].status[0]=111;
  monster[32].status[1]=214;
  monster[32].status[2]=60;
  monster[32].status[3]=126;
  monster[32].status[4]=70;
  monster[32].status[5]=156;

  monster[32].type[0]=4;//でんき
  monster[32].type[1]=0;//なし

  monster[32].myskill[0]=skill[64];//ボルテッカー
  monster[32].myskill[1]=skill[21];//アイアンテール
  monster[32].myskill[2]=skill[48];//ちきゅうなげ
  monster[32].myskill[3]=skill[13];//かわらわり
 
  monster[32].mimage = SDL_LoadBMP("025.bmp");
  monster[32].yimage = SDL_LoadBMP("025_2.bmp");
  monster[32].detail = SDL_LoadBMP("monster32.detail.bmp");



  strcpy(monster[33].name,"バクフーン");

  monster[33].status[0]=153;
  monster[33].status[1]=93;
  monster[33].status[2]=99;
  monster[33].status[3]=161;
  monster[33].status[4]=105;
  monster[33].status[5]=167;

  monster[33].type[0]=2;//ほのお
  monster[33].type[1]=0;//なし

  monster[33].myskill[0]=skill[65];//ふんか
  monster[33].myskill[1]=skill[61];//かえんほうしゃ
  monster[33].myskill[2]=skill[16];//きあいだま
  monster[33].myskill[3]=skill[66];//じんつうりき
 
  monster[33].mimage = SDL_LoadBMP("157.bmp");
  monster[33].yimage = SDL_LoadBMP("157_2.bmp");
  monster[33].detail = SDL_LoadBMP("monster33.detail.bmp");



  strcpy(monster[34].name,"ラティオス");

  monster[34].status[0]=156;
  monster[34].status[1]=99;
  monster[34].status[2]=100;
  monster[34].status[3]=182;
  monster[34].status[4]=130;
  monster[34].status[5]=178;

  monster[34].type[0]=15;//ドラゴン
  monster[34].type[1]=11;//エスパー

  monster[34].myskill[0]=skill[15];//りゅうのはどう
  monster[34].myskill[1]=skill[11];//なみのり
  monster[34].myskill[2]=skill[31];//サイコキネシス
  monster[34].myskill[3]=skill[33];//エナジーボール
 
  monster[34].mimage = SDL_LoadBMP("381.bmp");
  monster[34].yimage = SDL_LoadBMP("381_2.bmp");
  monster[34].detail = SDL_LoadBMP("monster34.detail.bmp");



  strcpy(monster[35].name,"ミロカロス");

  monster[35].status[0]=202;
  monster[35].status[1]=72;
  monster[35].status[2]=99;
  monster[35].status[3]=167;
  monster[35].status[4]=146;
  monster[35].status[5]=101;

  monster[35].type[0]=3;//みず
  monster[35].type[1]=0;//なし

  monster[35].myskill[0]=skill[11];//なみのり
  monster[35].myskill[1]=skill[12];//れいとうビーム
  monster[35].myskill[2]=skill[15];//りゅうのはどう
  monster[35].myskill[3]=skill[41];//こごえるかぜ

  monster[35].mimage = SDL_LoadBMP("350.bmp");
  monster[35].yimage = SDL_LoadBMP("350_2.bmp");
  monster[35].detail = SDL_LoadBMP("monster35.detail.bmp");


  strcpy(nl.name,"なる");
  nl.status[0] = 1;
  nl.status[1] = 1;
  nl.status[2] = 1;
  nl.status[3] = 1;
  nl.status[4] = 1;
  nl.status[5] = 1;
  
  nl.type[0] = 1;
  nl.type[1] = 1;
  
  nl.myskill[0] = skill[0];
  nl.myskill[1] = skill[1];
  nl.myskill[2] = skill[2];
  nl.myskill[3] = skill[3];

  nl.mimage = SDL_LoadBMP("119.bmp");
  nl.yimage = SDL_LoadBMP("119_2.bmp");  

}
