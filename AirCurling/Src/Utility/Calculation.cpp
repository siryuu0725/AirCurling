#include "Calculation.h"
#include <math.h>
#include <sstream>
#include <iomanip>

//ワールド座標計算関数
D3DXMATRIX Calculation::Matrix(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_)
{
	D3DXMATRIX world;
	D3DXMATRIX mat_trans, mat_scale, mat_rot, mat_rot_x, mat_rot_y, mat_rot_z;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 angle;

	D3DXMatrixIdentity(&world);

	m_pos = pos_;
	m_scale = scale_;
	angle = angle_;

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
float Calculation::EggplantAngle(D3DXVECTOR3 direction_, D3DXVECTOR3 vec_)
{
	//方向ベクトルと接線に垂直なベクトルのなす角を求める
	float a = (vec_.x * direction_.x) + (vec_.z * direction_.z);
	float b = sqrtf(vec_.x * vec_.x + vec_.z * vec_.z) * sqrtf(direction_.x * direction_.x + direction_.z * direction_.z);
	float radian = a / b;
	return acosf(radian);
}

//ベクトルの距離算出関数
float Calculation::Length(float target_pos_x, float target_pos_y)
{
	return sqrtf(target_pos_x * target_pos_x + target_pos_y * target_pos_y);
}

//ベクトル回転関数
D3DXVECTOR3 Calculation::Rote(D3DXVECTOR3 target_pos_, D3DXVECTOR3 target2_pos_, float radian_)
{
	D3DXVECTOR3 oldpos = target_pos_;

	target_pos_.x = (oldpos.x - target2_pos_.x) * cos(D3DXToRadian(radian_)) - (oldpos.z - target2_pos_.z) * sin(D3DXToRadian(radian_)) + target2_pos_.x;
	target_pos_.z = (oldpos.x - target2_pos_.x) * sin(D3DXToRadian(radian_)) + (oldpos.z - target2_pos_.z) * cos(D3DXToRadian(radian_)) + target2_pos_.z;

	return target_pos_;
}

