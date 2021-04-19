#include "Player.h"
#define min(a,b) ((a) < (b)) ? (a) : (b)
Player::Player() : GameCharacter("hahaha", "player", 10, 10, 10){
  this->level = new Level(1);
  this->coin = 60;
  this->calMpMax();
  this->level -> setBuff(this);
  this -> heal();
}

Player::Player(string name, int hp, int atk, int def) : 
  GameCharacter(name, "player", hp, atk, def){
  this->level = new Level(1);
  this->coin = 60;
  this->calMpMax();
  this->level -> setBuff(this);
  this -> heal();
}

void Player::addItem(Item ne){
  this -> setMaxHealth( this -> getMaxHealth() + ne.getHealth() );
  this -> increaseStates(ne.getHealth(), ne.getAttack(), ne.getDefense(), 0);
  (this -> inventory).push_back(ne);
}

void Player::increaseStates(int h, int a, int d, int m){
  int hp = this->getCurrentHealth();
  int atk = this->getAttack();
  int def = this->getDefense();
  int mhp = this->getMaxHealth();
  int mp = this->mp;
  
  this -> setMp( mp + m );
  this -> setCurrentHealth( min(hp + h, mhp) );
  this -> setAttack( atk + a );
  this -> setDefense( def + d );
}

void Player::raiseBound(int h, int m){
  this->mpMax += m;
  this -> setMaxHealth( this -> getMaxHealth() + h);
}

void Player::heal(){
  this->mp = this->mpMax;
  this -> setCurrentHealth( this -> getMaxHealth() );
}

ostream& operator << (ostream& outputStream, Player& ply){
  //print player status
  outputStream << "HP: " << ply.getCurrentHealth() << "/" << ply.getMaxHealth() << endl;
  outputStream << "MP: " << ply.getMp() << "/" << ply.getMpMax() << endl;
  outputStream << "Attack: " << ply.getAttack() << endl;
  outputStream << "Defense: " << ply.getDefense()  << endl;
  outputStream << "Coin: " << ply.getCoin() << endl;
  
  outputStream << endl;
  outputStream << *ply.getLevelO() << endl;
  
  outputStream << "inventory: " << endl;
  for(int i = 0; i < ply.getInventory().size(); i++){
    outputStream << "  " << ply.getInventory().at(i).getName() << endl;
  }
  
  outputStream << "skills: " << endl;
  for(int i = 0; i < ply.getSkills().size(); i++){
    outputStream << "  " << ply.getSkills()[i].getName() << endl;
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
  if(next == (Room*)NULL){
    cout << "Invalid option!" << endl;
    return;
  }
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

void Player::setMp(int mp){
  this -> mp = mp;
}

void Player::calMpMax(){
  this -> mpMax = this->level -> getLevel() * 100;
}

void Player::listMember(ofstream& playerFile){
  playerFile << this -> currentRoom->getIndex() << " ";
  playerFile << this -> previousRoom->getIndex() << endl;
  playerFile << this -> getName() << endl;
  playerFile << this -> getMaxHealth() << " ";
  playerFile << this -> getCurrentHealth() << " ";
  playerFile << this -> getAttack() << " ";
  playerFile << this -> getDefense() << " ";
  playerFile << this -> getCoin() << " ";
  playerFile << this -> getLevelO() -> getLevel() << " ";
  playerFile << this -> getLevelO() -> getXp() << " ";
  playerFile << this -> getMp() << endl;
  vector<Item> inventory = this -> getInventory();
  int size = inventory.size();
  playerFile << size << endl;
  for(int i = 0; i < size; i++){
    inventory[i].listMember( playerFile );
  }
  
  vector<Skill> skv = this -> getSkills();
  int skv_size = skv.size();
  playerFile << skv_size << endl;
  for(int i = 0; i < skv_size; i++){
    skv[i].listMember( playerFile );
  }
}

void Player::loadMember(ifstream& playerFile){
  string pName = "";
  getline( playerFile, pName );
  
  int mhp, chp, atk, def, co, lv, xp, mp;
  playerFile >> mhp >> chp >> atk >> def >> co >> lv >> xp >> mp;
  playerFile.ignore();
  this -> setGameCharacter( pName , "player", chp, atk, def);
  this -> setCoin( co );
  this -> getLevelO() -> resetBuff( this );
  this -> getLevelO() -> setLevel( lv, xp );
  this -> getLevelO() -> setBuff( this );
  this -> setMp( mp );
  
  this -> inventory.clear();
  
  int n;
  playerFile >> n;
  playerFile.ignore();
  while(n--){
    this->inventory.push_back( Item() );
    this->inventory.back().loadMember( playerFile );
  }
  
  int skv_size;
  playerFile >> skv_size;
  playerFile.ignore();
  
  while(skv_size--){
    this->skills.push_back( Skill() );
    this->skills.back().loadMember( playerFile );
  }
}

void Player::consumeMp(int dec){
  //we have ensured mp is enough
  this->mp -= dec;
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

void Player::setCoin(int co){
  this -> coin = co;
}

int Player::getCoin(){
  return this -> coin;
}

vector<Skill> Player::getSkills(){
  return this -> skills;
}

int Player::getMp(){
  return this -> mp;
}

void Player::addSkill(Skill sk){
  this->skills.push_back( sk );
}

int Player::getMpMax(){
  return this->mpMax;
}

Level* Player::getLevelO(){
  return this->level;
}