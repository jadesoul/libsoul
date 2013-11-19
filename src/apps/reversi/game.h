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

#define DRAW 0//平局

//代表一盘棋结束时的比分
class Score {
public:
	uchar black;//黑方棋子数
	uchar white;//白方棋子数
	uchar empty;//未下棋子数
	uchar winner;//胜利方，取值为BLACK, WHITE, DRAW平局
	
	Score(Board& board) {//游戏结束时，将board传入构造对象
		black=board.total[BLACK];
		white=board.total[WHITE];
		empty=board.total[EMPTY];
		if (black>white) winner=BLACK;
		else if (black<white) winner=WHITE;
		else winner=DRAW;
	}
	
	inline int diff() {
		return (int)black-(int)white;
	}
	
	void dump(ostream& o=cout) {
		o<<"BLACK:"<<(uint)black<<" WHITE:"<<(uint)white<<" EMPTY:"<<(uint)empty<<" ";
		if (winner==BLACK) o<<"BLACK WIN";
		else if (winner==WHITE) o<<"WHITE WIN";
		else o<<"DRAW GAME";
	}
	
	friend inline ostream& operator<<(ostream& o, Score& s) {
		s.dump(o);
		return o;
	}
};

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
	
	Game(Player& black, Player& white):
		black(black), white(white), pass_cnt(0) {}
	Game(Player& black, Player& white, Board& board):
		black(black), white(white), board(board), pass_cnt(0) {}
	
	Score start() {
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
		
		Score score(board);
		log_status(score);
		
		return score;
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


#endif /* GAME_H_1371896260_1 */

