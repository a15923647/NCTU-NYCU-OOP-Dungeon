#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#define INT_MAX 2147483647

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class NPC: public GameCharacter
{
private:
    string script;
    int coin;
    vector<Item> commodity;
public:
    NPC();
    NPC(ifstream&);
    void listCommodity(); /*print all the Item in this NPC*/

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*);
    void listMember(ofstream& );
    void loadMember(ifstream& );
    static bool exchange(Object*, Object*, Item&);
    //buyer saler Item
    //npc to player or player to npc
    /*
      if buyer has enough money (item.value)
      exchange item
        call player addItem
        erase npc commodity
        
        add Commodity to npc
        erase player's item
    */
    
    /* Set & Get function*/
    void setScript(string);
    void setCommodity(vector<Item>);
    void setCoin(int);
    string getScript();
    int getCoin();
    vector<Item> getCommodity();
};


#endif // NPC_H_INCLUDED
