//
// Created by HUAWEI on 06.12.2023.
//

#ifndef MAINSOLUTION_CLASSES_H
#define MAINSOLUTION_CLASSES_H

#include <iostream>
#include <list>
#include <unordered_set>
#include <map>

#include "../exceptions/exceptions.h"
#include "../utils/additionalFunctions.h"

using namespace std;

class Player;

class AbstractTreasure {
private:
    string title;
    float countOfGold;
public:
    AbstractTreasure(const string &title, float countOfGold) : title(title), countOfGold(countOfGold) {}

    virtual void info() = 0;

    virtual void showAfterVictory() = 0;

    float getCountOfGold() const {
        return countOfGold;
    }

    void setCountOfGold(float countOfGold) {
        this->countOfGold = countOfGold;
    }

};

class Chest : public AbstractTreasure {
public:
    Chest(const string &title, float countOfGold) : AbstractTreasure(title, countOfGold) {}

    void info() override {
        cout << "You have chest ! " << endl;
    }

    void showAfterVictory() override {
        cout << "You have won chest ! " << endl;
    }
};

class Wallet : public AbstractTreasure {
public:
    Wallet(const string &title, float countOfGold) : AbstractTreasure(title, countOfGold) {}

    void info() override {
        cout << "You have simple wallet " << endl;
    }

    void showAfterVictory() override {
        cout << "You have won simple wallet after victory !" << endl;
    }
};

class Achievement {
protected:
    string title;
    float countOfGold;
    bool exists;
public:
    Achievement(const string &title, float countOfGold, bool exists) : title(title), countOfGold(countOfGold),
                                                                       exists(exists) {}

    float getCountOfGold() const {
        return countOfGold;
    }

    bool getExists() const {
        return exists;
    }

    void setExists(bool exists) {
        this->exists = exists;
    }

    virtual void showMessageAfterVictory() = 0;

    virtual void infoAchievement() = 0;
};

class KilledMobAchievement : public Achievement {
public:
    KilledMobAchievement(const string &title, float countOfGold, bool exists) : Achievement(title, countOfGold,
                                                                                            exists) {}

    void showMessageAfterVictory() override {
        cout << "New Achievement !!! " << title << ". for that we give you " << countOfGold << endl;
    }

    void infoAchievement() override {
        cout << title << " . for that you earned : " << countOfGold << endl;
    }

};

class FirstTreasureAchievement : public Achievement {
public:
    FirstTreasureAchievement(const string &title, float countOfGold, bool exists) : Achievement(title, countOfGold,
                                                                                                exists) {}

    void showMessageAfterVictory() override {
        cout << "New Achievement !!! " << title << " Аor that we give you " << countOfGold << endl;
    }

    void infoAchievement() override {
        cout << title << " For that you earned : " << countOfGold << endl;
    }
};

class Enemy {
private:
    string name;
    float countOfGold;
protected:
    float healthPoints;
public:
    Enemy(const string &name, float healthPoints, float countOfGold) : name(name), healthPoints(healthPoints),
                                                                       countOfGold(countOfGold) {}

    virtual void description() = 0;

    float getHealthPoints() const {
        return healthPoints;
    }

    void setHealthPoints(float healthPoints) {
        Enemy::healthPoints = healthPoints;
    }

    float getCountOfGold() const {
        return countOfGold;
    }

    const string &getName() const {
        return name;
    }
};

class Orc : public Enemy {
public:
    Orc(const string &name, float healthPoints, float countOfGold) : Enemy(name, healthPoints, countOfGold) {}

    void description() override {
        cout << "Orc has arrived !!!! His health : " << healthPoints << endl;
    }

    void showHealth() {
        cout << "Orc's health : " << Enemy::getHealthPoints() << endl;
    }

};

class Magician : public Enemy {
public:
    Magician(const string &name, float healthPoints, float countOfGold) : Enemy(name, healthPoints, countOfGold) {}

    void description() override {
        cout << "Magician has arrived !!!! His health : " << healthPoints << endl;
    }

    void showHealth() {
        cout << "Magician's health : " << Enemy::getHealthPoints() << endl;
    }
};

class MagicianBoss : public Magician {
public:
    MagicianBoss(const string &name, float healthPoints, float countOfGold) : Magician(name, healthPoints,
                                                                                       countOfGold) {
        healthPoints *= 2;
    }

    void description() override {
        cout << "Magician BOSS has arrived !!!! His health : " << healthPoints << endl;
    }

    void showHealth() {
        cout << "Magician's health : " << getHealthPoints() << endl;
    }
};

class Player {
private:
    string nameOfHero;
    list<AbstractTreasure *> treasures;
    unordered_set<Achievement *> achievements;
    float countOfGold;
public:
    Player(const string &nameOfHero, const list<AbstractTreasure *> &treasures,
           const unordered_set<Achievement *> &achievements, float countOfGold) :
            nameOfHero(nameOfHero), treasures(treasures), achievements(achievements), countOfGold(countOfGold) {}


    const unordered_set<Achievement *> &getAchievements() const {
        return achievements;
    }

    float getCountOfGold() const {
        return countOfGold;
    }

    void setCountOfGold(float countOfGold) {
        this->countOfGold = countOfGold;
    }

    void addAchievement(Achievement *achievement) {
        if (achievements.count(achievement) == 0 || !achievement->getExists()) {
            achievement->showMessageAfterVictory();
            achievement->setExists(true);
            // ПЕРЕЗАПИСЫВАЕТ ДУБЛИКАТ БЛЯ
            achievements.insert(achievement);
            countOfGold += achievement->getCountOfGold();
        } else {
            throw NotUniqueAchievementException("");
        }
    }

    void addTreasure(AbstractTreasure *treasure) {
        treasures.push_back(treasure);
    }

    void infoPlayer() {
        cout << "Name of the player : " << nameOfHero << endl;
        cout << "Current count of gold : " << countOfGold << endl;
        cout << "Current treasures : " << treasures.size() << endl;
    }

    void showTreasures() {
        if (treasures.empty()) {
            cout << "Nothing to show : no treasures ! " << endl;
        } else {
            for (auto &tres: treasures) {
                tres->info();
            }
        }
    }

    void showAchievements() {
        // TODO FILE
        if (!achievements.empty()) {
            cout << "You have " << achievements.size() << " achievements" << endl;
        } else {
            cout << "No achievements ! " << endl;
        }
    }
};

class Game {
private:
    map<int, AbstractTreasure *> randomTreasure;
    map<int, Enemy *> randomEnemy;
    Player *player;
public:
    Game(const map<int, AbstractTreasure *> &randomTreasure, const map<int, Enemy *> &randomEnemy, Player *player)
            : randomTreasure(randomTreasure), randomEnemy(randomEnemy), player(player) {}

    Player *getPlayer() const {
        return player;
    }

    void startFight() {
        int keyOfEnemy = makeRandom(1, randomEnemy.size());
        auto enemy = randomEnemy.find(keyOfEnemy)->second;
        enemy->description();
        float healthOfeEnemy = enemy->getHealthPoints();
        while (healthOfeEnemy > 0) {
            cout << "Write number to hit!" << endl;
            float attack = (float) getNum();
            healthOfeEnemy -= attack;
            cout << "Current health of enemy : " << healthOfeEnemy << endl;
        }
        cout << "You won!!! Congratilations ! " << endl;
        cout << "For that mob you earned " << enemy->getCountOfGold() << " coins" << endl;
        player->setCountOfGold(player->getCountOfGold() + enemy->getCountOfGold());
        if (player->getAchievements().empty()) {
            KilledMobAchievement achievement("First killed mob!", 200, false);
           try{
               player->addAchievement(&achievement);
           } catch (NotUniqueAchievementException& ex){
               ex.what();
           }
        }
        if (enemy->getName() == "Boss-Alkadur") {
            cout << "You killed boss !!" << endl;
            int key = makeRandom(1, randomTreasure.size());
            auto treasure = randomTreasure.find(key)->second;
            treasure->showAfterVictory();
            player->addTreasure(treasure);
            FirstTreasureAchievement first("First treasure ! ", 400, false);
            try{
                player->addAchievement(&first);
            } catch (NotUniqueAchievementException& ex){
                ex.what();
            }
        }
    }
};

#endif //MAINSOLUTION_CLASSES_H
