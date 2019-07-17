#include "socketmonster.h"
#include"socketdata.h"


int  damage(Skill askill,Monster* amonster,Monster bmonster){
  double HPP,HPB;

  /*特性判定のためHP割合の判定をあらかじめ行っておく*/
  HPP = (double)amonster->status[0] / (double)get_monster(amonster->name).status[0];

  HPB = (double)bmonster.status[0]/(double)get_monster(bmonster.name).status[0];


  //printf("PAN-PAN PUNCH☆MIND PAN-PAN-PAN-PAN パンチ☆マインド PAN-PAN PUNCH☆MIND UNHAPPYよ、バーイバイ！ PAN-PAN PUNCH☆MIND PAN-PAN-PAN-PAN パンチ☆マインド  PAN-PAN PUNCH☆MIND UNHAPPYよ、バーイバイ！ PAN-PAN PUNCH☆MIND PAN-PAN-PAN-PAN パンチ☆マインド 全体止ま…るな！ ギリギリがんばれHAPPINESS！！ 七つ転んで八回目のジャンプ (ジャンプしてにっこり) つまりコロコロコロコロ　転がりながらでも (すっく立ち上がる) 始めたがりなら (なんとでもなるさ) 道は知らずとも (なんとでもなるさ) だからコロコロコロコロ　こころの向くままに そうだね…幸せはどこにあるのだろ？ 青い鳥はうちにいるって？ 籠が開いたら逃げちゃったよ！ (やあやあ誰か捕まえてはやく　半分っこしようよね) こーっち！！ 一緒にがんばっちゃおう (PAN-PAN) がんばっちゃおう (PAN-PAN) 元気になあれって叫んだら 生命力アップだ 精神力アップだ　強い自分になれそうだいっ がんばりましょ (PAN-PAN) がんばりましょ (PAN-PAN) 未来がキレイに晴れるようにね 私たちこれから きっとねきっとねHAPPYをつかみとるんだよ 馬が逃げても走ればいいのかな (塞翁さんしっかり) よーしパカパカパカパカ 明日へ駈けてゆこう (野を越え川泳げ) 終わりが良ければ (なんとかしちゃうよ) 誤魔化せるかもね (なんとかしちゃうよ) 急げパカパカパカパカ 勢いにまかせて PAN-PAN PUNCH☆MIND PAN-PAN-PAN-PAN パンチ☆マインド PAN-PAN PUNCH☆MIND 負けないで パンチ☆マインド PAN-PAN PUNCH☆MIND PAN-PAN-PAN-PAN パンチ☆マインド PAN-PAN PUNCH☆MIND 負けないで パンチ☆マインド PAN-PAN PUNCH☆MIND PAN-PAN-PAN-PAN パンチ☆マインド PAN-PAN PUNCH☆MIND もう一声だ パンチ☆マインド PAN-PAN PUNCH☆MIND あと一回だ パンチ☆マインド PAN-PAN PUNCH☆MIND はいはい最後の パンチ☆マインド 幸せはどこにあるのだろ？ 胸の中とか言わないでよ かたちが欲しいお年頃 (やあやあ誰か捕まえてはやく ケンカはしないよね) こーっち！こっちへおいでよ！！がんばっちゃおう (PAN-PAN) がんばっちゃおう (PAN-PAN) 元気になあれって叫んだら 生命力アップだ 精神力アップだ 強い自分になれそうだいっ がんばりましょ (PAN-PAN) がんばりましょ (PAN-PAN) 未来がキレイに晴れるようにね 私たちこれから きっとねきっとねHAPPYをつかみとるんだ UNHAPPYなんてさ気にしないんだよ PAN-PAN PUNCH☆MIND PAN-PAN-PAN-PAN パンチ☆マインド PAN-PAN PUNCH☆MIND UNHAPPYよ、バーイバイ！ PAN-PAN PUNCH☆MIND PAN-PAN-PAN-PAN パンチ☆マインド PAN-PAN PUNCH☆MIND UNHAPPYよ、バーイバイ！\n");
  //askillは攻撃技データ。amonsterは攻撃ポケモン。bmonsterは防御側ポケモン

  //0:なし 1:ノ 2:炎 3:水 4:電 5:草 6:氷 7:格 8:毒 9:地 10:飛 11:超 12:虫 13:岩 14:霊 15:竜 16:悪 17:鋼 18:妖

  /*ふしぎなまもり判定,ばつぐん未満はダメージ0*/
  if(strcmp(bmonster.name,"ヌケニン") == 0 && AandD[askill.type][bmonster.type[0]] * AandD[askill.type][bmonster.type[1]] <= 1 )
    return 0;

  /*技がはねるの場合ダメージ0で返す*/
  if(strcmp(askill.name,"はねる") == 0)
    return 0;

  /*技があまえるの場合ダメージ0で返す*/
  if(strcmp(askill.name,"あまえる") == 0)
    return 0;

  /*ひらいしんの判定 電気無効*/
  if(strcmp(bmonster.name,"ピカチュウ") == 0 && askill.type == 4)
    return 0;
  
  /*ひらいしんの判定 電気無効*/
  if(strcmp(bmonster.name,"アズマオウ") == 0 && askill.type == 4)
    return 0;

  /*ちょすいの判定 水無効*/
  if(strcmp(bmonster.name,"ヌオー") == 0 && askill.type == 3)
    return 0;

  /*ちょすいの判定 水無効*/
  if(strcmp(bmonster.name,"ニョロボン") == 0 && askill.type == 3)
    return 0;

  /*ふゆうの判定 地面無効*/
  if(strcmp(bmonster.name,"ラティオス") == 0 && askill.type == 9)
    return 0;

  /*ふゆうの判定 地面無効*/
  if(strcmp(bmonster.name,"シビルドン") == 0 && askill.type == 9)
    return 0;

  /*ふゆうの判定 地面無効*/
  if(strcmp(bmonster.name,"ゲンガー") == 0 && askill.type == 9)
    return 0;

  /*もらいびの判定　炎無効*/
  if(strcmp(bmonster.name,"サーナイト") == 0 && askill.type == 2)
    return 0;

  /*むしのしらせの判定　HP 1/3のときむしタイプ技威力1.5倍*/
  if(strcmp(amonster->name,"ドラピオン") == 0 && HPP <= (double)1/(double)3 && askill.type == 12)
    askill.power = askill.power * 1.5;

  /*むしのしらせの判定　HP 1/3のときむしタイプ技威力1.5倍*/
  if(strcmp(amonster->name,"ヘラクロス") == 0 && HPP <= (double)1/(double)3 && askill.type == 12)
    askill.power = askill.power * 1.5;

  /*むしのしらせの判定　HP 1/3のときむしタイプ技威力1.5倍*/
  if(strcmp(amonster->name,"ハッサム") == 0 && HPP <= (double)1/(double)3 && askill.type == 12)
    askill.power = askill.power * 1.5;

  /*もうかの判定*/
  if(strcmp(amonster->name,"バクフーン") == 0 && HPP <= (double)1/(double)3 && askill.type == 2)
    askill.power = askill.power * 1.5;

  /*もうかの判定*/
  if(strcmp(amonster->name,"リザードン") == 0 && HPP <= (double)1/(double)3 && askill.type == 2)
    askill.power = askill.power * 1.5;

  /*もうかの判定*/
  if(strcmp(amonster->name,"バシャーモ") == 0 && HPP <= (double)1/(double)3 && askill.type == 2)
    askill.power = askill.power * 1.5;

  /*げきりゅうの判定*/
  if(strcmp(amonster->name,"ラグラージ") == 0 && HPP <= (double)1/(double)3 && askill.type == 3)
    askill.power = askill.power * 1.5;

  /*しんりょくの判定*/
  if(strcmp(amonster->name,"ジュカイン") == 0 && HPP <= (double)1/(double)3 && askill.type == 5)
    askill.power = askill.power * 1.5;

  /*がんじょうの判定 一撃必殺無効*/
  if(strcmp(bmonster.name,"ハガネール") == 0){
    if(strcmp(askill.name,"つのドリル")==0 || strcmp(askill.name,"ぜったいれいど")==0 || strcmp(askill.name,"ハサミギロチン") == 0)
      return 0;
  }

  /*フェアリースキンの判定 ノーマル技がフェアリー技になり威力1.5倍*/
  if(strcmp(amonster->name,"ニンフィア") == 0 && askill.type == 1){
    askill.power = askill.power * 1.5;
    askill.type = 18;
  }

  /*ちからもちの判定　物理技威力2倍*/
  if(strcmp(amonster->name,"クチート") == 0 && askill.way == 0)
    askill.power = askill.power * 2;

  /*ちきゅうなげの判定 ダメージ一定(50)*/
  if(strcmp(askill.name,"ちきゅうなげ") == 0)
    return 50;

  /*いかりの前歯の判定 相手のHPを半分にする*/
  if(strcmp(askill.name,"いかりのまえば") == 0)
    return bmonster.status[0] /2;

  /*ジャイロボールの判定 威力は素早さ依存*/
  if(strcmp(askill.name,"ジャイロボール") == 0){
    askill.power = (25 * bmonster.status[5] / amonster->status[5]) + 1;
    if(askill.power > 150)
      askill.power = 150;
  }

  /*ふんかの判定 威力はHP依存*/
  if(strcmp(askill.name,"ふんか") == 0)
     askill.power = 150 * HPP;

  /*ゲッコウガの判定 変幻自在*/
  if(strcmp(amonster->name,"ゲッコウガ") == 0){
    if(amonster->type[0] != askill.type || amonster->type[1] != 0){
      amonster->type[0] = askill.type;
      amonster->type[1] = 0;
    }
  }

  srand((unsigned) time(NULL));

 if(askill.acc <= rand()%100){
   return 0;
 }else{
    int x,y;
     double D;
    if(askill.way == 0){
      x = amonster->status[1];
      y = bmonster.status[2];}
    else{
      x = amonster->status[3];
      y = bmonster.status[4];}
    //xとyは物理と特殊の判別してとくこうか攻撃か決める
    
    //使用技と使用ポケモンのタイプが一致した場合技の威力1.5倍
    //変幻自在によりゲッコウガは常にタイプ一致計算を行う
    if(askill.type == amonster->type[0] || askill.type == amonster->type[1])
      askill.power = askill.power * 1.5;

    double z;

    srand((unsigned) time(NULL));

    z = (85 + (double)(rand()*(100 - 85 + 1.0)/(1.0+RAND_MAX))) / 100;

    D = (((22 * askill.power * x )/ y)/50 +2) * z * AandD[askill.type][bmonster.type[0]] * AandD[askill.type][bmonster.type[1]];

    /*あついしぼうの判定 炎、氷ダメージ半減*/
    if(strcmp(bmonster.name,"カビゴン") == 0 || strcmp(bmonster.name,"トドゼルガ") == 0){
      if(askill.type == 2 || askill.type == 6)
	D = D/2;
    }

    /*マルチスケイルの判定 HPmaxのときダメージ半減*/
    if(strcmp(bmonster.name,"カイリュー") == 0 && HPB >= 1)
      D = D/2;

    /*かんそうはだの判定 炎1.25倍 みず無効*/
    if(strcmp(bmonster.name,"パラセクト") == 0){

      if(askill.type == 2)
	D = D * 1.25;

      else if(askill.type == 3)
	D = 0;

    }

    return D;//かえってくるDがダメージの値です。
  }
  return 0;
}
