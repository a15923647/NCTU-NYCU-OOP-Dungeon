#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Object.h"
#include "Monster.h"
#define NOATT 3

class Monster;

class Skill : public Object{
  public:
    Skill();
    Skill(ifstream&);
    Skill(int, string, string, int, int, int, int, int);
    void setAtt(int);
    void setMpCon(int);
    void setAtk(int);
    void setProf(int);
    void setCost(int);
    
    int getAtt();
    int getMpCon();
    int getAtk();
    int getProf();
    int getCost();
    
    /*
      show skill info
    */
    friend ostream& operator <<(ostream&, Skill&);
    
    void listMember(ofstream& );
    void loadMember(ifstream& );
    
    /*
    Fight monster via skill
    * attack
    * improve proficciency
    * calculate attack
    * calculate consumption
    */
    bool triggerEvent(Object*);//Monster object
    
  private:
    /*
    0: water
    1: fire
    2: grass
    */
    int attribute_id;
    int attack;
    int mpConsumption;
    int proficiency;
    int proficiency_max;
    int cost;
    //name, tag
};

#endif