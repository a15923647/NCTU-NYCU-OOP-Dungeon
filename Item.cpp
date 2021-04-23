#include "Item.h"

/*Item::Item() : Object("default_item","item"), health(0), attack(0), defense(0){

}*/

Item::Item() : Object("default_item","item"){
  this->health = 0;
  this->attack = 0;
  this->defense = 0;
  this->mp = 0;
}
Item::Item(string name, int inphea, int inpatt, int inpdef, int inpmp) : Object(name, "item"), health(inphea),  attack(inpatt), defense(inpdef), mp(inpmp){

}

Item::Item(ifstream& fin){
  this -> setTag("item");
  this -> loadMember( fin );
}

void Item::listMember(ofstream& roomFile){
  //roomFile << this -> getTag() << " ";
  roomFile << this -> getName() << " ";
  roomFile << this -> getHealth() << " ";
  roomFile << this -> getAttack() << " ";
  roomFile << this -> getDefense() << " ";
  roomFile << this -> getMp() << " ";
  roomFile << this -> getValue() << " ";
  roomFile << this -> getDurability() << endl;
}

void Item::loadMember(ifstream& roomFile){
  //string tag, name;
  string name;
  int h, a, d, m, va, dur;
  //roomFile >> tag >> name >> h >> a >> d >> m >> va >> dur;
  roomFile >> name >> h >> a >> d >> m >> va >> dur;
  //this -> setTag(tag);
  this -> setName(name);
  this -> setHealth(h);
  this -> setAttack(a);
  this -> setDefense(d);
  this -> setMp(m);
  this -> setValue(va);
  this -> setDurability(dur);
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

bool Item::triggerEvent(Object* obj){
  Player* player = dynamic_cast<Player*>(obj);
  if(player == NULL) return false;
  player -> addItem(*this);
  return true;
}

bool Item::operator == (Item a){
  if(a.getAttack() == this->getAttack() &&\
     a.getDefense() == this->getDefense() &&\
     a.getHealth() == this->getHealth() &&\
     a.getName() == this->getName())
       return true;
  
  return false;
}

ostream& operator << (ostream& out, Item item){
  out << "Attack: " << item.getAttack() << endl;
  out << "Defense: " << item.getDefense() << endl;
  out << "Health: " << item.getHealth() << endl;
  out << "MP: " << item.getMp() << endl;
  out << "Durability: " << item.getDurability() << endl;
}