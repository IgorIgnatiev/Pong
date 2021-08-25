#pragma once
#include<SFML/Graphics/RectangleShape.hpp>
#include<thread>
class C_Ball :
	public sf::RectangleShape
{
private:
	bool _move_x;
	bool _move_y;
	sf::RectangleShape obj;
public:
	C_Ball(float x, float y, float pos_x, float pos_y, float window_x, float window_y) : RectangleShape(sf::Vector2f(x, y))
	{
		this->setPosition(pos_x, pos_y);
		this->obj.setSize(sf::Vector2f(window_x, window_y));
		this->_move_x = true;
		this->_move_y = true;
	}
	bool get_move_x()
	{
		return this->_move_x;
	}
	bool get_move_y()
	{
		return this->_move_y;
	}
	void set_move_x(bool val)
	{
		this->_move_x = val;
	}
	void set_move_y(bool val)
	{
		this->_move_y = val;
	}
	void move()
	{
		while (true)
		{
			if (this->_move_x == true && this->_move_y == true)
			{
				this->setPosition(this->getPosition().x + 20, this->getPosition().y + 20);
			}
			else if (this->_move_x == true && this->_move_y == false)
			{
				this->setPosition(this->getPosition().x + 20, this->getPosition().y - 20);
			}
			else if (this->_move_x == false && this->_move_y == false)
			{
				this->setPosition(this->getPosition().x - 20, this->getPosition().y - 20);
			}
			else
			{
				this->setPosition(this->getPosition().x - 20, this->getPosition().y + 20);
			}
			if (this->getPosition().y <= 0)
			{
				this->_move_y = true;
			}
			else if (this->getPosition().y + this->getSize().y >= obj.getSize().y)
			{
				this->_move_y = false;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
};
