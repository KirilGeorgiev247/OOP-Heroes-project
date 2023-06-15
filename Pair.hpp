#pragma once
#include <iostream>

template <typename T, typename S>
class Pair {
private:
	T _first;
	S _second;

public:
	Pair() = default;
	Pair(const T& first, const S& second);

	const T& getFirst() const;
	const S& getSecond() const;

	void setFirst(const T& first);
	void setFirst(T&& first);
	void setSecond(const S& second);
	void setSecond(S&& second);
};

template <typename T, typename S>
Pair<T, S>::Pair(const T& first, const S& second) {
	_first = first;
	_second = second;
}

template <typename T, typename S>
const T& Pair<T, S>::getFirst() const {
	return _first;
}

template <typename T, typename S>
const S& Pair<T, S>::getSecond() const {
	return _second;
}

template <typename T, typename S>
void Pair<T, S>::setFirst(const T& first) {
	_first = first;
}

template <typename T, typename S>
void Pair<T, S>::setFirst(T&& first) {
	_first = std::move(first);
}

template <typename T, typename S>
void Pair<T, S>::setSecond(const S& second) {
	_second = second;
}

template <typename T, typename S>
void Pair<T, S>::setSecond(S&& second) {
	_second = std::move(second);
}

