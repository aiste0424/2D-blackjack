#pragma once
#include "Vector2D.h"

class GameObject
{

public:

	GameObject() {}
	virtual ~GameObject() = 0 {}
	const Vector2D& GetPosition() const;
	const Vector2D& GetDimension() const;
	const double GetAngle() const;

	void SetPosition(const Vector2D& position);
	void SetDimension(const Vector2D& dimension);
	void SetAngle(double angle = 0.0);

	virtual bool Update() = 0;
	virtual bool Render() = 0;

protected:

	Vector2D m_position;
	Vector2D m_dimension = { 0, 0 };
	double m_angle = { 0.0 };
};