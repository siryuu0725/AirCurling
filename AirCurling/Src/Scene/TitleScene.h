#ifndef TITLESCENE_H_
#define TITLESCENE_H_
#include"SceneBase.h"
#include "../UI/TitleUI.h"

/**
*@class  タイトルシーンクラス
*/

class TitleScene :public SceneBase
{
public:
	TitleScene() {}
	~TitleScene() {}


	/**
	 * @brief  描画情報送信まとめ関数
	 * @detail UIの描画情報送信処理を行う
	 */
	virtual void Draw()override;

#pragma region 各ステップ処理
	/**
 　　* @brief  初期化ステップ関数
 　　* @detail UI、サウンドの初期化を行う
 　　*/
	virtual void InitStep()override;

	/**
 　　* @brief  スレッド更新ステップ関数
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
 　　* @detail 次のシーン移行前のUIやサウンドの解放を行う
 　　*/
	virtual void EndStep()override;

#pragma endregion


	/**
     * @brief  インスタンス返還関数
     * @detail 管理クラスのポインタ配列に返す
     */
	static SceneBase* InstanceTitleScene();

private:
	TitleUI* m_ui; //!タイトル用UI
};

#endif