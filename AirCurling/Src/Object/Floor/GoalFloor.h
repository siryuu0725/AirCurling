#ifndef GOAL_H_
#define GOAL_H_

#include "../ObjectBase.h"

/**
*@class   ゴール床クラス
*/

class Goal :public ObjectBase
{
private:
	struct GoalInfo :public ObjectInfo
	{
		float m_red_radius;    //!赤色のゴール枠の半径
		float m_yellow_radius; //!黄色のゴール枠の半径
		float m_green_radius;  //!緑色のゴール枠の半径
	};

	//!外部データ保存用構造体
	struct GoalExternalInfo
	{
		GoalExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_red_radius(0.0f),
			m_yellow_radius(0.0f),
			m_green_radius(0.0f)
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;

		float m_red_radius;    //!赤色のゴール枠の半径
		float m_yellow_radius; //!黄色のゴール枠の半径
		float m_green_radius;  //!緑色のゴール枠の半径

	};

	GoalInfo m_goal_info;//!ステージ床情報
	GoalExternalInfo m_goal_externalinfo;

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
	const GoalInfo* GetObjInfo()const { return &m_goal_info; }
};
#endif