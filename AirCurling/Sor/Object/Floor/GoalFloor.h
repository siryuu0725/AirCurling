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
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_goal_info; }

private:
	ObjectInfo m_goal_info;//!ステージ床情報

	//!外部データ保存用構造体
	struct ObjectInfoCopy
	{
		//!座標
		float pos_x;  
		float pos_y;   
		float pos_z;   

		//!サイズ
		float scale_x; 
		float scale_y; 
		float scale_z; 

	}m_goal_info_copy;
};
#endif