#pragma once
#include "MyString.h"
#include "Enums.h"

namespace HeroNS {
	const MyString FIRE = "Fire";
	const MyString EARTH = "Earth";
	const MyString WATER = "Water";
}

class Hero {
public:
	
private:
	MyString _firstName;
	MyString _lastName;
	MyString _nickname;
	Enums::HeroType _powerType;
	size_t _powerRate = 0;
	size_t _price = 0;
	Enums::State _state;

public:
	Hero();
	Hero(const MyString& firstName, const MyString& lastName, const MyString& nickname, const Enums::HeroType& powerType, size_t powerRate, size_t price, const Enums::State& state);

	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getNickname() const;
	const Enums::HeroType& getHeroType() const;
	size_t getPowerRate() const;
	size_t getPrice() const;
	const Enums::State& getState() const;

	void setFirstName(const MyString& firstName);
	void setLastName(const MyString& lastName);
	void setNickname(const MyString& nickname);
	void setHeroType(const Enums::HeroType& heroType);
	void setPowerRate(size_t powerRate);
	void setPrice(size_t price);
	void setState(const Enums::State& state);

	friend std::ostream& operator<<(std::ostream& os, const Hero& obj);
};

bool operator==(const Hero& lhs, const Hero& rhs);

std::ostream& operator<<(std::ostream& os, const Hero& obj);