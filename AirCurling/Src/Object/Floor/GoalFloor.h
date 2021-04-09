/**
 * @file Goal.h
 * @brief ゴールとなる床オブジェクト
 * @details　中身：ゴール床クラス
**/
#ifndef GOALFLOOR_H_
#define GOALFLOOR_H_

#include "../ObjectBase.h"

constexpr float RedGoalRadius = 0.3f;    //!赤色のゴール枠の半径
constexpr float YellowGoalRadius = 2.0f; //!黄色のゴール枠の半径
constexpr float GreenGoalRadius = 6.0f;  //!緑色のゴール枠の半径

enum class GoalType
{
	Red,
	Yellow,
	Green
};

/**
* ゴール床クラス
*/
class Goal :public ObjectBase
{
public:
	Goal() {}
	~Goal() {}


	/**
	 * @brief  初期化関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details オブジェクト情報初期化
	 */
	virtual void Init(std::string stage_str_)override;

	/**
	 * @brief  外部データ読み込み関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	virtual void LoadExternalInfo(std::string stage_str_)override;

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief   FBXモデル解放関数
	 */
	virtual void ReleaseModel()override;

	/**
　　* @brief  オブジェクト情報Getter
	* @param[out] copy_info_ 保存用オブジェクト構造体
	* @details 引数にオブジェクトの情報を渡す
　　*/
	const void GetGoalInfo(ObjectInfo& copy_info_) { copy_info_ = m_goal_info; }

private:
	//!外部データ保存用構造体
	struct GoalExternalInfo
	{
		GoalExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;
	};

	ObjectInfo m_goal_info;//!ステージ床情報

	GoalExternalInfo m_goal_externalinfo;

};
#endif