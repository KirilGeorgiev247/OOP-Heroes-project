#pragma once
#include "CommandHandler.h"
#include <iostream>
#include <exception>
#include "MyLogger.h"

// test values
namespace GameNS {
	const size_t BUFF_SIZE = 1024;
}

class Game {
private:
	CommandHandler* _handler;
	MyLogger* _logger;

public:
	Game();
	void start();
	~Game();
};

