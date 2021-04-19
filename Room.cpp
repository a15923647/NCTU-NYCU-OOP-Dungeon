#include "Room.h"

Room::Room() : isExit(false), index(-1), noMonster(true){
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

Room::Room(bool exit, int ind, vector<Object*> objects) : isExit(exit), index(ind), objects(objects), noMonster(true){}

void Room::listMember(ofstream& roomFile){
  /*ofstream map("map", ios::out|ios::app);
  map << this->getIndex() << " ";
  int tmp = (this->getUpRoom()) == (Room*)NULL ? -1 : this->upRoom->getIndex();
  map << tmp << " ";
  
  tmp = (this->getDownRoom()) == (Room*)NULL ? -1 : this->downRoom->getIndex();
  map << tmp << " ";
  tmp = (this->getLeftRoom()) == (Room*)NULL ? -1 : this->leftRoom->getIndex();
  map << tmp << " ";
  tmp = (this->getRightRoom()) == (Room*)NULL ? -1 : this->rightRoom->getIndex();
  map << tmp << endl;

  map.close();
  */
  //implement in Record.cpp

  roomFile << this->getIndex() << endl;
  roomFile << this->getIsExit() << endl;
  
  vector<Object*> objs = this->getObjects();
  /*
   * # CLASSID
   * Monster     0
   * Player      1
   * NPC         2
   * Item        3 //impossible
   * Room        4 //impossible
   * endobjlist -1
   */
  for(int i = 0; i < objs.size(); i++){
    roomFile << tag2classid( objs[i]->getTag() ) << endl;
    objs[i]->listMember( roomFile );
  }
  roomFile << -1 << endl;//endobjlist
}

void Room::loadMember(ifstream& roomFile){
  //roomIndex has been read and set in Record::loadRoom
  int tmp, classid;
  roomFile >> tmp;
  this -> setIsExit(tmp);
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
