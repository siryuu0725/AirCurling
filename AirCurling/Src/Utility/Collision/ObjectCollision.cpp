#include "ObjectCollision.h"
#include "../../Object/Floor/GoalFloor.h"

ObjectCollision* ObjectCollision::mp_instance = nullptr;

//コンストラクタ
ObjectCollision::ObjectCollision() :
	m_hit_circleblock_id(0), m_hit_rectblock_id(0), m_goal_type(0)
{
	m_goal_radius[0] = RedGoalRadius;
	m_goal_radius[1] = YellowGoalRadius;
	m_goal_radius[2] = GreenGoalRadius;
}

ObjectCollision* ObjectCollision::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new ObjectCollision; }

	return mp_instance;
}

//矩形ブロック当たり判定関数
bool ObjectCollision::HitRectBlock()
{
	//個数分回す
	for (__int8 i = 0; i < m_rectblock_copy.size(); i++)
	{
		//上下左右、各頂点分回す
		for (__int8 point = 0; point < (__int8)HitRectPoint::PointMax; point++)
		{
			if (Collision::RectAndCircle(point, m_rectblock_copy[i].m_pos, m_player_copy.m_pos, m_rectblock_copy[i].m_width, m_rectblock_copy[i].m_height, m_player_copy.m_radius, m_rectblock_copy[i].m_angle.y) == true)
			{
				m_hit_rectblock_id = i;
				m_rectpoint = (HitRectPoint)point;
				return true;
			}
		}
	}

	return false;
}

//円形ブロック当たり判定関数
bool ObjectCollision::HitCircleBlock()
{
	//個数分回す
	for (__int8 i = 0; i < m_circleblock_copy.size(); i++)
	{
		if (Collision::CircleAndCircle(m_player_copy.m_pos, m_circleblock_copy[i].m_pos, m_player_copy.m_radius, m_circleblock_copy[i].m_radius) == true)
		{
			m_hit_circleblock_id = i;

			return true;
		}
	}

	return false;
}

//リセット床当たり判定関数
bool ObjectCollision::HitResetFloor()
{
	//個数分回す
	for (__int8 i = 0; i < m_resetfloor_copy.size(); i++)
	{
		if (Collision::CircleAndCircle(m_player_copy.m_pos, m_resetfloor_copy[i].m_pos, m_player_copy.m_radius, m_resetfloor_copy[i].m_radius) == true)
		{
			return true;
		}
	}

	return false;
}

//スピード減衰床当たり判定関数
bool ObjectCollision::HitStopFloor()
{
	//個数分回す
	for (__int8 i = 0; i < m_stopfloor_copy.size(); i++)
	{
		//上下左右分回す
		for (__int8 point = 0; point <= (__int8)HitRectPoint::LeftOrRight; point++)
		{
			if (Collision::RectAndCircle(point, m_stopfloor_copy[i].m_pos, m_player_copy.m_pos, m_stopfloor_copy[i].m_width, m_stopfloor_copy[i].m_height, m_player_copy.m_radius, m_stopfloor_copy[i].m_angle.y) == true)
			{
				return true;
			}
		}
	}

	return false;
}

//ゴール当たり判定関数
bool ObjectCollision::HitGoal()
{
	for (int i = 0; i < GoalTypeNum; i++)
	{
		if (Collision::CircleAndCircle(m_player_copy.m_pos, m_goal_copy.m_pos, m_player_copy.m_radius, m_goal_radius[i]) == true)
		{
			m_goal_type = i;
			return true;
		}
	}
	
	return false;
}

//各オブジェクト情報リセット関数
void ObjectCollision::ResetObjectInfo()
{
	m_rectblock_copy.clear();
	m_circleblock_copy.clear();
	m_resetfloor_copy.clear();
	m_stopfloor_copy.clear();
}

void ObjectCollision::ReleaseInstance()
{
	delete mp_instance;
	mp_instance = nullptr;
}

