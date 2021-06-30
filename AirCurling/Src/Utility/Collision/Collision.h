/**
 * @file Collision.h
 * @brief 当たり判定を行う
 * @details 中身：当たり判定クラス
**/
#ifndef COLLISION_H_
#define COLLISION_H_
#include "../Calculation.h"

enum class HitRectPoint
{
	TopOrUnder,
	LeftOrRight,
	LeftTop,
	RightTop,
	LeftUnder,
	RightUnder,
	PointMax
};

/**
* 当たり判定クラス
*/

class Collision
{
public:
	Collision() {}
	~Collision() {}

	/**
　   * @brief  矩形と円の当たり判定
	 * @param[in] type_ 当たり判定を取る箇所(例:矩形の左右面)
	 * @param[in] r_pos 矩形の座標
	 * @param[in] c_pos 円の座標
	 * @param[in] width_ 矩形の横幅
	 * @param[in] height_ 矩形の縦幅
	 * @param[in] radius_ 円の半径
	 * @param[in] rad_ 矩形の回転角度
　   */
	static bool RectAndCircle(__int8 hit_rect_type_, D3DXVECTOR3 rect_pos_, D3DXVECTOR3 circle_pos_,
		float width_, float height_, float radius_, float rect_rote_rad_);

	/**
　   * @brief  円と円の当たり判定
	 * @param[in] c1_pos 円1の座標
	 * @param[in] c2_pos 円2の座標
	 * @param[in] radius1_ 円1の半径
	 * @param[in] radius2_ 円2の半径
　   */
	static bool CircleAndCircle(D3DXVECTOR3 circle_pos_, D3DXVECTOR3 circle2_pos_, float radius1_, float radius2_);

	/**
　   * @brief  矩形と点の当たり判定
	 * @param[in] r_pos 矩形の座標
	 * @param[in] p_pos 点の座標
	 * @param[in] width_ 矩形の横幅
	 * @param[in] height_ 矩形の縦幅
	 * @details タイトルのUIの当たり判定で使う
　   */
	static bool RectAndPoint(D3DXVECTOR2 rect_pos_, D3DXVECTOR2 point_pos_, float width_, float height_);

};



#endif