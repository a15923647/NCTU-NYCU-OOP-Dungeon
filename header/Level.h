#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include "Player.h"
#include <fstream>
class Player;

class Level{
  private:
    int level;
    int xp;
    int maxXp;
    int hpBuff;
    int mpBuff;
    int attackBuff;
    int defenseBuff;
  public:
    Level();
    Level(int );
    void setLevel(int ,int );//level xp
    int getLevel();
    void increaseXp(Player*, int);
    int getXp();
    void calMaxXp();
    void calHpBuff();
    void calMpBuff();
    void calAttackBuff();
    void calDefenseBuff();
    void setBuff(Player*);
    void resetBuff(Player*);
    friend ostream& operator << (ostream&, Level&);
};

#endif
