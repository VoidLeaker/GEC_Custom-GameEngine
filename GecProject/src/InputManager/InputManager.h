#pragma once

#include "../InputManager/InputListener/IReceiveInput.h"
#include <vector>

// Singleton class that manages input listeners and updates them based on user input.

class InputManager
{
public:
	static InputManager& GetInstance()
	{
		static InputManager iManager;
		return iManager;
	}

	void addListener(IReceiveInput* listener);
	void removeListener(IReceiveInput* listener);
	void Update();

private:
	std::vector<IReceiveInput*> m_listeners;
};

#define INPUT_MAN InputManager::GetInstance()