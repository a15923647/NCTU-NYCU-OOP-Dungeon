#include "Player.h"
#define min(a,b) ((a) < (b)) ? (a) : (b)
Player::Player() : GameCharacter("hahaha", "player", 10, 10, 10){

}

Player::Player(string name, int hp, int atk, int def) : 
  GameCharacter(name, "player", hp, atk, def){}

void Player::addItem(Item ne){
  this -> increaseStates(ne.getHealth(), ne.getAttack(), ne.getDefense());
  (this -> inventory).push_back(ne);
}

void Player::increaseStates(int hpInc, int atkInc, int defInc){
  int hp = this->getCurrentHealth();
  int atk = this->getAttack();
  int def = this->getDefense();
  int mhp = this->getMaxHealth();

  this -> setHealth( min(hp + hpInc, mhp) );
  this -> setAttack( atk + atkInc );
  this -> setDefense( def + defInc );
}

bool Player::triggerEvent(Object* obj){
  Player* ply = dynamic_cast<Item*>(obj);
  if(ply == NULL) return false;
  //open chest
  this -> addItem(obj);
  return true;
}

ostream& operator << (ostream& outputStream, const Player& ply){
  //print player status
  outputStream << "HP: " << this->getHealth() << endl;
  outputStream << "Attack: " << this->getAttack() << endl;
  outputStream << "Defense: " << this->getDefense()  << endl;
  
  outputStream << "inventory: " << endl;
  for(int i = 0; i < inventory.size(); i++){
    outputStream << inventory.at(i).getName() << endl;
  }
}

void Player::changeRoom(Room* next){
  this -> previousRoom = this -> currentRoom;
  this -> currentRoom = next;
}

void Player::setCurrentRoom(Room* now){
  this -> currentRoom = now;
}

void Player::setPreviousRoom(Room* prev){
  this -> previousRoom = prev;
}

void Player::setInventory(vector<Item> v){
  this -> inventory = v;
}


void Player::listMember(ofstream& playerFile){
  playerFile << this -> currentRoom.getIndex() << " ";
  playerFile << this -> previousRoom.getIndex() << endl;
  vector<Item> inventory = this -> getInventory();
  int size = inventory.size();
  playerFile << size << endl;
  for(int i = 0; i < size; i++){
    inventory[i].listMember();
  }
}

override static void Player::loadMember(ifstream& playerFile){
  this -> inventory.clear();
  int n;
  playerFile >> n;
  string tag, name;
  int h, a, d;
  for(int i = 0; i < n; i++){
    playerFile >> tag >> name >> h >> a >> d;
    inventory.push_back( Item(name, h, a, d) );
  }
}
