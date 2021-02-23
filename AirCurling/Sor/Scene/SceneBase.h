#ifndef BASESCENE_H_
#define BASESCENE_H_

//!シーンステップ
enum class SceneStep
{
	InitStep,	 //!初期化ステップ
	ThreadStep,	 //!ロードステップ
	MainStep,	 //!メインステップ
	EndStep,	 //!エンドステップ
};

/**
*@clss  シーンベースクラス
*/
class SceneBase
{
public:
	SceneBase() {}
	~SceneBase() {}

	/**
　　* @brief  初期化ステップ関数
　　* @detail 各シーン内の初期化を行う
　　*/
	virtual void InitStep() {};

	/**
 　　* @brief  スレッド更新ステップ関数
 　　* @detail 各Fbxオブジェクトやテクスチャ読み込み時のロード画面更新ステップ、
 　　*/
	virtual void UpdateThreadStep() {};

	/**
　　* @brief  更新ステップ関数
　　* @detail 本編の更新処理を行う
　　*/
	virtual void MainStep() {};

	/**
　　* @brief  終了ステップ関数
　　* @detail 次のシーン移行前の解放処理を行う
　　*/
	virtual void EndStep() {};

	/**
　　* @brief  ステップ処理関数
　　* @detail 各ステップ処理を管理する
　　*/
	virtual void Update();

	/**
	 * @brief  描画情報送信まとめ関数
	 * @detail UIの描画情報送信処理を行う
	 */
	virtual void Draw() {};

	//!シーン移行フラグGetter
	const bool GetChangeSceneFlg()const {return m_change_scene; }

	//!現在のシーンステップGetter
	const SceneStep NowStep()const { return cur_step_step; }

protected:
	SceneStep cur_step_step;  //!現在のシーンステップ
	bool m_change_scene;      //!シーン移行フラグ
};


#endif