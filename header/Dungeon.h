#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <fstream>
#include <cstdlib>
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"
#include "Record.h"
#include "Object.h"
#include "Skill.h"

using namespace std;

class Dungeon{
private:
    Player player;
    Record record;
    vector<Room> rooms;
    vector<Skill> skill_repo;
public:
    Dungeon();
    /* Create a new player, and give him/her basic status */
    void createPlayer(string name);

    /* Create a map, which include several different rooms */
    void createMap();

    /* Deal with player's moveing action */
    void handleMovement();

    /* Deal with player's iteraction with objects in that room */
    void handleEvent(Object*);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();

    /* Deal with the player's action     */
    /* including showing the action list */
    /* that player can do at that room   */
    /* and dealing with player's input   */
    void chooseAction(Room* ,vector<Object*>);

    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();

    /* Deal with the whole game process */
    void runDungeon();

    void showWelcomeMenu();

    void handleCommunicate(vector<Object*>);

    void handleAttack(Room*, vector<Object*>);

    void handleExplore(Room*, vector<Object*>);
    
    void learnSkills();

};


#endif // DUNGEON_H_INCLUDED
