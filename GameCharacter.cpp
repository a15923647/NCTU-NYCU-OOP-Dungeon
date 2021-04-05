#include "GameCharacter.h"

GameCharacter::GameCharacter() : name(""), maxHealth(0), currentHealth(0), attack(0), defense(0){

}

GameCharacter::GameCharacter(string name, string tag, int health, int attack, int defense) {
  this -> setName(name);
  this -> setTag(tag);
  this -> currentHealth = health;
  this -> attack = attack;
  this -> defense = defense;
}

bool GameCharacter::checkIsDead(){
  return currentHealth <= maxHealth && currentHealth <= 0;
}

int GameCharacter::takeDamage(int point){
  //return current health
  this -> currentHealth -= point;
  return getCurrentHealth();
}

void GameCharacter::setMaxHealth(int max) { this ->  maxHealth = max; }
void GameCharacter::setCurrentHealth(int cur) { this -> currentHealth = cur ;}
void GameCharacter::setAttack(int atk) { this -> attack = atk; }
void GameCharacter::setDefense(int def) { this -> defense = def; }
void GameCharacter::setGameCharacter(string name, string tag, int h, int a, int d){
  this -> setName(name);
  this -> setTag(tag);
  this -> setCurrentHealth(h);
  this -> setAttack(a);
  this -> setDefense(d);
}

int GameCharacter::getMaxHealth() { return this -> maxHealth; }
int GameCharacter::getCurrentHealth() { return this -> currentHealth; }
int GameCharacter::getAttack() { return this -> attack; }
int GameCharacter::getDefense() { return this -> defense; }

bool GameCharacter::triggerEvent(Object* obj){ return true; }
void GameCharacter::listMember(ofstream& ofs){ return; }
void GameCharacter::loadMember(ifstream& ifs){ return; }
