#pragma once
#include "User.h"
#include "MyString.h"
#include "MyVector.hpp"
#include "Hero.h"

namespace PlayerNS {
	const MyString NO_HEROES_ERROR = "No heroes\n";
	const MyString NOT_ENOUGH_FUNDS_ERROR = "Not enough coins for this hero!\n";
	const MyString NO_SUCH_HERO = "No such hero!\n";
	const MyString ALREADY_IN_THIS_STATE_ERROR = "Already in this state!\n";
}

class Player : public User {
private:
	size_t _heroCoins = 0;
	MyVector<Hero> _heroes;
public:
	Player( const MyString& firstName, const MyString& lastName,
		const MyString& email, const MyString& username,
		const MyString& password, size_t heroCoins);

	int getIndexOfHeroByNickname(const MyString& nickname) const;

	const Hero& getHeroByIndex(size_t index) const;

	User* clone() const override;

	void printInfo() const override;

	bool isDeletable() const override;

	bool hasPermissionsToDelete() const override;

	void addHero(const Hero& hero) override;

	void setHeroState(const MyString& nickname, Enums::State) override;

	//void removePlayer(size_t id) override;

	size_t getHeroesCount() const override;

	size_t getCoins() const override;

	void setCoins(int coins) override;

	void removeHeroByIndex(size_t index) override;
};