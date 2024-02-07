#pragma once
//#include "Drawable.h"
#include "Keys.hpp"
#include "Textures.hpp"
//#include "AnimatedSprites.hpp"

enum activeType
{
	Wait,
	Remove,
	Update,
	Draw, 
	Update_Draw,
};

class StateManager;

class State{
	bool quit = 0;

	friend class StateManager;

protected:
	sf::View m_view;

	void endState() { this->quit = 1; }

public:
	Vec2f mousePosView(); //{ return this->app->mousePosWindow() - (sf::Vector2f(app->getWindowSize()) / 2) + m_view.getCenter(); }
	float dt;

	activeType background_state;

	StateManager* app;

	std::map<std::string, Key*> keybinds;
	
	void loadKeysFromFile(std::string file_path, bool debug = 0);

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow * window) = 0;

	//void updateInput();
	State(StateManager * app);
	virtual ~State();



};
/*

To add new keys find the enum value and put that in the supported keys config file.
Then you can uses that key in the keybinds config file for your state.
*/

