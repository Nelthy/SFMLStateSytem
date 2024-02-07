#include "StateManager.h"

Key * StateManager::getKey(std::string key_name)
{
	key_map.lock();
	Key* key = m_supported_keys[key_name];
	key_map.unlock();
	return key;
}

StateManager::StateManager()
{
	initKeys();
	initWindow();
}

StateManager::~StateManager()
{
	for (size_t i = 0; i < m_keys.size(); i++)
	{
		delete m_keys[i];
	}
}

void StateManager::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			Key* nkey = new Key(key_value);
			this->m_supported_keys[key] = nkey;
			m_keys.push_back(nkey);
		}
	}
	ifs.close();
}

void StateManager::initWindow()
{
	std::ifstream ifs("Config/window.ini");

	std::string title = "None";

	sf::VideoMode window_bounds(2560, 1440);
	unsigned framerate_limit = 165;
	bool vertical_sync_enabled = false;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}
	ifs.close();
	m_window = new sf::RenderWindow(window_bounds, title);//idk what "this" means it is just creating a heap variable from the pointer "window". 4/10
	if (framerate_limit != 0)
	{
		m_window->setFramerateLimit(framerate_limit);
	}

	m_window->setVerticalSyncEnabled(vertical_sync_enabled);


	if (m_icon.loadFromFile("Assets/icon.png")) {
		m_window->setIcon(16, 16, m_icon.getPixelsPtr());
	}


	this->m_default_view = m_window->getDefaultView();
}

void StateManager::endApp(std::string reason)
{
	this->end_reason = reason;

	quit = true;
}

void StateManager::checkEnd() {
	if (this->quit == true)
	{
	std::cout<<"Ending Application" << "\n";
	std::cout<<"Reason: "<<end_reason << "\n";

	for (size_t i = 0; i < m_states.size(); i++)
	{
		delete m_states[i];//PS if you get an error here you messed up the memory in the state.
	}
	this->m_window->close();
	}
}

sf::Vector2u StateManager::getWindowSize()
{
	return m_window->getSize();
}

void StateManager::updateMouse()
{
	m_mousePosScreen = sf::Mouse::getPosition();
	m_mousePosWindow = sf::Mouse::getPosition(*this->m_window);
}

void StateManager::updateKeys() {
	for (Uint i = 0; i < m_keys.size(); i++)
	{
		Key* ckey = this->m_keys[i];
		ckey->isreleased = 0;

		if (sf::Keyboard::isKeyPressed(ckey->boundkey)) {
			ckey->ispressed = 1;
			if (ckey->pressedlast == 1)
			{
				ckey->ispressed = 0;
				ckey->isheld = 1;
				ckey->timeheld = ckey->time.getElapsedTime().asSeconds();
			}
			ckey->pressedlast = 1;
		}
		else {
			if (ckey->isheld) {
				ckey->isreleased = 1;
			}
			ckey->ispressed = 0;
			ckey->pressedlast = 0;
			ckey->isheld = 0;
			ckey->timeheld = 0;
			ckey->time.restart();
		}
	}
}

void StateManager::updateWindow()
{
	while (this->m_window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			endApp("User Closed Window");
			return;
		}
		if (this->sfEvent.type == sf::Event::Resized)
		{
			std::cout<<"Window Resized" << "\n";
			//this->m_window->setView(m_window->getDefaultView());
			for (size_t i = 0; i < m_states.size(); i++)
			{
				sf::Vector2f scale_factor;
				scale_factor.x = m_window->getSize().x / m_states[i]->m_view.getSize().x;
				scale_factor.y = m_window->getSize().y / m_states[i]->m_view.getSize().y;

				sf::Vector2f new_size(scale_factor.x * m_states[i]->m_view.getSize().x, scale_factor.y * m_states[i]->m_view.getSize().y);

				m_states[i]->m_view.setSize(new_size);




			}
			m_default_view.setSize(sf::Vector2f(m_window->getSize()));
		}
	}
	m_window->clear();
	sf::RectangleShape layer_fog;

	layer_fog.setFillColor(sf::Color(50, 50, 50, 50));
	layer_fog.setSize(sf::Vector2f(getWindowSize()));
	layer_fog.setPosition(m_default_view.getCenter() - sf::Vector2f(getWindowSize().x / 2, getWindowSize().y / 2));
	

	for (size_t i = 0; i < m_draw_stack.size(); i++)
	{
		if (i > 0)
		{
		
			m_window->draw(layer_fog);
		}
	
		m_window->setView(m_states[m_draw_stack[i]]->m_view);
	
	
	
	
		m_states[m_draw_stack[i]]->draw(m_window);
		m_window->setView(this->getDefaultView());
		}
	m_draw_stack.clear();
	m_window->display();
}

void StateManager::updateDt()
{
	this->dt = this->dtClock.getElapsedTime().asSeconds();
	this->dtClock.restart();
}

void StateManager::UpdateState(State* state) {
	state->update();

}

void StateManager::removeState(unsigned short int index)
{
	delete m_states[index];

	for (size_t i = 0; i < m_states.size() - index; i++)
	{
		if (i < m_states.size() - 1)
		{
			m_states[index + i] = m_states[index + i + 1];
		}
	}
	m_states.pop_back();

}

bool StateManager::isQuit()
{
	return quit;
}

void StateManager::update()
{

	updateDt();
	updateMouse();
	updateKeys();
	updateStates();
	updateWindow();
	checkEnd();


}

void StateManager::updateStates()
{
	/*
	update, draw, update and draw, neither
	*/
	//update back

	state_vector.lock();
	if (m_states.size() < 1)
	{
		endApp("No More States");
		state_vector.unlock();
		return;
	}
	//update background states
	for (Uint i = 0; i < m_states.size()-1; i++)
	{
		switch (m_states[i]->background_state)
		{
		case(Wait):
			break;
		case(Remove):
			removeState(i);
			break;
		case(Update):
			m_states[i]->dt = this->dt;
			m_update_futures.push_back(std::async(std::launch::async, UpdateState, m_states[i]));
			break;
		case(Draw):
			m_draw_stack.push_back(i);
			break;
		case(Update_Draw):
			m_states[i]->dt = this->dt;
			m_update_futures.push_back(std::async(std::launch::async, UpdateState, m_states[i]));
			m_draw_stack.push_back(i);
			break;
		}
		if (m_states[i]->quit == 1)
		{
			removeState(i);
		}
	}
	state_vector.unlock();
	//update main state
	if (!m_states.back()->quit)
	{
		m_states.back()->dt = this->dt;
		UpdateState(m_states.back());
		m_draw_stack.push_back(m_states.size() - 1);
	}
	else
	{
		removeState(m_states.size() - 1);
	}


	for (size_t i = 0; i < m_update_futures.size(); i++)
	{
		m_update_futures[i].wait();
	}

	m_update_futures.clear();


	


}
