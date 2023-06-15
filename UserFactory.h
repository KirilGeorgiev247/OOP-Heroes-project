#pragma once
#include "User.h"
#include "MyString.h"
#include "Enums.h"

namespace UserFactoryNS {
	const size_t M_MONEY = 2000;
}

class UserFactory {
public:
	static User* createUser(const MyString& firstname, const MyString& lastname, const MyString& email, const MyString& username, const MyString& password, Enums::UserType);
};