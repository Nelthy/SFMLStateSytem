#pragma once
#include "State.h"


class StateManager
{
public:
	template <typename T, typename ...TArgs>
	void pushNewState(TArgs&&...m_Args) {
		T* state = new T(this, std::forward<TArgs>(m_Args)...);
		state_vector.lock();
		m_states.push_back(state);
		state_vector.unlock();

	}

	Key * getKey(std::string key_name);

	StateManager();
	~StateManager();

	void endApp(std::string reason);

	sf::Vector2u getWindowSize();

	bool isQuit();

	sf::Vector2i mousePosScreen() { return this->m_mousePosScreen; };
	sf::Vector2i mousePosWindow() { return this->m_mousePosWindow; };

	const sf::View getDefaultView() { return m_default_view; };

	const float* getDt() { return &this->dt; };
 
private:

	sf::View m_default_view;
	sf::Vector2i m_mousePosScreen;
	sf::Vector2i m_mousePosWindow;
	friend class App;
	void update();
	
	void updateStates();
	void initKeys();
	void initWindow();

	void updateMouse();

	void updateKeys();

	void updateWindow();
	
	void updateDt();

	static void UpdateState(State* state);

	void removeState(unsigned short int index);

	std::string end_reason;

	void checkEnd();

	std::mutex state_vector;
	std::mutex key_map;

	std::vector<State*> m_states;

	std::vector<unsigned short int> m_draw_stack;

	std::map<std::string, Key*> m_supported_keys;
	std::vector<Key*> m_keys;

	sf::RenderWindow* m_window;
	sf::Image m_icon;
	sf::Event sfEvent;

	std::vector<std::future<void>> m_update_futures;


	sf::Clock dtClock;
	bool quit = 0;
	float dt;
};

