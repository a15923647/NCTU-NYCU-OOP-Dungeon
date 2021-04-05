#include "Room.h"
#include "Monster.h"
#include "Player.h"
#include "NPC.h"
#include "Item.h"
#include <stdlib.h>
#include <fstream>
/*#define CREATE_OBJ(classid) switch(classid){\
  case 0:\
    (Monster*)obj = new Monster();\
    break;\
  case 1:\
    (Player*)obj = new Player();\
    break;\
  case 2:\
    (NPC*)obj = new NPC();\
    break;\
  case 3:\
    (Item*)obj = new Item();\
    break;\
  case 4:\
    (Room*)obj = new Room();\
    break;\
  case -1:\
    return;\
}*/

Room::Room() : isExit(false), index(-1), objects(NULL){
  
}

int tag2classid(string tag){
  if(tag == "monster") return 0;
  else if(tag == "player") return 1;
  else if(tag == "NPC") return 2;
  else if(tag == "item") return 3;
  else if(tag == "room") return 4;
}

Room::Room(bool exit, int ind, vector<Object*> objects) : isExit(exit), index(ind), objects(objects){}

void Room::listMember(ofstream& roomFile){
  ofstream map = open("map", ios::out|ios::append);
  map << this->getIndex() << " ";
  map << (this->getUpRoom())->getIndex() == NULL ? -1 : this->upRoom->getIndex() << " ";
  map << (this->getDownRoom())->getIndex() == NULL ? -1 : this->downRoom->getIndex()  << " ";
  map << (this->getLeftRoom())->getIndex() == NULL ? -1 : this->leftRoom->getIndex() << " ";
  map << (this->getRightRoom())->getIndex() == NULL ? -1 : this->rightRoom->getIndex() << endl;

  map.close();

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
  for(roomFile >> classid; classid != -1; roomFile >> classid){
    if(classid == 0) {
      Monster* obj = new Monster();
      obj->loadMember(roomFile);
    }
    else if(classid == 1) {
      Player* obj = new Player();
      obj->loadMember(roomFile);
    }
    else if(classid == 2){
      NPC* obj = new NPC();
      obj->loadMember(roomFile);
    }
    else if(classid == 3){
      Item* obj = new Item();
      obj->loadMember(roomFile);
    }
    else if(classid == 4){
      Room* obj = new Room();
      obj->loadMember(roomFile);
    }
    else if(classid == -1) return;
    /*
    case 0:
      Monster* obj = new Monster();
      break;
    case 1:
      Player* obj = new Player();
      break;
    case 2:
      NPC* obj = new NPC();
      break;
    case 3:
      Item* obj = new Item();
      break;
    case 4:
      Room* obj = new Room();
      break;
    case -1:
      return;
    }*/
    //obj->loadMember(roomFile);
  }
}

bool Room::popObject(Object* obj){
  int size = this ->  objects.size();
  for(int i = 0; i < size; i++){
    if(obj == this -> objects.at(i)){
      objects.erase( objects.begin() + i );
      delete [] obj;
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


bool Room::triggerEvent(Object* ){
  //no need to implement
  return true;
}
