#include "pch.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	ResetKey();
}

void Keyboard::ResetKey()
{
	for (int i = 0; i < KEY_CODE_SIZE; i++)
	{
		mKeyStates[i] = 0;
	}
}


BOOL Keyboard::IsPressing(BYTE keyCode)
{
	return mKeyStates[keyCode];
}

void Keyboard::ReadInput(IDirectInputDevice8* DIKeyboard)
{
	if (DIKeyboard != nullptr)
	{
		DIKeyboard->Acquire();
		DIKeyboard->GetDeviceState(sizeof(mKeyStates), (LPVOID)& mKeyStates);
	}
}
