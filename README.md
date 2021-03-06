# AirCuring
ゲーム名「エアカーリング」

・使用言語：C,C++

・プレイ人数：1人

[ゲーム概要]

プレイヤー(赤いパック)を打ってゴール(三色の円)まで止める。もしくは打つたびに増えていくターン数が上限を超えると終了です。
終了時のスコアがゴルフのように低ければ低いほど良い結果となります。また反射回数が特定回数重なるたびにスコアが減算します。
各オブジェクトは添付画像より詳細があります。
このゲームはよくあるブロック崩しを遊んでいる

[なぜこのゲームを作ったのか]

このゲームはよくあるブロック崩しゲームを遊んでいた時にボールが矩形の頂点に当たっとき物理法則にのっとった反射をしていないことが気に食わず、
頂点(角)に衝突した時の反射を利用したゲームを自分で作りたいと思ったのが切っ掛けでした。

[操作方法]

プレイヤーにはShotMode(プレイヤーを動かせるモード)とViewMode(カメラを動かせるモード)がありそれぞれ操作やできることが異なります。

<ShotMode時>

マウス：向いている方向を変える

F：モード切替

Space：打つ

ESC：ポーズ画面


<ViewMode時>

W：カメラ上移動

A：カメラ左移動

S：カメラ右移動

D：カメラ下移動

F：モード切替

ESC：ポーズ画面

[アピールポイント]

このゲームは私がオブジェクトの反射やエフェクトなどやってみたいことを勉強しながら作りたいと思ったため個人で制作したものとなっています。
またUIやエフェクト以外の各オブジェクトもすべて自作したものを使用しています。
ゲームのアピールポイントとしましてはこのゲームのキーポイントでもある衝突後の反射です。特に矩形との反射に関しましては上下左右だけでなく各頂点と衝突した際も反射角を計算し反射するようにしています。
この頂点との反射はあまり参考になるものが見つからず最終的には自分で計算式を考え、それを反射処理に置き換え使用しています。

次にプログラムに関するアピールポイントです。

・Player(パック)の反射処理

記述している箇所はPlayer.cppのReflection～(ReflectionCircle、ReflectionVertexなど)関数の中身となっています。
特に矩形の頂点(角)の処理内容は反射について調べはしましたが自分の求めるようなものがあまり見つからなかったため、
自分自身で図や式を書きながら思考し独自で考えたもので、コードの内容的には簡易なものように見えますが、一番時間を掛けた箇所でもあります。

・当たり判定を第三者に任せ同じオブジェクトが複数ある場合はまとめて検索できるようにして回している点。
こうすることで同じオブジェクトが何個増えようと処理自体を大きく変える必要が無く、管理しやすくしています。
記述している箇所はObjectCollision.cppです。

・各オブジェクトのデータ(座標やサイズ)は外部データとして扱っている点
外部データにすることでマップ内のオブジェクトの配置を変えたい場合などは外部データだけ変え、プログラムの処理はデータを読み込むだけのため、変える必要がなく短いコードで処理できるようにしています。
記述している箇所は各オブジェクト.cpp内の初期化関数内となっています。


[ゲームを起動する際の注意点]

・ゲーム内にSEやBGMがあるためサウンドデバイスがある状態での起動をお願いします。

・必要なツール

Visual Studio 2019
  
・必要なsdk  

Microsoft DirectX SDK (June 2010)  [こちら](https://www.microsoft.com/en-us/download/details.aspx?id=6812)  

Microsoft DirectX SDkはダウンロードしたexeに従えば簡単にインストールできます。

Autodesk Fbxsdk(2019.0VS2015)  [こちら](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2019-0)

こちらもダウンロードしたexeに従えばインストールできます。

sdkをダウンロードしたら以下の環境変数を登録してください。  

・DXSDK_DIR

  値 : C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\
  
・FBXSDK_DIR  

　値 : C:\Program Files\Autodesk\FBX\FBX SDK\


コーディング規約

ファイル名について

・ファイル名が20文字以上になる場合省略できるところは省略する(例:FBX）

命名規則

アッパーキャメル

・クラス名、ファイル名、関数名、構造体名、定数(列挙体も)

スネークケース(ただし「_ 」は2つまで)

・変数名

変数名の付け方

・クラス内であればm_を先頭に着ける(例:m_value)

・クラス内の構造体変数にもm_を付ける(例:m_value)

・ポインタ変数であればp_を先頭に着ける(m_よりも優先度高)(例:p_value)

・配列(vector、mapも)には最後にs(複数形)を付ける(例:values)

・bool型にはis_を付ける(例:is_up)

・引数には名前の最後に_を付ける(例:value_)

・ローカル変数には何もつけずにスネークケース

条件分岐について

・クラスのインスタンス化は1行に収める

・毎更新の中に含まれる条件分岐は複数行に分ける(デバックしやすいため)

コメントの書き方

・基本doxygen方式

・Header変数、Sorce内の関数名の上、処理の説明は//で書く

他細かい個所

・整数型はできるだけintではなく__int16等を使う

・NULLはできるだけ使わず、nullptrを使う

・定数については#defineではなくconstexprを使用

・アクセス指定の並び順は上からpublicな構造体や列挙体→privateな構造体変数や列挙体変数→publicな関数→privateなメンバ変数