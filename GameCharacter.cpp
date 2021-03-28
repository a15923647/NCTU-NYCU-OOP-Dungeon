#include "GameCharacter.h"

GameCharacter::GameCharacter() : name(""), maxHealth(0), currentHealth(0), attack(0), defense(0){

}

GameCharacter::GameCharacter(string name, string tag, int health, int attack, int defense) {
  this -> name = name;
  this -> tag = tag;
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

void GameCharacter::setMaxHealth(int max) : maxHealth(max) {}
void GameCharacter::setCurrentHealth(int cur) : currentHealthHealth(cur) {}
void GameCharacter::setAttack(int atk) : attack(atk) {}
void GameCharacter::setDefense(int def) : defense(def) {}

int GameCharacter::getMaxHealth() { return this -> maxHealth; }
int GameCharacter::getCurrentHealth() { return this -> currentHealth; }
int GameCharacter::getAttack() { return this -> attack; }
int GameCharacter::getDefense() { return this -> defense; }
