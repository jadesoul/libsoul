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
	
	uint white_cnt;
	uint black_cnt;
	uint empty_cnt;
	
	Game(Player& black, Player& white):black(black), white(white) {
		white_cnt=black_cnt=2;
		empty_cnt=60;
	}
	
	void start() {
		// while ()
	}
};

#endif /* GAME_H_1371896260_1 */

