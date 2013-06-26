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
	
	Game(Player& black, Player& white):black(black), white(white), pass_cnt(0) {}
	
	void start() {
		log_status("Game Start!!");
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
		log_status("Game Over!!");
		
		log_debug(board);
		
		uint black_cnt=board.total[BLACK];
		uint white_cnt=board.total[WHITE];
		uint empty_cnt=board.total[EMPTY];
		log_status("BLACK:"<<black_cnt<<" WHITE:"<<white_cnt<<" EMPTY:"<<empty_cnt);
		if (black_cnt>white_cnt) {
			log_status("winner is BLACK");
		} else if (black_cnt<white_cnt) {
			log_status("winner is WHITE");
		} else {
			log_status("draw game");
		}
	}
	
	//用于游戏引擎，给定字符串（64字符的游戏局面和1个字符的turn）
	//返回下子的位置坐标 (2个字符)，下标均是从1开始计算
	string deal(string& query) {
		pass_cnt=0;
		board.init_from_str(query);
		color& turn=board.turn;
		Player& player=(turn==BLACK)?black:white;
		uchar& mobility=board.total[ACTIVE];
		
		if (mobility==0) {
			pass_cnt+=1;
			return "00";//表示PASS
		} else {
			pass_cnt=0;
			uchar byte=player.play(board);
			uchar x=byte>>4, y=byte&0x0F;
			assert(x<8 AND y<8);
			char s[3];
			s[0]='1'+x;//从1开始编号
			s[1]='1'+y;
			s[2]=0;
			return s;
		}
		
	}
};

class GameTest {
public:
	GameTest() {
		// human_vs_human();
		// AI_vs_AI();
		Look1AI_vs_AI();
	}
	
	void human_vs_human() {
		HumanPlayer black, white;
		Game game(black, white);
		game.start();
	}
	
	void AI_vs_AI() {
		EasyAIPlayer player;
		Player& black=player;
		Player& white=player;
		Game game(black, white);
		game.start();
	}
	
	void Look1AI_vs_AI() {
		// EasyAIPlayer black;
		// EasyAIPlayer white;
		
		// Look1AIPlayer black;
		// Look1AIPlayer white;
		
		// Look2AIPlayer black;
		// Look2AIPlayer white;
		
		RandomAIPlayer black;
		RandomAIPlayer white;
		
		Game game(black, white);
		game.start();
	}
	
};

#endif /* GAME_H_1371896260_1 */

