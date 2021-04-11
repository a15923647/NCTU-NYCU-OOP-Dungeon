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

  this -> setCurrentHealth( min(hp + hpInc, mhp) );
  this -> setAttack( atk + atkInc );
  this -> setDefense( def + defInc );
}

ostream& operator << (ostream& outputStream, Player& ply){
  //print player status
  outputStream << "HP: " << ply.getCurrentHealth() << "/" << ply.getMaxHealth() << endl;
  outputStream << "Attack: " << ply.getAttack() << endl;
  outputStream << "Defense: " << ply.getDefense()  << endl;
  
  outputStream << "inventory: " << endl;
  for(int i = 0; i < ply.getInventory().size(); i++){
    outputStream << ply.getInventory().at(i).getName() << endl;
  }
}

bool Player::triggerEvent(Object* obj){
  Player* player = dynamic_cast<Player*>(obj);
  if(player  == NULL) return false;
  //open chest
  cout << *player;
  return true;
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
  playerFile << this -> currentRoom->getIndex() << " ";
  playerFile << this -> previousRoom->getIndex() << endl;
  playerFile << this -> getName() << endl;
  playerFile << this -> getMaxHealth() << " ";
  playerFile << this -> getCurrentHealth() << " ";
  playerFile << this -> getAttack() << " ";
  playerFile << this -> getDefense() << endl;
  vector<Item> inventory = this -> getInventory();
  int size = inventory.size();
  playerFile << size << endl;
  for(int i = 0; i < size; i++){
    inventory[i].listMember( playerFile );
  }
}

void Player::loadMember(ifstream& playerFile){
  string pName = "", fmt_alg;
  getline( playerFile, pName );
  
  int mhp, chp, atk, def;
  playerFile >> mhp >> chp >> atk >> def;
  getline( playerFile, fmt_alg );
  this -> setGameCharacter( pName , "player", chp, atk, def);
  
  this -> inventory.clear();
  int n;
  playerFile >> n;
  string tag, name;
  int h, a, d;
  for(int i = 0; i < n; i++){
    playerFile >> tag >> name >> h >> a >> d;
	getline( playerFile, fmt_alg );
    inventory.push_back( Item(name, h, a, d) );
  }
}

vector<Item> Player::getInventory(){
  return this -> inventory;
}

Room* Player::getCurrentRoom(){
  return this ->  currentRoom;
}

Room* Player::getPreviousRoom(){
  return this -> previousRoom;
}
