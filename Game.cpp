#include "Game.h"

Game::Game() {
	_handler = CommandHandler::getInstance();
	_logger = MyLogger::getInstance();
}

void Game::start() {
	char buff[GameNS::BUFF_SIZE];

	while (true)
	{
		try
		{
			std::cin.getline(buff, GameNS::BUFF_SIZE);

			_handler->execute(MyString(buff));

			_logger->print("- - - - - - - - - - - - - - - - - - -");
			_logger->newLine();
		}
		catch (const std::exception& ex)
		{
			_logger->print(ex.what());
			_logger->newLine();
		}
	}
}

Game::~Game() {
	_handler->deleteCommandHandler();
	_logger->deleteInstance();
}