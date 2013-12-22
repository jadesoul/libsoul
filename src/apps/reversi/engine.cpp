/**
 * File: engine.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-06-24 17:49:20.175000
 * Written In: Peking University, beijing, China
 */

#define APP_NAME "EngineX"
#include "board.h"
#include "player.h"
#include "game.h"
#include "ai.h"

extern uint verbose=50;

bool check(char* s) {
	int n=strlen(s);
	if (n!=65) return false;
	for (int i=0; i<64; ++i) {
		if (!(s[i]=='0' || s[i]=='1' || s[i]=='2'))
			return false;
	}
	if (!(s[64]=='1' || s[64]=='2'))
		return false;
	return true;
}

//以CGI的形式作为服务器端游戏引擎，供web界面以Ajax形式调用
int main(int argc, char * argv[]) {
	cout<<"Content-Type: text/plain; charset=utf8\n\n";
	if (argc!=2 || !check(argv[1])) return -1;
	
	// EasyAIPlayer player;
	// Look2AIPlayer player;
	// RandomAIPlayer player;
	MonteCarloAIPlayer player;
	
	Player& black=player;
	Player& white=player;
	Game game(black, white);
	
	string query=argv[1];
	cout<<game.deal(query);
	return 0;
}
