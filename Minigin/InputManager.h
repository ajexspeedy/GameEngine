#pragma once
#include <unordered_map>
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

	struct KeyCommands
	{
		Command* pCommand;
		KeyState state = KeyState::Idle;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		~InputManager();
		bool ProcessInput();
		void HandleInput();

		void AddButtonCommand(ControllerButton button, Command* command);
		void AddKeyCommand(SDL_Scancode code, Command* command); // TODO: Add keyboard support

	
		KeyState GetKeyState(ControllerButton button) const;
		KeyState GetKeyState(std::pair<SDL_Scancode,KeyCommands> pair) const;


	private:
		XINPUT_STATE m_CurrentState{}, m_PreviousState{};



		bool IsPressed(ControllerButton button) const;
		bool WasPressed(ControllerButton button) const;
		bool Pressed(ControllerButton button, const XINPUT_STATE& keystate) const;

		bool IsPressed(SDL_Scancode code) const;
		bool WasPressed(SDL_Scancode code) const;
		

		std::unordered_map<ControllerButton, KeyCommands> m_ControllerCommands;
		std::unordered_map<SDL_Scancode, KeyCommands> m_KeyboardCommands;

		
		
		KeyState m_PrevKeystate;
	};

}
