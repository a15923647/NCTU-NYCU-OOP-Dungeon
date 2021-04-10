#include "Record.h"
#define ROOM_FILE_PRE "roomFile"
#define PLAYER_FILE_PRE "playerFile"

Record::Record(){

}

void Record::savePlayer(Player* player, ofstream& playerFile){
  player -> listMember( playerFile );
}

void Record::saveRooms(vector<Room>& roomList, ofstream& roomFile){
  roomFile << roomList.size() << endl;
  for(int i = 0; i < roomList.size(); i++){
    roomList[i].listMember(roomFile);
  }
}

void Record::loadPlayer(Player* player, ifstream& playerFile, vector<Room>& roomList){
  int cur, pre;
  playerFile >> cur >> pre;
  string fmt_alg;
  getline( playerFile, fmt_alg );
  player -> loadMember(playerFile);

  //put player on the map
  player -> setCurrentRoom( &roomList[ cur ] );
  player -> setPreviousRoom( &roomList[ pre ] );
}



void Record::loadRooms(vector<Room>& roomList, ifstream& roomFile){
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
    roomList[ roomIdx ].loadMember(roomFile);//load isExit
    //load other members since room cannot access monster, npc, player, item
    int classid;
    vector<Object*> objs;
    objs.clear();
    for(roomFile >> classid; classid != -1; roomFile >> classid){
      switch(classid){
        case 0:
          objs.push_back( new Monster() );
          break;
        case 1:
          objs.push_back( new Player() );
          break;
        case 2:
          objs.push_back( new NPC() );
          break;
        case 3:
          objs.push_back( new Item() );
          break;
        case 4:
          objs.push_back( new Room() );
          break;
        case -1:
          return;
          break;
      }
      objs.back() -> loadMember( roomFile );
    }
    roomList[roomIdx].setObjects( objs );
  }
  //connect them together
  ifstream map("map");
  int t;
  map >> t;
  string fmt_alg;
  getline( map, fmt_alg );
  while( t-- ){
    int i, u, d, l, r;
	map >> i >> u >> d >> l >> r;
	
    if(u != -1) roomList[i].setUpRoom( &roomList[u] );
    if(d != -1) roomList[i].setDownRoom( &roomList[d] );
    if(l != -1) roomList[i].setLeftRoom( &roomList[l] );
    if(r != -1) roomList[i].setRightRoom( &roomList[r] );
  }
  map.close();
}

void Record::saveToFile(Player* player, vector<Room>& roomList){
  string rmf = ROOM_FILE_PRE + player->getName();
  ofstream roomFile( rmf.c_str() );
  this -> saveRooms( roomList, roomFile );
  
  string pf = PLAYER_FILE_PRE + player->getName();
  ofstream playerFile( pf.c_str() );
  this -> savePlayer( player, playerFile );
  
  roomFile.close();
  playerFile.close();
}

bool Record::loadFromFile(Player* player, vector<Room>& roomList){
  string pName;
  cout << "Player name: ";
  cin >> pName;

  string rmf = ROOM_FILE_PRE + pName;
  ifstream roomFile( rmf.c_str() );
  if(roomFile.good())
    this -> loadRooms( roomList, roomFile );
  else
    cerr << "open roomFile fail\n", exit(0);
 
  string pf = PLAYER_FILE_PRE + pName;
  ifstream playerFile( pf.c_str() );
  if(playerFile.good())
    this -> loadPlayer( player, playerFile, roomList );
  else
    cerr << "open playerFile fail\n", exit(0);

  roomFile.close();
  playerFile.close();
  return true;//sucess
}
