#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


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
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

void dae::InputManager::HandleInput() const
{

	for (auto& command : m_Commands)
	{
		if(GetKeyState(command.first) == KeyState::Pressed)
		{
			command.second->Execute();
		
		}
	}
	
	
}

void dae::InputManager::AddButtonCommand(ControllerButton button, Command* command)
{
	m_Commands[button] = command;
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

	
	switch (button)
	{
	case ControllerButton::ButtonA:
	case ControllerButton::ButtonB:
	case ControllerButton::ButtonX:
	case ControllerButton::ButtonY:
	case ControllerButton::RightShoulder:
	case ControllerButton::LeftShoulder:
	case ControllerButton::RightThumb:
	case ControllerButton::LeftThumb:
	case ControllerButton::Back:
	case ControllerButton::Start:
	case ControllerButton::RightDPad:
	case ControllerButton::LeftDPad:
	case ControllerButton::DownDPad:
	case ControllerButton::UpDPad:
		if (keystate.Gamepad.wButtons == button)
			return true;
	
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