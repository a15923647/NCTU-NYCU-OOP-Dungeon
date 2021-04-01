#include "Item.h"
#include<stdlib.h> //for including atoi
#define loadItem(varName,value) (switch(varName){\
  case "tag":\
    this -> setTag(value);\
    break;\
  case "name":\
    this -> setName(value);\
    break;\
  case "health":\
    this -> setHealth(atoi(value));\
    break;\
  case "attack":\
    this -> setAttack(atoi(value));\
    break;\
  case "defense":\
    this -> setDefense(atoi(value));\
    break;\
}\
)
Item::Item() : Object("default_item","item"), health(0), attack(0), defense(0){

}

Item::Item(string name, int inphea, int inpatt, int inpdef) : Object(name, "item"), health(inphea),  attack(inpatt), defense(inpdef){

}

override ofstream& Item::listMember(ofstream& fout){
  fout << "tag " << this -> getTag() << endl;
  fout << "name " << this -> getName() << endl;
  fout << "health " << this -> getHealth() << endl;
  fout << "attack " << this -> getAttack() << endl;
  fout << "defense " << this -> getDefense() << endl;
}

override static void Item::loadMember(ifstream& fin){
  string varName, inp_line;
  getline()
  while()
    //undone..
}

int Item::getHealth(){
  return this -> health;
}

int Item::getAttack(){
  return this -> attack;
}

int Item::getDefense(){
  return this -> defense;
}

void Item::setHealth(int inp) : health(inp){

}

void Item::setAttack(int inp) : attack(inp){

}

void Item::setDefense(int inp) : defense(inp){

}
/*
bool Item::triggerEvent(Object* obj){
  Player player = dynamic_cast<Player *>(obj);
  if(player == NULL) return false;
  player -> addItem(this);
}
*/

