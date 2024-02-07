#pragma once
#include "StateManager.h"

class App
{
public:
	StateManager state_man;
	void update()
	{
		state_man.update();
	};

private:


};

