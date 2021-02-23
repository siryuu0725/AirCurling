#ifndef GOAL_H_
#define GOAL_H_

#include "../ObjectBase.h"

/**
*@clss   ゴール床クラス
*/

class Goal :public ObjectBase
{
public:
	Goal() {}
	~Goal() {}


	/**
	 * @brief  初期化関数
	 * @param (stage_id_) 選択ステージ名(例"Stage1")
	 * @detail オブジェクト情報初期化
	 */
	void Init(std::string stage_id_);

	/**
	 * @brief  描画情報送信関数
	 */
	void SetUpBuffer();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_goal_info; }

private:
	ObjectInfo m_goal_info;//!ステージ床情報

	//!外部データ保存用構造体
	struct GoalExternalInfo
	{
		//!座標
		float pos[3];
		//!サイズ
		float scale[3];

	}m_goal_info_copy;
};
#endif