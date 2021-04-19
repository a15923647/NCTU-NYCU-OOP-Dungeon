#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"
#include "Skill.h"
using namespace std;

class Skill;
class Monster: public GameCharacter
{
private:
    int attribute_id;
public:
    Monster();
    Monster(string,int,int,int);

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*);
    void listMember(ofstream& );
    void loadMember(ifstream& );
    void reset( Monster& );
    int getAtt();
    void setAtt(int);
	
	  friend ostream& operator <<(ostream& , const Monster& );
};


#endif // ENEMY_H_INCLUDED
