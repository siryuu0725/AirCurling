#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "SceneBase.h"
#include "../System/FBX.h"
#include "../System/Sound/SoundController.h"
#include "../Scene/SceneController.h"

#include "../Object/Block/BlockController.h"
#include "../Object/Camera.h"
#include "../Object/Player.h"
#include "../Object/Sky.h"
#include "../Object/Floor/Floor.h"
#include "../Object/Floor/GoalFloor.h"

#include "../UI/GameUI.h"
#include "../UI/LoadUI.h"
#include "../UI/PoseUI.h"


#include <Windows.h>
#include "../Object/PlayerDirection.h"

/**
*@clss  ゲームシーンクラス
*/

class GameScene :public SceneBase
{
public:
	GameScene();
	~GameScene() {}

	/**
	 * @brief  描画情報送信まとめ関数
	 * @detail 各オブジェクト、エフェクトなどの描画情報送信処理を行う
	 */
	virtual void SetUpBuffer()override;

#pragma region 各ステップ処理

	/**
 　　* @brief  初期化ステップ関数
 　　* @detail 各オブジェクト、エフェクトやサウンドの初期化を行う
 　　*/
	virtual void InitStep()override;

	/**
 　　* @brief  ロード画面更新ステップ関数
 　　* @detail 各Fbxオブジェクトやテクスチャ読み込み時のロード画面更新ステップ、
 　　*/
	virtual void UpdateThreadStep()override;

	/**
 　　* @brief  更新ステップ関数
 　　* @detail 本編の更新処理を行う
 　　*/
	virtual void MainStep()override;

	/**
 　　* @brief  終了ステップ関数
 　　* @detail 次のシーン移行前のオブジェクトやUI、サウンドの解放を行う
 　　*/
	virtual void EndStep()override;

#pragma endregion

#pragma region 各オブジェクトまとめ関数
	/**
 　　* @brief  オブジェクト初期化関数
 　　* @detail 各オブジェクトの初期化を行う
 　　*/
	void ObjectInit();

	/**
 　　* @brief  オブジェクト更新関数
 　　* @detail  各オブジェクトの更新処理を行う
 　　*/
	void ObjectUpdate();

	/**
 　　* @brief  オブジェクト描画情報送信関数
 　　* @detail 各オブジェクトの描画情報送信を行う
 　　*/
	void ObjectSetUpBuffer();

	/**
 　　* @brief  オブジェクト解放関数
 　　* @detail 各オブジェクトの解放を行う
 　　*/
	void ObjectDelete();

	/**
　　* @brief  UI解放関数
　　* @detail 各ゲームUIの解放を行う
　　*/
	void UIDelete();

#pragma endregion

	/**
     * @brief  インスタンス返還関数
     * @detail 管理クラスのポインタ配列に返す
     */
	static SceneBase* InstanceGameScene();
private:
	Camera* m_camera;                    //!カメラオブジェクト
	BlockController* m_block_controller; //!ブロック管理オブジェクト
	Player* m_player;                    //!プレイヤーオブジェクト
	PlayerDirection* m_player_direction; //!プレイヤーの方向オブジェクト
	SkyDome* m_sky_dome;                 //!背景オブジェクト
	SkyFloor* m_sky_floor;               //!背景床オブジェクト
	Floor* m_floor;                      //!ステージ床オブジェクト
	DebufController* m_debuf;            //!リセットデバフオブジェクト
	Goal* m_goal;                        //!ゴールオブジェクト

	GameUI* m_gmae_ui; //!ゲーム用UI
	LoadUI* m_load_ui; //!ロード画面用UI
	PoseUI* m_pose_ui; //!ヘルプ画面用UI


	HANDLE thread_h;
	DWORD thread_id;

	static DWORD WINAPI LoadResorse(LPVOID lpparm_);

	bool m_pose; //!ポーズ画面かどうか
};

#endif