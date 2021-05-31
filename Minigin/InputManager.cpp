#include "ImposterPCH.h"
#include "InputManager.h"
#include <SDL.h>


dae::InputManager::~InputManager()
{
	for (auto commandPair : m_ControllerCommands)
	{
		delete commandPair.second.pCommand;
		commandPair.second.pCommand = nullptr;
	}
	for (auto commandPair : m_KeyboardCommands)
	{
		delete commandPair.second.pCommand;
		commandPair.second.pCommand = nullptr;
	}
}

bool dae::InputManager::ProcessInput()
{

	m_PreviousState = m_CurrentState;
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);


	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{

			/*std::cout << "Key down" << std::endl;
			std::cout << e.key.keysym.sym << std::endl;*/

		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
	}

	return true;
}

void dae::InputManager::HandleInput()
{

	for (auto& command : m_ControllerCommands)
	{
		if (GetKeyState(command.first) == KeyState::Pressed)
		{
			command.second.pCommand->Execute();

		}
	}


	for (auto& command : m_KeyboardCommands)
	{

		KeyState state = GetKeyState(command);
		if (state == KeyState::Pressed)
		{
			command.second.pCommand->Execute();
		}
		command.second.state = state;
	}


}

void dae::InputManager::AddButtonCommand(ControllerButton button, Command* command)
{
	m_ControllerCommands[button] = KeyCommands{command};

}

void dae::InputManager::AddKeyCommand(SDL_Scancode code, Command* command)
{
	m_KeyboardCommands[code] = KeyCommands{ command };
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

bool dae::InputManager::IsPressed(SDL_Scancode code) const
{
	return SDL_GetKeyboardState(nullptr)[code];
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

dae::KeyState dae::InputManager::GetKeyState(std::pair<SDL_Scancode, KeyCommands> command) const
{

	if (command.second.state == KeyState::Pressed || command.second.state == KeyState::Held)
	{
		if (IsPressed(command.first))
		{
			return KeyState::Held;

		}
		return KeyState::Released;

	}
	else
	{
		if (IsPressed(command.first))
		{
			return KeyState::Pressed;
		}
		return KeyState::Idle;
	}
}
