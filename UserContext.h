#pragma once
#include <iostream>
#include <exception>
#include "Player.h"
#include "Admin.h"
#include "User.h"
#include "Enums.h"
#include "UserFactory.h"

namespace UserContextNS {
	const size_t DEFAULT_CAPACITY = 8;
	const MyString OUT_OF_RANGE_ERROR = "Out of range!";
}

class UserContext {
private:
	User** _users;
	size_t _size;
	size_t _capacity;
public:
	UserContext();
	UserContext(size_t capacity);
	UserContext(const UserContext& other);
	UserContext& operator=(const UserContext& other);
	~UserContext();

	UserContext(UserContext&& other) noexcept;
	UserContext& operator=(UserContext&& other) noexcept;

private:
	void copyFrom(const UserContext& other);
	void free();
	void moveFrom(UserContext&& other) noexcept;
	void resize(size_t capacity);
public:

	void createUser(const MyString& firstName, const MyString& lastName, const MyString& email, 
		const MyString& username, const MyString& password, Enums::UserType type);

	void removeByUsername(const MyString& username);

	size_t getSize() const;
	bool isEmpty() const;

	const User* operator[](size_t index) const;
	User* operator[](size_t index);
};