#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

class Player;

class Level{
  private:
    int level;
    int xp;
    int maxXp;
    int hpBuff;
    int mpBuff;
    int maxHpBuff;
    int attackBuff;
    int defenseBuff;
  public:
    Level();
    Level(int );
    void setLevel(int );
    int getLevel();
    void increaseXp(Player*, int);
    int getXp();
    void calMaxXp();
    void calHpBuff();
    void calMpBuff();
    void calAttackBuff();
    void calDefenseBuff();
    void setBuff(Player*);
    void resetBuff(Player*);
};

#endif
