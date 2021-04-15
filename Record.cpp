#include "Record.h"
#define ROOM_FILE_PRE "roomFile"
#define PLAYER_FILE_PRE "playerFile"
#define MAP_FILE_PRE "map"
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
  
  //roomFile.ignore();//fmt_alg
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
  /*//connect them together
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
  map.close();*/
  //implement in Record::loadFromFile
}

void Record::saveToFile(Player* player, vector<Room>& roomList){
  string subdir = "record";
  create_dir_ifnext( subdir );
  subdir = subdir + '/' + player->getName();
  create_dir_ifnext( subdir );
  
  time_t now = time( 0 );
  string tim( ctime(&now) );
  int tim_size = tim.size();
  for(int i = 0; i < tim_size; i++)
    if(tim[i] == ' ')
      tim[i] = '_';
    else if(tim[i] == ':')
      tim[i] = '-';
  
  string mapf = subdir + '/' + MAP_FILE_PRE + '_' + tim;
  mapf = mapf.substr( 0, mapf.length()-1 );
  ofstream map( mapf );
  if(!map){
    map.open(mapf.c_str(), std::fstream::trunc);
  }
  map << roomList.size() << endl;
  int room_size = roomList.size();
  for(int i = 0; i < room_size; i++){
    map << roomList[i].getIndex() << " ";
    int tmp = (roomList[i].getUpRoom()) == (Room*)NULL ? -1 : roomList[i].getUpRoom()->getIndex();
    map << tmp << " ";
  
    tmp = (roomList[i].getDownRoom()) == (Room*)NULL ? -1 : roomList[i].getDownRoom()->getIndex();
    map << tmp << " ";
    tmp = (roomList[i].getLeftRoom()) == (Room*)NULL ? -1 : roomList[i].getLeftRoom()->getIndex();
    map << tmp << " ";
    tmp = (roomList[i].getRightRoom()) == (Room*)NULL ? -1 : roomList[i].getRightRoom()->getIndex();
    map << tmp << endl;
  }

  string rmf = subdir + '/' + ROOM_FILE_PRE + '_' + tim;
  rmf = rmf.substr( 0, rmf.length()-1 );
  ofstream roomFile( rmf.c_str() );
  if(!roomFile){
    roomFile.open(rmf.c_str(), std::fstream::trunc);
  }
  
  this -> saveRooms( roomList, roomFile );
  
  string pf = subdir + '/' + PLAYER_FILE_PRE + '_' + tim;
  pf = pf.substr( 0, pf.length()-1 );
  ofstream playerFile( pf.c_str() );
  if(!playerFile){
    playerFile.open(pf.c_str(), std::fstream::trunc);
  }
  
  this -> savePlayer( player, playerFile );
  
  map.close();
  roomFile.close();
  playerFile.close();
}

bool Record::loadFromFile(Player* player, vector<Room>& roomList){
  string pName;
  cout << "Player name: ";
  cin >> pName;
  
  string subdir = "record";
  subdir += '/' + pName;
  
  vector<string> files = vector<string>();
  getdir(subdir ,files);
  
  vector<string> timev;
  timev.clear();
  for(int i = 0; i < files.size(); i++){
    if( files[i].substr(0, strlen( ROOM_FILE_PRE )) == ROOM_FILE_PRE){
      timev.push_back( files[i].substr( strlen( ROOM_FILE_PRE )+1 ) );
      cout << timev.size() << ": " << timev.back() << endl;
    }
  }
  
  int idx;
  cin >> idx;
  for(; idx <= 0 || idx > files.size(); cout << "Invalid index.\nInput again.\n")
    cin >> idx;
  idx -= 1;
  
  string rmf = ROOM_FILE_PRE;
  rmf += ('_' + timev[idx]);
  rmf = (subdir + '/') + rmf;
  //load objects in each room and set isExit
  ifstream roomFile( rmf.c_str() );
  if(roomFile.good())
    this -> loadRooms( roomList, roomFile );
  else
    cerr << "open roomFile fail\n", exit(0);
  //connect them
  string mapf = MAP_FILE_PRE;
  mapf += ('_' + timev[idx]);
  mapf = (subdir + '/') + mapf;
  ifstream map( mapf.c_str() );
  if(!map.good())
    cerr << "open map fail\n", exit(0);
  
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
  
  //load player
  string pf = PLAYER_FILE_PRE;
  pf += ('_' + timev[idx]);
  pf = (subdir + '/') + pf;
  
  ifstream playerFile( pf.c_str() );
  if(playerFile.good())
    this -> loadPlayer( player, playerFile, roomList );
  else
    cerr << "open playerFile fail\n", exit(0);

  map.close();
  roomFile.close();
  playerFile.close();
  return true;//sucess
}

