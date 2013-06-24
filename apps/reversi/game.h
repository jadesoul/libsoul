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
	
	inline uint white_cnt() {
		return board.total[WHITE];
	}
	
	inline uint black_cnt() {
		return board.total[BLACK];
	}
	
	inline uint empty_cnt() {
		return board.total[EMPTY];
	}
	
	inline uint mobility() {
		return board.total[ACTIVE];
	}
	
	inline bool game_over() {//无子可下，或者连续两次PASS
		return empty_cnt()==0 OR pass_cnt>=2;
	}
	
	Game(Player& black, Player& white):black(black), white(white) {
		pass_cnt=0;
	}
	
	void start() {
		// while (!game_over()) {
			// color& turn=board.turn;
			// if (turn==BLACK) {
				// if (mobility()==0) {
					// pass_cnt+=1;
					// turn=WHITE;
				// } else {
					// black.play(board);
					// pass_cnt=0;
				// }
			// } else {
				// if (mobility()==0) {
					// pass_cnt+=1;
					// turn=BLACK;
				// } else {
					// white.play(board);
					// pass_cnt=0;
				// }
			// }
		// }
		
		while (!game_over()) {
			color& turn=board.turn;
			Player& player=(turn==BLACK)?black:white;
			
			if (mobility()==0) {
				pass_cnt+=1;
				player.pass(board);
			} else {
				black.play(board);
				pass_cnt=0;
			}
			
		}
	}
};

class GameTest {
public:
	GameTest() {
		play();
	}
	
};

#endif /* GAME_H_1371896260_1 */

