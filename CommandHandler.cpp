#include "CommandHandler.h"

CommandHandler::CommandHandler() {
	_system = System::getInstance();
}

CommandHandler* CommandHandler::_instance = nullptr;

CommandHandler* CommandHandler::getInstance() {
	if (_instance == nullptr)
		_instance = new CommandHandler();
	return _instance;
}

void CommandHandler::deleteCommandHandler() {
	delete _instance;
}

void CommandHandler::getHeroInfo(MyString& firstname, MyString& lastname,
	MyString& nickname, Enums::HeroType& powerType,
	size_t& powerRate, size_t& price) {
	MyString type;

	char buff[CommandHandlerNS::BUFF_SIZE];
	_logger->print(CommandHandlerNS::ENTER_FIRSTNAME);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	firstname = buff;

	_logger->print(CommandHandlerNS::ENTER_LASTNAME);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	lastname = buff;

	_logger->print(CommandHandlerNS::ENTER_NICKNAME);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	nickname = buff;

	_logger->print(CommandHandlerNS::ENTER_POWER_TYPE);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	type = buff;

	if (HeroNS::EARTH == type)
		powerType = Enums::HeroType::Earth;
	else if (HeroNS::FIRE == type)
		powerType = Enums::HeroType::Fire;
	else if (HeroNS::WATER == type)
		powerType = Enums::HeroType::Water;
	else
		throw std::logic_error(CommandHandlerNS::NOT_VALID_HERO_TYPE_ERROR.c_str());

	// error handling
	_logger->print(CommandHandlerNS::ENTER_POWER_RATE);
	std::cin >> powerRate;

	// error handling
	_logger->print(CommandHandlerNS::ENTER_PRICE);
	std::cin >> price;
}

void CommandHandler::getUserInfo(MyString& firstname, MyString& lastname, MyString& email) {
	char buff[CommandHandlerNS::BUFF_SIZE];
	_logger->print(CommandHandlerNS::ENTER_FIRSTNAME);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	firstname = buff;

	_logger->print(CommandHandlerNS::ENTER_LASTNAME);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	lastname = buff;

	_logger->print(CommandHandlerNS::ENTER_EMAIL);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	email = buff;
}

void CommandHandler::getCredentials(MyString& username, MyString& password) {
	char buff[CommandHandlerNS::BUFF_SIZE];
	_logger->print(CommandHandlerNS::ENTER_USERNAME);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	username = buff;
	_logger->print(CommandHandlerNS::ENTER_PASSWORD);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	password = buff;
}

void CommandHandler::execute(const MyString& command) {
	try
	{
		bool isFirstCommand = false;
		if (CommandHandlerNS::ADMINISTRATOR_SIGN_IN_CMND == command)
		{
			isFirstCommand = true;
			signInAsAdmin();
			isAdminLoggedIn = true;
		}

		if (_system->getUsers().getSize() < 3
			&& command != CommandHandlerNS::ADD_NEW_PLAYER_CMND)
		{
			if (!isAdminLoggedIn)
			{
				_logger->print("Logging out...");
				_logger->newLine();
				logOut();
			}
			throw std::logic_error(CommandHandlerNS::NOT_ENOUGH_USERS_ERROR.c_str());
		}

		if (!_system->isMarketWithEnoughHeroes() && command != CommandHandlerNS::ADD_HERO_CMND)
		{
			if (!isAdminLoggedIn)
			{
				_logger->print("Logging out...");
				_logger->newLine();
				logOut();
			}
			throw std::logic_error(CommandHandlerNS::NOT_ENOUGH_HEROES_ERROR.c_str());
		}

		if (CommandHandlerNS::ADD_NEW_PLAYER_CMND == command)
			addNewPlayer();
		else if (CommandHandlerNS::SHOW_USERS_CMND == command)
			showUsers();
		else if (CommandHandlerNS::DELETE_PLAYER_CMND == command)
			deletePlayer();
		else if (CommandHandlerNS::ADD_HERO_CMND == command)
			addNewHero();
		else if (CommandHandlerNS::ADD_HERO_FROM_SOLD_CMND == command)
			returnSoldHeroToAvailable();
		else if (CommandHandlerNS::DELETE_MY_PROFILE_CMND == command)
			deleteCurrProfile();
		else if (CommandHandlerNS::SHOW_MARKET_CMND == command)
			showMarket();
		else if (CommandHandlerNS::BUY_HERO_CMND == command)
			buyHero();
		else if (CommandHandlerNS::LOG_OUT_CMND == command)
			logOut();
		else if (CommandHandlerNS::SET_TO_ATTACK_CMND == command)
			setHeroState(Enums::State::Attack);
		else if (CommandHandlerNS::SET_TO_DEFENCE_CMND == command)
			setHeroState(Enums::State::Defence);
		else if (CommandHandlerNS::ATTACK_PLAYER_CMND == command)
			startAttack(false);
		else if (CommandHandlerNS::ATTACK_PLAYER_RANDOM_CMND == command)
			startAttack(true);
		else if (CommandHandlerNS::SHOW_RANKING_CMND == command)
			showRankings();
		else if (CommandHandlerNS::PLAYER_SIGN_IN_CMND == command)
			signInAsPlayer();
		else if (CommandHandlerNS::SHOW_BALANCE_CMND == command)
			showBalance();
		else if (CommandHandlerNS::SHOW_PLAYERS_CMND == command)
			showPlayers();
		else
			if (!isFirstCommand)
				throw std::invalid_argument(CommandHandlerNS::NO_SUCH_COMMAND_ERROR.c_str());
	}
	catch (const std::exception& ex) {
		_logger->print(ex.what());
		_logger->newLine();
	}
}

void CommandHandler::addNewPlayer() {
	MyString username;
	MyString password;
	MyString email;
	MyString firstname;
	MyString lastname;

	getUserInfo(firstname, lastname, email);
	getCredentials(username, password);

	_system->addPlayer(firstname, lastname, email, username, password);
}

void CommandHandler::addNewAdmin() {
	MyString username;
	MyString password;
	MyString email;
	MyString firstname;
	MyString lastname;

	getUserInfo(firstname, lastname, email);
	getCredentials(username, password);

	_system->addAdmin(firstname, lastname, email, username, password);
}

bool CommandHandler::signInAsAdmin() {
	MyString username;
	MyString password;

	getCredentials(username, password);
	bool isSuccess = _system->logIn(username, password);
	if (isSuccess)
	{
		_logger->print(CommandHandlerNS::SUCCESS_LOGIN_MESSAGE_ADMIN);
		_logger->newLine();
	}
	else
		throw std::invalid_argument(CommandHandlerNS::UNSUCCESS_LOGIN_ERROR.c_str());

	return _system->isMarketWithEnoughHeroes();
}

void CommandHandler::signInAsPlayer() {
	MyString username;
	MyString password;

	getCredentials(username, password);
	bool isSuccess = _system->logIn(username, password);
	if (isSuccess)
	{
		_logger->print(CommandHandlerNS::SUCCESS_LOGIN_MESSAGE_PLAYER);
		_logger->newLine();
	}
	else
		throw std::invalid_argument(CommandHandlerNS::UNSUCCESS_LOGIN_ERROR.c_str());
}

void CommandHandler::showRankings() const {
	_system->showRankings();
}

void CommandHandler::showUsers() const {
	_system->showInfo();
}

void CommandHandler::deletePlayer() {
	MyString username;

	_logger->print(CommandHandlerNS::ENTER_USERNAME_FOR_DELETED_PLAYER);
	char buff[CommandHandlerNS::BUFF_SIZE];
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	username = buff;

	_system->removeUserByUsername(username);
}

void CommandHandler::addNewHero() {
	MyString firstName;
	MyString lastName;
	MyString nickname;
	Enums::HeroType powerType;
	size_t powerRate;
	size_t price;

	getHeroInfo(firstName, lastName, nickname, powerType, powerRate, price);

	_system->addHero(firstName, lastName, nickname, powerType, powerRate, price, Enums::State::NotSet);
}

void CommandHandler::returnSoldHeroToAvailable() {
	try
	{
		MyString nickname;
		_system->showSoldHeroes();

		_logger->print(CommandHandlerNS::ENTER_NICKNAME_OF_HERO_TO_RETURN);
		char buff[CommandHandlerNS::BUFF_SIZE];
		std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
		nickname = buff;

		_system->returnSoldHeroByNickname(nickname);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

void CommandHandler::deleteCurrProfile() {
	_system->deleteCurrUser();
}

void CommandHandler::showMarket() const {
	_system->showAvailableHeroes();
}

void CommandHandler::buyHero() {
	MyString nickname;

	_logger->print(CommandHandlerNS::ENTER_NICKNAME);
	char buff[CommandHandlerNS::BUFF_SIZE];
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	nickname = buff;

	_system->buyHero(nickname);
}

void CommandHandler::logOut() {
	if (_system->isSomeoneLoggedIn())
	{
		_system->logOut();
		isAdminLoggedIn = false;
	}
	else
		throw std::logic_error(CommandHandlerNS::UNSUCCESS_LOGOUT_ERROR.c_str());
}

void CommandHandler::setHeroState(Enums::State state) {
	MyString nickname;

	_logger->print(CommandHandlerNS::ENTER_NICKNAME);
	char buff[CommandHandlerNS::BUFF_SIZE];
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	nickname = buff;

	_system->setState(state, nickname);
}

void CommandHandler::startAttack(bool isRandom) {
	MyString username;
	MyString attackingNickname;
	MyString attackedNickname;

	_logger->print(CommandHandlerNS::ENTER_USERNAME);
	char buff[CommandHandlerNS::BUFF_SIZE];
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	username = buff;

	_logger->print(CommandHandlerNS::ENTER_ATTACKING_SUPERHERO);
	std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
	attackingNickname = buff;

	if (isRandom)
	{
		_system->startAttack(username, attackingNickname);
	}
	else
	{
		_logger->print(CommandHandlerNS::ENTER_ATTACKED_SUPERHERO);
		std::cin.getline(buff, CommandHandlerNS::BUFF_SIZE);
		attackedNickname = buff;

		_system->startAttack(username, attackingNickname, attackedNickname);
	}
}

CommandHandler::~CommandHandler() {
	_logger = nullptr;
	_system->deleteSystem();
}

void CommandHandler::showBalance() const {
	_system->showBalance();
}

void CommandHandler::showPlayers() const {
	_system->showPlayers();
}