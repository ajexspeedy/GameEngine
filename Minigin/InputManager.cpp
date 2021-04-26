#include "ImposterPCH.h"
#include "InputManager.h"
#include <SDL.h>


dae::InputManager::~InputManager()
{
	for(auto commandPair:m_ControllerCommands)
	{
		delete commandPair.second;
		commandPair.second = nullptr;
	}
	for (auto commandPair : m_KeyboardCommands)
	{
		delete commandPair.second;
		commandPair.second = nullptr;
	}
}

bool dae::InputManager::ProcessInput()
{
	
	m_PreviousState = m_CurrentState;
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{

			/*std::cout << "Key down" << std::endl;
			std::cout << e.key.keysym.sym << std::endl;*/
			
	 	}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

void dae::InputManager::HandleInput()
{

	for (auto& command : m_ControllerCommands)
	{
		if(GetKeyState(command.first) == KeyState::Pressed)
		{
			command.second->Execute();
		
		}
	}
	
	
	for (auto& command : m_KeyboardCommands)
	{
		
		KeyState state = GetKeyState(command.first);
		if (state == KeyState::Pressed)
		{
			command.second->Execute();
		}
		m_PrevKeystate = state;
	}
	
	
}

void dae::InputManager::AddButtonCommand(ControllerButton button, Command* command)
{
	m_ControllerCommands[button] = command;
}

void dae::InputManager::AddKeyCommand(int code, Command* command)
{
	m_KeyboardCommands[code] = command;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	return Pressed(button, m_CurrentState);
}

bool dae::InputManager::WasPressed(ControllerButton button) const
{

	return Pressed(button, m_PreviousState);
}

bool dae::InputManager::Pressed(ControllerButton button, const XINPUT_STATE& keystate) const
{
	if (keystate.Gamepad.wButtons == button)
		return true;


	
	switch (button)
	{
	
		break;
	case ControllerButton::LeftTrigger:
		if (keystate.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			return true;
		break;
	case ControllerButton::RightTrigger:
		if (keystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			return true;
		break;
	case ControllerButton::LeftThumbStick:
		if (keystate.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && keystate.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			if (keystate.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && keystate.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		return true;
		break;
	case ControllerButton::RightThumbStick:
		if (keystate.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && keystate.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			if (keystate.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && keystate.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		return true;
		break;
	default:
		return false;
	}



	return false;

}

bool dae::InputManager::IsPressed(int key) const
{
	return SDL_GetKeyboardState(nullptr)[static_cast<SDL_Scancode>(key)];
}

bool dae::InputManager::WasPressed() const
{
	return (m_PrevKeystate == KeyState::Pressed) || (m_PrevKeystate == KeyState::Held);
}


dae::KeyState dae::InputManager::GetKeyState(ControllerButton button) const
{
	if (WasPressed(button))
	{
		if (IsPressed(button))
		{
			return KeyState::Held;
		}
		return KeyState::Released;
	}
	else
	{
		if (IsPressed(button))
		{
			return KeyState::Pressed;
		}
		return KeyState::Idle;
	}
}

dae::KeyState dae::InputManager::GetKeyState(int key) const
{

	if (WasPressed())
	{
		if (IsPressed(key))
		{
			return KeyState::Held;
		}
		return KeyState::Released;
	}
	else
	{
		if (IsPressed(key))
		{
			return KeyState::Pressed;
		}
		return KeyState::Idle;
	}
}
