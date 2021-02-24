#ifndef GOAL_H_
#define GOAL_H_

#include "../ObjectBase.h"

/**
*@class   ゴール床クラス
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
	void Init(std::string stage_str_);

	/**
	 * @brief  外部データ読み込み関数
	 * @detail 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadGoalExternalInfo(std::string stage_str_);

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

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
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;

	}m_goal_externalinfo;
};
#endif