#pragma once
#include "MyVector.hpp"
#include "Hero.h"
#include "MyString.h"

// test the value logic
namespace MarketNS {
	const size_t PLAYER_STARTING_COINS = 2000;
	const size_t PLAYER_PERIODIC_COINTS = 300;


	const MyString DEFAULT_HERO_FIRSTNAME_1 = "Leo";
	const MyString DEFAULT_HERO_LASTNAME_1 = "Messi";
	const MyString DEFAULT_HERO_NICKNAME_1 = "FireMan";
	const Enums::HeroType DEFAULT_HERO_POWERTYPE_1 = Enums::HeroType::Fire;
	const size_t DEFAULT_HERO_POWERRATE_1 = 1600;
	const size_t DEFAULT_HERO_PRICE_1 = 1600;

	const MyString DEFAULT_HERO_FIRSTNAME_2 = "Solly";
	const MyString DEFAULT_HERO_LASTNAME_2 = "March";
	const MyString DEFAULT_HERO_NICKNAME_2 = "WaterMan";
	const Enums::HeroType DEFAULT_HERO_POWERTYPE_2 = Enums::HeroType::Water;
	const size_t DEFAULT_HERO_POWERRATE_2 = 700;
	const size_t DEFAULT_HERO_PRICE_2 = 700;

	const MyString DEFAULT_HERO_FIRSTNAME_3 = "Joao";
	const MyString DEFAULT_HERO_LASTNAME_3 = "Felix";
	const MyString DEFAULT_HERO_NICKNAME_3 = "EarthMan";
	const Enums::HeroType DEFAULT_HERO_POWERTYPE_3 = Enums::HeroType::Earth;
	const size_t DEFAULT_HERO_POWERRATE_3 = 800;
	const size_t DEFAULT_HERO_PRICE_3 = 800;

	const MyString DEFAULT_HERO_FIRSTNAME_4 = "Joao";
	const MyString DEFAULT_HERO_LASTNAME_4 = "Pedro";
	const MyString DEFAULT_HERO_NICKNAME_4 = "BlackMagic";
	const Enums::HeroType DEFAULT_HERO_POWERTYPE_4 = Enums::HeroType::Fire;
	const size_t DEFAULT_HERO_POWERRATE_4 = 1000;
	const size_t DEFAULT_HERO_PRICE_4 = 1000;

	const MyString DEFAULT_HERO_FIRSTNAME_5 = "Cristiano";
	const MyString DEFAULT_HERO_LASTNAME_5 = "Ronaldo";
	const MyString DEFAULT_HERO_NICKNAME_5 = "CR7";
	const Enums::HeroType DEFAULT_HERO_POWERTYPE_5 = Enums::HeroType::Water;
	const size_t DEFAULT_HERO_POWERRATE_5 = 1400;
	const size_t DEFAULT_HERO_PRICE_5 = 1400;

	const MyString INVALID_NICKNAME_ERROR = "Invalid nickname!\n";
}

class Market {
private:
	static Market* _instance;
	MyVector<Hero> _availableHeroes;
	MyVector<Hero> _soldOutHeroes;

	void seed();
	Market();
public:

	Market(const Market& other) = delete;
	Market(Market&&) = delete;
	Market& operator=(const Market& other) = delete;
	Market& operator=(Market&&) = delete;

	static Market* getInstance();

	static void deleteMarket();

	void returnSoldHeroByNickname(const MyString& nickname);

	const MyVector<Hero>& getAvailableHeroes() const;
	const MyVector<Hero>& getSoldHeroes() const;

	int getIndexOfHeroByNickname(const MyString& nickname) const;
	const Hero& getHeroByIndex(size_t index) const;
	void removeHeroByIndex(size_t index);

	void addHero(const MyString& firstname, const MyString& lastname, const MyString& nickname,
		Enums::HeroType type, size_t powerRate, size_t price, Enums::State state);
};