#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"
#include "Level.h"
#include "Skill.h"

using namespace std;
class Item;
class Skill;
class Level;
class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
    vector<Skill> skills;
    int coin;
    int mp;
    int mpMax;
    Level* level;
public:
    Player();
    Player(string,int,int,int);
    void addItem(Item);
    void increaseStates(int,int,int,int);//h a d mp
    void raiseBound(int,int);
    void changeRoom(Room*);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*);
    void listMember(ofstream& );
    void loadMember(ifstream& );

    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item>);
    void setSkills(vector<Skill>);
    void setCoin(int);
    void setMp(int);
    void addSkill(Skill);
    void calMpMax();
    void heal();//reset mp and hp
    void consumeMp(int);
    void popProp(Item*);
    void updateProp(vector<Item*>);
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Item>& getInventory();
    int getCoin();
    int getMp();
    int getMpMax();
    vector<Skill> getSkills();
    Level* getLevelO();
    friend ostream& operator <<(ostream& , const Player& );
    void showMoreInfo();
};

#endif // PLAYER_H_INCLUDED
