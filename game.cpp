#include "Base.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Operator.h"
using namespace std;
int main(){
	srand(time(0));
	init();
	display();
	while(1){
		deal_with_input();
		display();
		deal_with_timer();
		if(!check()){
			system("pause");
			Sleep(500);
			return 0;
		}
		automatic();
	}	
	return 0;
}
