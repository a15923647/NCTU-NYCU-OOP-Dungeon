#include "Level.h"
using namespace std;

Level::Level(){
  this->level = 1;
  this->xp = 0;
  this -> calMaxXp();
  this -> calHpBuff();
  this -> calMpBuff();
  this -> calAttackBuff();
  this -> calDefenseBuff();
}

Level::Level(int lv){
  this->level = lv;
  this->xp = 0;
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

void Level::setLevel(int lv, int xp){
  this->level = lv;
  this->xp = xp;
  this -> calMaxXp();
  this -> calHpBuff();
  this -> calMpBuff();
  this -> calAttackBuff();
  this -> calDefenseBuff();
}
void Level::setBuff(Player* player){
  player -> increaseStates(0, +this->attackBuff, +this->defenseBuff, 0);
  player -> raiseBound(+this->hpBuff, +this->mpBuff);
}

void Level::resetBuff(Player* player){
  player -> increaseStates(0, -this->attackBuff, -this->defenseBuff, 0);
  player -> raiseBound(-this->hpBuff, -this->mpBuff);
}

void Level::increaseXp(Player* player, int inc){
  this -> resetBuff(player);
  this->xp += inc;
  while(this->xp >= this->maxXp){
    this->level++;
    cout << "Level Up!" << endl;
    this -> calMpBuff();
    this->xp -= this->maxXp;
  }
  this -> calHpBuff();
  this -> calAttackBuff();
  this -> calDefenseBuff();
  this -> setBuff(player);
}

ostream& operator << (ostream& out, Level& level){
  out << "level: " << level.level << endl;
  out << "xp: " << level.xp << "/" << level.maxXp << endl;
  out << "hpBuff: " << level.hpBuff << endl;
  out << "mpBuff: " << level.mpBuff << endl;
  out << "attackBuff: " << level.attackBuff << endl;
  out << "defenseBuff: " << level.defenseBuff << endl;
}