#include "Admin.h"

Admin::Admin(const MyString& firstName, const MyString& lastName,
	const MyString& email, const MyString& username,
	const MyString& password) : User(firstName, lastName, email, username, password) { }

User* Admin::clone() const {
	User* copy = new Admin(*this);
	return copy;
}

//void Admin::showSystemInfo() const {
//
//}

void Admin::printInfo() const {
	_logger->print("Admin: ");
	_logger->print(_username + " " + _email);
	_logger->newLine();
}

//void Admin::addAdmin(const Admin& admin) {
//
//}
//
//void Admin::addAdmin(Admin&& admin) {
//
//}
//
//void Admin::addPlayer(const Admin& admin) {
//
//}
//
//void Admin::addPlayer(Admin&& admin) {
//
//}

bool Admin::isDeletable() const {
	//throw std::logic_error(AdminNS::ADMINS_NOT_DELETABLE_ERROR.c_str());
	return false;
}

bool Admin::hasPermissionsToDelete() const {
	return true;
}

//void Admin::removePlayer(size_t id) {
//	//_system->removeUserById(id);
//}

void Admin::addHero(const Hero& hero) {
	throw std::logic_error(AdminNS::INVALID_ADMIN_COMMAND_ERROR.c_str());
}

void Admin::setHeroState(const MyString& nickname, Enums::State) {
	throw std::logic_error(AdminNS::INVALID_ADMIN_COMMAND_ERROR.c_str());
}

int Admin::getIndexOfHeroByNickname(const MyString& nickname) const {
	throw std::logic_error(AdminNS::INVALID_ADMIN_COMMAND_ERROR.c_str());
}

const Hero& Admin::getHeroByIndex(size_t index) const {
	throw std::logic_error(AdminNS::INVALID_ADMIN_COMMAND_ERROR.c_str());
}

size_t Admin::getHeroesCount() const {
	throw std::logic_error(AdminNS::INVALID_ADMIN_COMMAND_ERROR.c_str());
}

size_t Admin::getCoins() const {
	throw std::logic_error(AdminNS::INVALID_ADMIN_COMMAND_ERROR.c_str());
}

void Admin::setCoins(int coins) {
	throw std::logic_error(AdminNS::INVALID_ADMIN_COMMAND_ERROR.c_str());
}

void Admin::removeHeroByIndex(size_t index) {
	throw std::logic_error(AdminNS::INVALID_ADMIN_COMMAND_ERROR.c_str());
}