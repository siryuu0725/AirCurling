#include "Collision.h"


#include <math.h>

//!矩形の上下と円の当たり判定
//bool Collision::RectTopToCircle(D3DXVECTOR3 r_pos, D3DXVECTOR3 c_pos, float width_, float height_, float radius_,float rad_)
//{
//	D3DXVECTOR3 rote_pos;  //!矩形の回転角度分円をずらした時の座標
//
//	//!衝突時、対象の回転角度分座標をずらす
//	rote_pos = Calculation::Rote(c_pos, r_pos, rad_);
//
//	//!矩形の回転前の座標で判定を行う
//	if (rote_pos.x > r_pos.x - (width_ / 2) &&
//		rote_pos.x < r_pos.x + (width_ / 2) &&
//		rote_pos.z + radius_ > r_pos.z - (height_ / 2) &&
//		rote_pos.z - radius_ < r_pos.z + (height_ / 2))
//	{
//		return true;
//	}
//
//	return false;
//}

//!矩形の左右と円の当たり判定
//bool Collision::RectLeftToCircle(D3DXVECTOR3 r_pos, D3DXVECTOR3 c_pos, float width_, float height_, float radius_, float rad_)
//{
//	D3DXVECTOR3 rote_pos; //!矩形の回転角度分円をずらした時の座標
//
//	//!衝突時、対象の回転角度分座標をずらす
//	rote_pos = Calculation::Rote(c_pos, r_pos, rad_);
//
//	//!矩形の回転前の座標で判定を行う
//	if (rote_pos.x + radius_ > r_pos.x - (width_ / 2) &&
//		rote_pos.x - radius_ < r_pos.x + (width_ / 2) &&
//		rote_pos.z > r_pos.z - (height_ / 2) &&
//		rote_pos.z < r_pos.z + (height_ / 2))
//	{
//		return true;
//
//	}
//
//	return false;
//}

//!矩形の頂点と円の当たり判定
bool Collision::RectVertexToCircle(__int8 type_, D3DXVECTOR3 r_pos, D3DXVECTOR3 c_pos, float width_, float height_, float radius_, float rad_)
{
	D3DXVECTOR3 rote_pos; //!矩形の回転角度分円をずらした時の座標
	D3DXVECTOR3 ver_pos;  //!衝突時の頂点座標保存用

	D3DXVECTOR3 vec; //!矩形の頂点と円とのベクトル

	//!衝突時、対象の回転角度分座標をずらす
	rote_pos = Calculation::Rote(c_pos, r_pos, rad_);

	switch ((HitRectPoint)type_)
	{
	case HitRectPoint::TopOrUnder: //上下
		//矩形の回転前の座標で判定を行う
		if (rote_pos.x > r_pos.x - (width_ / 2) &&
			rote_pos.x < r_pos.x + (width_ / 2) &&
			rote_pos.z + radius_ > r_pos.z - (height_ / 2) &&
			rote_pos.z - radius_ < r_pos.z + (height_ / 2))
		{
			return true;
		}
		break;
	case HitRectPoint::LeftOrRight: //左右
		//矩形の回転前の座標で判定を行う
		if (rote_pos.x + radius_ > r_pos.x - (width_ / 2) &&
			rote_pos.x - radius_ < r_pos.x + (width_ / 2) &&
			rote_pos.z > r_pos.z - (height_ / 2) &&
			rote_pos.z < r_pos.z + (height_ / 2))
		{
			return true;

		}
		break;
	case HitRectPoint::LeftTop: //左上頂点
		ver_pos.x = r_pos.x - (width_ / 2);
		ver_pos.z = r_pos.z + (height_ / 2);
		break;
	case HitRectPoint::RightTop: //左下頂点
		ver_pos.x = r_pos.x - (width_ / 2);
		ver_pos.z = r_pos.z - (height_ / 2);
		break;
	case HitRectPoint::LeftUnder: //左下頂点
		ver_pos.x = r_pos.x + (width_ / 2);
		ver_pos.z = r_pos.z + (height_ / 2);
		break;
	case HitRectPoint::RightUnder: //右下頂点
		ver_pos.x = r_pos.x + (width_ / 2);
		ver_pos.z = r_pos.z - (height_ / 2);
		break;
	default:
		break;
	}

	//!ベクトル算出
	vec.x = ver_pos.x - rote_pos.x;
	vec.z = ver_pos.z - rote_pos.z;

	//!円の半径と矩形の幅の距離
	float c = sqrtf(vec.x * vec.x + vec.z * vec.z);

	if (c <= radius_)
	{
		return true;
	}
	
	return false;
}

//!円と円の当たり判定
bool Collision::CircleToCircle(D3DXVECTOR3 c1_pos, D3DXVECTOR3 c2_pos, float radius1_, float radius2_)
{
	float length;        //!対象の円との距離
	float value_radius;  //!対象との半径の合計
	D3DXVECTOR3 vec;     //!対象とのベクトル

	//!対象とのベクトル算出
	vec.x = c1_pos.x - c2_pos.x;
	vec.z = c1_pos.z - c2_pos.z;

	//!対象の円との距離算出
	length = sqrtf(vec.x * vec.x + vec.z * vec.z);

	//!対象との半径の合計算出
	value_radius = radius1_ + radius2_;

	if (length < value_radius)
	{
		return true;
	}

	return false;
}

//!矩形と点の当たり判定
bool Collision::RectToPoint(D3DXVECTOR2 r_pos, D3DXVECTOR2 p_pos, float width_, float height_)
{
	if (p_pos.x >= r_pos.x
		&& p_pos.x <= r_pos.x + width_
		&& p_pos.y >= r_pos.y
		&& p_pos.y <= r_pos.y + height_)
	{
		return true;
	}
	else
	{
		return false;
	}
}