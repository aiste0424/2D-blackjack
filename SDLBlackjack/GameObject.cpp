#include "GameObject.h"

const Vector2D& GameObject::GetPosition() const
{
	return m_position;
}

const Vector2D& GameObject::GetDimension() const
{
	return m_dimension;
}

void GameObject::SetPosition(Vector2D position)
{
	m_position = position;
}

void GameObject::SetDimension(Vector2D dimension)
{
	m_position = dimension;
}
