#include "Dungeon.h"
#include <stdlib.h>
//init -> choose action -> ck game logic -> end or choose action
//init: createRoom -> createPlayer
Dungeon::Dungeon(){

}

void Dungeon::createPlayer(string name){
  this -> player = Player(name, 66, 10, 10);
  this -> player.setCurrentRoom( &(this->rooms[0]) );
  this -> player.setPreviousRoom( &(this->rooms[0]) );
}

string split_first(string& str){
  int i = 0;
  for(i = 0; i < str.length() && str[i] != ' ' ; i++);

  string res = str.substr( 0, i );
  if(str[i+1]) str = str.substr( i + 1 );
  else str = "";

  return res;
}

void Dungeon::createMap(){
  ifstream map("map");
  if(!map.good()){//format chk?
    cerr << "Fail to open map file.\nPlease check your map file\n";
    exit(0);
  }
  int nor;//number of room
  map >> nor;
  this -> rooms.clear();
  for(int i = 0; i < nor; i++){
    this -> rooms.push_back(Room());
    rooms[i].setIndex(i);
  }

  int t = nor;
  while(t--){
    int idx, tmp;
    map >> idx;
    map >> tmp; tmp != -1 ? this->rooms[idx].setUpRoom( &(this->rooms[tmp]) ) : this->rooms[idx].setUpRoom( NULL );
    map >> tmp; tmp != -1 ? this->rooms[idx].setDownRoom( &(this->rooms[tmp]) ) : this->rooms[idx].setDownRoom( NULL );
    map >> tmp; tmp != -1 ? this->rooms[idx].setLeftRoom( &(this->rooms[tmp]) ) : this->rooms[idx].setLeftRoom( NULL );
    map >> tmp; tmp != -1 ? this->rooms[idx].setRightRoom( &(this->rooms[tmp]) ) : this->rooms[idx].setRightRoom( NULL );
  }
  //default exit is the last room
  this -> rooms[nor-1].setIsExit( true );
  map.close();
  //load objects
  string inp_line, name;
  int ridx = 0;
  //load NPC
  ifstream npc( "npc" );
  string script;
  int sp_cnt = 0;
  vector<Item> cmd;
  cmd.clear();
  NPC* new_npc;
  while(getline(npc, inp_line)){
    for(sp_cnt = 0; sp_cnt < inp_line.length() && inp_line[sp_cnt] != ' '; sp_cnt++);
    
    if(sp_cnt == 0){
      //store cmd
      //consider the first NPC
      if(cmd.size() != 0) 
        new_npc -> setCommodity(cmd);//set cmd of old npc

      cmd.clear();

      name = split_first( inp_line );
      ridx = atoi( split_first( inp_line ).c_str() );

      new_npc = new NPC;
      this -> rooms[ridx].getObjects().push_back( new_npc );
    }
    else if(sp_cnt == 2){
      new_npc -> setScript( new_npc->getScript() + inp_line.substr(2) + "\n" );
    }
    else if(sp_cnt == 4){
      string itmName;
      int h, a, d;

      inp_line = inp_line.substr(4);
      itmName = split_first( inp_line );
      h = atoi( split_first( inp_line ).c_str() );
      a = atoi( split_first( inp_line ).c_str() );
      d = atoi( split_first( inp_line ).c_str() );

      cmd.push_back( Item(itmName, h, a, d) );
    }
  }
  //load Monster
  ifstream monster("Monster");
  while(!monster.eof()){
    int h, a, d;
    monster >> ridx >> name >> h >> a >> d;
    Monster* new_mon = new Monster(name, h, a, d);
    this -> rooms[ridx].getObjects().push_back( new_mon );
  }
}

void Dungeon::handleMovement(){
  Room* cur = this -> player.getCurrentRoom();
  Room* pre = this -> player.getPreviousRoom();

  Room* u = cur -> getUpRoom();
  Room* d = cur -> getDownRoom();
  Room* l = cur -> getLeftRoom();
  Room* r = cur -> getRightRoom();
  
  string ans = "";

  while(ans != "U" || ans != "D" || ans != "L" || ans != "R"){
    cout << "which room you want to go?\n";
    if(u != NULL) cout << "Up: U" << endl;
    if(d != NULL) cout << "Down: D" << endl;
    if(l != NULL) cout << "Left: L" << endl;
    if(r != NULL) cout << "Right: R" << endl;
    cin >> ans;
  }

  if(ans == "U") player.changeRoom( u );
  if(ans == "D") player.changeRoom( d );
  if(ans == "L") player.changeRoom( l );
  if(ans == "R") player.changeRoom( r );
  
}

/*
void Dungeon::handleEvent(Object* obj){
  //deal with player's interaction with object
  //replaced by chooseAction()
}
*/

void Dungeon::showWelcomeMenu(){
  cout << "------------------------" << endl;
  cout << "===Welcome to Dungeon===" << endl;
  cout << "Select your choice" << endl;
  cout << "1. Create a new player" << endl;
  cout << "2. Load previous record" << endl;
  cout << "3. Quit game" << endl;
}

void Dungeon::startGame(){
  //load from file? create new player?
  int choice = 0;
  while(choice < 1 || choice > 3){
    this -> showWelcomeMenu();
    cin >> choice;
  }
  //init 
  if(choice == 1){
    string name;
    cout << "Input your player name: ";
    cin >> name;
    this -> createMap();
    this -> createPlayer(name);
  }
  else if(choice == 2){
    record.loadFromFile( &(this->player), this->rooms );
  }
  else if(choice == 3)
    exit(0);
}

void Dungeon::chooseAction(vector<Object*> objects){
  int choice = -1;
  while(choice > 7 || choice < 1){
    cout << "choose your action" << endl;
    cout << "------------------------" << endl;
    cout << "1. check status and inventory" << endl;
    cout << "2. move to next room" << endl;
    cout << "3. communicate to someone" << endl;
    cout << "4. attack with monster" << endl;
    cout << "5. explore treasure" << endl;
    cout << "6. save game" << endl;
    cout << "7. exit this game" << endl;
    cout << "your choice: ";
    cin >> choice;
  }

  switch(choice){
    case 1:
      this -> player.triggerEvent( &(this->player) );
      break;
    case 2:
      this -> handleMovement();
      break;
    case 3:
      this -> handleCommunicate( objects );
      break;
    case 4:
      this -> handleAttack( objects );
      break;
    case 5:
      this -> handleExplore( objects );
      break;
    case 6:
      this -> record.saveToFile( &(this->player), this->rooms);
      break;
    case 7:
      cout << "bye" << endl;
      exit(0);
      break;
  }
}

void Dungeon::handleCommunicate(vector<Object*> objects){
  vector<NPC*> npc_list;
  npc_list.clear();
  for(int i = 0; i < objects.size(); i++){
    if(objects[i]->getTag() == "npc" ){
      NPC* nnpc = dynamic_cast<NPC*>( objects[i] );
      if(nnpc != NULL)
        npc_list.push_back( nnpc );
      cout << npc_list.size() << ": " << nnpc->getName() << endl;
    }
  }
  
  if(npc_list.size() == 0){
    cout << "There is nobody in this room." << endl;
    return;
  }

  int choice = -1;
  cout << "Which one do you want to talk to?";
  cin >> choice;
  if(choice > 0 && choice <= npc_list.size()){
    npc_list[choice] -> triggerEvent( &(this->player) );
  }
  else{
    cout << "invalid choice" << endl;
  }
}

void Dungeon::handleAttack(vector<Object*> objects){
  vector<Monster*> monster_list;
  monster_list.clear();
  for(int i = 0; i < objects.size(); i++){
    if(objects[i]->getTag() == "monster"){
      Monster* nmon = dynamic_cast<Monster*>( objects[i] );
      if(nmon != NULL)
        monster_list.push_back( nmon );
      cout << monster_list.size() << ": " << nmon->getName() << endl;
    }
  }

  if(monster_list.size() == 0){
    cout << "There is no monster here." << endl;
    return;
  }

  int choice = -1;
  cout << "Which monster you want to defeat?";
  cin >> choice;
  if(choice > 0 && choice <= monster_list.size()){
    monster_list[choice] -> triggerEvent( &(this->player) );
  }
  else{
    cout << "invalid choice" << endl;
  }
}

void Dungeon::handleExplore(vector<Object*> objects){
  vector<Item*> item_list;
  item_list.clear();
  for(int i = 0; i < objects.size(); i++){
    if(objects[i]->getTag() == "item"){
      Item* nitm = dynamic_cast<Item*>( objects[i] );
      if(nitm != NULL)
        item_list.push_back( nitm );
      cout << item_list.size() << ": " << nitm->getName() << endl;
    }
  }

  if(item_list.size() == 0){
    cout << "There is no treasure here." << endl;
    return;
  }

  int choice = -1;
  cout << "Which treasure you want to pick up?";
  cin >> choice;
  if(choice > 0 && choice <= item_list.size()){
    item_list[choice] -> triggerEvent( &(this->player) );
  }
  else{
    cout << "invalid choice" << endl;
  }
}

bool Dungeon::checkGameLogic(){
  if((this->player).checkIsDead()){
    cout << "Lose\n";
    return false;
  }
  if((this->player).getCurrentRoom() -> getIsExit()) {
    cout << "found exit";
    return false;
  }
  //if((this->boss).checkIsDead()) return false; implement later
  return true;
}

void Dungeon::runDungeon(){
  this -> startGame();
  //choose action
  while(this -> checkGameLogic()){
    Room* cur = this->player.getCurrentRoom();
    this -> chooseAction( cur->getObjects() );
  }

}
