#include "Record.h"
#define CREATE_OBJ(tag) (switch(tag){    \
    case "item":                         \
      Item* obj = new Item();            \
      break;                             \
    case "NPC":                          \
      NPC* obj = new NPC();              \
      break;                             \
    case "monster":                      \
      Monster* obj = new Monster();      \
      break;                             \
    case "player":                       \
      Player* obj = new Player();        \
      break;                             \
    case "room":                         \
      Room* obj = new Room();            \
      break;                             \
  }                                      \
)
/*
 script split by 
 script : 
 '''
 '''
inventory :
- obj1.listMember
- obj2.listMember...

commodity :
- obj1.listMember
- obj2.listMember...

other split by <space>

 */
Record::Record(){

}

void Record::savePlayer(Player* player, ofstream& fout){
    
}

void Record::saveRoom(vector<Room>& roomList, ofsteram& fout){
  for(int i = 0; i < roomList.size(); i++)  {
    //fout << roomList[i].index << endl; change implement
    roomList[i].listMember();
    //store objects
    //get room objects and store them
    vector<Object*> objList = roomList[i].getObjects();
    for(int j = 0; j < objList.size(); j++){
      fout << "objlist:" << endl;
      objList[i] -> listMember(fout);
    }
  }
}

void Record::loadPlayer(Player* player, ifstream& fin){

}



void Record::loadRoom(vector<Room>& roomList, ifstream& fin){
//create room first
//then connect each of them by linked list
  roomList.clear();
  string inp_line;
  string tag;
  int tag_pos = -1;
  //get a object tag and create the coherent object
  while(tag_pos == -1){
    getline(fin, inp_line);
    tag_pos = inp_line.find("tag");
  }
  //extract the tag
  tag = inp_line.substr(tag_pos + 4);
  //create the coherent object
  CREATE_OBJ(tag);

  /*while(getline(fin, inp_line)){
    //read an empty line
    if( inp_line.empty() ) continue;
    //if : in line
    int first_match = -1;
    if( (first_match = inp_line.find(":")) != -1){
      //a list
      for( first_match = inp_line.find("-") ;\
           first_match != -1;\
           getline(fin, inp_line), inp_line.find("-") ){
        
      }
    }
  }*/
  //use virtual static loadMember function instead
}

void Record::saveToFile(Player* player, vector<Room>&){

}

void Record::loadFromFile(Player* player, vector<Room>&){

}
