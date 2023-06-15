#include "Hero.h"

Hero::Hero() {}

Hero::Hero(const MyString& firstName, const MyString& lastName, const MyString& nickname, const Enums::HeroType& powerType, size_t powerRate, size_t price, const Enums::State& state) : _firstName(firstName), _lastName(lastName), _nickname(nickname), 
	_powerRate(powerRate), _powerType(powerType), _price(price), _state(state) { }

const MyString& Hero::getFirstName() const {
	return _firstName;
}

const MyString& Hero::getLastName() const {
	return _lastName;
}

const MyString& Hero::getNickname() const {
	return _nickname;
}

const Enums::HeroType& Hero::getHeroType() const {
	return _powerType;
}

size_t Hero::getPowerRate() const {
	return _powerRate;
}

size_t Hero::getPrice() const {
	return _price;
}

const Enums::State& Hero::getState() const {
	return _state;
}

void Hero::setFirstName(const MyString& firstName) {
	_firstName = firstName;
}

void Hero::setLastName(const MyString& lastName) {
	_lastName = lastName;
}

void Hero::setNickname(const MyString& nickname) {
	_nickname = nickname;
}

void Hero::setHeroType(const Enums::HeroType& heroType) {
	_powerType = heroType;
}

void Hero::setPowerRate(size_t powerRate) {
	_powerRate = powerRate;
}

void Hero::setPrice(size_t price) {
	_price = price;
}

void Hero::setState(const Enums::State& state) {
	_state = state;
}

bool operator==(const Hero& lhs, const Hero& rhs) {
	return (lhs.getFirstName() == rhs.getFirstName() && lhs.getLastName() == rhs.getLastName() &&
		lhs.getNickname() == rhs.getNickname() && lhs.getHeroType() == rhs.getHeroType() &&
		lhs.getPowerRate() == rhs.getPowerRate() && lhs.getPrice() == rhs.getPrice() &&
		lhs.getState() == rhs.getState());
}

std::ostream& operator<<(std::ostream& os, const Hero& obj) {
	os << obj._nickname << " ";
	os << "price: " << obj._price << "$ type: ";
	switch (obj._powerType)
	{
	case Enums::HeroType::Fire:
		os << HeroNS::FIRE;
		break;
	case Enums::HeroType::Water:
		os << HeroNS::WATER;
		break;
	case Enums::HeroType::Earth:
		os << HeroNS::EARTH;
		break;
	}

	os << " power: " << obj._powerRate;
	os << std::endl;

	return os;
}