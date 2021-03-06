#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Object.h"
#include "Player.h"//triggerEvent
using namespace std;

class Player;
class Item: public Object
{
private:
    int health, attack, defense, mp;
    int value;
    int durability;
    bool active, continuous;
    /*
      active: 
        true: like armour
        false: like potion
      continuous:
        only active items can have continuous attribute
        true: recover hp in every round
    */
public:
    Item();
    Item(ifstream&);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object*);

    void listMember(ofstream& );
    void loadMember(ifstream& );

    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    int getValue();
    int getDurability();
    int getMp();
    bool getActive();
    bool getContinuous();
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setValue(int);
    void setDurability(int);
    void setMp(int);
    void setActive(bool);
    void setContinuous(bool);
    void decDur(int);
    
    bool operator == (Item);
    friend ostream& operator <<(ostream&, Item);
};

#endif // ITEM_H_INCLUDED
