#pragma once
#include<string>

struct _declspec(dllexport) IPlayer
{
	virtual ~IPlayer() = default;
	virtual char* GetColor() const = 0;
	virtual const std::string& GetName() const = 0;
};