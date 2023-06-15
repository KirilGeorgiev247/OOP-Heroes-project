#pragma once
#include "User.h"

namespace AdminNS {
	const MyString ADMINS_NOT_DELETABLE_ERROR = "Admins cannot be deleted! \n";
	const MyString INVALID_ADMIN_COMMAND_ERROR = "Invalid admin command!\n";
}

class Admin : public User {
public:
	Admin(const MyString& firstName, const MyString& lastName,
		const MyString& email, const MyString& username,
		const MyString& password);

	/*void addAdmin(const Admin& admin);
	void addAdmin(Admin&& admin);

	void addPlayer(const Admin& admin);
	void addPlayer(Admin&& admin);*/
	
	void addHero(); // TODO

	//void showSystemInfo() const override;

	void printInfo() const override;

	User* clone() const override;

	bool isDeletable() const override;

	void addHero(const Hero& hero) override;

	bool hasPermissionsToDelete() const override;

	void setHeroState(const MyString& nickname, Enums::State) override;

	//void removePlayer(size_t id) override;

	int getIndexOfHeroByNickname(const MyString& nickname) const override;

	const Hero& getHeroByIndex(size_t index) const override;

	size_t getHeroesCount() const override;

	size_t getCoins() const override;

	void setCoins(int coins) override;

	void removeHeroByIndex(size_t index) override;
};


