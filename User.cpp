#include "User.h"

size_t User::_idCounter = 0;

User::User(const MyString& firstName, const MyString& lastName,
	const MyString& email, const MyString& username,
	const MyString& password) {
	validateUsername(username);
	validatePassword(password);
	_id = User::_idCounter++;
	_firstName = firstName;
	_lastName = lastName;
	_email = email;
	_username = username;
	_password = password;
}

size_t User::getId() const {
	return _id;
}

const MyString& User::getFirstName() const {
	return _firstName;
}
const MyString& User::getLastName() const {
	return _lastName;
}
const MyString& User::getEmail() const {
	return _email;
}
const MyString& User::getUsername() const {
	return _username;
}

void User::setFirstName(const MyString& firstName) {
	_firstName = firstName;
}

void User::setLastName(const MyString& lastName) {
	_lastName = lastName;
}

void User::setEmail(const MyString& email) {
	_email = email;
}

void User::setUsername(const MyString& username) {
	validateUsername(username);
	_username = username;
}

void User::setPassword(const MyString& password) {

	validatePassword(password);
	_password = password;
}

bool User::checkPassword(const MyString& password) {
	return _password == password;
}

void User::validateUsername(const MyString& username) const {
	if (username.length() > UserNS::USERNAME_EXPECTED_LENGTH)
		throw std::invalid_argument(UserNS::INVALID_USERNAME_LENGTH_ERROR.c_str());

	if (!Utility::hasOnlySmallLetters(username))
		throw std::invalid_argument(UserNS::INVALID_USERNAME_LETTERS_ERROR.c_str());
}

void User::validatePassword(const MyString& password) const {
	if (!Utility::hasDigit(password))
		throw std::invalid_argument(UserNS::PASSWORD_NO_DIGIT_ERROR.c_str());
	if (!Utility::hasUpperLetter(password))
		throw std::invalid_argument(UserNS::PASSWORD_NO_UPPER_ERROR.c_str());
	if (!Utility::hasLowerLetter(password))
		throw std::invalid_argument(UserNS::PASSWORD_NO_LOWER_ERROR.c_str());
}

User::~User() {
	_logger = nullptr;
}