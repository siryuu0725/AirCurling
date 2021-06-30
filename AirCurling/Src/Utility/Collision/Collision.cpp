#include "Collision.h"
#include <math.h>

//矩形の頂点と円の当たり判定
bool Collision::RectAndCircle(__int8 hit_rect_type_, D3DXVECTOR3 rect_pos_, D3DXVECTOR3 circle_pos_,
	float width_, float height_, float radius_, float rect_rote_rad_)
{
	D3DXVECTOR3 rot_pos(0.0f, 0.0f, 0.0f); //矩形の回転角度分円をずらした時の座標
	D3DXVECTOR3 ver_pos(0.0f, 0.0f, 0.0f);  //衝突時の頂点座標保存用

	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f); //矩形の頂点と円とのベクトル

	//衝突時、対象の回転角度分座標をずらす
	rot_pos = Calculation::Rotate_Y(circle_pos_, rect_pos_, rect_rote_rad_);

	switch ((HitRectPoint)hit_rect_type_)
	{
	case HitRectPoint::TopOrUnder: //上下
		//矩形の回転前の座標で判定を行う
		if (rot_pos.x > rect_pos_.x - (width_ / 2) &&
			rot_pos.x < rect_pos_.x + (width_ / 2) &&
			rot_pos.z + radius_ > rect_pos_.z - (height_ / 2) &&
			rot_pos.z - radius_ < rect_pos_.z + (height_ / 2))
		{
			return true;
		}
		else
			return false;
		break;
	case HitRectPoint::LeftOrRight: //左右
		//矩形の回転前の座標で判定を行う
		if (rot_pos.x + radius_ > rect_pos_.x - (width_ / 2) &&
			rot_pos.x - radius_ < rect_pos_.x + (width_ / 2) &&
			rot_pos.z > rect_pos_.z - (height_ / 2) &&
			rot_pos.z < rect_pos_.z + (height_ / 2))
		{
			return true;
		}
		else
			return false;
		break;
	case HitRectPoint::LeftTop: //左上頂点
		ver_pos.x = rect_pos_.x - (width_ / 2);
		ver_pos.z = rect_pos_.z + (height_ / 2);
		break;
	case HitRectPoint::RightTop: //左下頂点
		ver_pos.x = rect_pos_.x - (width_ / 2);
		ver_pos.z = rect_pos_.z - (height_ / 2);
		break;
	case HitRectPoint::LeftUnder: //左下頂点
		ver_pos.x = rect_pos_.x + (width_ / 2);
		ver_pos.z = rect_pos_.z + (height_ / 2);
		break;
	case HitRectPoint::RightUnder: //右下頂点
		ver_pos.x = rect_pos_.x + (width_ / 2);
		ver_pos.z = rect_pos_.z - (height_ / 2);
		break;
	default:
		break;
	}

	//ベクトル算出
	vec.x = ver_pos.x - rot_pos.x;
	vec.z = ver_pos.z - rot_pos.z;

	//円の半径と矩形の幅の距離
	float c = sqrtf(vec.x * vec.x + vec.z * vec.z);

	if (c <= radius_)
	{
		return true;
	}
	
	return false;
}

//円と円の当たり判定
bool Collision::CircleAndCircle(D3DXVECTOR3 circle_pos_, D3DXVECTOR3 circle2_pos_, float radius1_, float radius2_)
{
	float length = 0.0f;        //対象の円との距離
	float value_radius = 0.0f;  //対象との半径の合計
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);     //対象とのベクトル

	//対象とのベクトル算出
	vec.x = circle_pos_.x - circle2_pos_.x;
	vec.z = circle_pos_.z - circle2_pos_.z;

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
bool Collision::RectAndPoint(D3DXVECTOR2 rect_pos_, D3DXVECTOR2 point_pos_, float width_, float height_)
{
	if (point_pos_.x >= rect_pos_.x
	 && point_pos_.x <= rect_pos_.x + width_
	 && point_pos_.y >= rect_pos_.y
	 && point_pos_.y <= rect_pos_.y + height_)
	{
		return true;
	}
	else
	{
		return false;
	}
}