#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime> 
#include "fileoper.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "Room.h"
#include "Skill.h"

using namespace std;

/* This is the record system. Get the information of the  */
/* player and rooms then save them to (a) file(s). Notice */
/* that using pass by reference can prevent sending the   */
/* whole vector to the function.                          */

class Record
{
private:
    void savePlayer(Player*, ofstream&);
    void saveRooms(vector<Room>&, ofstream&);
    void saveSkill_repo(vector<Skill>&, ofstream&);
    void loadPlayer(Player*, ifstream&, vector<Room>&);
    void loadRooms(vector<Room>&, ifstream&);
    void loadSkill_repo(vector<Skill>&, ifstream&);

public:
    Record();
    void saveToFile(Player*, vector<Room>&, vector<Skill>&);
    bool loadFromFile(Player*, vector<Room>&, vector<Skill>&);

};

#endif // RECORD_H_INCLUDED
