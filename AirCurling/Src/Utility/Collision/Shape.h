/**
 * @file Shape.h
 * @brief 各オブジェクト用の型を保存する
 * @details 中身：型基底クラス
**/
#ifndef SHAPE_H_
#define SHAPE_H_
#include <d3dx9.h>

/**
* 型基底クラス
*/

class Shape
{
public:
	Shape() {}
	~Shape() {}

public:
	virtual D3DXVECTOR3 GetCirclePos()const { return D3DXVECTOR3(); };

	virtual float GetRadius()const { return 0.0f; }

public:
	virtual D3DXVECTOR3 GetBoxPos()const { return D3DXVECTOR3(); };

	virtual float GetWidth()const { return 0.0f; }
	virtual float GetHeight()const { return 0.0f; }
	virtual float GetRote()const { return 0.0f; }
};


/**
*@clss  矩形型クラス
*/

class RectShape : public Shape {
public:
	RectShape(D3DXVECTOR3 pos_, float width_, float height_, float rote_) :
		m_pos(pos_), m_width(width_), m_height(height_), m_rote(rote_) {}
	~RectShape() {}

	virtual D3DXVECTOR3 GetBoxPos()const override { return m_pos; }

	virtual float GetWidth()const override { return m_width; }

	virtual float GetHeight()const override { return m_height; }

	virtual float GetRote()const override { return m_rote; }
private:
	D3DXVECTOR3 m_pos;
	float m_width, m_height;

	float m_rote;
};

/**
*@clss  円型クラス
*/
class CircleShape :public Shape
{
public:
	CircleShape(D3DXVECTOR3 pos_, float radius_) :
		m_pos(pos_), m_radius(radius_) {}
	~CircleShape() {}

	virtual D3DXVECTOR3 GetCirclePos()const override { return m_pos; }

	virtual float GetRadius()const override { return m_radius; }

private:
	D3DXVECTOR3 m_pos;
	float m_radius;
};

#endif