#include "Monster.h"
Monster::Monster() {
  this -> setGameCharacter("default_monster", "monster", 10, 10, 10);
  this -> setMaxHealth(1000);
  this -> attribute_id = 0;
}

Monster::Monster(string name, int hp, int atk, int def, int att){
  this -> setGameCharacter(name, "monster", hp, atk, def);
  this -> setMaxHealth(1000);
  this -> attribute_id = att;
}

ostream& operator << (ostream& outputStream, Monster& mon){
  //print monster status
  outputStream << "Attribute: " << mon.getAtt() << endl;
  outputStream << "HP: " << mon.getCurrentHealth() << "/" << mon.getMaxHealth() << endl;
  outputStream << "Attack: " << mon.getAttack() << endl;
  outputStream << "Defense: " << mon.getDefense()  << endl;
  
  /*outputStream << "inventory: " << endl;
  for(int i = 0; i < mon.getInventory().size(); i++){
    outputStream << mon.getInventory().at(i).getName() << endl;
  }*///implement drop item
}

void Monster::reset(Monster& bk){
  this -> setGameCharacter(bk.getName(), "monster", bk.getCurrentHealth(), bk.getAttack(), bk.getDefense());
  this -> setMaxHealth( bk.getMaxHealth() );
  this -> setAtt( bk.getAtt() );
}

bool Monster::triggerEvent(Object* obj){
  //implement combat system
  /*
    backup this monster
    reset if player retreat
  */
  Monster mon_bk( *this );//use copy constructor
  
  //attack or retreat
  Player *player = dynamic_cast<Player*>(obj);
  if(player == NULL) return false;

  cout << "Encounter monster: " << this->getName() << endl;
  cout << "Select your choice: \n" << "0 : attack\n1 : retreat and go back to the previous room\n";
  cout << "Your choice: \n";
  string choice = "";
  while( !(player->checkIsDead()) && !(this->checkIsDead()) ){
    //combat until retreat or one die
    /*
      idea:
        input uuddllrrba to trigger magic attack
    */
    cin >> choice;
    while(choice != "0" && choice != "1" && choice != "uuddllrrba"){
      //input error
      cout << "Invalid input\nPlz choose again\nYour choice: \n";
      cin >> choice;
    }
    
    double m_dodge_rate = 0.5;//maybe create a member in GameCharacter
	  double p_dodge_rate = 0.5;
    srand( time(NULL) );
    
    if(choice == "1"){
      //reset monster
      this -> reset( mon_bk );
      player -> changeRoom( player->getPreviousRoom() );
      break;
    }
    else if( choice == "uuddllrrba" ){
      //player use skill
      //select skill to trigger skill event
      //check mp is enough for skill
      vector<Skill> plysk = player -> getSkills();
      cout << "select which skill you want to launch" << endl;
      cout << "Current MP: " << player->getMp() << endl;
      for(int i = 0; i < plysk.size(); i++)
        cout << i+1 << endl << plysk[i];
      int sk_choice;
      cin >> sk_choice;
      sk_choice--;
      if(sk_choice < 0 || sk_choice >= plysk.size()){
        cout << "Invalid choice!\n";
        continue;
      }
      if(plysk[sk_choice].getMpCon() > player->getMp()){
        cout << "Your Mp is not adequate\n";
        continue;
      }
      
      player -> consumeMp( plysk[sk_choice].getMpCon() );
      if(!plysk[sk_choice].triggerEvent( this ))
        cout << "launch fail." << endl;
    }
    else if(choice == "0"){//combat system
      //player uses normal attack
      if(player->getAttack() > this->getDefense() ){
        if( ((double)rand() / (RAND_MAX + 1.0) > m_dodge_rate ) )
          this -> takeDamage( player->getAttack() );
        else
          cout << "You sucessfully dodge attack" << endl;
      }
    }
    
    if(this -> checkIsDead()){
      cout << "victory" << endl;
      player -> getLevelO() -> increaseXp( player, this->xp );
      player -> heal();
      for(int i = 0; i < this->drop.size(); i++){
        player -> addItem( this->drop[i] );
      }
      return true;
    }
    
    //monster attack
    if( this -> getAttack() > player -> getDefense()){
      if((double)rand() / (RAND_MAX + 1.0) > p_dodge_rate)
        player -> takeDamage( this->getAttack() );
      else
        cout << this -> getName() << " sucessfully dodge your attac\n";
    }
	
	  cout << "Monster state" << endl;
    cout << this -> getName() << endl;
	  cout << *this << endl;
    
    cout << "Player state" << endl;
    cout << player -> getName() << endl;
    player -> triggerEvent( player );
  }
  return true;
}

void Monster::listMember(ofstream& roomFile){
  roomFile << this -> getName() << " ";
  roomFile << this -> getMaxHealth() << " ";
  roomFile << this -> getCurrentHealth() << " ";
  roomFile << this -> getAttack() << " ";
  roomFile << this -> getDefense() << " ";
  roomFile << this -> getAtt() << " ";
  roomFile << this->xp << endl;
  
  roomFile << this->drop.size() << endl;
  for(int i = 0; i < this->drop.size(); i++)
    this->drop[i].listMember( roomFile );
}

void Monster::loadMember(ifstream& roomFile){
  int mh, ch, atk, def, att, xp;
  string name;
  roomFile >> name >> mh >> ch >> atk >> def >> att >> xp;
  this -> setName(name);
  this -> setMaxHealth(mh);
  this -> setCurrentHealth(ch);
  this -> setAttack(atk);
  this -> setDefense(def);
  this -> setAtt(att);
  this->xp = xp;
  roomFile.ignore();
  
  int nodrop;
  roomFile >> nodrop;
  roomFile.ignore();
  while(nodrop--){
    this->drop.push_back( Item() );
    drop.back().loadMember( roomFile );
  }
}

int Monster::getAtt(){
  return this->attribute_id;
}

void Monster::setAtt(int atrid){
  this->attribute_id = atrid;
}

void Monster::setDrop(vector<Item> drop){
  this->drop = drop;
}

vector<Item> Monster::getDrop(){
  return this->drop;
}

void Monster::setXp(int xp){
  this->xp = xp;
}

int Monster::getXp(){
  return this->xp;
}