#pragma once
#include "MyString.h"
#include "System.h"
#include "MyLogger.h"

namespace CommandHandlerNS {
	const MyString ADMINISTRATOR_SIGN_IN_CMND = "sign in as administrator";
	const MyString PLAYER_SIGN_IN_CMND = "sign in as player";
	const MyString ADD_NEW_PLAYER_CMND = "add new player";
	const MyString ADD_NEW_ADMIN_CMND = "add new admin";
	const MyString DELETE_PLAYER_CMND = "delete player";
	const MyString SHOW_USERS_CMND = "show users";
	const MyString SHOW_PLAYERS_CMND = "show players";
	const MyString ADD_HERO_CMND = "add new hero";
	const MyString ADD_HERO_FROM_SOLD_CMND = "return sold hero";
	const MyString DELETE_MY_PROFILE_CMND = "delete my profile";
	const MyString SHOW_MARKET_CMND = "show market";
	const MyString BUY_HERO_CMND = "buy hero";
	const MyString LOG_OUT_CMND = "log out";
	const MyString SET_TO_DEFENCE_CMND = "set to defence";
	const MyString SET_TO_ATTACK_CMND = "set to attack";
	const MyString ATTACK_PLAYER_CMND = "attack";
	const MyString ATTACK_PLAYER_RANDOM_CMND = "attack random";

	const MyString SHOW_RANKING_CMND = "show ranking";
	const MyString SHOW_BALANCE_CMND = "show balance";

	const MyString ENTER_FIRSTNAME = "Enter firstname: ";
	const MyString ENTER_LASTNAME = "Enter lastname: ";
	const MyString ENTER_USERNAME = "Enter username: ";
	const MyString ENTER_EMAIL = "Enter email: ";
	const MyString ENTER_PASSWORD = "Enter password: ";
	const MyString ENTER_USERNAME_FOR_DELETED_PLAYER = "Enter username for deleted player: ";

	const MyString ENTER_NICKNAME = "Enter nickname: ";
	const MyString ENTER_POWER_TYPE = "Enter power type: ";
	const MyString ENTER_POWER_RATE = "Enter power rate: ";
	const MyString ENTER_PRICE = "Enter price: ";

	const MyString ENTER_ATTACKING_SUPERHERO = "Enter superhero you want to attack with: ";
	const MyString ENTER_ATTACKED_SUPERHERO = "Enter superhero you want to attack: ";
	const MyString ENTER_NICKNAME_OF_HERO_TO_RETURN = "Enter nickname of the hero you want to return: ";

	const MyString SUCCESS_LOGIN_MESSAGE_ADMIN = "You have logged in as administrator!";

	const MyString SUCCESS_LOGIN_MESSAGE_PLAYER = "You have logged in as player!";

	const MyString UNSUCCESS_LOGOUT_ERROR = "Noone is logged in!";
	const MyString UNSUCCESS_LOGIN_ERROR = "Unsuccessful login!";
	const MyString NOT_VALID_HERO_TYPE_ERROR = "Not a valid hero type";
	const MyString NOT_ENOUGH_USERS_ERROR = "Default admin has to login and create other users!";
	const MyString NOT_ENOUGH_HEROES_ERROR = " Not enough available heroes (3) on the market! Admin should log out and add heroes";

	const MyString NO_SUCH_COMMAND_ERROR = "No such command";

	const size_t BUFF_SIZE = 1024;
}

class CommandHandler {
private:
	static CommandHandler* _instance;
	MyLogger* _logger = MyLogger::getInstance();

	System* _system;
	bool isAdminLoggedIn = false;

	void getCredentials(MyString& username, MyString& password);
	void getUserInfo(MyString& firstname, MyString& lastname, MyString& email);
	void getHeroInfo(MyString& firstname, MyString& lastname,
		MyString& nickname, Enums::HeroType& powerType,
		size_t& powerRate, size_t& price);
	CommandHandler();
	~CommandHandler();
public:
	CommandHandler(const CommandHandler&) = delete;
	CommandHandler(CommandHandler&&) = delete;
	CommandHandler& operator=(const CommandHandler&) = delete;
	CommandHandler& operator=(CommandHandler&&) = delete;

	static CommandHandler* getInstance();

	static void deleteCommandHandler();

	void execute(const MyString& command);

	bool signInAsAdmin();
	void signInAsPlayer();
	void addNewPlayer();
	void addNewAdmin();
	void deletePlayer();
	void addNewHero();
	void returnSoldHeroToAvailable();
	void deleteCurrProfile();
	void buyHero();
	void logOut();
	void setHeroState(Enums::State state);
	void startAttack(bool isRandom);

	void showRankings() const;
	void showBalance() const;
	void showUsers() const;
	void showMarket() const;
	void showPlayers() const;
};

