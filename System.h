#pragma once
#include <iostream>
#include "Pair.hpp"
#include "MyVector.hpp"
#include "User.h"
#include "Market.h"
#include "UserContext.h"
#include "MyString.h"
#include "Enums.h"
#include "MyLogger.h"

namespace SystemNS {
	const MyString DEFAULT_ADMIN_USERNAME = "adminofadminssss";
	const MyString DEFAULT_ADMIN_PASSWORD = "Parola123";
	const MyString DEFAULT_FIRSTNAME_ADMIN = "TheFirst";
	const MyString DEFAULT_LASTNAME_ADMIN = "OfAll";
	const MyString DEFAULT_EMAIL_ADMIN = "admin123@avv.bg";

	const MyString DEFAULT_USER_USERNAME_1 = "kircenzo";
	const MyString DEFAULT_USER_PASSWORD_1 = "Parola123";
	const MyString DEFAULT_USER_EMAIL_1 = "kircenzo@abv.bg";
	const MyString DEFAULT_USER_FIRSTNAME_1 = "Kire";
	const MyString DEFAULT_USER_LASTNAME_1 = "Kirov";

	const MyString DEFAULT_USER_USERNAME_2 = "vancenzo";
	const MyString DEFAULT_USER_PASSWORD_2 = "Parola123";
	const MyString DEFAULT_USER_EMAIL_2 = "vancenzo@abv.bg";
	const MyString DEFAULT_USER_FIRSTNAME_2 = "Vanio";
	const MyString DEFAULT_USER_LASTNAME_2 = "Vaniov";

	const MyString DEFAULT_USER_USERNAME_3 = "bacepesho";
	const MyString DEFAULT_USER_PASSWORD_3 = "Parola123";
	const MyString DEFAULT_USER_EMAIL_3 = "bacepesho@abv.bg";
	const MyString DEFAULT_USER_FIRSTNAME_3 = "Pesho";
	const MyString DEFAULT_USER_LASTNAME_3 = "Peshev";

	const MyString ADMINS_NOT_DELETABLE_ERROR = "Admins cannot be deleted!\n";
	const MyString NO_SUCH_USER_ERROR = "No such user!\n";
	const MyString NO_PERMISSION_TO_DELETE_ERROR = "No permissions to delete!\n";

	const size_t X_MONEY = 500;
	const size_t K_MONEY = 400;
	const size_t Z_MONEY = 800;
	const size_t M_MONEY = 2000;
	const size_t J_MONEY = 900;
}

class System {
private:
	static System* _instance;
	UserContext _users;
	int _currentUserId;
	Market* _market = nullptr;
	MyVector<MyString> _playersToReceiveMoney;
	static size_t _createdPlayers;
	MyLogger* _logger = MyLogger::getInstance();

	System();
	~System();
	User* getUserById(size_t id);
public:

	System(const System& other) = delete;
	System(System&&) = delete;
	System& operator=(const System& other) = delete;
	System& operator=(System&&) = delete;

	static System* getInstance();

	static void deleteSystem();

	const UserContext& getUsers() const;

	User* getUserByUsername(const MyString& username);
	void addPlayer(const MyString& firstname, const MyString& lastname, const MyString& email, 
				   const MyString& username, const MyString& password);
	void addAdmin(const MyString& firstname, const MyString& lastname, const MyString& email,
		const MyString& username, const MyString& password);
	void addHero(const MyString& firstname, const MyString& lastname, const MyString& nickname, 
		Enums::HeroType type, size_t powerRate, size_t price, Enums::State state);

	void showSoldHeroes() const;

	void showAvailableHeroes() const;

	void returnSoldHeroByNickname(const MyString& nickname);

	void removeUserByUsername(const MyString& username);

	void deleteCurrUser();

	void buyHero(const MyString& nickname);

	bool logIn(const MyString& username, const MyString& password);

	void showInfo() const;

	void showPlayers() const;

	void showBalance();

	bool isMarketWithEnoughHeroes() const;

	bool isSomeoneLoggedIn() const;

	void showRankings();

	void logOut();

	void setState(Enums::State, const MyString& nickname);

	void startAttack(const MyString& username, const MyString& attackingNickname, 
		const MyString& attackedNickname);

	void startAttack(const MyString& username, const MyString& attackingNickname);
private:
	void giveMoney();
	bool makeAttack(User* attackingUser, User* attackedUser, Hero attackingHero, Hero attackedHero);
	void makeAttack(User* attackingUser, User* attackedUser, Hero attackingHero);
	size_t getIndexById(size_t id) const;
	void buffHeroes(Hero& attackingHero, Hero& attackedHero);
	void sort(Pair<MyString, size_t>* players, size_t count);
	void seed();
};

