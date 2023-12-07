#include <iostream>
#include "domain/classes.h"
#include "utils/additionalFunctions.h"
#include <cstdlib>

using namespace std;
void startGame(Game* game){
    int index;
    do{
        menu();
        cout << "Your option : ";
        index = getNum();
        switch (index) {
            case 1:{
                game->startFight();
                break;
            }
            case 2:{
                game->showAchievements();
                break;
            }
            case 3: {
                game->getPlayer()->showTreasures();
                break;
            }
            case 4:{
                game->getPlayer()->infoPlayer();
                break;
            }
            case 5:{
                cout << "End of the game" << endl;
                break;
            }
        }
    } while (index != 5);
}
int main(){
    srand ( time(NULL) );
    Chest chest = Chest("chest", 200);
    Wallet wallet = Wallet("wallet", 40);
    list<AbstractTreasure* > list;
    Orc orc = Orc("Orc", 200, 25);
    Magician magician = Magician("Greate-Magician", 100, 40);
    MagicianBoss boss = MagicianBoss("Boss-Alkadur", 400, 150);
    unordered_set<int> achievement;
    Player player("Vlad", list, achievement,  0);

    map<int, AbstractTreasure*> treasures;
    treasures.insert(pair<int, AbstractTreasure *>(1, &chest));
    treasures.insert(pair<int, AbstractTreasure *>(2, &wallet));
    map<int, Enemy*> enemies;
    enemies.insert(pair<int, Enemy*>(1, &magician));
    enemies.insert(pair<int, Enemy*>(2, &orc));
    enemies.insert(pair<int, Enemy*>(3, &boss));
    map<int, Achievement*> achievements;
    KilledMobAchievement killed("You killed your first mob!" , 200, 1);
    FirstTreasureAchievement treasure("First treasure!", 100, 2);
    achievements.insert(pair<int, Achievement*>(1, &killed));
    achievements.insert(pair<int, Achievement*>(2, &treasure));
    Game game(treasures, enemies, achievements ,&player);

    startGame(&game);
    return 0;
}
