#ifndef _BOMB_
#define _BOMB_
#include "Base.h"
#include "Player.h"
class Bomb{
	public:
		pair<int, int> location;
		int blast_time;
		int miss_time;
		int scale = 1;
};
#endif
