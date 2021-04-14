#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#define INT_MAX 2147483647

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class NPC: public GameCharacter
{
private:
    string script;
    vector<Item> commodity;
public:
    NPC();
    NPC(string, string, vector<Item>);
    void listCommodity(); /*print all the Item in this NPC*/

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*);
    void listMember(ofstream& );
    void loadMember(ifstream& );

    /* Set & Get function*/
    void setScript(string);
    void setCommodity(vector<Item>);
    string getScript();
    vector<Item> getCommodity();
};


#endif // NPC_H_INCLUDED
