#include "UserFactory.h"
#include "Player.h"
#include "Admin.h"

User* UserFactory::createUser(const MyString& firstname, const MyString& lastname, const MyString& email, const MyString& username, const MyString& password, Enums::UserType type) {
	try
	{
		switch (type)
		{
		case Enums::UserType::Admin:
			return new Admin(firstname, lastname, email, username, password);
		case Enums::UserType::Player:
			return new Player(firstname, lastname, email, username, password, UserFactoryNS::M_MONEY);
		}
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}