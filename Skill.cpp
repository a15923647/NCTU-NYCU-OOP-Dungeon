#include "Skill.h"

using namespace std;

Skill::Skill(){
  this -> setName( "fire ball" );
  this -> setTag( "skill" );
  this->attribute_id = 1;
  this->attack = 10;
  this->mpConsumption = 2;
  this->proficiency = 0;
  this->proficiency_max = 10;
}

Skill::Skill(int cost, string name, string tag, int att, int atk, int mpc, int prof, int prof_max){
  this->cost = cost;
  this -> setName( name );
  this -> setTag( tag );
  this->attribute_id = att;
  this->attack = atk;
  this->mpConsumption = mpc;
  this->proficiency = prof;
  this->proficiency_max = prof_max;
}

Skill::Skill(ifstream& fin){
  this -> loadMember( fin );
}

void Skill::setAtt(int atr){this->attribute_id = atr;}
void Skill::setMpCon(int mc){this->mpConsumption = mc;}
void Skill::setAtk(int atk){this->attack = atk;}
void Skill::setProf(int prof){this->proficiency = prof;}
void Skill::setCost(int co){this->cost = co;}

int Skill::getAtt(){return this->attribute_id;}
int Skill::getMpCon(){return this->mpConsumption;}
int Skill::getAtk(){return this->attack;}
int Skill::getProf(){return this->proficiency;}
int Skill::getCost(){return this->cost;}

string atrid2atr(int atrid){
  switch(atrid){
    case 0:
      return "ice";
      break;
    case 1:
      return "fire";
      break;
    case 2:
      return "grass";
      break;
    default:
      return "unknown";
      break;
  }
}

/*
  show skill info
*/
ostream& operator <<(ostream& out, Skill& sk){
  out << "attribute: " << atrid2atr(sk.attribute_id) << endl;
  out << "attack: " << sk.attack << endl;
  out << "proficiency: " << sk.proficiency << "/" << sk.proficiency_max << endl;
  out << "MP consumption: " << sk.mpConsumption << endl;
}


/*
Fight monster via skill
* ensure magic can be launched
* type counter
* proficiency buff
* calculate attack
* proficiency++
*/
bool Skill::triggerEvent(Object* mon){//Monster object
  Monster* monster = dynamic_cast<Monster*>(mon);
  if(!monster)
    return false;
  int final_attack = this->attack;
  //type counter
  srand( time(NULL) );
  if((this->getAtt() - monster->getAtt() - NOATT) % NOATT == -1)
    final_attack = (int)((1+rand()/RAND_MAX) * final_attack);
  
  final_attack = (int)((1+0.1 * this->proficiency) * final_attack);
  
  cout << "your magic attack point: " << final_attack << endl;
  cout << "monster defense point: " << monster -> getDefense() << endl;
  
  double m_magic_dodge_rate = 0.1;
  
  if(monster->getDefense() < final_attack)
    if(((double)rand() / (RAND_MAX + 1.0) > m_magic_dodge_rate))
      monster -> takeDamage( final_attack );
    else
      cout << "monster dodged your attack" << endl;
  
  if(this->proficiency <= this->proficiency_max)
    this->proficiency++;
  
  return true;
}

void Skill::listMember(ofstream& roomFile){
  roomFile << this->cost << " ";
  roomFile << this->getName() << " ";
  roomFile << this->getTag() << " ";
  roomFile << this->attribute_id << " ";
  roomFile << this->attack << " ";
  roomFile << this->mpConsumption << " ";
  roomFile << this->proficiency << " ";
  roomFile << this->proficiency_max << endl;
}

void Skill::loadMember(ifstream& roomFile){
  string name, tag;
  int att, atk, mpc, prof, prof_max, cost;
  roomFile >> cost >> name >> tag >> att >> atk >> mpc >> prof >> prof_max;
  roomFile.ignore();
  
  this->cost = cost;
  this -> setName( name );
  this -> setTag( tag );
  this->attribute_id = att;
  this->attack = atk;
  this->mpConsumption = mpc;
  this->proficiency = prof;
  this->proficiency_max = prof_max;
}