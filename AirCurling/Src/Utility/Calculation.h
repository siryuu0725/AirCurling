﻿#ifndef CALCULATION_H
#define CALCULATION_H

#include <d3d9.h>
#include <d3dx9.h>

#include <vector>
#include <string>

/**
*@class  計算機クラス
*/

class Calculation
{
public:
	Calculation() {}
	~Calculation() {}

	/**
 　　* @brief  ベクトルの距離算出関数
     * @param (target_pos_x_)  対象のベクトルのX座標
     * @param (target_pos_y_)  対象のベクトルのY座標
	 * @return ベクトルの長さを出す
 　　*/
	static float Length(float target_pos_x_, float target_pos_y_);

	/**
 　　* @brief  ベクトル回転関数
	 * @param (target_pos_)  回転させるベクトル
	 * @param (target2_pos_)  回転させる中心点(軸)
	 * @param (radian_)  回転角度
	 * @return 引数1のから引数2までのベクトルを引数3度分回転させる
 　　*/
	static D3DXVECTOR3 Rote(D3DXVECTOR3 target_pos_, D3DXVECTOR3 target2_pos_, float radian_);

	/**
 　　* @brief  ワールド座標計算関数
	 * @param (pos_) オブジェクトの座標
	 * @param (scale_) オブジェクトのサイズ
	 * @param (angle_) オブジェクトの回転角度
	 * @return 対象のワールド座標を計算する
 　　*/
	static D3DXMATRIX Matrix(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_);

	/**
 　　* @brief なす角計算関数
	 * @param (direction_) 対象1のベクトル
	 * @param (vec_) 対象2のベクトル
	 * @return 引数1と引数2に指定したベクトルのなす角を求める
 　　*/
	static float EggplantAngle(D3DXVECTOR3 direction_, D3DXVECTOR3 vec_);
};





#endif
