#ifndef _PLAYER_
#define _PLAYER_
#include "Map.h"
#include "Base.h"
#include "Bomb.h"
class Player{
	public:
		pair<int, int> location;
		char symbol;
		Bomb bomb[1000];
		int power = 1;
		int bomb_num = 0;
		int speed = 10;
		int move_time = 10;
		int bomb_time = 20;
		int score = 0;
		bool is_live = true;
		bool is_delete = false;
		bool is_set = false;
		Player(int x, int y, char symbol){
			this->location.first = x;
			this->location.second = y;
			this->symbol = symbol;
		};
		
		//¸üÐÂÎ»ÖÃ
		void update_location(char type){
			if(! this->is_live) return;
			if(this->move_time) return;
			if(Map[location.first][location.second] == this->symbol)
				Map[location.first][location.second] = ' ';
			switch(type){
				case 'w':
				case 72:
					if(Map[location.first - 1][location.second] == ' ' || Map[location.first - 1][location.second] == '.' || Map[location.first - 1][location.second] == 'F' || Map[location.first - 1][location.second] == 'P')
						location.first -= 1;
					break;
				case 's':
				case 80:
					if(Map[location.first + 1][location.second] == ' ' || Map[location.first + 1][location.second] == '.' || Map[location.first + 1][location.second] == 'F' || Map[location.first + 1][location.second] == 'P')
						location.first += 1;
					break;
				case 'a':
				case 75:
					if(Map[location.first][location.second - 1] == ' ' || Map[location.first][location.second - 1] == '.' || Map[location.first][location.second - 1] == 'F' || Map[location.first][location.second - 1] == 'P')
						location.second -= 1;
					break;
				case 'd':
				case 77:
					if(Map[location.first][location.second + 1] == ' ' || Map[location.first][location.second + 1] == '.' || Map[location.first][location.second + 1] == 'F' || Map[location.first][location.second + 1] == 'P')
						location.second += 1;
					break;
			}
			if(Map[location.first][location.second] == '.') this->is_live = false;
			if(Map[location.first][location.second] == ' ' || Map[location.first][location.second] == 'F' || Map[location.first][location.second] == 'P'){
				if(Map[location.first][location.second] == 'F' && this->speed >= 2) this->speed -= 2;
				if(Map[location.first][location.second] == 'P' && this->power < 4) this->power++;
				Map[location.first][location.second] = this->symbol;
			}
			this->move_time = this->speed; 
			return;
		}
};	
Player player1(1, 1, '$');
Player player2(1, col, '#');
Player robot1(row, col, '&');
Player robot2(row, 1, '@');
#endif
