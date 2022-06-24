#include "Monster.h"
Monster::Monster() {
  this -> setGameCharacter("default_monster", "monster", 10, 10, 10);
  this -> setMaxHealth(100);
  this -> attribute_id = 0;
}

Monster::Monster(ifstream& fin){
  this -> setTag("monster");
  this -> loadMember( fin );
}

ostream& operator << (ostream& outputStream, Monster& mon){
  //print monster status
  outputStream << "Name: " << mon.getName() << endl;
  outputStream << "Attribute: " << mon.getAtt() << endl;
  outputStream << "HP: " << mon.getCurrentHealth() << "/" << mon.getMaxHealth() << endl;
  outputStream << "Attack: " << mon.getAttack() << endl;
  outputStream << "Defense: " << mon.getDefense()  << endl;
}

void Monster::reset(Monster& bk){
  this -> setGameCharacter(bk.getName(), "monster", bk.getCurrentHealth(), bk.getAttack(), bk.getDefense());
  this -> setMaxHealth( bk.getMaxHealth() );
  this -> setAtt( bk.getAtt() );
}

void listOpt(){
  cout << "Select your choice: " << endl;
  cout << "0 : attack" << endl;
  cout << "1 : use props" << endl;
  cout << "2 : retreat and go back to the previous room" << endl;
  cout << "Your choice: " << endl;
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
  
  
  //combat init
  string choice = "";
  vector<Skill> plysk = player -> getSkills();
  vector<Item> tmpi = player -> getInventory();
  vector<Item*> contiProps, inactProps;
  int tmpi_size = tmpi.size();
  for(int i = 0; i < tmpi_size; i++)
    if(tmpi[i].getContinuous())
      contiProps.push_back( &tmpi[i] );
    else if(!tmpi[i].getActive())
      inactProps.push_back( &tmpi[i] );
      
  int conti_size = contiProps.size();
  int inact_size = inactProps.size();
  
  //combat until retreat or one die
  while( !(player->checkIsDead()) && !(this->checkIsDead()) ){
    /*
      idea:
        input uuddllrrba to trigger magic attack
    */
    
    for(int i = 0; i < conti_size; i++)
      contiProps[i] -> triggerEvent( player );
    
    listOpt();
    cin >> choice;
    while(choice != "0" && choice != "1" && choice != "2" && choice != "uuddllrrba"){
      //input error
      cout << "Invalid input\nPlease choose again\nYour choice: \n";
      cin >> choice;
    }
    
    double m_dodge_rate = 0.5;//maybe create a member in GameCharacter
	  double p_dodge_rate = 0.5;
    srand( time(NULL) );
    if(choice == "1"){
      cout << "your prop list: " << endl;
      for(int i = 0; i < inact_size; i++)
        cout << i+1 << ": " << inactProps[i] -> getName() << endl;
      cout << "show more detail?(y/n)" << endl;
      char det;
      cin >> det;
      if(det == 'y'){
        cout << "select index" << endl;
        cout << "type 0 to quit" << endl;
        int idx;
        cin >> idx;
        while(idx > 0 && idx <= inact_size){
          idx--;
          cout << *inactProps[idx] << endl;
          cin >> idx;
        }
      }
      
      cout << "which props to use?" << endl;
      cout << "type 0 if don't want to use any" << endl;
      int idx;
      cin >> idx;
      idx--;
      if(idx >= 0 && idx < inact_size){
        int h = inactProps[idx] -> getHealth();
        int a = inactProps[idx] -> getAttack();
        int d = inactProps[idx] -> getDefense();
        int m = inactProps[idx] -> getMp();
        player -> increaseStates(h, a, d, m);
        inactProps[idx] -> decDur(1);
        if(inactProps[idx] -> getDurability() <= 0){
          player -> popProp(inactProps[idx]);
          inactProps.erase( inactProps.begin() + idx );
          inact_size--;
        }
        
        cout << "your state: " << endl;
        player -> triggerEvent( player );
      }
      continue;
    }
    else if(choice == "2"){
      //reset monster
      this -> reset( mon_bk );
      player -> changeRoom( player->getPreviousRoom() );
      player -> updateProp(inactProps);
      player -> setSkills(plysk);
      break;
    }
    else if(choice == "uuddllrrba"){
      //player use skill
      //select skill to trigger skill event
      //check mp is enough for skill
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
      cout << "your attack: " << player -> getAttack() << endl;
      cout << "Monster defense" << this->getDefense() << endl;
      int r = rand();
      double random_rate;
      for(int i = 0; i < 5; i++, r = rand());/*{
        random_rate = (double)r / (RAND_MAX + 1.0);
        cout << "r: " << r << endl;
        cout << "(double)r: " << (double)r << endl;
        cout << RAND_MAX + 1.0 << endl;
      }*/
      random_rate = (double)r / (RAND_MAX + 1.0);
      if(player->getAttack() > this->getDefense() ){
        if( ( random_rate > m_dodge_rate ) ){
          cout << "monster takes " << player->getAttack() << " points of damage" << endl;
          this -> takeDamage( player->getAttack() );
        }
        else
          cout << this -> getName() << " sucessfully dodge your attack\n";
      }
    }
    
    if(this -> checkIsDead()){
      cout << "victory" << endl;
      player -> getLevelO() -> increaseXp( player, this->xp );
      player -> heal();
      player -> updateProp(inactProps);
      player -> setSkills(plysk);
      for(int i = 0; i < this->drop.size(); i++){
        cout << "find trophy: " << endl;
        cout << this->drop[i] << endl;
        player -> addItem( this->drop[i] );
      }
      return true;
    }
    
    //monster attack
    if( this -> getAttack() > player -> getDefense()){
      if((double)rand() / (RAND_MAX + 1.0) > p_dodge_rate){
        cout << "you take " << this->getAttack() << "points of damage" << endl;
        player -> takeDamage( this->getAttack() );
      }
      else
        cout << "You sucessfully dodge attack" << endl;
    }
	
	  cout << "Monster state" << endl;
	  cout << *this << endl;
    
    cout << "Player state" << endl;
    player -> triggerEvent( player );
  }
  //used reference
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
  while(nodrop--)
    this->drop.push_back( Item( roomFile ) );
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