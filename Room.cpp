#include "Room.h"

Room::Room() : isExit(false), index(-1), noMonster(true), noNPC(true), noTrea(true){
  vector<Object*> tmp;
  tmp.clear();
  this -> objects = tmp;
  this -> upRoom = (Room*)NULL;
  this -> downRoom = (Room*)NULL;
  this -> leftRoom = (Room*)NULL;
  this -> rightRoom = (Room*)NULL;
}

int tag2classid(string tag){
  if(tag == "monster") return 0;
  else if(tag == "player") return 1;
  else if(tag == "NPC") return 2;
  else if(tag == "item") return 3;
  else if(tag == "room") return 4;
}

void Room::listMember(ofstream& roomFile){
  roomFile << this->index << endl;//will be read by Record::loadRooms to specify which room to load
  roomFile << this->isExit << endl;
  
  /*
   * # CLASSID
   * Monster     0
   * Player      1//impossible
   * NPC         2
   * Item        3 
   * Room        4 //impossible
   * endobjlist -1
   */
   int objs_size = this->objects.size();
   roomFile << objs_size << endl;
   
  for(int i = 0; i < objs_size; i++){
    roomFile << tag2classid( this->objects[i] -> getTag() ) << endl;
    this->objects[i] -> listMember( roomFile );
  }
}

void Room::loadMember(ifstream& roomFile){
  int tmp;
  roomFile >> tmp;
  this -> isExit = tmp;
  roomFile.ignore();
  //cannot new descendent objects, so load other objects in Record::loadRooms
}

bool Room::popObject(Object* obj){
  int size = this ->  objects.size();
  for(int i = 0; i < size; i++){
    if(obj == this -> objects.at(i)){
      objects.erase( objects.begin() + i );
      return true;
    }
  }
  return false;
}
/*
void Room::pushObject(Object* obj){
  (this -> objects).push_back(obj);
}
*/
void Room::setUpRoom(Room* u){
  this -> upRoom = u;
}
void Room::setDownRoom(Room* d){
  this -> downRoom = d;
}
void Room::setLeftRoom(Room* l){
  this -> leftRoom = l;
}
void Room::setRightRoom(Room* r){
  this -> rightRoom = r;
}

void Room::setIsExit(bool val){
  this -> isExit = val;
}

void Room::setIndex(int ind){
 this -> index = ind;
}

void Room::setObjects(vector<Object*> obj){
  this -> objects = obj;
}

void Room::setNoMon(bool clear){
  this->noMonster = clear;
}

void Room::setNoNPC(bool nnpc){
  this->noNPC = nnpc;
}

void Room::setNoTrea(bool nnt){
  this->noTrea = nnt;
}

bool Room::getIsExit(){
  return this -> isExit;
}

int Room::getIndex(){
  return this -> index;
}

vector<Object*> Room::getObjects(){
  return this -> objects;
}

Room* Room::getUpRoom(){
  return this -> upRoom;
}

Room* Room::getDownRoom(){
  return this -> downRoom;
}

Room* Room::getLeftRoom(){
  return this -> leftRoom;
}

Room* Room::getRightRoom(){
  return this -> rightRoom;
}

bool Room::getNoMon(){
  return this->noMonster;
}

bool Room::triggerEvent(Object* ){
  //no need to implement
  return true;
}

bool Room::getNoNPC(){
  return this->noNPC;
}

bool Room::getNoTrea(){
  return this->noTrea;
}