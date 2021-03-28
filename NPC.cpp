#include "NPC.h"
#include<climits>
NPC::NPC(){

}

NPC::NPC(string name, string script, vector<Item> commodity) \
  : GameCharacter(name, "NPC". INT_MAX, INT_MAX), script(script), commodity(commodity){};

void NPC::listCommodity(){
  cout << "Commodity list: \n";
  for(int i = 0; i < commodity.size(); i++){
    cout << commodity.at(i).getName() << endl;
  }
}
