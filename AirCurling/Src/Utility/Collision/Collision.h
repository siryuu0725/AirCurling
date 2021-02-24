#ifndef SHOTUI_H_
#define SHOTUI_H_
#include "Shape.h"
#include "../Vec.h"
#include "../Calculation.h"

/**
*@class  当たり判定クラス
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
	static bool RectTopToCircle(D3DXVECTOR3 r_pos, D3DXVECTOR3 c_pos, float width_, float height_,float radius_, float rad_);

	/**
　   * @brief  矩形の左右と円の当たり判定
	 * @param (r_pos) 矩形の座標
	 * @param (c_pos) 円の座標
	 * @param (width_) 矩形の横幅
	 * @param (height_) 矩形の縦幅
	 * @param (radius_) 円の半径
	 * @param (rad_) 矩形の回転角度
　   */
	static bool RectLeftToCircle(D3DXVECTOR3 r_pos, D3DXVECTOR3 c_pos, float width_, float height_, float radius_, float rad_);

	/**
　   * @brief  矩形の頂点と円の当たり判定
	 * @param (r_pos) 矩形の座標
	 * @param (c_pos) 円の座標
	 * @param (width_) 矩形の横幅
	 * @param (height_) 矩形の縦幅
	 * @param (radius_) 円の半径
	 * @param (rad_) 矩形の回転角度
　   */
	static bool RectVertexToCircle(std::string type_,D3DXVECTOR3 r_pos, D3DXVECTOR3 c_pos, float width_, float height_, float radius_, float rad_);

#pragma endregion

	/**
　   * @brief  円と円の当たり判定
	 * @param (c1_pos) 円1の座標
	 * @param (c2_pos) 円2の座標
	 * @param (radius1_) 円1の半径
	 * @param (radius2_) 円2の半径
　   */
	static bool CircleToCircle(D3DXVECTOR3 c1_pos, D3DXVECTOR3 c2_pos, float radius1_, float radius2_);

	/**
　   * @brief  矩形と点の当たり判定
	 * @param (r_pos) 矩形の座標
	 * @param (p_pos) 点の座標
	 * @param (width_) 矩形の横幅
	 * @param (height_) 矩形の縦幅
	 * @detail タイトルのUIの当たり判定で使う
　   */
	static bool RectToPoint(D3DXVECTOR2 r_pos, D3DXVECTOR2 p_pos, float width_, float height_);

};



#endif