/**
 * @file Player.h
 * @brief ゲームで操作するプレイヤーを扱う
 * @details 中身：プレイヤー(パック)クラス、更新ステップ列挙体
**/
#ifndef PLAYER_H_
#define PLAYER_H_
#include "ObjectBase.h"
#include "../System/Inputter.h"
#include "../System/Sound/SoundController.h"
#include "../Utility/Collision/Collision.h"
#include "../Utility/Calculation.h"

#include "Camera.h"
#include "Block/BlockController.h"
#include "Floor/Floor.h"
#include "Floor/Debuf/DebufController.h"
#include "Floor/GoalFloor.h"

constexpr unsigned __int8 GameTrun = 9;       //!ゲームの制限ターン
constexpr float FrameTime = 0.001f;           //!1フレームで加算する時間
constexpr float StopSpeed = 0.01f;            //!0に近い数字(摩擦によるプレイヤーの移動停止用)
constexpr unsigned __int8 ReflectMax = 5;     //!反射によるスコア減算の反射回数
constexpr unsigned __int8 ReflectScore = -5;  //!反射によるスコア減算数
constexpr unsigned __int8 RedGoalScore = -3;    //!赤色のゴール地点のスコア減算数
constexpr unsigned __int8 YellowGoalScore = -2; //!黄色のゴール地点のスコア減算数
constexpr unsigned __int8 GreenGoalScore = -1;  //!緑色のゴール地点のスコア減算数

constexpr float StopFloorFriction = 1.0f;     //!スピード減衰床の上での摩擦係数
constexpr float Gravity= 9.8f;                //!重力
constexpr float PlayerPosMin_Y = -29.0;       //!プレイヤー座標の最低値(Y座標のみ)
constexpr float PlayerUpSpeed = 0.1f;         //!プレイヤーの上に上がるスピード(終了演出用)
constexpr float HitEffectPosLength = 1.3f;    //!衝突エフェクトをプレイヤーから離す距離の倍率
//!ゴールエフェクトは良く見えるように2つ描画させる
constexpr float GoalEffectPosHeight = 4.0f;   //!床から出すゴールエフェクトの高さ
constexpr float GoalEffect2PosHeight = 10.0f; //!床から出すゴールエフェクトの高さ


//!更新ステップ
enum class PlayerUpdateStep
{
	StartProduction,  //!開始演出
	GameMain,		  //!本編
	EndProduction,	  //!終了演出
};

/**
* プレイヤー(パック)クラス
*/
class Player :public ObjectBase
{
public:
	struct PlayerInfo :public ObjectInfo
	{
		//!初期化
		PlayerInfo() :
			m_old_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_nor_vec(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_speed(0.0f),
			m_change_radian(0.0f),
			m_mass(0.0f),
			m_friction(0.0f),
			m_timer(0),
			m_reflect_counter(0),
			m_trun_counter(0),
			m_score_counter(0),
			m_is_turnend(false),
			m_is_start(false),
			m_is_goal(false),
			m_end(false),
			m_is_movement(false),
			m_efk_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{}

		D3DXVECTOR3 m_old_pos;  //!移動前座標(回転用)

		D3DXVECTOR3 m_nor_vec; //!方向ベクトル

		float m_speed;     //!移動スピード
		float m_setspeed;  //!移動スピード

		float m_change_radian; //!回転角度

		/* 摩擦用 */
		float m_mass;         //!質量
		float m_friction;     //!動摩擦係数
		float m_acceleration; //!加速度

		float m_timer;  //!経過時間

		int m_reflect_counter; //!反射回数
		int m_trun_counter;    //!進行ターン数
		__int8 m_score_counter;  //!加算するスコア数

		/* 操作可能判定 */
		bool m_is_start; //!ゲームスタート
		bool m_is_goal;	 //!ゴール時
		bool m_end;	     //!ゲームエンドフラグ

		bool m_is_movement;
		bool m_is_turnend;       //!1ターン終了フラグ

		D3DXVECTOR3 m_efk_pos;      //!エフェクト表示座標保存用
	};

private:
	PlayerInfo player_info;

public:
	/**
 　　* @brief  コンストラクタ
 　　* @param (camera_) カメラアドレス
 　　* @param (ui_)     ゲームUIアドレス
 　　* @param (block_)  ブロック管理アドレス
 　　* @param (floor_)  ゲーム床アドレス
 　　* @param (stop_)   停止デバフアドレス
 　　* @param (reset_)  リセットデバフアドレス
 　　* @param (goal_)   ゴールアドレス
 　　*/
	Player(Camera* camera_, BlockController* block_, 
		Floor* floor_, DebufController* debuf_, Goal* goal_);

	/**
	 * @brief  初期化関数
	 * @param (stage_id_) 選択ステージ名(例"Stage1")
	 * @detail オブジェクト情報初期化
	 */
	void Init(std::string stage_str_);

	/**
	 * @brief  他オブジェクト情報取得関数
	 * @detail 当たり判定等で使用するほかのオブジェクト情報を取得
	 */
	void SetOtherObjeInfo();

	/**
	 * @brief  外部データ読み込み関数
	 * @detail 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadPlayerExternalInfo(std::string stage_str_);

	/**
	 * @brief  更新関数
	 * @detail 更新処理まとめ関数
	 */
	void Update();

	/**
	 * @brief   描画情報送信関数
	 * @detail  Fbx管理クラスにオブジェクト情報を送る
	 */
	void Draw();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
 　　* @brief  開始演出関数
 　　* @detail ゲーム開始時にプレイヤーが上から降ってくるような演出を行う
 　　*/
	void StartProduction();

	/**
 　　* @brief  終了演出関数
 　　* @detail ゴール時、またはターン制限を超えたときにプレイヤーが上に上がっていく演出を行う
 　　*/
	void EndProduction();

	/**
 　　* @brief  移動関数
 　　* @detail プレイヤーの移動処理行う
 　　*/
	void Move();

#pragma region 当たり判定
	/**
　　* @brief  当たり判定関数
　　* @detail 各オブジェクトとの当たり判定まとめ
　　* @detail 衝突時にプレイヤーの反射も行っている
　　*/
	void HitController();

	/**
 　　* @brief  矩形型ブロック当たり判定関数
 　　* @detail 各矩形型ブロックとの当たり判定を行う
 　　* @detail 何処に当たったかで反射する向きが違うため、上下、左右、頂点と当たり判定を分けている
 　　*/
	void HitRectBlock();

	/**
 　　* @brief  円形型ブロック当たり判定関数
 　　* @detail 各円形型ブロックとの当たり判定を行う
 　　*/
	void HitCircleBlock();

	/**
 　　* @brief  リセットデバフ当たり判定関数
 　　* @detail 当たると初期位置に戻される床との当たり判定を行う
 　　*/
	void HitReset();

	/**
 　　* @brief  停止デバフ当たり判定関数
 　　* @detail 当たると摩擦係数が増す床との当たり判定を行う
 　　*/
	void HitStop();

	/**
 　　* @brief  ゴール当たり判定関数
 　　* @detail ゴール床との当たり判定を行う
   　* @detail ゴール床はターンが終わった時に当たり判定を行う
 　　* @detail 緑、黄色、赤と当たる箇所にスコアが違うため別々で行う
 　　*/
	void HitGoal();

#pragma endregion

	/**
 　　* @brief  衝突時エフェクト開始関数
 　　* @detail プレイヤーとブロックが衝突したときにeffectにエフェクトを表示するように問い合わせる
 　　*/
	void StartHitEffect(D3DXVECTOR3 block_pos_);

	/**
 　　* @brief  落下時エフェクト開始関数
 　　* @detail プレイヤーが床から落ちたときにeffectにエフェクトを表示するように問い合わせる
 　　*/
	void StartFallEffect();

	/**
 　　* @brief  リセット時エフェクト開始関数
 　　* @detail プレイヤーとリセットデバフと衝突したときにeffectにエフェクトを表示するように問い合わせる
 　　*/
	void StartResetEffect();

	/**
 　　* @brief  ゲーム終了時エフェクト開始関数
 　　* @detail ゴール、またはターン制限を超えたときにeffectにエフェクトを表示するように問い合わせる
 　　*/
	void StartGoalEffect();

	/**
 　　* @brief  矩形型ブロック反射方向計算関数
     * @param (type_)  衝突した辺情報(上下か左右か)
	 * @param (rad_)   衝突対象の回転角度
 　　* @detail 反射後の方向ベクトルを算出する
 　　*/
	D3DXVECTOR3 ReflectionRect(HitRectPoint type_, float rad_);

	/**
　　* @brief  円形型ブロック反射方向計算関数
	* @param (circle_pos_)  衝突対象の座標
　　* @detail 反射後の方向ベクトルを算出する
　　*/
	D3DXVECTOR3 ReflectionCircle(D3DXVECTOR3 circle_pos_);

	/**
　　* @brief  矩形型ブロック頂点反射方向計算関数
	* @param (type_)  衝突した頂点情報
	* @param (r_pos_)  衝突対象の座標
	* @param (width_)  衝突対象の横幅
	* @param (height_) 衝突対象の縦幅
	* @param (rad_)    衝突対象の回転角度
　　* @detail 反射後の方向ベクトルを算出する
　　*/
	D3DXVECTOR3 ReflectionVertex(HitRectPoint type_, D3DXVECTOR3 r_pos_, float width_, float height_, float rad_);

	/**
 　　* @brief  初期位置移動関数
 　　* @detail ステージ床から落ちた場合プレイヤーを初期位置まで戻す処理行う
 　　*/
	void ResetPos();

	/**
 　　* @brief  プレイヤー操作可能判定関数
 　　* @detail 開始演出が終わってから操作できるようにSetterを用意
 　　*/
	void SetIsMovePlayer(bool move_) { player_info.m_is_movement = move_; }

	/**
 　　* @brief  プレイヤーのスピードSetter
 　　* @detail プレイヤーの移動スピードをUIの方でSetするよう
 　　*/
	void SetAddSpeed(float speed_) { player_info.m_setspeed = speed_; }

	/**
　　* @brief  オブジェクト情報Getter
	* @param (copy_info_) 保存用オブジェクト構造体
	* @details 引数にオブジェクトの情報を渡す
　　*/
	void GetPlayerInfo(PlayerInfo& copy_info_) { copy_info_ = player_info; }

private:
	struct PlayerExternalInfo
	{
		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;

		float m_radius;     //!半径
		float speed;        //!移動スピード
		float m;            //!質量
		float fa;           //!動摩擦係数
		int score_counter;  //!加算するスコア数

	};

	PlayerExternalInfo m_player_externalinfo;

	Camera* mp_camera;         //!カメラ保存用
	BlockController* mp_block; //!ブロック管理保存用
	Floor* mp_floor;			  //!ステージ床保存用
	DebufController* mp_debuf; //!デバフ床保存用
	Goal* mp_goal;			  //!ゴール保存用

	PlayerUpdateStep m_update_step; //!更新ステップ

};


#endif