#pragma once
#define KEY_CODE_SIZE 256 // Bytes, 32 bytes = 256 bits

class Keyboard {
public:
	Keyboard();
	void ResetKey();
	BOOL IsPressing(BYTE keyCode);

	void ReadInput(IDirectInputDevice8* DIKeyboard);

private:
	BYTE mKeyStates[KEY_CODE_SIZE];
};