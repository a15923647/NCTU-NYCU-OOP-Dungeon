#include "NPC.h"
class Player;
class NPC;
NPC::NPC(){
  this -> setGameCharacter("default_NPC", "NPC", INT_MAX, INT_MAX, INT_MAX);
}

NPC::NPC(ifstream& fin){
  this -> setTag("NPC");
  this -> loadMember(fin);
}

void NPC::listCommodity(){
  cout << "Commodity list: \n";
  for(int i = 0; i < this -> commodity.size(); i++){
    cout << this -> commodity.at(i).getName() << endl;
  }
}

bool NPC::triggerEvent(Object* obj){
  Player* player = dynamic_cast<Player*>(obj);
  if(player == NULL) return false;
  
  cout << this -> getScript() << endl;
  
  cout << "What do you want to do?" << endl;
  cout << "1: buy some stock" << endl;
  cout << "2: sale something to me" << endl;
  string choice;
  cin >> choice;
  while(choice != "1" && choice != "2"){
    cout << "invalid choice\n" << "choose again\n";
    cin >> choice;
  }
  
  if(choice == "1"){
    cout << "What do you want to buy?" << endl;
    for(int i = 0; i < this -> commodity.size(); i++){
      cout << (i+1) << '.' << this -> commodity[i].getName() << " : " << this -> commodity[i].getValue() << endl;
    }
    int chkout;
    cout << "check out more information about item" << endl;
    cout << "input the item index of which you are interested in" << endl;
    cout << "enter \'0\' to quit" << endl;
    cin >> chkout;
    while(chkout != 0){
      chkout--;
      if(chkout >= 0 && chkout < commodity.size())
        cout << commodity[chkout];
      else
        cout << "Invalid index\nchoose again" << endl;
      cin >> chkout;
    }
    
    cout << "Input item index of which you want to buy" << endl;
    cout << "Type \'0\' to quit" << endl;
    int idx;
    cin >> idx;
    
    if(idx == 0)
      return true;
    
    idx--;
    
    if(NPC::exchange((Object*)player, (Object*)this, this->commodity[idx]))
      cout << "close a deal" << endl;
  }
  else if(choice == "2"){
    cout << "Which item you want to sale?" << endl;
    vector<Item> pinv = player->getInventory();
    for(int i = 0; i < pinv.size(); i++){
      cout << (i+1) << '.' << pinv[i].getName() << " : " << pinv[i].getValue() << endl;
    }
    
    int chkout;
    cout << "Input item index to acquire more information" << endl;
    cout << "enter \'0\' to quit" << endl;
    cin >> chkout;
    while(chkout != 0){
      chkout--;
      if(chkout >=0 && chkout < pinv.size())
        cout << pinv[chkout];
      else
        cout << "Invalid index\nchoose again" << endl;
      cin >> chkout;
    }
    
    cout << "Input item index of which you want to sale" << endl;
    cout << "Type \'0\' to quit" << endl;
    int idx;
    cin >> idx;
    
    if(idx == 0)
      return true;
    
    idx--;
    
    if(NPC::exchange((Object*)this, (Object*)player, pinv[idx]))
      cout << "close a deal" << endl;
  }
}

void NPC::listMember(ofstream& roomFile){
  int scr_line_cnt = 0;
  for(int i = 0; i < this->script.size(); i++)
    if(this->script[i] == '\n') scr_line_cnt++;
  
  roomFile << scr_line_cnt << endl;
  roomFile << this -> getScript() << endl;
  roomFile << this -> getMaxHealth() << " ";
  roomFile << this -> getCurrentHealth() << " ";
  roomFile << this -> getAttack() << " ";
  roomFile << this -> getDefense() << " ";
  roomFile << this -> getName() << " ";
  roomFile << this -> getCoin() << endl;
  vector<Item> commodity = this -> getCommodity();
  int size = commodity.size();
  roomFile << size << endl;
  for(int i = 0; i < size; i++){
    commodity[i].listMember(roomFile);
  }
}

void NPC::loadMember(ifstream& roomFile){
  string name, script, tmp;
  int scr_line_cnt, mh, ch, atk, def, co;
  roomFile >> scr_line_cnt;
  roomFile.ignore();
  
  while(scr_line_cnt--){
    getline(roomFile, tmp);
    script += (tmp + "\n");
  }
  roomFile.ignore();
  /*for(getline(roomFile, tmp); \
      tmp != ""; \
	  script += (tmp + "\n"), getline(roomFile, tmp));*/

  roomFile >> mh >> ch >> atk >> def >> name >> co;
  roomFile.ignore();
  
  this -> setScript(script);
  this -> setMaxHealth(mh);
  this -> setCurrentHealth(ch);
  this -> setAttack(atk);
  this -> setDefense(def);
  this -> setName(name);
  this -> setCoin(co);
  //load commodity
  this -> commodity.clear();
  int size;
  roomFile >> size;
  while(size--)
    this -> commodity.push_back( Item( roomFile ) );
}

bool NPC::exchange(Object* buyer, Object* saler, Item& item){
  if(dynamic_cast<NPC*>( buyer ) && dynamic_cast<Player*>( saler )){
    NPC* b = dynamic_cast<NPC*>( buyer );
    Player* s = dynamic_cast<Player*>( saler );
    //Player -> NPC
    if(b->getCoin() >= item.getValue()){
      //xchg coin
      b->setCoin( b->getCoin() - item.getValue() );
      s->setCoin( s->getCoin() + item.getValue() );
      //xchg item
      vector<Item> bycom = b->getCommodity();
      bycom.push_back( item );
      b->setCommodity( bycom );
      
      vector<Item> sainv = s->getInventory();
      int idx = 0;
      bool sucess = false;
      while(idx < sainv.size() && !sucess){
        if(sainv[idx] == item){
          sainv.erase( sainv.begin() + idx );
          sucess = true;
          //avoid negative chk should be implement
          s->increaseStates( -item.getHealth(), -item.getAttack(), -item.getDefense(), -item.getMp() );
        }
        idx++;
      }
      s->setInventory( sainv );
      
      return true;
    }
    else
      cout << "Buyer has not enough amount of money.\n";
    return false;
  }
  else if(dynamic_cast<Player*>( buyer ) && dynamic_cast<NPC*>( saler )){
    Player* b = dynamic_cast<Player*>( buyer );
    NPC* s = dynamic_cast<NPC*>( saler );
    
    //NPC -> Player
    if(b->getCoin() >= item.getValue()){
      //xchg coin
      b->setCoin( b->getCoin() - item.getValue() );
      s->setCoin( s->getCoin() + item.getValue() );
      //xchg item
      b->addItem(item);
      
      vector<Item> sacom = s->getCommodity();
      int idx = 0;
      bool sucess = false;
      while(idx < sacom.size() && !sucess){
        if(sacom[idx] == item){
          sacom.erase( sacom.begin() + idx );
          sucess = true;
        }
        idx++;
      }
      s->setCommodity( sacom );
      
      return true;
    }
    else
      cout << "Buyer has not enough amount of money.\n";
  }
  else{
    cerr << "cast fail\n";
  }
  return false;
}

void NPC::setScript(string inp){
  this -> script = inp;
}

vector<Item> NPC::getCommodity(){
  return this -> commodity;
}

void NPC::setCommodity(vector<Item> cmt){
  this -> commodity = cmt;
}

string NPC::getScript(){
  return this -> script;
}

void NPC::setCoin(int co){
  this -> coin = co;
}

int NPC::getCoin(){
  return this -> coin;
}