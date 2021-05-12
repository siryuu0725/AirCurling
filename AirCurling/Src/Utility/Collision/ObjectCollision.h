/**
 * @file ObjectCollision.h
 * @brief オブジェクト同士の当たり判定を管理する(第三者)
 * @details 中身：当たり判定クラス
**/
#ifndef OBJECTCOLLISION_H_
#define OBJECTCOLLISION_H_
#include "Collision.h"
#include "../Vec.h"
#include "../Calculation.h"
#include "../../Object/ObjectBase.h"

constexpr unsigned __int8 GoalTypeNum = 3;

/**
* オブジェクト当たり判定管理
*/

class ObjectCollision
{
public:
	ObjectCollision();
	~ObjectCollision() {}

	static ObjectCollision* Instance();

	/**
 　　* @brief 矩形ブロック当たり判定関数
 　　* @details ステージにある矩形ブロックとプレイヤーとの当たり判定を行う
 　　*/
	bool HitRectBlock();

	/**
 　　* @brief 円形ブロック当たり判定関数
 　　* @details ステージにある円形ブロックとプレイヤーとの当たり判定を行う
 　　*/
	bool HitCircleBlock();

	/**
 　　* @brief リセット床当たり判定関数
 　　* @details ステージにあるリセット床とプレイヤーとの当たり判定を行う
 　　*/
	bool HitResetFloor();

	/**
 　　* @brief スピード減衰床当たり判定関数
 　　* @details ステージにあるスピード減衰床とプレイヤーとの当たり判定を行う
 　　*/
	bool HitStopFloor();

	/**
 　　* @brief ゴール当たり判定関数
 　　* @details ゴールとプレイヤーとの当たり判定を行う
 　　*/
	bool HitGoal();

#pragma region オブジェクト情報Setter

	/**
　　* @brief  矩形ブロック情報Set関数
	* @param[in] obj_info_ 矩形ブロックオリジナル情報構造体
　　* @details 当たり判定用クラスの矩形ブロック情報構造体にオリジナルの情報をコピーする
　　*/
	const void SetRectBlockInfo(ObjectBase::ObjectInfo& obj_info_) { m_rectblock_copy.push_back(obj_info_); }

	/**
　　* @brief  円形ブロック情報Set関数
	* @param[in] obj_info_ 円形ブロックオリジナル情報構造体
　　* @details 当たり判定用クラスの円形ブロック情報構造体にオリジナルの情報をコピーする
　　*/
	const void SetCircleBlockInfo(ObjectBase::ObjectInfo& obj_info_) { m_circleblock_copy.push_back(obj_info_); }

	/**
　　* @brief  リセット床情報Set関数
	* @param[in] obj_info_ リセット床オリジナル情報構造体
　　* @details 当たり判定用クラスのリセット床情報構造体にオリジナルの情報をコピーする
　　*/
	const void SetResetFloorInfo(ObjectBase::ObjectInfo& obj_info_) { m_resetfloor_copy.push_back(obj_info_); }

	/**
　　* @brief  スピード減衰床情報Set関数
	* @param[in] obj_info_ スピード減衰床オリジナル情報構造体
　　* @details 当たり判定用クラスのスピード減衰床情報構造体にオリジナルの情報をコピーする
　　*/
	const void SetStopFloorInfo(ObjectBase::ObjectInfo& obj_info_) { m_stopfloor_copy.push_back(obj_info_); }

	/**
　　* @brief  プレイヤー情報Set関数
	* @param[in] obj_info_ プレイヤーオリジナル情報構造体
　　* @details 当たり判定用クラスのプレイヤー情報構造体にオリジナルの情報をコピーする
　　*/
	const void SetPlayerInfo(ObjectBase::ObjectInfo& obj_info_) { m_player_copy = obj_info_; }

	/**
　　* @brief  ゴール情報Set関数
	* @param[in] obj_info_ ゴールオリジナル情報構造体
　　* @details 当たり判定用クラスのゴール情報構造体にオリジナルの情報をコピーする
　　*/
	const void SetGoalInfo(ObjectBase::ObjectInfo& obj_info_) { m_goal_copy = obj_info_; }

#pragma endregion 

	/**
　　* @brief 衝突矩形IDGetter関数
　　* @details 衝突した矩形ブロックのIDを返す
　　*/
	const __int8 GetRectBlockID() { return m_hit_rectblock_id; }

	/**
　　* @brief 衝突円形IDGetter関数
　　* @details 衝突した円形ブロックのIDを返す
　　*/
	const __int8 GetCircleBlockID() { return m_hit_circleblock_id; }
	
	/**
　　* @brief 衝突ゴールタイプGetter関数
　　* @details ゴール時の色(種類)を返す
　　*/
	const __int8 GetGoalType() { return m_goal_type; }

	/**
　　* @brief 矩形ブロック衝突箇所Getter関数
　　* @details 当衝突時に矩形ブロックのどの箇所に衝突したかを返す
　　*/
	const HitRectPoint GetHitRectPoint() { return m_rectpoint; }

	/**
　　* @brief 各オブジェクト情報リセット関数
　　* @details 前回と違うステージを選んだ場合前のオブジェクト情報が残っているため使用する
　　*/
	void ResetObjectInfo();

	/**
	*	@brief Instance解放関数(Debug用)
	*	@details 手動でインスタンスを解放する
	*/
	void ReleaseInstance();

private:
	static ObjectCollision* mp_instance;
	 
	ObjectBase::ObjectInfo m_player_copy;                    //!プレイヤー情報保存用
	ObjectBase::ObjectInfo m_goal_copy;                      //!ゴール情報保存用
	std::vector<ObjectBase::ObjectInfo> m_rectblock_copy;    //!矩形ブロック情報保存用
	std::vector<ObjectBase::ObjectInfo> m_circleblock_copy;  //!円形ブロック情報保存用
	std::vector<ObjectBase::ObjectInfo> m_resetfloor_copy;   //!リセット床情報保存用
	std::vector<ObjectBase::ObjectInfo> m_stopfloor_copy;    //!スピード減衰床情報保存用

	__int8 m_hit_circleblock_id;  //!衝突した円形ブロックのID保存用
	__int8 m_hit_rectblock_id;	  //!衝突した矩形ブロックのID保存用
	__int8 m_goal_type;		  //!ゴール時のゴールタイプ(色)保存用

	float m_goal_radius[GoalTypeNum];  //!各ゴールの半径保存用

	HitRectPoint m_rectpoint; //!矩形の衝突した箇所保存用
};



#endif