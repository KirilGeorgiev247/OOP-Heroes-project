#include "UserContext.h"

static size_t closestPowerOfTwo(size_t n)
{
	n--;

	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;

	return n + 1;
};

void UserContext::copyFrom(const UserContext& other) {
	_users = new User * [other._capacity];
	_size = other._size;
	_capacity = other._capacity;

	for (size_t i = 0; i < _size; ++i)
		_users[i] = other._users[i]->clone();
}

void UserContext::free() {
	delete[] _users;
}

void UserContext::resize(size_t capacity) {
	User** temp = _users;
	_capacity = capacity;
	_users = new User * [_capacity];

	for (size_t i = 0; i < _size; ++i)
		_users[i] = std::move(temp[i]);

	delete[] temp;
}

void UserContext::moveFrom(UserContext&& other) noexcept {
	_users = other._users;
	_size = other._size;
	_capacity = other._capacity;
	other._users = nullptr;
	other._size = 0;
	other._capacity = 0;
}

UserContext::UserContext()
	: UserContext(UserContextNS::DEFAULT_CAPACITY) {}

UserContext::UserContext(size_t capacity)
	: _size(0) {
	_capacity = closestPowerOfTwo(capacity);
	_users = new User * [_capacity];
}

UserContext::UserContext(const UserContext& other) {
	copyFrom(other);
}

UserContext& UserContext::operator= (const UserContext& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

UserContext::~UserContext() {
	free();
}

UserContext::UserContext(UserContext&& other) noexcept {
	moveFrom(std::move(other));
}

UserContext& UserContext::operator= (UserContext&& other) noexcept {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void UserContext::createUser(const MyString& firstName, const MyString& lastName, const MyString& email,
	const MyString& username, const MyString& password, Enums::UserType type) {
	try
	{
		if (_size == _capacity)
			resize(_capacity * 2);
		_users[_size++] = UserFactory::createUser(firstName, lastName, email, username, password, type);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

void UserContext::removeByUsername(const MyString& username) {
	for (size_t i = 0; i < _size; i++)
	{
		if (_users[i]->getUsername() == username)
		{
			delete _users[i];
			_users[i] = nullptr;
			swap(_users[i], _users[_size - 1]);
			_size--;
			break;
		}
	}
}

size_t UserContext::getSize() const {
	return _size;
}


bool UserContext::isEmpty() const {
	return _size == 0;
}


const User* UserContext::operator[](size_t index) const {
	if (index > _size)
		throw std::out_of_range(UserContextNS::OUT_OF_RANGE_ERROR.c_str());
	return _users[index];
}


User* UserContext:: operator[](size_t index) {
	if (index > _size)
		throw std::out_of_range(UserContextNS::OUT_OF_RANGE_ERROR.c_str());
	return _users[index];
}
