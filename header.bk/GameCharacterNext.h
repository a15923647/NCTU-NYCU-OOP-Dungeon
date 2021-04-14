#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include "Object.h"
using namespace std;

class GameCharacter: public Object
{
private:
    string name;
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
	int level;
    int mp;
	int xp;
	int xp_max;
	double dodge_rate;
	double cstrike_rate;//critical strike rate
public:
    GameCharacter();
    GameCharacter(string,string,int,int,int);
    bool checkIsDead();
    int takeDamage(int);
    bool triggerEvent(Object* );
    void listMember(ofstream& );
    void loadMember(ifstream& );
	
    /* Set & Get function*/
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setAttack(int);
    void setDefense(int);
	void setDodge(double);
	void setCstrike(double);
    void setLevel(int);
    void setGameCharacter(string, string , int, int , int);
    int getMaxHealth();
    int getCurrentHealth();
    int getAttack();
    int getDefense();
    int getLevel();
    double getDodge();
    double getCstrile();
    
    int setXpMax(int);//a function return the xp max of this level
};
#endif // GAMECHARACTER_H_INCLUDED
