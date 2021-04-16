#include "Dungeon.h"
//#define DEBUG 1
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
  if(i < str.length()) str = str.substr( i + 1 );
  else str = "";

  return res;
}

void Dungeon::createMap(){
  ifstream map("map");
  if(!map.good()){
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
  
  //for loading objects
  string inp_line, name;
  int ridx = 0;
  vector<Object*> objs_tmp[nor];
  //init all objs_tmp
  for(int i = 0; \
      i < nor; \
      objs_tmp[i] = this -> rooms[i].getObjects(), i++);
  
  //load NPC
  ifstream npc( "npc" );
  if(!npc.good())
    cerr << "open npc file fail.\nPlease ensure the file exists." << endl, exit(0);
  int coin;
  string script;
  vector<Item> cmd;
  cmd.clear();
  NPC* new_npc;
  
  int nonpc;
  npc >> nonpc;
  npc.ignore();
  
  while(nonpc--){
    npc >> name >> ridx >> coin;
    npc.ignore();
    new_npc = new NPC;
    new_npc -> setName( name );
    new_npc -> setCoin( coin );
    objs_tmp[ridx].push_back( new_npc );
    
    int scr_line;
    string tmp;
    npc >> scr_line;
    npc.ignore();
    while(scr_line--)
      getline( npc, tmp ), script += (tmp + '\n');
    new_npc -> setScript( script );
    
    int noi;
    npc >> noi;
    npc.ignore();
    while(noi--){
      string itmName;
      int h, a, d, va, dur;
      npc >> itmName >> h >> a >> d >> va >> dur;
      npc.ignore();
      Item nitm(itmName, h, a, d);
      nitm.setValue(va);
      nitm.setDurability(dur);
      cmd.push_back( nitm );
    }
    new_npc -> setCommodity(cmd);
  }
  
  //load Monster
  ifstream monster("Monster");
  if(!monster.good())
    cerr << "open monster file fail.\nPlease ensure the file exists." << endl, exit(0);
  
  if(!monster.eof()) 
    monster >> ridx;
  while(!monster.eof() && ridx != -3){
    int h, a, d;
    monster >> name >> h >> a >> d;
	
    Monster* new_mon = new Monster(name, h, a, d);
    objs_tmp[ridx].push_back( new_mon );
	
	  monster >> ridx;
  }
  
  //load treasure
  int notr;//number of treasure
  ifstream treasure("treasure");
  treasure >> notr;
  while(notr--){
    string t_name;
	  int t_h, t_a, t_d, t_va, t_dur;
	  treasure >> ridx >> t_name >> t_h >> t_a >> t_d >> t_va >> t_dur;
    
	  Item* nt = new Item( t_name, t_h, t_a, t_d );
    nt -> setValue(t_va);
    nt -> setDurability(t_dur);
    objs_tmp[ridx].push_back( nt );
  
	  treasure.ignore();
  }
  
  //bind all objects to coherent rooms
  for(int i = 0; \
      i < nor; \
	  this -> rooms[i].setObjects( objs_tmp[i] ), i++);
}

void Dungeon::handleMovement(){
  Room* cur = this -> player.getCurrentRoom();
  Room* pre = this -> player.getPreviousRoom();

  Room* u = cur -> getUpRoom();
  Room* d = cur -> getDownRoom();
  Room* l = cur -> getLeftRoom();
  Room* r = cur -> getRightRoom();
  
  string ans = "";

  while(ans != "U" && ans != "D" && ans != "L" && ans != "R"){
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

void Dungeon::chooseAction(Room* cur, vector<Object*> objects){
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
	#ifdef DEBUG
	cout << "8. debug" << endl;
	#endif
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
      this -> handleAttack( cur, objects );
      break;
    case 5:
      this -> handleExplore( cur, objects );
      break;
    case 6:
      this -> record.saveToFile( &(this->player), this->rooms);
      break;
    case 7:
      cout << "bye" << endl;
      exit(0);
      break;
	  #ifdef DEBUG
	  case 8:
	    this -> debug();
	    break;
	  #endif
	  default:
	  cout << "Cannot recognize your choice.\n" << "Please select again.\n";
      cin >> choice;
      break;
  }
}


void Dungeon::handleCommunicate(vector<Object*> objects){
  vector<NPC*> npc_list;
  npc_list.clear();
  for(int i = 0; i < objects.size(); i++){
    if(objects[i]->getTag() == "NPC" ){
      NPC* nnpc = dynamic_cast<NPC*>( objects[i] );
      if(nnpc != NULL){
        npc_list.push_back( nnpc );
        cout << npc_list.size() << ": " << nnpc->getName() << endl;
	    }
    }
  }
  
  if(npc_list.size() == 0){
    cout << "There is nobody in this room." << endl;
    return;
  }

  int choice = -1;
  cout << "Which one do you want to talk to?";
  cin >> choice;
  if(choice > 0 && choice <= npc_list.size())
    npc_list[choice - 1] -> triggerEvent( &(this->player) );
  else
    cout << "invalid choice" << endl;
}

void Dungeon::handleAttack(Room* cur, vector<Object*> objects){
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
  if(choice > 0 && choice <= monster_list.size())
    monster_list[choice - 1] -> triggerEvent( &(this->player) );
  
	if(monster_list[choice - 1] -> checkIsDead())
	  //monster dead, pop object from room
	  cur -> popObject( monster_list[choice - 1] );
  else
    cout << "invalid choice" << endl;
}

void Dungeon::handleExplore(Room* cur, vector<Object*> objects){
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
    item_list[choice - 1] -> triggerEvent( &(this->player) );
	  cur -> popObject( item_list[choice - 1] );//remove from room after being picked up
  }
  else
    cout << "invalid choice" << endl;
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
    this -> chooseAction( cur, cur->getObjects() );
  }
}

void Dungeon::debug(){
  cout << "about room: " << endl;
  Room* cur = this -> player.getCurrentRoom();
  vector<Object*> robjs = cur -> getObjects();
  cout << "objects:" << endl;
  for(int i = 0; i < robjs.size(); i++){
    cout << robjs[i]->getName() << endl;
  }
}