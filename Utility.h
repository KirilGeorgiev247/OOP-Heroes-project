#pragma once
#include "MyString.h"

struct Utility {
public:
	static bool hasLowerLetter(const MyString& str);

	static bool hasUpperLetter(const MyString& str);

	static bool hasDigit(const MyString& str);

	static bool hasOnlySmallLetters(const MyString& str);

	static size_t getRandomNumberInRange(size_t num);
};

