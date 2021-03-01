#pragma once
#include <map>
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

namespace dae
{
	enum ControllerButton : WORD
	{
		RightDPad = XINPUT_GAMEPAD_DPAD_RIGHT,
		LeftDPad = XINPUT_GAMEPAD_DPAD_LEFT,
		DownDPad = XINPUT_GAMEPAD_DPAD_DOWN,
		UpDPad = XINPUT_GAMEPAD_DPAD_UP,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightThumb =  XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		Back = XINPUT_GAMEPAD_BACK,
		Start = XINPUT_GAMEPAD_START,
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		LeftTrigger,
		RightTrigger,
		LeftThumbStick,
		RightThumbStick,

	};

	enum class KeyState
	{
		Idle, Pressed, Held, Released
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void HandleInput() const;

		void AddButtonCommand(ControllerButton button, Command* command);

		bool IsPressed(ControllerButton button) const;
		bool WasPressed(ControllerButton button) const;
		bool Pressed(ControllerButton button, const XINPUT_STATE& keystate) const;
		KeyState GetKeyState(ControllerButton) const;


	private:
		XINPUT_STATE m_CurrentState{}, m_PreviousState{};





		std::map<ControllerButton, Command*> m_Commands;

		
	};

}
