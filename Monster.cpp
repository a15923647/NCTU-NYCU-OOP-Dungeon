#include "Monster.h"
Monster::Monster() {
  this -> setGameCharacter("default_monster", "monster", 10, 10, 10);
  this -> setMaxHealth(1000);
}

Monster::Monster(string name, int hp, int atk, int def){
  this -> setGameCharacter(name, "monster", hp, atk, def);
  this -> setMaxHealth(1000);
}

ostream& operator << (ostream& outputStream, Monster& mon){
  //print player status
  outputStream << "HP: " << mon.getCurrentHealth() << "/" << mon.getMaxHealth() << endl;
  outputStream << "Attack: " << mon.getAttack() << endl;
  outputStream << "Defense: " << mon.getDefense()  << endl;
  
  /*outputStream << "inventory: " << endl;
  for(int i = 0; i < mon.getInventory().size(); i++){
    outputStream << mon.getInventory().at(i).getName() << endl;
  }*/
}

bool Monster::triggerEvent(Object* obj){
  //implement combat system
  //attack or retreat
  Player *player = dynamic_cast<Player*>(obj);
  if(player == NULL) return false;

  cout << "Encounter monster: " << this->getName() << endl;
  cout << "Select your choice: \n" << "0 : attack\n1 : retreat and go back to the previous room\n";
  cout << "Your choice: \n";
  string choice = "";
  while( !(player->checkIsDead()) && !(this->checkIsDead()) ){
    //combat until retreat or one die
    cin >> choice;
    while(choice != "0" && choice != "1"){
      //input error
      cout << "Invalid input\nPlz choose again\nYour choice: \n";
      cin >> choice;
    }
    if(choice == "1"){
      player -> changeRoom( player->getPreviousRoom() );
      break;
    }
    //combat system
	srand( time(NULL) );
	double m_dodge_rate = 0.9;//maybe create a member in GameCharacter
    //player attack
    if(player->getAttack() > this->getDefense() ){
      if( ((double)rand() / (RAND_MAX + 1.0) > m_dodge_rate ) )
        this -> takeDamage( player->getAttack() );
      else
        cout << "You sucessfully dodge attack" << endl;
    }

    if(this -> checkIsDead()){
      cout << "victory" << endl;
      break;
    }
    //monster attack
	double p_dodge_rate = 0.5;
    if( this -> getAttack() > player -> getDefense()){
      if((double)rand() / (RAND_MAX + 1.0) > p_dodge_rate)
        player -> takeDamage( this->getAttack() );
      else
        cout << this -> getName() << " sucessfully dodge your attac\n";
    }
	
	cout << "Monster state" << endl;
    cout << this -> getName() << endl;
	player -> triggerEvent( player );
    
    cout << "Player state" << endl;
    cout << player -> getName() << endl;
    cout << *this;
  }

}

void Monster::listMember(ofstream& roomFile){
  roomFile << this -> getName() << " ";
  roomFile << this -> getMaxHealth() << " ";
  roomFile << this -> getCurrentHealth() << " ";
  roomFile << this -> getAttack() << " ";
  roomFile << this -> getDefense() << endl;
}

void Monster::loadMember(ifstream& roomFile){
  int mh, ch, atk, def;
  string name;
  roomFile >> name >> mh >> ch >> atk >> def;
  this -> setName(name);
  this -> setMaxHealth(mh);
  this -> setCurrentHealth(ch);
  this -> setAttack(atk);
  this -> setDefense(def);
  string fmt_alg;
  getline( roomFile, fmt_alg );
}
