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

void NPC::setScript(string inp) : script(inp){}

void NPC::getCommodity(){
  return commodity;
}
