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

	struct ObjectInfoCopy
	{
		float pos_x;   //!座標
		float pos_y;   //!座標
		float pos_z;   //!座標

		float scale_x; //!サイズ
		float scale_y; //!サイズ
		float scale_z; //!サイズ

	}goal_info_copy;
};
#endif