#pragma once

struct Enums {
	enum class UserType {
		Admin,
		Player
	};

	enum class HeroType {
		Fire = 0,
		Earth = 1,
		Water = 2,
	};

	enum class State {
		Attack = 0,
		Defence = 1,
		NotSet = 2,
	};
};