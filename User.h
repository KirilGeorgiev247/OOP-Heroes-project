#pragma once
#include "MyString.h"
#include "Hero.h"
#include "Utility.h"
#include "MyLogger.h"

// TODO: validations
namespace UserNS {
	const size_t USERNAME_EXPECTED_LENGTH = 16;

	const MyString INVALID_USERNAME_LENGTH_ERROR = "Username length should be exactly 16!\n";
	const MyString INVALID_USERNAME_LETTERS_ERROR = "Username should be only out of lower letters!\n";

	const MyString PASSWORD_NO_DIGIT_ERROR = "Password should have at least one digit!\n";
	const MyString PASSWORD_NO_UPPER_ERROR = "Password should have at least one upper letter!\n";
	const MyString PASSWORD_NO_LOWER_ERROR = "Password should have at least one lower letter!\n";
}

class User {
protected:
	size_t _id;
	MyString _firstName;
	MyString _lastName;
	MyString _email;
	MyString _username;
	MyString _password;

	MyLogger* _logger = MyLogger::getInstance();
private:
	void validateUsername(const MyString& username) const;
	void validatePassword(const MyString& password) const;

public:
	static size_t _idCounter;

	User(const MyString& firstName, const MyString& lastName, const MyString& email,
		const MyString& username, const MyString& password);

	size_t getId() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getEmail() const;
	const MyString& getUsername() const;

	void setFirstName(const MyString& firstName);
	void setLastName(const MyString& lastName);
	void setEmail(const MyString& email);
	void setUsername(const MyString& username);
	void setPassword(const MyString& password);

	bool checkPassword(const MyString& password);

	virtual void printInfo() const = 0;
	virtual User* clone() const = 0;
	virtual bool isDeletable() const = 0;
	virtual bool hasPermissionsToDelete() const = 0;
	//virtual void removePlayer(size_t id) = 0;
	virtual void addHero(const Hero& hero) = 0;
	virtual void setHeroState(const MyString& nickname, Enums::State) = 0;

	virtual int getIndexOfHeroByNickname(const MyString& nickname) const = 0;

	virtual const Hero& getHeroByIndex(size_t index) const = 0;
	virtual void removeHeroByIndex(size_t index) = 0;

	virtual size_t getHeroesCount() const = 0;
	virtual size_t getCoins() const = 0;

	virtual void setCoins(int coins) = 0;

	virtual ~User();
};