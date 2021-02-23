#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include"SceneBase.h"
#include<vector>
#include <string>

//!シーンID
enum class SceneId
{
	Title,  //!タイトル
	Game,	//!ゲーム
	Result,	//!リザルト
	Max		//!シーン数
};

/**
*@clss  シーン管理クラス
*/
class SceneController
{
private:
	SceneController() {};
	~SceneController();
public:

	/**
　　* @brief  インスタンス化関数
　　* @detail 初回のみインスタンス化し、それ以外は実態を呼ぶ
　　*/
	static SceneController* Instance();

	/**
	 * @brief  初期化関数
	 * @detail 各シーン初期化関数
	 */
	void Init();

	/**
     * @brief  更新関数
     * @detail 更新処理まとめ関数
     */
	void Update();

	/**
     * @brief   描画情報送信関数
     * @detail  Fbx管理クラスにオブジェクト情報を送る
     */
	void SetUpBuffer();

	/**
	 * @brief   描画関数
	 */
	void SceneDraw();


	/**
	 * @brief   現在シーンSetter
	 */
	void SetSceneId(SceneId sceneid_);

	/**
     * @brief  シーン切り替え判定関数
     * @detail 各シーンで切り替え判定を行う
     */
	void ChangeScene();

	/**
	 * @brief  選択ステージSetter
	 * @detail タイトルで選んだステージを保存
	 */
	void SetStageID(std::string stage_);

	/**
	 * @brief  選択ステージGettr
	 * @detail タイトルで選んだステージを取得
	 */
	std::string GetStageID() { return m_stage; }

	/**
	 * @brief  各ゲーム管理クラスアドレス配列
	 * @detail 配列に指定したゲームを入れるとそのゲームの管理クラスのnewが返ってくる
	 */
	static SceneBase* (*s_controller_array[static_cast<int>(SceneId::Max)])();

private:
	static SceneController* p_instance;
	SceneBase* m_scene;

	SceneId m_cur_scene_id;

	std::string m_stage;
};

#endif // !SCENEMANAGER_H_