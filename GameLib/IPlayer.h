#pragma once
#include<string>

struct _declspec(dllexport) IPlayer
{
	virtual ~IPlayer() = default;
	virtual const char& GetColor() = 0;
	virtual const std::string& GetName() = 0;
};