#include "Player.h"

Player::Player(const MyString& firstName, const MyString& lastName,
	const MyString& email, const MyString& username,
	const MyString& password, size_t heroCoins)
	: User(firstName, lastName, email, username, password), _heroCoins(heroCoins) { }

void Player::printInfo() const {
	_logger->print("Player: ");
	_logger->print(_username);
	_logger->print(' ');
	_logger->print(_heroCoins);
	_logger->print('$');
	_logger->newLine();
	if (!_heroes.getSize())
		_logger->print(PlayerNS::NO_HEROES_ERROR.c_str());
	for (size_t i = 0; i < _heroes.getSize(); i++) {
		_logger->print("->");
		_logger->print(i + 1);
		_logger->print('.');
		_logger->print(_heroes[i]);
	}
}

User* Player::clone() const {
	User* copy = new Player(*this);
	return copy;
}

bool Player::isDeletable() const {
	return true;
}

bool Player::hasPermissionsToDelete() const {
	return false;
}

//void Player::removePlayer(size_t id) {
//	if (_id != id)
//	{
//		throw; // logic error
//	}
//	//_system->removeUserById(id);
//}

void Player::addHero(const Hero& hero) {
	if (_heroCoins > hero.getPrice())
	{
		_heroes.pushBack(hero);
		_heroCoins -= hero.getPrice();
	}
	else
		throw std::logic_error(PlayerNS::NOT_ENOUGH_FUNDS_ERROR.c_str());
}

void Player::setHeroState(const MyString& nickname, Enums::State state) {
	bool exists = false;
	for (size_t i = 0; i < _heroes.getSize(); i++)
	{
		if (_heroes[i].getNickname() == nickname)
		{
			exists = true;
			if (_heroes[i].getState() == state)
				_logger->print(PlayerNS::ALREADY_IN_THIS_STATE_ERROR);
			else
			{
				MyString stateStr;
				switch (state)
				{
				case Enums::State::Attack:
					stateStr = "attack"; break;
				case Enums::State::Defence:
					stateStr = "defence"; break;
				}
				_heroes[i].setState(state);
				_logger->print(_heroes[i].getNickname() + " set to " + stateStr + " successfully!\n");
			}
		}
	}

	if (!exists)
	{
		throw std::invalid_argument(PlayerNS::NO_SUCH_HERO.c_str());
	}
}

int Player::getIndexOfHeroByNickname(const MyString& nickname) const {
	for (size_t i = 0; i < _heroes.getSize(); i++)
	{
		if (_heroes[i].getNickname() == nickname)
			return i;
	}
	return -1;
}

const Hero& Player::getHeroByIndex(size_t index) const {
	return _heroes[index];
}

size_t Player::getHeroesCount() const {
	return _heroes.getSize();
}

size_t Player::getCoins() const {
	return _heroCoins;
}

void Player::setCoins(int coins) {
	coins < 0 ? _heroCoins = 0 : _heroCoins = coins;
}

void Player::removeHeroByIndex(size_t index) {
	_heroes.removeAtIndex(index);
}