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


void Keyboard::SetKey(BYTE keyCode, BOOL isSet)
{
	int index = keyCode / 8;
	int offset = keyCode % 8;
	if (isSet)
		mKeyStates[index] |= 1UL << offset;
	else
		mKeyStates[index] &= ~(1UL << offset);
}

BOOL Keyboard::IsPressing(BYTE keyCode)
{
	int index = keyCode / 8;
	int offset = keyCode % 8;

	return (mKeyStates[index] >> offset) & 1U;
}

void Keyboard::OnKeyDown(BYTE keyCode)
{
	SetKey(keyCode, TRUE);
}

void Keyboard::OnKeyUp(BYTE keyCode)
{
	SetKey(keyCode, FALSE);
}
