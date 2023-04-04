#ifndef _OPERATOR_
#define _OPERATOR_
#include "Base.h"
#include "Map.h"
#include "Bomb.h"
#include "Player.h"
char item(){
	int sign = rand() % 10 + 1;
	if(sign == 1) return 'F';
	if(sign == 3) return 'P';
	return '.';
}
void miss_bomb(Bomb &bom){
	int x = bom.location.first;
	int y = bom.location.second;
	if(Map[player1.location.first][player1.location.second] == '.'){
		player1.is_live = false;
	}
	if(Map[player2.location.first][player2.location.second] == '.'){
		player2.is_live = false;
	}
	if(Map[robot1.location.first][robot1.location.second] == '.'){
		robot1.is_live = false;
	}
	if(Map[robot2.location.first][robot2.location.second] == '.'){
		robot2.is_live = false;
	}
	Map[x][y] = ' ';
	for(int i = 0; i < 4; i++){
		int temx = x;
		int temy = y;
		for(int j = 1; j <= bom.scale; j++){
			if(Map[temx + dx[i]][temy + dy[i]] == '.') Map[temx + dx[i]][temy + dy[i]] = ' ';
			temx = temx + dx[i];
			temy = temy + dy[i];
		}
		
	}
	return;
	
}
void blast_bomb(Bomb &bom, Player &p){
	Map[bom.location.first][bom.location.second] = '.';
	for(int i = 0; i < 4; i++){
		int x = bom.location.first + dx[i];
		int y = bom.location.second + dy[i];
		for(int j = 1; j <= bom.scale; j++){
			if(x <= 0 || x > row || y <= 0 || y > col) continue;
			if(Map[x][y] == 'O'){
				p.score++;
				Map[x][y] = item();
				break;
			}
			else if(Map[x][y] != 'X') Map[x][y] = '.';
			else if(Map[x][y] == 'X') break;
			x = x + dx[i];
			y = y + dy[i];
		}
		
	}
	bom.miss_time = 2;
}
void set_bomb(Player &p){
	if(p.is_set) return;
	if(!p.is_live) return;
	Map[p.location.first][p.location.second] = '*';
	p.bomb_num++;
	if(p.bomb_num == 999) p.bomb_num = 1;
	p.bomb[p.bomb_num].location.first = p.location.first;
	p.bomb[p.bomb_num].location.second = p.location.second;
	p.bomb[p.bomb_num].scale = p.power;
	p.bomb[p.bomb_num].blast_time = 5;
	p.is_set = true;
	return;
}
//炸弹爆炸
void deal_with_bomb(Player &p){
	if(p.bomb_time) return;
	else p.bomb_time = 20;
	for(int i = 1; i <= p.bomb_num; i++){
		if(p.bomb[i].blast_time == 1){
			blast_bomb(p.bomb[i], p);
			p.is_set = false;
			p.bomb[i].blast_time = 0;
		}
		else if(p.bomb[i].blast_time) p.bomb[i].blast_time--;
		if(p.bomb[i].miss_time == 1){
			miss_bomb(p.bomb[i]);
			p.bomb[i].miss_time = 0;
		}
		else if(p.bomb[i].miss_time) p.bomb[i].miss_time--;
	}
	return;
}
void deal_with_input(){
	if(_kbhit()){
		char key = _getch();
		if(key == -32) key = _getch();
		//cout << "you have pressed " << (int)key << " " << key <<endl;
		switch(key){
			case 'w':
			case 'a':
			case 's':
			case 'd':
				player1.update_location(key);
				break;
			case ' ':
				set_bomb(player1);
				break;
			case 72:
			case 75:
			case 77:
			case 80:
				player2.update_location(key);
				break;
			case 13:
				set_bomb(player2);
				break;
		}
		//todo
	}
	return;
}
void init(){
	for(int i = 0; i < row + 2; i++){
		for(int j = 0; j < col + 2; j++){
			Map[i][j] = Map_origin[i][j];
		}
	}
	player1 = Player(1, 1, '$');
	player2 = Player(1, col, '#');
	robot1 = Player(row, col, '&');
	robot2 = Player(row, 1, '@');
	Map[player1.location.first][player1.location.second] = '$';
	Map[player2.location.first][player2.location.second] = '#';
	Map[robot1.location.first][robot1.location.second] = '&';
	Map[robot2.location.first][robot2.location.second] = '@';
	return;
};
void deal_with_counter(Player &p){
	if(p.move_time) p.move_time--;
	if(p.bomb_time) p.bomb_time--;
	return;
}
void automatic(){
	robot_time++;
	if(robot_time == 50){
		robot1.update_location('a');
		robot2.update_location('d');
		return;
	}
	if(robot_time == 100){
		set_bomb(robot1);
		set_bomb(robot2);
		return;
	}
	if(robot_time == 110){
		robot1.update_location('d');
		robot2.update_location('a');
		return;
	}
	if(robot_time == 150){
		robot1.update_location('w');
		robot2.update_location('w');
		return;
	}
	if(robot_time == 250){
		robot1.update_location('s');
		robot2.update_location('s');
		robot_time = 0;
		return;
	}
	return;
}
void deal_with_timer(){
	deal_with_bomb(player1);
	deal_with_bomb(player2);
	deal_with_bomb(robot1);
	deal_with_bomb(robot2);
	deal_with_counter(player1);
	deal_with_counter(player2);
	deal_with_counter(robot1);
	deal_with_counter(robot2);
}
bool check(){
	if(!robot1.is_live && !robot2.is_live){
		system("cls");
		printf("We win !!!\n");
		printf("\n");
		printf("player1's score is %d\n", player1.score);
		printf("player2's score is %d\n", player2.score);
		return false;
	}
	if(!player1.is_live && !player2.is_live){
		system("cls");
		printf("We lose !!!\n");
		printf("\n");
		printf("player1's score is %d\n", player1.score);
		printf("player2's score is %d\n", player2.score);
		return false;	
	};
	return true;
}
void display(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	SetConsoleCursorPosition( hConsole, coordScreen );
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	//打印地图
	printf("F : 增加移动速度          P : 增加炸弹威力\n");
	for(int i = 0 ; i <= row + 1; i++){
		for(int j = 0; j <= col + 1; j++){
			printf("%c ", Map[i][j]);
		}
		printf("\n");
	}
	printf("player1's score is %d        ", player1.score);
	printf("\n");
	printf("player1's power is %d        ", player1.power);
	printf("player1's speed is %d        ", 10 - player1.speed);
	printf("\n");
	printf("-------------------------------------------------");
	printf("\n");
	printf("player2's score is %d        ", player2.score);
	printf("\n");
	printf("player2's power is %d        ", player2.power);
	printf("player2's speed is %d        ", 10 - player2.speed);
	printf("\n");
	printf("=================================================================\n");
	printf("robot1's score is %d        \n", robot1.score);
	printf("robot2's score is %d        \n", robot2.score);
	
 // 打 印 显 示 的 信 息
}
#endif
