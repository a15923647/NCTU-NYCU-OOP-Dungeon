#include "Level.h"
#include "Player.h"
using namespace std;

Level::Level(){
  this->level = 1;
  this -> calMaxXp();
  this -> calHpBuff();
  this -> calMpBuff();
  this -> calAttackBuff();
  this -> calDefenseBuff();
}

Level::Level(int lv){
  this->level = lv;
  this -> calMaxXp();
  this -> calHpBuff();
  this -> calMpBuff();
  this -> calAttackBuff();
  this -> calDefenseBuff();
}

int Level::getLevel(){return this->level;}
int Level::getXp(){return this->xp;}

inline void Level::calMaxXp(){this->maxXp = this->level * 20;}
inline void Level::calHpBuff(){this->hpBuff = this->level * 5;}
inline void Level::calMpBuff(){this->mpBuff = this->level * 3;}
inline void Level::calAttackBuff(){this->attackBuff = this->level * 3;}
inline void Level::calDefenseBuff(){this->defenseBuff = this->level * 10;}

void Level::setLevel(int lv){this->level = lv;}
void Level::setBuff(Player* player){
  player -> increaseStates(+this->hpBuff, +this->attackBuff, +this->defenseBuff/*, +this->mpBuff*/);
}

void Level::resetBuff(Player* player){
  player -> increaseStates(-this->hpBuff, -this->attackBuff, -this->defenseBuff/*, -this->mpBuff*/);
}

void Level::increaseXp(Player* player, int inc){
  this -> resetBuff(player);
  this->xp += inc;
  while(this->xp >= this->maxXp){
    this->level++;
    this -> calMpBuff();
    this->xp -= this->maxXp;
  }
  this -> calHpBuff();
  this -> calAttackBuff();
  this -> calDefenseBuff();
  this -> setBuff(player);
}