/**
 * @file Collision.h
 * @brief 当たり判定を行う
 * @details 中身：当たり判定クラス
**/
#ifndef COLLISION_H_
#define COLLISION_H_
#include "Shape.h"
#include "../Vec.h"
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


#pragma region 矩形と円
	/**
　   * @brief  矩形の上下と点の当たり判定
	 * @param (r_pos) 矩形の座標
	 * @param (c_pos) 円の座標
	 * @param (width_) 矩形の横幅
	 * @param (height_) 矩形の縦幅
	 * @param (radius_) 円の半径
	 * @param (rad_) 矩形の回転角度
　   */
	//static bool RectTopToCircle(D3DXVECTOR3 r_pos, D3DXVECTOR3 c_pos, float width_, float height_,float radius_, float rad_);

	/**
　   * @brief  矩形の左右と円の当たり判定
	 * @param (r_pos) 矩形の座標
	 * @param (c_pos) 円の座標
	 * @param (width_) 矩形の横幅
	 * @param (height_) 矩形の縦幅
	 * @param (radius_) 円の半径
	 * @param (rad_) 矩形の回転角度
　   */
	//static bool RectLeftToCircle(D3DXVECTOR3 r_pos, D3DXVECTOR3 c_pos, float width_, float height_, float radius_, float rad_);

	/**
　   * @brief  矩形の頂点と円の当たり判定
	 * @param[in] r_pos 矩形の座標
	 * @param[in] c_pos 円の座標
	 * @param[in] width_ 矩形の横幅
	 * @param[in] height_ 矩形の縦幅
	 * @param[in] radius_ 円の半径
	 * @param[in] rad_ 矩形の回転角度
　   */
	static bool RectVertexToCircle(__int8 type_,D3DXVECTOR3 r_pos, D3DXVECTOR3 c_pos, float width_, float height_, float radius_, float rad_);

#pragma endregion

	/**
　   * @brief  円と円の当たり判定
	 * @param[in] c1_pos 円1の座標
	 * @param[in] c2_pos 円2の座標
	 * @param[in] radius1_ 円1の半径
	 * @param[in] radius2_ 円2の半径
　   */
	static bool CircleToCircle(D3DXVECTOR3 c1_pos, D3DXVECTOR3 c2_pos, float radius1_, float radius2_);

	/**
　   * @brief  矩形と点の当たり判定
	 * @param[in] r_pos 矩形の座標
	 * @param[in] p_pos 点の座標
	 * @param[in] width_ 矩形の横幅
	 * @param[in] height_ 矩形の縦幅
	 * @details タイトルのUIの当たり判定で使う
　   */
	static bool RectToPoint(D3DXVECTOR2 r_pos, D3DXVECTOR2 p_pos, float width_, float height_);

};



#endif