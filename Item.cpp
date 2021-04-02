#include "Item.h"

Item::Item() : Object("default_item","item"), health(0), attack(0), defense(0){

}

Item::Item(string name, int inphea, int inpatt, int inpdef) : Object(name, "item"), health(inphea),  attack(inpatt), defense(inpdef){

}

override ofstream& Item::listMember(ofstream& roomFile){
  roomFile << this -> getTag() << " ";
  roomFile << this -> getName() << " ";
  roomFile << this -> getHealth() << " ";
  roomFile << this -> getAttack() << " ";
  roomFile << this -> getDefense() << endl;
}

override static void Item::loadMember(ifstream& roomFile){
  string tag, name;
  int h, a, d;
  roomFile >> tag >> name >> h >> a >> d;
  this -> setTag(tag);
  this -> setName(name);
  this -> setHealth(h);
  this -> setAttack(a);
  this -> setDefense(d);
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

bool Item::triggerEvent(Object* obj){
  Player player = dynamic_cast<Player *>(obj);
  if(player == NULL) return false;
  player -> addItem(this);
}


