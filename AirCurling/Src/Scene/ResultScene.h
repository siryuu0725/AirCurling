﻿/**
 * @file GameScene.h
 * @brief リザルトシーン(エンドシーン)を管理する
 * @details 中身：リザルトシーンクラス
**/

#ifndef RESULTSCENE_H_
#define RESULTSCENE_H_
#include"SceneBase.h"
#include "../System/FBX.h"
#include "../System/Sound/SoundController.h"
#include "../Scene/SceneController.h"

#include "../UI/ResultUI/ResultUI.h"

constexpr __int16 ResultBGMVolume = -300;   //!ゲームシーンのBGM音量

/**
* リザルトシーンクラス
*/
class ResultScene :public SceneBase
{
public:
	ResultScene();
	~ResultScene() {}

#pragma region 各ステップ処理
	/**
 　　* @brief  初期化ステップ関数
 　　* @details UI、サウンドの初期化を行う
 　　*/
	virtual void InitStep()override;

	/**
 　　* @brief  スレッド更新ステップ関数
 　　* @details 各Fbxオブジェクトやテクスチャ読み込み時のロード画面更新ステップ、
 　　*/
	virtual void UpdateThreadStep()override;

	/**
 　　* @brief  更新ステップ関数
 　　* @details 本編の更新処理を行う
 　　*/
	virtual void MainStep()override;

	/**
 　　* @brief  終了ステップ関数
 　　* @details 次のシーン移行前のUIやサウンドの解放を行う
 　　*/
	virtual void EndStep()override;

#pragma endregion

	/**
	 * @brief  描画情報送信まとめ関数
	 * @details UIの描画情報送信処理を行う
	 */
	virtual void Draw()override;

	/**
	 * @brief  インスタンス返還関数
	 * @details 管理クラスのポインタ配列に返す
	 */
	static SceneBase* Instance();

private:
	ResultUI* mp_ui; //!リザルト画面用UI
};

#endif