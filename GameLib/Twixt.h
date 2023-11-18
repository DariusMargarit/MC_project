#pragma once

#include "IGame.h"
#include <memory>

export import Player;
export import Game;

class _declspec(dllexport) Twixt 
{
public:
	void Run();
};