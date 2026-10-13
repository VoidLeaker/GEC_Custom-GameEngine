#pragma once

#include "IReceiveInput.h"
#include <vector>

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