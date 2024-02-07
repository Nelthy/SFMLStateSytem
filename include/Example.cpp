#include <iostream>
#include "App.hpp"


class teststate : public State {


public:
	teststate(StateManager* app) : State(app) {};
	void update() {};
	void draw(sf::RenderWindow* window) {
		sf::CircleShape circle(100);

		window->draw(circle);
		
	
	};
};

int main() {
 

	App app;
	app.state_man.pushNewState<teststate>();
	while (!app.state_man.isQuit())
	{
		app.update();
	}
	return 0;
}