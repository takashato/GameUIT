#pragma once
#include <exception>

class GameException : public std::exception 
{
private:
	std::string msgOut;
	GameException(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file);

public:
	const char* what() const noexcept override { return msgOut.c_str(); }

	template <typename ...Args>
	static void Throw(UINT line, LPCSTR func, LPCSTR file, Args... msgs)
	{
		std::ostringstream ss;
		((ss << msgs << " "), ...);
		throw GameException(ss.str().c_str(), line, func, file);
	}

#define ThrowGameException(...) GameException::Throw(__LINE__, __func__, __FILE__, __VA_ARGS__);
};
