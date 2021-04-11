#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class Monster: public GameCharacter
{
private:
public:
    Monster();
    Monster(string,int,int,int);

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*);
    void listMember(ofstream& );
    void loadMember(ifstream& );
};


#endif // ENEMY_H_INCLUDED