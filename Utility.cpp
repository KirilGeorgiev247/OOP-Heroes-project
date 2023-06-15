#include "Utility.h"

bool Utility::hasLowerLetter(const MyString& str) {
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			return true;
	}

	return false;
}

bool Utility::hasUpperLetter(const MyString& str) {
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			return true;
	}

	return false;
}

bool Utility::hasDigit(const MyString& str) {
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			return true;
	}

	return false;
}

bool Utility::hasOnlySmallLetters(const MyString& str) {
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] < 'a' || str[i] > 'z')
			return false;
	}

	return true;
}

size_t Utility::getRandomNumberInRange(size_t num) {
	srand((unsigned int)time(NULL));

	return rand() % num;
}