#include "Calculation.h"
#include <math.h>
#include <sstream>
#include <iomanip>

//ワールド座標計算関数
D3DXMATRIX Calculation::Matrix(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_)
{
	D3DXMATRIX world;
	D3DXMATRIX mat_trans, mat_scale, mat_rot, mat_rot_x, mat_rot_y, mat_rot_z;

	D3DXVECTOR3 m_pos = pos_;
	D3DXVECTOR3 m_scale = scale_;
	D3DXVECTOR3 angle = angle_;

	D3DXMatrixIdentity(&world);

	D3DXMatrixTranslation(&mat_trans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixScaling(&mat_scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationX(&mat_rot_x, D3DXToRadian(angle.x));
	D3DXMatrixRotationY(&mat_rot_y, D3DXToRadian(angle.y));
	D3DXMatrixRotationZ(&mat_rot_z, D3DXToRadian(angle.z));

	mat_rot = mat_rot_x * mat_rot_y * mat_rot_z;

	world *= mat_scale * mat_rot * mat_trans;

	return world;
}

//なす角計算関数
float Calculation::EggplantAngle(D3DXVECTOR3 vec1_, D3DXVECTOR3 vec2_)
{
	//vec1_とvec2_のなす角を求める
	float a = (vec2_.x * vec1_.x) + (vec2_.z * vec1_.z);
	float b = sqrtf(vec2_.x * vec2_.x + vec2_.z * vec2_.z) * sqrtf(vec1_.x * vec1_.x + vec1_.z * vec1_.z);
	float radian = a / b;
	return acosf(radian);
}

//ベクトルの距離算出関数
float Calculation::Length(D3DXVECTOR3 target_vec_)
{
	return sqrtf(target_vec_.x * target_vec_.x + target_vec_.y * target_vec_.y + target_vec_.z * target_vec_.z);
}

//ベクトルY軸回転関数
D3DXVECTOR3 Calculation::Rotate_Y(D3DXVECTOR3 target_pos_, D3DXVECTOR3 axis_pos_, float rote_rad_)
{
	D3DXVECTOR3 oldpos = target_pos_;

	target_pos_.x = (oldpos.x - axis_pos_.x) * cos(D3DXToRadian(rote_rad_)) - (oldpos.z - axis_pos_.z) * sin(D3DXToRadian(rote_rad_)) + axis_pos_.x;
	target_pos_.z = (oldpos.x - axis_pos_.x) * sin(D3DXToRadian(rote_rad_)) + (oldpos.z - axis_pos_.z) * cos(D3DXToRadian(rote_rad_)) + axis_pos_.z;

	return target_pos_;
}

