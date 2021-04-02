#include "Record.h"
#include <assert.h>
/*
 */
Record::Record(){

}

void Record::savePlayer(Player* player, ofstream& playerFile){
  player -> listMember(playerFile);
}

void Record::saveRoom(vector<Room>& roomList, ofsteram& fout){
  fout << roomList.size();
  for(int i = 0; i < roomList.size(); i++){
    roomList[i].listMember(fout);
  }
}

void Record::loadPlayer(Player* player, ifstream& playerFile, vecotr<Room>& roomList){
  int cur, pre;
  playerFile >> cur >> pre;
  player -> loadMember(playerFile);
  //put player on the map
  player -> setCurrentRoom( &roomList[ cur ] );
  player -> setPreviousRoom( &roomList[ pre ] );
}



void Record::loadRoom(vector<Room>& roomList, ifstream& roomFile){
/*
  create room first
  then connect each of them by linked list
*/
  roomList.clear();
  int n;
  roomFile >> n;
  //create empty rooms
  for(int i = 0; i < n; i++){
    roomList.push_back(Room());
    roomList[i].setIndex(i);
  }
  //load every room
  int roomIdx = -1;
  for(roomFile >> roomIdx; !roomFile.eof(); roomFile >> roomIdx){
    roomList[ roomIdx ].loadMember(roomFile);
  }
  //connect them together
  ifstream map = open("map");
  int t = n;
  while( t-- ){
    int i, u, d, l, r;
    roomFile >> i >> u >> d >> l >> r;
    if(u != -1) roomList[i].setUpRoom( &roomList[u] );
    if(d != -1) roomList[i].setDownRoom( &roomList[d] );
    if(l != -1) roomList[i].setLeftRoom( &roomList[l] );
    if(r != -1) roomList[i].setRightRoom( &roomList[r] );
  }
  map.close();
}

void Record::saveToFile(Player* player, vector<Room>&){

}

void Record::loadFromFile(Player* player, vector<Room>&){

}
