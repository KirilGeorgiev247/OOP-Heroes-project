#pragma once
#include <iostream>
#include <exception>
#include "swap.hpp"

namespace MyVectorNS {
	const size_t DEFAULT_CAPACITY = 8;
}

template <typename T>
class MyVector {
private:
	T* _array;
	size_t _size = 0;
	size_t _capacity = 0;
public:
	MyVector();
	MyVector(size_t capacity);
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);
	~MyVector();

	MyVector(MyVector&& other) noexcept;
	MyVector& operator=(MyVector&& other) noexcept;

private:
	void copyFrom(const MyVector& other);
	void free();
	void moveFrom(MyVector&& other);
	void resize(size_t capacity);

public:
	static size_t closestPowerOfTwo(size_t n);

	void pushBack(const T& newElem); //add a new element in the end
	void pushBack(T&& newElem); //add a new element in the end

	void popBack(); //removes the last element

	void setAtIndex(const T& element, size_t index);
	void setAtIndex(T&& element, size_t index);

	void removeAtIndex(size_t index);

	void empty();

	bool contains(const T& obj) const;

	size_t getSize() const;
	bool isEmpty() const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);
};

template <typename T>
size_t MyVector<T>::closestPowerOfTwo(size_t n)
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

template <typename T>
void MyVector<T>::copyFrom(const MyVector<T>& other) {
	_array = new T[other._capacity];

	for (size_t i = 0; i < other._size; ++i)
		_array[i] = other._array[i];

	_size = other._size;
	_capacity = other._capacity;
}

template <typename T>
void MyVector<T>::free() {
	delete[] _array;
}

template <typename T>
void MyVector<T>::resize(size_t capacity) {
	T* temp = _array;
	_capacity = capacity;
	_array = new T[_capacity];

	for (size_t i = 0; i < _size; ++i)
		_array[i] = temp[i];

	delete[] temp;
}

template <typename T>
void MyVector<T>::moveFrom(MyVector<T>&& other) {
	_array = other._array;
	_size = other._size;
	_capacity = other._capacity;
	other._array = nullptr;
	other._size = 0;
	other._capacity = 0;
}

template<typename T>
MyVector<T>::MyVector()
	: MyVector(MyVectorNS::DEFAULT_CAPACITY) {}

template <typename T>
MyVector<T>::MyVector(size_t capacity)
	: _size(0) {
	_capacity = closestPowerOfTwo(capacity);
	_array = new T[_capacity];
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other) {
	copyFrom(other);
}

template <typename T>
MyVector<T>& MyVector<T>::operator= (const MyVector<T>& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
MyVector<T>::~MyVector() {
	free();
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept {
	moveFrom(std::move(other));
}

template <typename T>
MyVector<T>& MyVector<T>::operator= (MyVector<T>&& other) noexcept {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
void MyVector<T>::pushBack(const T& newElem) {
	if (_size >= _capacity)
		resize(_capacity * 2);

	_array[_size++] = newElem;
}

template <typename T>
void MyVector<T>::pushBack(T&& newElem) {
	if (_size == _capacity)
		resize(_capacity * 2);

	_array[_size++] = std::move(newElem);
}

template <typename T>
void MyVector<T>::popBack() {
	if (_size)
		_size--;
	else
		throw std::length_error("Already empty!");

	if (_size * 4 <= _capacity && _capacity > 1)
		resize(_capacity / 2);
}

template <typename T>
void MyVector<T>::empty() {
	for (size_t i = 0; i < _size; i++)
		popBack();
}

template <typename T>
void MyVector<T>::setAtIndex(const T& element, size_t index) {
	if (index >= _size)
		throw std::length_error("No such index!");

	_array[index] = element;
}

template <typename T>
void MyVector<T>::setAtIndex(T&& element, size_t index) {
	if (index >= _size)
		throw std::length_error("No such index!");

	_array[index] = std::move(element);
}

template <typename T>
void MyVector<T>::removeAtIndex(size_t index) {
	swap(_array[index], _array[_size - 1]);
	popBack();
}

template <typename T>
bool MyVector<T>::contains(const T& obj) const {
	for (size_t i = 0; i < _size; i++)
	{
		if (_array[i] == obj)
			return true;
	}
	
	return false;
}

template <typename T>
size_t MyVector<T>::getSize() const {
	return _size;
}

template <typename T>
bool MyVector<T>::isEmpty() const {
	return _size == 0;
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
	if (index > _size)
		throw std::out_of_range("Out of range!");
	return _array[index];
}

template <typename T>
T& MyVector<T>:: operator[](size_t index) {
	if (index > _size)
		throw std::out_of_range("Out of range!");
	return _array[index];
}