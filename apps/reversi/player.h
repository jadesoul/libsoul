#ifndef PLAYER_H_1371915057_31
#define PLAYER_H_1371915057_31
/**
 * File: player.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-06-22 23:30:57.305000
 * Written In: Peking University, beijing, China
 */

#include "board.h"

//所有玩家的抽象基类
class Player {
public:
	//下子的抽象接口，返回一个字节共8bit，(前4bit, 后4bit)代表下子位置(x, y)
	//调用此函数前，需确保有子可下
	virtual uchar play(Board& b)=0;
};

class HumanPlayer : public Player {
public:
	uchar play(Board& b) {
		uchar self=b.turn;
		uint x, y;
		do {
			b.dump(clog);
			log_info(((self==BLACK)?"BLACK":"WHITE")<<" HumanPlayer, Please input point for play:");
			clog<<"x=";
			cin>>x;
			clog<<"y=";
			cin>>y;
			cout<<endl;
			log_info("(x, y)=("<<x<<", "<<y<<")");
			
		} while (x<8 AND y<8 AND b.play(x, y)==0);
		return (x<<4)+y;
	}
};

//所有AI的基类
class AIPlayer : public Player {
// public:
	// virtual uchar play(Board& b)=0;
}

//最简单的AI，选择第一个可下子的位置下子
class EasyAIPlayer : public AIPlayer {
public:
	uchar play(Board& b) {
		uchar self=b.turn;
		b.dump(clog);
		for_n(x, 8) {
			for_n(y, 8) {
				if (b.map[x][y]==ACTIVE) {
					log_info(((self==BLACK)?"BLACK":"WHITE")<<" AIPlayer, play at ("<<x<<", "<<y<<")");
					b.play(x, y);
					return (x<<4)+y;
				}
			}
		}
		assert(false);
		return 0;
	}
};

//向后看一步棋的AI
class Look1AIPlayer : public AIPlayer {
public:
	uchar play(Board& b) {
		uchar self=b.turn;
		b.dump(clog);
		
		uchar best_move=-1;
		uchar min_mobility=-1;
		//找出下子之后使得对方行动力最低的一步走法
		
		for_n(x, 8) {
			for_n(y, 8) {
				if (b.map[x][y]==ACTIVE) {
					Board think=b;
					uchar move=(x<<4)+y;//走法
					uchar eat=think.play(x, y);//吃子数
					uchar mobility=think.mobility();//对手行动力
					
					mobility+=eat;//综合考虑行动力与吃子数，优先选择行动力小，吃子数少的下法
					if (mobility<min_mobility) {
						min_mobility=mobility;
						best_move=move;
					}
					
				}
			}
		}
		uint x=best_move>>4, y=best_move&0x0F;
		log_info(((self==BLACK)?"BLACK":"WHITE")<<" AIPlayer, play at ("<<x<<", "<<y<<")");
		b.play(x, y);
		return best_move;
	}
};

//向后看2步棋的AI
class Look2AIPlayer : public AIPlayer {
public:	
	uchar play(Board& b) {
		uchar self=b.turn;
		b.dump(clog);
		
		uchar best_move=-1;
		uchar min_mobility=-1;
		//找出下子之后使得对方行动力最低的一步走法
		
		for_n(x, 8) {
			for_n(y, 8) {
				if (b.map[x][y]==ACTIVE) {
					Board think=b;
					uchar move=(x<<4)+y;//走法
					uchar eat=think.play(x, y);//吃子数
					uchar mobility=think.mobility();//对手行动力
					
					mobility+=eat;//综合考虑行动力与吃子数，优先选择行动力小，吃子数少的下法
					if (mobility<min_mobility) {
						min_mobility=mobility;
						best_move=move;
					}
					
				}
			}
		}
		uint x=best_move>>4, y=best_move&0x0F;
		log_info(((self==BLACK)?"BLACK":"WHITE")<<" AIPlayer, play at ("<<x<<", "<<y<<")");
		b.play(x, y);
		return best_move;
	}
};

#endif /* PLAYER_H_1371915057_31 */
