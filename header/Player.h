#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;
class Item;
class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
    int coin;
public:
    Player();
    Player(string,int,int,int);
    void addItem(Item);
    void increaseStates(int,int,int);
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
    void setCoin(int);
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Item> getInventory();
    int getCoin();
    friend ostream& operator <<(ostream& , const Player& );
};

#endif // PLAYER_H_INCLUDED
