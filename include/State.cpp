#include "State.h"
#include "StateManager.h"

//void State::startDt() 
//{
//	dtClock.restart();
//}
//
//void State::stopDt()
//{
//	this->curr_dt += dtClock.getElapsedTime().asSeconds();
//}
//
//void State::resetDt() 
//{
//	this->dt = curr_dt;
//	this->curr_dt = 0;
//	
//}


Vec2f State::mousePosView() {
	return this->app->mousePosWindow() - (sf::Vector2f(app->getWindowSize()) / 2) + m_view.getCenter();
}
State::State(StateManager* app)
{
	this->app = app;
	this->m_view = app->getDefaultView();
}

State::~State()
{
}
void State::loadKeysFromFile(std::string file_path, bool debug)
{
	std::ifstream ifs(file_path);

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)//tf does >> do? 
		{
			//	std::cout<<key<<"\n";
			this->keybinds[key] = app->getKey(key2);
			if (debug)
			{
				std::cout << key << ": " << key2 << "\n";
			}
		}
	}
}

