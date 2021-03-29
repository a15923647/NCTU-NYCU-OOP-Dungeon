#include "Record.h"

Record::Record(){

}

void Record::savePlayer(Player* player, ofstream& fout){
  
}

void Record::saveRoom(vector<Room>& roomList, ofsteram& fout){
  for(int i = 0; i < roomList.size(); i++)  {
    fout << roomList[i].index << endl;
    //store objects
    //get room objects and store them
    vector<Object*> objList = roomList[i].getObjects();
    for(int j = 0; j < objList.size(); j++){
      objList[i] -> listMember(fout);
    }
  }
}

void Record::loadPlayer(Player* player, ifstream& fin){

}

void Record::loadRoom(vector<Room>&, ifstream& fin){

}

void Record::saveToFile(Player* player, vector<Room>&){

}

void Record::loadFromFile(Player* player, vector<Room>&){

}
