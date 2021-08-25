#pragma once
#include<SFML/Graphics/RectangleShape.hpp>
class C_Player :
	public sf::RectangleShape
{
private:
	int _points;
public:
	C_Player(float x, float y, float pos_x, float pos_y) : RectangleShape(sf::Vector2f(x, y))
	{
		this->setPosition(pos_x, pos_y);
		this->_points = 0;
	}
	int get_points()
	{
		return this->_points;
	}
	void set_points(short point)
	{
		this->_points = point;
	}
	void inc()
	{
		this->_points += 1;
	}
};