//
// Created by HUAWEI on 06.12.2023.
//

#ifndef MAINSOLUTION_CLASSES_H
#define MAINSOLUTION_CLASSES_H
#include <iostream>
#include <list>
#include <unordered_set>
#include "../exceptions/exceptions.h"

using namespace std;

class AbstractTreasure{
private:
    string title;
    float countOfGold;
public:
    AbstractTreasure(const string &title, float countOfGold) : title(title), countOfGold(countOfGold) {}

    const string &getTitle() const {
        return title;
    }

    void setTitle(const string &title) {
        this->title = title;
    }

    float getCountOfGold() const {
        return countOfGold;
    }

    void setCountOfGold(float countOfGold) {
        this->countOfGold = countOfGold;
    }

};
class Player;
class Achievement{
private:
    string title;
public:
    explicit Achievement(const string &title) : title(title) {}

    const string &getTitle() const {
        return title;
    }

    void setTitle(const string &title) {
        this->title = title;
    }
    virtual void setNewGold (Player * player) = 0;
    virtual void addAchivement(Player * player) = 0;
};
class Player{
private:
    string nameOfHero;
    string password;
    list<AbstractTreasure*> treasures;
    unordered_set<Achievement*> achievements;
    float attack;
    float countOfGold;
public:
    Player(const string &nameOfHero, const string &password, float attack, float countOfGold) :
    nameOfHero(nameOfHero), password(password), attack(attack), countOfGold(countOfGold) {
        countOfGold = 0;
        attack = 100;
    }

    const string &getNameOfHero() const {
        return nameOfHero;
    }

    void setNameOfHero(const string &nameOfHero) {
        this->nameOfHero = nameOfHero;
    }

    const string &getPassword() const {
        return password;
    }

    void setPassword(const string &password) {
        this->password = password;
    }

    const list<AbstractTreasure *> &getTreasures() const {
        return treasures;
    }

    void setTreasures(const list<AbstractTreasure *> &treasures) {
        this->treasures = treasures;
    }

    const unordered_set<Achievement *> &getAchievements() const {
        return achievements;
    }

    void setAchievements(const unordered_set<Achievement *> &achievements) {
        this->achievements = achievements;
    }

    float getCountOfGold() const {
        return countOfGold;
    }

    void setCountOfGold(float countOfGold) {
        this->countOfGold = countOfGold;
    }

};
class KilledMobAchievement : Achievement{
private:
    float countOfGold;
public:
    KilledMobAchievement(const string &title, float countOfGold) : Achievement(title), countOfGold(countOfGold) {}

    void showMessage(){
        cout << "Congrats you killed your first mob!" << endl;
    }
    void setNewGold(Player *player) override {
        player->setCountOfGold(player->getCountOfGold() + countOfGold);
    }

    void addAchivement(Player *player) override {
        auto achievements = player->getAchievements();
        if(!(achievements.find(this) == achievements.end())){
            achievements.insert(this);
        } else{
            throw NotUniqueAchievementException("Achievement already exists");
        }
    }
};
class FirstTreasureAchievement : Achievement{
private:
    float countOfGold;
public:
    FirstTreasureAchievement(const string &title, float countOfGold) : Achievement(title), countOfGold(countOfGold) {}

    void showMessage(){
        cout << "Congrats you got your first treasure!!" << endl;
    }
    void setNewGold(Player *player) override {
        player->setCountOfGold(player->getCountOfGold() + countOfGold);
    }
    void addAchivement(Player *player) override {
        auto achievements = player->getAchievements();
        if(!(achievements.find(this) == achievements.end())){
            achievements.insert(this);
        } else{
            throw NotUniqueAchievementException("Achievement already exists");
        }
    }
};
class Enemy{
private:
    string name;
    float healthPoints;

};
#endif //MAINSOLUTION_CLASSES_H
