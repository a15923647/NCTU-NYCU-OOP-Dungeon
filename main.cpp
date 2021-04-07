#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "Dungeon.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "Room.h"
#include "Record.h"
#include "Object.h"

using namespace std;
int main(void){
    Dungeon dungeon = Dungeon();
    dungeon.runDungeon();
    return 0;
}
