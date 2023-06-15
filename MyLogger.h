#pragma once
#include <iostream>
#include "MyString.h"
#include "Hero.h"

class MyLogger {
private:
	static MyLogger* _instance;
	MyLogger();

public:
	MyLogger(const MyLogger&) = delete;
	MyLogger& operator=(const MyLogger&) = delete;
	MyLogger(MyLogger&&) = delete;
	MyLogger& operator=(MyLogger&&) = delete;

	static MyLogger* getInstance();
	static void deleteInstance();

	void print(const MyString& content) const;
	void print(const char* content) const;
	void print(char content) const;
	void print(const Hero& content) const;
	void print(size_t content) const;
	void newLine() const;
};

