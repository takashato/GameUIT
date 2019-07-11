#pragma once
#define KEY_CODE_SIZE 32 // Bytes, 32 bytes = 256 bits

class Keyboard {
public:
	Keyboard();
	void ResetKey();
	void SetKey(BYTE keyCode, BOOL state);
	BOOL IsPressing(BYTE keyCode);

	void OnKeyDown(BYTE keyCode);
	void OnKeyUp(BYTE keyCode);
private:
	BYTE mKeyStates[KEY_CODE_SIZE];
};