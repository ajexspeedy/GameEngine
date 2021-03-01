#pragma once
#include <iostream>
#include "GameObject.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
	
};




