#include "Item.h"

Item::Item() : Object("default_item","item"){
  this->health = 0;
  this->attack = 0;
  this->defense = 0;
  this->mp = 0;
  this->value = 0;
  this->active = true;
  this->continuous = false;
}

Item::Item(ifstream& fin){
  this -> setTag("item");
  this -> loadMember( fin );
}

void Item::listMember(ofstream& roomFile){
  roomFile << this -> getName() << " ";
  roomFile << this -> getHealth() << " ";
  roomFile << this -> getAttack() << " ";
  roomFile << this -> getDefense() << " ";
  roomFile << this -> getMp() << " ";
  roomFile << this -> getValue() << " ";
  roomFile << this -> getDurability() << " ";
  roomFile << this -> getActive() << " ";
  roomFile << this -> getContinuous() << endl;
}

void Item::loadMember(ifstream& roomFile){
  string name;
  int h, a, d, m, va, dur;
  bool act, conti;
  roomFile >> name >> h >> a >> d >> m >> va >> dur >> act >> conti;
  this -> setName(name);
  this -> setHealth(h);
  this -> setAttack(a);
  this -> setDefense(d);
  this -> setMp(m);
  this -> setValue(va);
  this -> setDurability(dur);
  this -> setActive(act);
  this -> setContinuous(conti);
  roomFile.ignore();
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

int Item::getValue(){
  return this -> value;
}

int Item::getDurability(){
  return this -> durability;
}

int Item::getMp(){
  return this -> mp;
}

bool Item::getActive(){
  return this -> active;
}

bool Item::getContinuous(){
  return this -> continuous;
}

void Item::setHealth(int inp){ 
  this -> health = inp;
}

void Item::setAttack(int inp){
  this -> attack = inp;
}

void Item::setDefense(int inp){
  this -> defense = inp;
}

void Item::setValue(int va){
  this -> value = va;
}

void Item::setDurability(int dur){
  this -> durability = dur;
}

void Item::setMp(int mp){
  this -> mp = mp;
}

void Item::setActive(bool act){
  this -> active = act;
}

void Item::setContinuous(bool conti){
  this -> continuous = conti;
}

bool Item::triggerEvent(Object* obj){
  Player* player = dynamic_cast<Player*>(obj);
  if(player == NULL) return false;
  
  //handle continuous props
  player -> increaseStates(this->health, this->attack, this->defense, this->mp);
  
  return true;
}

bool Item::operator == (Item a){
  if(a.getAttack() == this->getAttack() &&\
     a.getDefense() == this->getDefense() &&\
     a.getHealth() == this->getHealth() &&\
     a.getName() == this->getName() &&\
     a.getMp() == this->getMp() &&\
     /*a.getDurability() == this->getDurability() &&*/\
     a.getActive() == this->getActive() &&\
     a.getContinuous() == this->getContinuous())
       return true;
  
  return false;
}

ostream& operator << (ostream& out, Item item){
  out << "Name: " << item.getName() << endl;
  out << "Attack: " << item.getAttack() << endl;
  out << "Defense: " << item.getDefense() << endl;
  out << "Health: " << item.getHealth() << endl;
  out << "MP: " << item.getMp() << endl;
  out << "Durability: " << item.getDurability() << endl;
  out << "Active: " << item.getActive() << endl;
  out << "Continuous: " << item.getContinuous() << endl;
}

void Item::decDur(int wear){
  this->durability -= wear;
}