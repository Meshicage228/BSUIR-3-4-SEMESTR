#ifndef MAINSOLUTION_CLASSES_H
#define MAINSOLUTION_CLASSES_H
#include <iostream>
#include <list>
#include <unordered_set>
#include <map>
#include <fstream>
#include "../exceptions/exceptions.h"
#include "../utils/additionalFunctions.h"

using namespace std;
fstream fout;
class Player;

class AbstractTreasure {
private:
    string title;
    float countOfGold;
public:
    AbstractTreasure(const string &title, float countOfGold) : title(title), countOfGold(countOfGold) {}

    virtual void info() = 0;

    virtual void showAfterVictory() = 0;
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
    int numericalOrder;
public:
    Achievement(const string &title, float countOfGold, int numericalOrder) : title(title), countOfGold(countOfGold),
                                                                              numericalOrder(numericalOrder) {}

    float getCountOfGold() const {
        return countOfGold;
    }

    int getNumericalOrder() const {
        return numericalOrder;
    }

    virtual void showMessageAfterVictory() = 0;

    virtual void infoAchievement() = 0;
};

class KilledMobAchievement : public Achievement {
public:
    KilledMobAchievement(const string &title, float countOfGold, int numericalOrder) : Achievement(title, countOfGold,
                                                                                                   numericalOrder) {}

    void showMessageAfterVictory() override {
        cout << "New Achievement !!! " << title << ". for that we give you " << countOfGold << endl;
    }

    void infoAchievement() override {
        cout << title << " For that you earned : " << countOfGold << endl;
    }

};

class FirstTreasureAchievement : public Achievement {
public:
    FirstTreasureAchievement(const string &title, float countOfGold, int numericalOrder) : Achievement(title,
                                                                                                       countOfGold,
                                                                                                       numericalOrder) {}

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
};

class Player {
private:
    string nameOfHero;
    list<AbstractTreasure *> treasures;
    unordered_set<int> achievements;
    float countOfGold;
public:
    Player(const string &nameOfHero, const list<AbstractTreasure *> &treasures, const unordered_set<int> &achievements,
           float countOfGold) : nameOfHero(nameOfHero), treasures(treasures), achievements(achievements),
                                countOfGold(countOfGold) {}


    const unordered_set<int> &getAchievements() const {
        return achievements;
    }

    float getCountOfGold() const {
        return countOfGold;
    }

    void setCountOfGold(float countOfGold) {
        this->countOfGold = countOfGold;
    }

    void addAchievement(Achievement *achievement) {
            achievement->showMessageAfterVictory();
            achievements.insert(achievement->getNumericalOrder());
            countOfGold += achievement->getCountOfGold();
    }

    void addTreasure(AbstractTreasure *treasure) {
        treasures.push_back(treasure);
    }

    void infoPlayer() {
        fout.open("playerInfo.txt", ios::app);
        cout << "Name of the player : " << nameOfHero << endl;
        cout << "Current count of gold : " << countOfGold << endl;
        cout << "Current treasures : " << treasures.size() << endl;

        fout << "Name of the player : " << nameOfHero << endl;
        fout << "Current count of gold : " << countOfGold << endl;
        fout << "Current treasures : " << treasures.size() << endl;

        fout.close();
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
};

class Game {
private:
    map<int, AbstractTreasure *> randomTreasure;
    map<int, Enemy *> randomEnemy;
    map<int, Achievement*> achievements;
    Player *player;
public:
    Game(const map<int, AbstractTreasure *> &randomTreasure, const map<int, Enemy *> &randomEnemy,
         const map<int, Achievement *> &achievements, Player *player) : randomTreasure(randomTreasure),
                                                                        randomEnemy(randomEnemy),
                                                                        achievements(achievements), player(player) {}

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
            if(healthOfeEnemy > 0) {
                cout << "Current health of enemy : " << healthOfeEnemy << endl;
            }
        }
        cout << "You won!!! Congratilations ! " << endl;
        cout << "For that mob you earned " << enemy->getCountOfGold() << " coins" << endl;
        player->setCountOfGold(player->getCountOfGold() + enemy->getCountOfGold());
        if (player->getAchievements().empty()) {
            KilledMobAchievement achievement("First killed mob!", 200, 1);
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
            FirstTreasureAchievement first("First treasure ! ", 400, 2);
            try{
                player->addAchievement(&first);
            } catch (NotUniqueAchievementException& ex){
                ex.what();
            }
        }
    }
    void showAchievements() {
        if (!player->getAchievements().empty()) {
            for(auto& it : player->getAchievements()){
                auto achiv  = achievements.find(it)->second;
                achiv->infoAchievement();
            }
        } else {
            cout << "No achievements ! " << endl;
        }
    }
};
#endif
