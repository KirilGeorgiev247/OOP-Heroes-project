#include "MyLogger.h"

MyLogger* MyLogger::_instance = nullptr;

MyLogger::MyLogger() {}

MyLogger* MyLogger::getInstance() {
	if (_instance == nullptr)
		_instance = new MyLogger();
	return _instance;
}
void MyLogger::deleteInstance() {
	delete _instance;
}

void MyLogger::print(const MyString& content) const {
	std::cout << content;
}

void MyLogger::print(const char* content) const {
	std::cout << content;
}

void MyLogger::print(char content) const {
	std::cout << content;
}

void MyLogger::print(size_t content) const {
	std::cout << content;
}

void MyLogger::newLine() const {
	std::cout << std::endl;
}

void MyLogger::print(const Hero& content) const {
	std::cout << content;
}