#ifndef GAME_TEST_H_1372368585_78
#define GAME_TEST_H_1372368585_78
/**
 * File: game_test.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-06-28 05:29:45.779000
 * Written In: Peking University, beijing, China
 */

#include "player.h"
#include "game.h"
#include "ai.h"

class GameTest {
public:
	GameTest() {
		// human_vs_human();
		AI_vs_AI();
	}
	
	void human_vs_human() {
		HumanPlayer black, white;
		Game game(black, white);
		game.start();
	}
	
	void AI_vs_AI() {
		// EasyAIPlayer black;
		// EasyAIPlayer white;
		
		// Look1AIPlayer black;
		Look1AIPlayer white;
		
		// Look2AIPlayer black;
		// Look2AIPlayer white;
		
		RandomAIPlayer black;
		// RandomAIPlayer white;
		
		// MonteCarloAIPlayer black;
		// MonteCarloAIPlayer white;
		
		
		uint total=10000;
		log_warn("start "<<total<<" games ...")
		uint win[3]={0, 0, 0};
		int total_diff=0;
		//比赛，多比几盘
		for_n(i, total) {
			// if (i%10==0)
				// log_warn("progress: "<<i<<"/"<<total);
			Game game(black, white);
			Score score=game.start();
			win[score.winner]+=1;
			total_diff+=score.diff();
		}
		log_warn("in "<<total<<" games: black:white="<<win[BLACK]<<":"<<win[WHITE]
			<<" draw="<<win[DRAW]<<" diff="<<total_diff);
	}
};

#endif /* GAME_TEST_H_1372368585_78 */
