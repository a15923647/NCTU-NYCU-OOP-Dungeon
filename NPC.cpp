#include "NPC.h"
NPC::NPC(){
  this -> setGameCharacter("default_NPC", "NPC", INT_MAX, INT_MAX, INT_MAX);
}

NPC::NPC(string name, string script, vector<Item> commodity){
  this -> setGameCharacter(name, "NPC", INT_MAX, INT_MAX, INT_MAX);
  this -> script = script;
  this -> commodity = commodity;
}

void NPC::listCommodity(){
  cout << "Commodity list: \n";
  for(int i = 0; i < this -> commodity.size(); i++){
    cout << this -> commodity.at(i).getName() << endl;
  }
}

bool NPC::triggerEvent(Object* obj){//change to select number
  Player* player = dynamic_cast<Player*>(obj);
  if(player == NULL) return false;
  //call player's addItem to give the item to player
  for(int i = 0; i < this -> commodity.size(); i++){
    cout << this -> commodity[i].getName() << endl;
    #ifdef DEBUG
	cout << "  health: " << this -> getHealth() << endl;
    #endif	
  }
  cout << "Choose the item you want: ";
  bool sucess = false;
  string query;
  while(!sucess && this -> commodity.size() != 0){
    cin >> query;
    for(int i = 0; i < commodity.size(); i++){
        if(query == commodity.at(i).getName()){
            player->addItem( commodity.at(i) );
            this -> commodity.erase( this->commodity.begin() + i );//remove object
			sucess = true;
        }
    }
  }
  return true;
}

void NPC::listMember(ofstream& roomFile){
  roomFile << this -> getScript() << endl;
  roomFile << this -> getMaxHealth() << " ";
  roomFile << this -> getCurrentHealth() << " ";
  roomFile << this -> getAttack() << " ";
  roomFile << this -> getDefense() << " ";
  roomFile << this -> getName() << endl;
  vector<Item> commodity = this -> getCommodity();
  int size = commodity.size();
  roomFile << size << endl;
  for(int i = 0; i < size; i++){
    commodity[i].listMember(roomFile);
  }
}

void NPC::loadMember(ifstream& roomFile){
  //DEBUG
  cout << "load new NPC\n";
  string name, script, tmp;
  int mh, ch, atk, def;
  getline(roomFile, tmp);
  for(getline(roomFile, tmp); \
      tmp != ""; \
	  script += (tmp + "\n"), getline(roomFile, tmp));

  roomFile >> mh >> ch >> atk >> def >> name;
  getline(roomFile, tmp);//format alignment
  
  this -> setScript(script);
  this -> setMaxHealth(mh);
  this -> setCurrentHealth(ch);
  this -> setAttack(atk);
  this -> setDefense(def);
  this -> setName(name);
  //load commodity
  this -> commodity.clear();
  int size;
  roomFile >> size;
  while(size--){
    this -> commodity.push_back( Item() );
	this -> commodity.back().loadMember( roomFile );
  }
  
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
