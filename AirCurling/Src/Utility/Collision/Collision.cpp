#include "Collision.h"
#include <math.h>

//矩形の頂点と円の当たり判定
bool Collision::RectAndCircle(__int8 type_, D3DXVECTOR3 r_pos_, D3DXVECTOR3 c_pos_, float width_, float height_, float radius_, float rad_)
{
	D3DXVECTOR3 rote_pos(0.0f, 0.0f, 0.0f); //矩形の回転角度分円をずらした時の座標
	D3DXVECTOR3 ver_pos(0.0f, 0.0f, 0.0f);  //衝突時の頂点座標保存用

	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f); //矩形の頂点と円とのベクトル

	//衝突時、対象の回転角度分座標をずらす
	rote_pos = Calculation::Rote(c_pos_, r_pos_, rad_);

	switch ((HitRectPoint)type_)
	{
	case HitRectPoint::TopOrUnder: //上下
		//矩形の回転前の座標で判定を行う
		if (rote_pos.x > r_pos_.x - (width_ / 2) &&
			rote_pos.x < r_pos_.x + (width_ / 2) &&
			rote_pos.z + radius_ > r_pos_.z - (height_ / 2) &&
			rote_pos.z - radius_ < r_pos_.z + (height_ / 2))
		{
			return true;
		}
		else
			return false;
		break;
	case HitRectPoint::LeftOrRight: //左右
		//矩形の回転前の座標で判定を行う
		if (rote_pos.x + radius_ > r_pos_.x - (width_ / 2) &&
			rote_pos.x - radius_ < r_pos_.x + (width_ / 2) &&
			rote_pos.z > r_pos_.z - (height_ / 2) &&
			rote_pos.z < r_pos_.z + (height_ / 2))
		{
			return true;
		}
		else
			return false;
		break;
	case HitRectPoint::LeftTop: //左上頂点
		ver_pos.x = r_pos_.x - (width_ / 2);
		ver_pos.z = r_pos_.z + (height_ / 2);
		break;
	case HitRectPoint::RightTop: //左下頂点
		ver_pos.x = r_pos_.x - (width_ / 2);
		ver_pos.z = r_pos_.z - (height_ / 2);
		break;
	case HitRectPoint::LeftUnder: //左下頂点
		ver_pos.x = r_pos_.x + (width_ / 2);
		ver_pos.z = r_pos_.z + (height_ / 2);
		break;
	case HitRectPoint::RightUnder: //右下頂点
		ver_pos.x = r_pos_.x + (width_ / 2);
		ver_pos.z = r_pos_.z - (height_ / 2);
		break;
	default:
		break;
	}

	//ベクトル算出
	vec.x = ver_pos.x - rote_pos.x;
	vec.z = ver_pos.z - rote_pos.z;

	//円の半径と矩形の幅の距離
	float c = sqrtf(vec.x * vec.x + vec.z * vec.z);

	if (c <= radius_)
	{
		return true;
	}
	
	return false;
}

//円と円の当たり判定
bool Collision::CircleAndCircle(D3DXVECTOR3 c1_pos_, D3DXVECTOR3 c2_pos_, float radius1_, float radius2_)
{
	float length = 0.0f;        //対象の円との距離
	float value_radius = 0.0f;  //対象との半径の合計
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);     //対象とのベクトル

	//対象とのベクトル算出
	vec.x = c1_pos_.x - c2_pos_.x;
	vec.z = c1_pos_.z - c2_pos_.z;

	//対象の円との距離算出
	length = sqrtf(vec.x * vec.x + vec.z * vec.z);

	//対象との半径の合計算出
	value_radius = radius1_ + radius2_;

	if (length < value_radius)
	{
		return true;
	}

	return false;
}

//矩形と点の当たり判定
bool Collision::RectAndPoint(D3DXVECTOR2 r_pos_, D3DXVECTOR2 p_pos_, float width_, float height_)
{
	if (p_pos_.x >= r_pos_.x
	 && p_pos_.x <= r_pos_.x + width_
	 && p_pos_.y >= r_pos_.y
	 && p_pos_.y <= r_pos_.y + height_)
	{
		return true;
	}
	else
	{
		return false;
	}
}