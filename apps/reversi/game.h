#ifndef GAME_H_1371896260_1
#define GAME_H_1371896260_1
/**
 * File: game.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-06-22 18:17:40.104000
 * Written In: Peking University, beijing, China
 */

#include "player.h"

class Game {
public:
	Board board;
	
	Player& black;
	Player& white;
	
	uint pass_cnt;//PASS次数
	
	inline bool game_over() {//无子可下，或者连续两次PASS
		uchar& empty_cnt=board.total[EMPTY];
		return empty_cnt==0 OR pass_cnt>=2;
	}
	
	Game(Player& black, Player& white):black(black), white(white) {
		pass_cnt=0;
	}
	
	void start() {
		cout<<"Game Start!!"<<endl;
		while (!game_over()) {
			color& turn=board.turn;
			Player& player=(turn==BLACK)?black:white;
			uchar& mobility=board.total[ACTIVE];
			
			if (mobility==0) {
				board.pass();
				pass_cnt+=1;
			} else {
				player.play(board);
				pass_cnt=0;
			}
		}
		cout<<"Game Over!!"<<endl;
		
		board.dump();
		
		uint black_cnt=board.total[BLACK];
		uint white_cnt=board.total[WHITE];
		uint empty_cnt=board.total[EMPTY];
		cout<<"BLACK:"<<black_cnt<<" WHITE:"<<white_cnt<<" EMPTY:"<<empty_cnt<<endl;
		if (black_cnt>white_cnt) cout<<"winner is BLACK";
		else if (black_cnt<white_cnt) cout<<"winner is WHITE";
		else cout<<"draw game";
		cout<<endl;
	}
};

class GameTest {
public:
	GameTest() {
		// start_human_vs_human();
		start_AI_vs_AI();
	}
	
	void start_human_vs_human() {
		HumanPlayer black(BLACK), white(WHITE);
		Game game(black, white);
		game.start();
	}
	
	void start_AI_vs_AI() {
		AIPlayer black(BLACK), white(WHITE);
		Game game(black, white);
		game.start();
	}
};

#endif /* GAME_H_1371896260_1 */

