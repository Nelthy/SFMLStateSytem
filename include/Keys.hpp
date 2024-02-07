#pragma once

#include "Vec2f.hpp"
#include "Vec2f.inl"



//using Uint = size_t;


class Key
{

	// if the key was pressed last frame
public:
	Key(int keynum) {
		this->boundkey = sf::Keyboard::Key(keynum);
	};
	sf::Clock time;
	float timeheld=0;
	bool pressedlast = 0;
	bool isheld=0;
	bool ispressed = 0;
	bool isreleased = 0;
	sf::Keyboard::Key boundkey;
};


