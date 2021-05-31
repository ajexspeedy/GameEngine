// Qbert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Minigin.h>
#include "QbertGame.h"
int main(int, char* [])
{
    dae::Minigin engine;
    engine.m_pGame = new dae::QbertGame{};
    engine.Run();
    return 0;
}

