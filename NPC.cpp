#include "NPC.h"
#include<climits>
NPC::NPC() : GameCharacter(name, "NPC", INT_MAX, INT_MAX){
}

NPC::NPC(string name, string script, vector<Item> commodity) \
  : GameCharacter(name, "NPC". INT_MAX, INT_MAX), script(script), commodity(commodity){};

void NPC::listCommodity(){
  cout << "Commodity list: \n";
  for(int i = 0; i < this -> commodity.size(); i++){
    cout << this -> commodity.at(i).getName() << endl;
  }
}

bool NPC::triggerEvent(Object* obj){
  Player* player = dynamic_cast<Player*>(obj);
  if(player == NULL) return false;
  //call player's addItem to give the item to player'
  cout << "Choose the item you want: ";
  bool sucess = false;
  string query;
  while(!sucess){
    cin >> query;
    for(int i = 0; i < commodity.size(); i++){
        if(query == commodity.at(i)->getName()){
            player->addItem(commodity.at(i));
            this -> commodity.erase(i);
        }
    }
  }
  return true;
}

void NPC::listMember(ofstream& fout){
  fout << "tag " << this -> getTag() << endl;
  fout << "name " << this -> getName() << endl;
  fout << "maxHealth " << this -> getMaxHealth() << endl;
  fout << "currentHealth " << this -> getCurrentHealth() << endl;
  fout << "attack " << this -> getAttack() << endl;
  fout << "defense " << this -> getDefense() << endl;
  fout << "commodity : " << endl;
  for(int i = 0; i < commodity.size(); i++){
    fout << " - " << commodity[i].listMember();
  }
  fout << "script : " << endl;
  fout << "'''" << endl;
  fout << this -> getScript() << endl;
  fout << "'''" << endl;
  //undone
}
void NPC::setScript(string inp) : script(inp){}

void NPC::getCommodity(){
  return commodity;
}
