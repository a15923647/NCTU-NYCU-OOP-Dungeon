#include "Room.h"

Room::Room() : isExit(false), index(-1), object(NULL){
  
}

Room::Room(bool exit, int ind, vector<Object*> objects) : isExit(exit), index(ind), objects(objects){}

ostream& Room::operator << (ostream& outputStream, Room& room){
  //for save room
  //list all objects

}

bool popObject(Object* obj){
  size = obj->size();
  for(int i = 0; i < size; i++){
    if(obj == this -> objects.at(i)){
      objects.erase(i);
      delete [] obj;
      return true;
    }
  }
  return false;
}

void Room::pushObject(Object* obj){
  (this -> objects).push_back(obj);
}

void Room::setUpRoom(Room* now){
  this -> upRoom = now;
}
void Room::setDownRoom(Room* now){
  this -> downRoom = now;
}
void Room::setLeftRoom(Room* now){
  this -> leftRoom = now;
}
void Room::setRightRoom(Room* now){
  this -> RightRoom = now;
}

void Room::setIsExit(bool val) : 
  isExit(val){}

void Room::setIndex(int ind) : index(ind){}

void Room::setObjects(vector<Objects*> obj) : objects(obj){}

bool Room::getIsExit(){
  return this -> isExit;
}

int Room::getIndex(){
  return this -> index;
}

vector<Objects*> Room::getObjects(){
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

