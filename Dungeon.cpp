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
    
    this->rooms[ridx].setNoNPC(false);
    
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
    int h, a, d, att, xp;
    monster >> name >> h >> a >> d >> att >> xp;
	
    Monster* new_mon = new Monster(name, h, a, d, att);
    objs_tmp[ridx].push_back( new_mon );
    new_mon -> setXp( xp );
    
    int nodrop;
    monster >> nodrop;
    vector<Item> tmp_drop;
    tmp_drop.clear();
    while(nodrop--){
      string i_name;
      int i_h, i_a, i_d;
      monster >> i_name >> i_h >> i_a >> i_d;
      monster.ignore();
      tmp_drop.push_back( Item( i_name, i_h, i_a, i_d ) );
    }
	  new_mon -> setDrop( tmp_drop );
    
    this->rooms[ridx].setNoMon(false);
    
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
    
    rooms[ridx].setNoTrea(false);
    
	  treasure.ignore();
  }
  
  //bind all objects to coherent rooms
  for(int i = 0; \
      i < nor; \
	  this -> rooms[i].setObjects( objs_tmp[i] ), i++);
  
  //load skills
  ifstream skills_file( "skills" );
  int nosk;
  skills_file >> nosk;
  skills_file.ignore();
  while(nosk--){
    string name, tag;
    int cost, att, atk, mpCon, prof, prof_max;
    skills_file >> cost >> name >> tag >> att >> atk >> mpCon >> prof >> prof_max;
    skills_file.ignore();
    skill_repo.push_back( Skill(cost, name, tag, att, atk, mpCon, prof, prof_max) );
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

  while(ans != "U" && ans != "D" && ans != "L" && ans != "R"){
    cout << "which room you want to go?\n";
    if(u != NULL && (cur -> getNoMon() || u == pre))
      cout << "Up: U" << endl;
    if(d != NULL && (cur -> getNoMon() || d == pre))
      cout << "Down: D" << endl;
    if(l != NULL && (cur -> getNoMon() || l == pre))
      cout << "Left: L" << endl;
    if(r != NULL && (cur -> getNoMon() || r == pre))
      cout << "Right: R" << endl;
    cin >> ans;
  }

  if(ans == "U" && (cur -> getNoMon() || u == pre))
    player.changeRoom( u );
  else if(ans == "D" && (cur -> getNoMon() || d == pre))
    player.changeRoom( d );
  else if(ans == "L" && (cur -> getNoMon() || l == pre))
    player.changeRoom( l );
  else if(ans == "R" && (cur -> getNoMon() || r == pre))
    player.changeRoom( r );
  else
    cout << "Invalid choice" << endl;
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
    record.loadFromFile( &(this->player), this->rooms, this->skill_repo );
  }
  else if(choice == 3)
    exit(0);
}
/*
void Dungeon::chooseAction(Room* cur, vector<Object*> objects){
  int choice = -1;
  while(choice > 8 || choice < 1){
    cout << "choose your action" << endl;
    cout << "------------------------" << endl;
    cout << "1. check status and inventory" << endl;
    cout << "2. move to next room" << endl;
    cout << "3. communicate to someone" << endl;
    cout << "4. attack with monster" << endl;
    cout << "5. explore treasure" << endl;
    cout << "6. learn skills" << endl;
    cout << "7. save game" << endl;
    cout << "8. exit this game" << endl;
	#ifdef DEBUG
	cout << "8. debug" << endl;
	#endif
    cout << "your choice: ";
    cin >> choice;
  }

  switch(choice){
    case 1:
      this -> player.triggerEvent( &(this->player) );
      cout << "Show more information? (y/n)" << endl;
      char choice;
      cin >> choice;
      if(choice == 'y')
        this->player.showMoreInfo();
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
      this -> learnSkills();
    case 7:
      this -> record.saveToFile( &(this->player), this->rooms, this->skill_repo);
      break;
    case 8:
      cout << "bye" << endl;
      exit(0);
      break;
	  default:
	  cout << "Cannot recognize your choice.\n" << "Please select again.\n";
      cin >> choice;
      break;
  }
}
*/

void Dungeon::chooseAction(Room* cur, vector<Object*> objects){
  int choice = -1;
  /*
    chk state
    move
    learn
  
    handleAttack
    handleCommunicate
    handleExplore
  */
  //list all option
  cout << "choose your action" << endl;
  cout << "------------------------" << endl;
  cout << "1. check status and inventory" << endl;
  cout << "2. move to next room" << endl;
  cout << "3. learn some skills" << endl;
  
  int opt = 3;
  int monOpt = -1;
  int npcOpt = -1;
  int treaOpt = -1;
  if(!(cur -> getNoMon())){
    monOpt = ++opt;
    cout << opt << ". attack with monster" << endl;
  }
  if(!(cur -> getNoNPC())){
    npcOpt = ++opt;
    cout << opt << ". communicate to someone" << endl;
  }
  if(!(cur -> getNoTrea())){
    treaOpt = ++opt;
    cout << opt << ". explore treasure" << endl;
  }
  int saveOpt = ++opt;
  cout << opt << ". save record" << endl;
  int byeOpt = ++opt;
  cout << opt << ". exit this game" << endl;
  
  //call function
  cin >> choice;
  switch(choice){
    case 1:
      this -> player.triggerEvent( &(this->player) );
      cout << "Show more information? (y/n)" << endl;
      char ch;
      cin >> ch;
      if(ch == 'y')
        this->player.showMoreInfo();
      break;
    case 2:
      this -> handleMovement();
      break;
    case 3:
      this -> learnSkills();
    default:
      if(choice <= opt){
        if(choice == monOpt)
          this -> handleAttack( cur, objects );
        else if(choice == npcOpt)
          this -> handleCommunicate( objects );
        else if(choice == treaOpt)
          this -> handleExplore( cur, objects );
        else if(choice == saveOpt)
          this -> record.saveToFile( &(this->player), this->rooms, this->skill_repo);
        else if(choice == byeOpt)
          cout << "bye" << endl, exit(0);
      }
      else
        cout << "Invalid input" << endl;
  }
}
void Dungeon::learnSkills(){
  if(this->skill_repo.size() == 0){
    cout << "No skills can be learned.\n";
    return;
  }
  
  cout << "Which skill you want to learn?" << endl;
  cout << "your coin: " << this->player.getCoin() << endl;
  for(int i = 0; i < this->skill_repo.size(); i++){
    cout << i << endl;
    cout << "skill name: " << this->skill_repo[i].getName() << endl;
    cout << "cost: " << this->skill_repo[i].getCost() << endl;
    cout << this->skill_repo[i] << endl;
  }
  
  int choice;
  cin >> choice;
  if(choice < 0 || choice >= this->skill_repo.size()){
    cout << "Invalid choice!\n";
    return;
  }
  if(this->skill_repo[choice].getCost() > player.getCoin()){
    cout << "You don't have enough coin.\n";
    return;
  }
  
  this->player.setCoin( this->player.getCoin() - this->skill_repo[choice].getCost());
  this->player.addSkill( this->skill_repo[choice] );
  this->skill_repo.erase( this->skill_repo.begin() + choice );
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
  
	if(monster_list[choice - 1] -> checkIsDead()){
	  //monster dead, pop object from room
	  cur -> popObject( monster_list[choice - 1] );
    //to chk whether this room can be passed through
    if(monster_list.size()-1 == 0)
      cur -> setNoMon(true);
  }
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