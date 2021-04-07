#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Object.h"
#include "NPC.h"
#include "Item.h"

using namespace std;

class Room : public Object
{
private:
    Room* upRoom;
    Room* downRoom;
    Room* leftRoom;
    Room* rightRoom;
    bool isExit;
    int index;
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
public:
    Room();
    Room(bool, int, vector<Object*>);
    bool popObject(Object*); /*pop out the specific object, used when the interaction is done*/
    // e.g. monster is dead, NPC leave...
    void listMember(ofstream& );
    void loadMember(ifstream& );
    bool triggerEvent(Object* );

    /* Set & Get function*/
    void setUpRoom(Room*);
    void setDownRoom(Room*);
    void setLeftRoom(Room*);
    void setRightRoom(Room*);
    void setIsExit(bool);
    void setIndex(int);
    void setObjects(vector<Object*>);
    bool getIsExit();
    int getIndex();
    vector<Object*> getObjects();
    Room* getUpRoom();
    Room* getDownRoom();
    Room* getLeftRoom();
    Room* getRightRoom();
};

#endif // ROOM_H_INCLUDED
