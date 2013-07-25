<<<<<<< HEAD
﻿#ifndef PLAYER_H_1371915057_31
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
			log_debug(b);
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
class AIPlayer : public Player {};

//最简单的AI，选择第一个可下子的位置下子
class EasyAIPlayer : public AIPlayer {
public:
	uchar play(Board& b) {
		uchar self=b.turn;
		
		log_debug(b);
		
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

//也是很简单的AI，随机选择一个可下子的位置下子
//棋力灰常弱，可以作为Baseline
class RandomAIPlayer : public AIPlayer {
public:
	uchar play(Board& b) {
		uchar self=b.turn;
		
		log_debug(b);
		
		int mobility=b.mobility();
		assert(mobility>=1);
		uint index=random.randint(1, mobility);
		for_n(x, 8) {
			for_n(y, 8) {
				if (b.map[x][y]==ACTIVE) {
					if (--index==0) {
						log_info(((self==BLACK)?"BLACK":"WHITE")<<" AIPlayer, play at ("<<x<<", "<<y<<")");
						b.play(x, y);
						return (x<<4)+y;
					}
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
		log_debug(b);
		
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
		assert(best_move!=-1);
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
		// if (verbose!=LOG_LEVEL_NONE AND verbose<=LOG_LEVEL_INFO) b.dump(clog);
		log_debug(b);
		
		uchar best_move=-1;
		
		//两步棋后当前下子方的平均行动力
		//即两步棋后当前下子方的总行动力，除以一步棋后对手的总下法数（行动力）
		//可以理解为，一步棋后，对手的每种下法平均将给自己带来多少行动力
		float max_avg_mobility=-1;//根据最大化此值选择下法
		
		uint total_mobility1;//一步棋后对手的总下法数（行动力）
		uint total_mobility2;//两步棋后当前下子方的总行动力
		
		
		//找出下子之后使得对方行动力最低的一步走法
		
		for_n(x1, 8) {
			for_n(y1, 8) {
				if (b.map[x1][y1]==ACTIVE) {
					Board think1=b;
					uchar move1=(x1<<4)+y1;//自己走法
					uchar eat1=think1.play(x1, y1);//自己吃子数
					uchar mobility1=think1.mobility();//对手行动力
					
					if (mobility1==0) {//如果下某步棋后对手不能下子，则直接下这步棋
						best_move=move1;
						goto play;
					}
					total_mobility1=mobility1;
					total_mobility2=0;
					
					for_n(x2, 8) {
						for_n(y2, 8) {
							if (think1.map[x2][y2]==ACTIVE) {
								Board think2=think1;
								uchar move2=(x2<<4)+y2;//对手走法
								uchar eat2=think2.play(x2, y2);//对手吃子数
								uchar mobility2=think2.mobility();//自己行动力
								total_mobility2+=mobility2;	
							}
						}
					}
					
					float avg_mobility=float(total_mobility2)/total_mobility1;
					if (avg_mobility>max_avg_mobility) {
						max_avg_mobility=avg_mobility;
						best_move=move1;
					}
				}
			}
		}
play:
		assert(best_move!=-1);
		uint x=best_move>>4, y=best_move&0x0F;
		log_info(((self==BLACK)?"BLACK":"WHITE")<<" AIPlayer, play at ("<<x<<", "<<y<<")");
		b.play(x, y);
		return best_move;
	}
};

#endif /* PLAYER_H_1371915057_31 */
=======
﻿#ifndef PLAYER_H_1371915057_31
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
			log_debug(b);
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


#endif /* PLAYER_H_1371915057_31 */
>>>>>>> master
