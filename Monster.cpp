#include "Monster.h"
Monster::Monster() : setGameCharacter("default_monster", "monster", 10, 10, 10){

}
Monster::Monster(string name, int hp, int atk, int def) : 
  setGameCharacter(name, "monster", hp, atk, def) {}

bool Monster::triggerEvent(Object* obj){
  //implement combat system
  //attack or retreat
  Player *player = dynamic_cast<Player*>(obj);
  if(player == NULL) return false;

  cout << "Encounter monster: " << this->getName << endl;
  cout << "Select your choice: " << "0 : attack\n1 : retreat and go back to the previous room\n";
  cout << "Your choice: \n";
  string choice = "";
  while( !(player->checkIsDead()) && !(this->checkIsDead()) ){
    //combat until retreat or one die
    cin >> choice;
      while(choice != "0" || choice != "1"){
      //input error
      cout << "Invalid input\nPlz choose again\nYour choice: \n";
      cin >> choice;
    }
    if(choice == "1"){
      player -> changeRoom( player->getPreviousRoom() );
      break;
    }
    //combat system
    //player attack
    if(player->getAttack() > this->getDefense()){
      this -> takeDamage( player->getAttack() );
    }

    if(this -> checkIsDead()){
      break;
    }
    //monster attack
    if( this -> getAttack() > player -> getDefense() ){
      player -> takeDamage( this->getAttack() );
    }
  }

}

void Monster::listMember(ofstream& fout){
  fout << "tag " << this -> getTag() << endl;
  fout << "name " << this -> getName() << endl;
  fout << "maxHealth " << this -> getMaxHealth() << endl;
  fout << "currentHealth " << this -> getCurrentHealth() << endl;
  fout << "attack " << this -> getAttack() << endl;
  fout << "defense " << this -> getDefense() << endl;
}
