#include "System.h"

System::System() {
	seed();

	_currentUserId = _users[0]->getId();
	_market = Market::getInstance();
}

System* System::_instance = nullptr;

size_t System::_createdPlayers = 0;

System* System::getInstance() {
	if (_instance == nullptr) {
		try
		{
			_instance = new System();
		}
		catch (const std::exception& ex)
		{
			MyLogger::getInstance()->print(ex.what());
		}
	}
	return _instance;
}

void System::deleteSystem() {
	delete _instance;
}

const UserContext& System::getUsers() const {
	return _users;
}

User* System::getUserById(size_t id) {
	return _users[id];
}

User* System::getUserByUsername(const MyString& username) {
	for (size_t i = 0; i < _users.getSize(); i++)
	{
		if (_users[i]->getUsername() == username)
			return _users[i];
	}
	return nullptr;
}

void System::addPlayer(const MyString& firstname, const MyString& lastname, const MyString& email,
	const MyString& username, const MyString& password) {
	try
	{
		_users.createUser(firstname, lastname, email, username, password, Enums::UserType::Player);
		_createdPlayers++;
	}
	catch (const std::exception& ex)
	{
		_logger->print(ex.what());
	}
}

void System::addAdmin(const MyString& firstname, const MyString& lastname, const MyString& email,
	const MyString& username, const MyString& password) {
	try
	{
		_users.createUser(firstname, lastname, email, username, password, Enums::UserType::Admin);
	}
	catch (const std::exception& ex)
	{
		_logger->print(ex.what());
	}
}

void System::removeUserByUsername(const MyString& username) {
	User* currUser = getUserById(_currentUserId);
	try
	{
		if (currUser != nullptr)
		{
			if (currUser->hasPermissionsToDelete())
			{
				User* userToDelete = getUserByUsername(username);
				if (userToDelete != nullptr)
				{
					if (userToDelete->isDeletable())
					{
						_users.removeByUsername(username);
					}
					else
					{
						userToDelete = nullptr;
						throw std::logic_error(SystemNS::ADMINS_NOT_DELETABLE_ERROR.c_str());
					}
				}
				else
					throw std::invalid_argument(SystemNS::NO_SUCH_USER_ERROR.c_str());
				userToDelete = nullptr;
			}
			else
			{
				throw std::logic_error(SystemNS::NO_PERMISSION_TO_DELETE_ERROR.c_str());
			}
		}

	}
	catch (const std::exception& ex)
	{
		_logger->print(ex.what());
	}
	currUser = nullptr;
}

size_t System::getIndexById(size_t id) const {
	return 0;
}

bool System::logIn(const MyString& username, const MyString& password) {
	User* user = getUserByUsername(username);
	if (user != nullptr)
	{
		if (user->checkPassword(password))
		{
			_currentUserId = user->getId();

			if (user->isDeletable())
			{
				if (_playersToReceiveMoney.contains(username))
					giveMoney();
				else
					_playersToReceiveMoney.pushBack(username);

				if (_playersToReceiveMoney.getSize() == _createdPlayers)
					giveMoney();
			}

			user = nullptr;
			return true;
		}
	}

	return false;
}

void System::showPlayers() const {
	try
	{
		size_t ind = 1;
		for (size_t i = 0; i < _users.getSize(); i++)
		{
			if (_users[i]->isDeletable())
			{
				_logger->print(ind++);
				_logger->print('.');
				_users[i]->printInfo();
			}
		}
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

void System::showInfo() const {
	try
	{
		for (size_t i = 0; i < _users.getSize(); i++)
		{
			_logger->print(i + 1);
			_logger->print('.');
			_users[i]->printInfo();
		}
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

bool System::isMarketWithEnoughHeroes() const {
	return _market->getAvailableHeroes().getSize() > 2;
}

void System::addHero(const MyString& firstname, const MyString& lastname, const MyString& nickname,
	Enums::HeroType type, size_t powerRate, size_t price, Enums::State state) {
	_market->addHero(firstname, lastname, nickname, type, powerRate, price, state);
}

void System::showSoldHeroes() const {
	for (size_t i = 0; i < _market->getSoldHeroes().getSize(); i++)
		_logger->print(_market->getSoldHeroes()[i]);
}

void System::returnSoldHeroByNickname(const MyString& nickname) {
	try
	{
		_market->returnSoldHeroByNickname(nickname);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

void System::deleteCurrUser() {
	User* user = getUserById(_currentUserId);
	if (user->isDeletable())
	{
		logOut();
		_users.removeByUsername(user->getUsername());
		_logger->print("You profile was successfully deleted!");
	}
	else
		_logger->print("Admins cannot be deleted!\n");

	user = nullptr;
}

void System::showAvailableHeroes() const {
	for (size_t i = 0; i < _market->getAvailableHeroes().getSize(); i++) {
		_logger->print(i + 1);
		_logger->print(". ");
		_logger->print(_market->getAvailableHeroes()[i]);
	}
}

void System::buyHero(const MyString& nickname) {
	try
	{
		int index = _market->getIndexOfHeroByNickname(nickname);
		if (index != -1)
		{
			getUserById(_currentUserId)->addHero(_market->getHeroByIndex(index));
			_market->removeHeroByIndex(index);
		}
		else
			throw std::exception("No such hero!\n");
	}
	catch (const std::logic_error& ex) {
		_logger->print(ex.what());
	}
	catch (const std::exception& ex)
	{
		_logger->print(ex.what());
	}
}

bool System::isSomeoneLoggedIn() const {
	return _currentUserId != -1;
}

void System::logOut() {
	_currentUserId = -1;
	_logger->print("You have successfully logged out!\n");
}

void System::setState(Enums::State state, const MyString& nickname) {
	try
	{
		getUserById(_currentUserId)->setHeroState(nickname, state);
	}
	catch (const std::logic_error& ex)
	{
		_logger->print(ex.what());
	}
}

void System::startAttack(const MyString& username, const MyString& attackingNickname) {
	User* currUser = getUserById(_currentUserId);
	User* attackedUser = getUserByUsername(username);
	try
	{
		if (attackedUser == nullptr)
			throw std::invalid_argument("Such user does not exists!\n");
		int attackingIndex = currUser->getIndexOfHeroByNickname(attackingNickname);
		if (attackingIndex == -1)
			throw std::invalid_argument("Invalid nickname of the hero you attack with!\n");

		if (currUser->getHeroByIndex(attackingIndex).getState() != Enums::State::Attack)
			throw std::invalid_argument("Your here is not set to attack!\n");

		if (!attackedUser->getHeroesCount())
			makeAttack(currUser, attackedUser, currUser->getHeroByIndex(attackingIndex));
		else
		{
			size_t attackedIndex = Utility::getRandomNumberInRange(attackedUser->getHeroesCount());
			bool shouldHeroBeDestroyed = makeAttack(currUser, attackedUser,
				currUser->getHeroByIndex(attackingIndex), attackedUser->getHeroByIndex(attackedIndex));

			if (shouldHeroBeDestroyed)
				attackedUser->removeHeroByIndex(attackedIndex);
		}
	}
	catch (const std::invalid_argument& ex) {
		_logger->print(ex.what());
	}
	catch (const std::logic_error& ex) {
		_logger->print(ex.what());
	}
	currUser = nullptr;
	attackedUser = nullptr;
}

void System::startAttack(const MyString& username, const MyString& attackingNickname,
	const MyString& attackedNickname) {
	User* currUser = getUserById(_currentUserId);
	User* attackedUser = getUserByUsername(username);
	try
	{
		if (attackedUser == nullptr)
			throw std::invalid_argument("Such user does not exists!\n");
		int attackingIndex = currUser->getIndexOfHeroByNickname(attackingNickname);
		if (attackingIndex == -1)
			throw std::invalid_argument("Invalid nickname of the hero you attack with!\n");

		if (currUser->getHeroByIndex(attackingIndex).getState() != Enums::State::Attack)
			throw std::invalid_argument("Your here is not set to attack!\n");

		if (!attackedUser->getHeroesCount())
			makeAttack(currUser, attackedUser, currUser->getHeroByIndex(attackingIndex));
		else
		{
			int attackedIndex = attackedUser->getIndexOfHeroByNickname(attackedNickname);
			if (attackedIndex == -1)
				throw std::logic_error("Invalid nickname of the hero you attack!\n");
			bool shouldHeroBeDestroyed = makeAttack(currUser, attackedUser,
				currUser->getHeroByIndex(attackingIndex), attackedUser->getHeroByIndex(attackedIndex));

			if (shouldHeroBeDestroyed)
				attackedUser->removeHeroByIndex(attackedIndex);
		}
	}
	catch (const std::invalid_argument& ex)
	{
		_logger->print(ex.what());
	}
	catch (const std::logic_error& ex) {
		_logger->print(ex.what());
	}

	currUser = nullptr;
	attackedUser = nullptr;
}

bool System::makeAttack(User* attackingUser, User* attackedUser,
	Hero attackingHero, Hero attackedHero) {
	buffHeroes(attackingHero, attackedHero);
	bool shouldHeroBeDestroyed = false;
	try
	{
		int powerDiff = attackingHero.getPowerRate() - attackedHero.getPowerRate();

		if (powerDiff > 0)
		{
			shouldHeroBeDestroyed = true;
			attackingUser->setCoins(attackingUser->getCoins() + powerDiff);
			attackedUser->setCoins(attackedUser->getCoins() - powerDiff);
		}
		else if (powerDiff < 0)
		{
			attackingUser->setCoins(attackingUser->getCoins() + 2 * powerDiff);
			attackedUser->setCoins(attackedUser->getCoins() + SystemNS::Z_MONEY);
		}
		else
			attackingUser->setCoins(attackingUser->getCoins() - SystemNS::K_MONEY);
	}
	catch (const std::exception& ex)
	{
		_logger->print(ex.what());
	}

	return shouldHeroBeDestroyed;
}

void System::makeAttack(User* attackingUser, User* attackedUser,
	Hero attackingHero) {
	try
	{
		attackedUser->setCoins(attackedUser->getCoins() - attackingHero.getPowerRate());
		attackingUser->setCoins(attackingUser->getCoins() + SystemNS::X_MONEY);
	}
	catch (const std::exception& ex)
	{
		_logger->print(ex.what());
	}
}

void System::buffHeroes(Hero& attackingHero, Hero& attackedHero) {
	if (attackingHero.getHeroType() != attackedHero.getHeroType())
	{
		switch (attackingHero.getHeroType())
		{
		case Enums::HeroType::Fire:
			switch (attackedHero.getHeroType())
			{
			case Enums::HeroType::Water:
				attackedHero.setPowerRate(attackedHero.getPowerRate() * 2);
				break;
			case Enums::HeroType::Earth:
				attackingHero.setPowerRate(attackingHero.getPowerRate() * 2);
				break;
			}
			break;
		case Enums::HeroType::Water:
			switch (attackedHero.getHeroType())
			{
			case Enums::HeroType::Fire:
				attackingHero.setPowerRate(attackingHero.getPowerRate() * 2);
				break;
			case Enums::HeroType::Earth:
				attackedHero.setPowerRate(attackedHero.getPowerRate() * 2);
				break;
			}
			break;
		case Enums::HeroType::Earth:
			switch (attackedHero.getHeroType())
			{
			case Enums::HeroType::Water:
				attackingHero.setPowerRate(attackingHero.getPowerRate() * 2);
				break;
			case Enums::HeroType::Fire:
				attackedHero.setPowerRate(attackedHero.getPowerRate() * 2);
				break;
			}
			break;
		}
	}
}

void System::giveMoney() {
	try
	{
		for (size_t i = 0; i < _playersToReceiveMoney.getSize(); i++)
		{
			getUserByUsername(_playersToReceiveMoney[i])->setCoins(getUserByUsername(_playersToReceiveMoney[i])->getCoins() + SystemNS::J_MONEY);
		}

		_playersToReceiveMoney.empty();
	}
	catch (const std::exception& ex)
	{
		_logger->print(ex.what());
	}
}

void System::showRankings() {
	try
	{
		Pair<MyString, size_t>* players = new Pair<MyString, size_t>[_createdPlayers];
		size_t index = 0;

		for (size_t i = 0; i < _users.getSize(); i++)
		{
			if (_users[i]->isDeletable())
				players[index++] = Pair<MyString, size_t>(_users[i]->getUsername(), _users[i]->getCoins());
		}

		sort(players, _createdPlayers);

		for (size_t i = 0; i < _createdPlayers; i++)
		{
			_logger->print(i + 1);
			_logger->print('.');
			_logger->print(players[i].getFirst());
			_logger->print(": ");
			_logger->print(players[i].getSecond());
			_logger->print("$");
			_logger->newLine();
		}

		delete[] players;
	}
	catch (const std::exception& ex)
	{
		_logger->print(ex.what());
	}
}

void System::sort(Pair<MyString, size_t>* players, size_t count) {
	if (!players || count == 0)
		return;

	for (size_t i = 0; i < count - 1; i++)
	{
		size_t max = i;

		for (size_t j = i + 1; j < count; j++)
		{
			if (players[j].getSecond() > players[max].getSecond())
				max = j;
		}

		if (players[max].getSecond() > players[i].getSecond())
			std::swap(players[i], players[max]);
	}
}

System::~System() {
	_market->deleteMarket();
	_logger = nullptr;
}

void System::seed() {
	addAdmin(SystemNS::DEFAULT_FIRSTNAME_ADMIN, SystemNS::DEFAULT_LASTNAME_ADMIN,
		SystemNS::DEFAULT_EMAIL_ADMIN, SystemNS::DEFAULT_ADMIN_USERNAME, SystemNS::DEFAULT_ADMIN_PASSWORD);

	addPlayer(SystemNS::DEFAULT_USER_FIRSTNAME_1,
		SystemNS::DEFAULT_USER_LASTNAME_1, SystemNS::DEFAULT_USER_EMAIL_1, SystemNS::DEFAULT_USER_USERNAME_1, SystemNS::DEFAULT_USER_PASSWORD_1);

	addPlayer(SystemNS::DEFAULT_USER_FIRSTNAME_2,
		SystemNS::DEFAULT_USER_LASTNAME_2, SystemNS::DEFAULT_USER_EMAIL_2, SystemNS::DEFAULT_USER_USERNAME_2, SystemNS::DEFAULT_USER_PASSWORD_2);

	addPlayer(SystemNS::DEFAULT_USER_FIRSTNAME_3,
		SystemNS::DEFAULT_USER_LASTNAME_3, SystemNS::DEFAULT_USER_EMAIL_3, SystemNS::DEFAULT_USER_USERNAME_3, SystemNS::DEFAULT_USER_PASSWORD_3);
}

void System::showBalance() {
	_logger->print(getUserById(_currentUserId)->getCoins());
	_logger->newLine();
}