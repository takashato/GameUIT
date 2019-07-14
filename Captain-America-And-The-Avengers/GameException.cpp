#include "pch.h"
#include "GameException.h"

GameException::GameException(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file)
{
	std::ostringstream ss;
	ss << "[Exception]: " << msg << "\n";
	ss << "[Line]: " << line << "\n";
	ss << "[Func]: " << func << "\n";
	ss << "[File]: " << file << "\n";
	msgOut = ss.str();
	//Debug::O ut(what());
}
