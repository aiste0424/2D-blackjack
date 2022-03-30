#pragma once
#include <string>
#include "Vector2D.h"

class GameObject
{

public:

	GameObject() {}
	virtual ~GameObject() = 0 {}
	const Vector2D& GetPosition() const;
	const Vector2D& GetDimension() const;

	void SetPosition(Vector2D position);
	void SetDimension(Vector2D dimension);

	virtual bool Update() { return true; };
	virtual bool Render() { return true; };

protected:

	Vector2D m_position;
	Vector2D m_dimension;
};

