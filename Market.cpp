#include "Market.h"

Market* Market::_instance = nullptr;

Market* Market::getInstance() {
    if (_instance == nullptr) 
        _instance = new Market();
    return _instance;
}

void Market::deleteMarket() {
    delete _instance;
}

Market::Market() {
    seed();
}

void Market::seed() {
    addHero(MarketNS::DEFAULT_HERO_FIRSTNAME_1, MarketNS::DEFAULT_HERO_LASTNAME_1, MarketNS::DEFAULT_HERO_NICKNAME_1, MarketNS::DEFAULT_HERO_POWERTYPE_1,
        MarketNS::DEFAULT_HERO_POWERRATE_1, MarketNS::DEFAULT_HERO_PRICE_1, Enums::State::NotSet);

    addHero(MarketNS::DEFAULT_HERO_FIRSTNAME_2, MarketNS::DEFAULT_HERO_LASTNAME_2, MarketNS::DEFAULT_HERO_NICKNAME_2, MarketNS::DEFAULT_HERO_POWERTYPE_2,
        MarketNS::DEFAULT_HERO_POWERRATE_2, MarketNS::DEFAULT_HERO_PRICE_2, Enums::State::NotSet);

    addHero(MarketNS::DEFAULT_HERO_FIRSTNAME_3, MarketNS::DEFAULT_HERO_LASTNAME_3, MarketNS::DEFAULT_HERO_NICKNAME_3, MarketNS::DEFAULT_HERO_POWERTYPE_3,
        MarketNS::DEFAULT_HERO_POWERRATE_3, MarketNS::DEFAULT_HERO_PRICE_3, Enums::State::NotSet);

    addHero(MarketNS::DEFAULT_HERO_FIRSTNAME_4, MarketNS::DEFAULT_HERO_LASTNAME_4, MarketNS::DEFAULT_HERO_NICKNAME_4, MarketNS::DEFAULT_HERO_POWERTYPE_4,
        MarketNS::DEFAULT_HERO_POWERRATE_4, MarketNS::DEFAULT_HERO_PRICE_4, Enums::State::NotSet);

    addHero(MarketNS::DEFAULT_HERO_FIRSTNAME_5, MarketNS::DEFAULT_HERO_LASTNAME_5, MarketNS::DEFAULT_HERO_NICKNAME_5, MarketNS::DEFAULT_HERO_POWERTYPE_5,
        MarketNS::DEFAULT_HERO_POWERRATE_5, MarketNS::DEFAULT_HERO_PRICE_5, Enums::State::NotSet);
}

const MyVector<Hero>& Market::getAvailableHeroes() const {
    return _availableHeroes;
}

const MyVector<Hero>& Market::getSoldHeroes() const {
    return _soldOutHeroes;
}

void Market::addHero(const MyString& firstname, const MyString& lastname, const MyString& nickname,
    Enums::HeroType type, size_t powerRate, size_t price, Enums::State state) {
    _availableHeroes.pushBack(Hero(firstname, lastname, nickname, type, powerRate, price, state));
}

void Market::returnSoldHeroByNickname(const MyString& nickname) {
    int ind = -1;
    for (size_t i = 0; i < _soldOutHeroes.getSize(); i++)
    {
        if (_soldOutHeroes[i].getNickname() == nickname)
            ind = i; break;
    }

    if (ind != -1)
    {
        _availableHeroes.pushBack(_soldOutHeroes[ind]);
        _soldOutHeroes.removeAtIndex(ind);
    }
    else
        throw std::logic_error(MarketNS::INVALID_NICKNAME_ERROR.c_str());
}

int Market::getIndexOfHeroByNickname(const MyString& nickname) const {
    for (size_t i = 0; i < _availableHeroes.getSize(); i++)
    {
        if (_availableHeroes[i].getNickname() == nickname)
            return i;
    }
    return -1;
}

const Hero& Market::getHeroByIndex(size_t index) const {
    return _availableHeroes[index];
}

void Market::removeHeroByIndex(size_t index) {
    _availableHeroes.removeAtIndex(index);
}