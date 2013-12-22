#ifndef AI_H_1372368194_48
#define AI_H_1372368194_48
/**
 * File: ai.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-06-28 05:23:14.481000
 * Written In: Peking University, beijing, China
 */

#include "player.h"
#include "game.h"

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
	Random random;
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

//利用蒙特卡罗搜索算法找出赢棋概率最大的走法
//基本思想:
//	针对当前局面所有可能的下子位置，衍生出一个新的残局，并同时扮演黑白的角色随机下棋，直到终局
//	对每个残局进行一局棋的推演称作一个轮回，对每个下子位置，重复执行若干个轮回，统计输赢情况
//	计算出每个位置的输赢概率，选择胜率最高的位置落子
class MonteCarloAIPlayer : public AIPlayer {
public:
	uchar play(Board& board) {
		uchar self=board.turn;
		log_debug(board);
		
		
		
		RandomAIPlayer player;//用于推演时随机下棋
		dict<uchar, int> predict;//统计每个下子位置最终的总赢子数
		
		for_n(x, 8) {
			for_n(y, 8) {
				if (board.map[x][y]==ACTIVE) {//针对每个落子点
					Board think=board;
					uchar move=(x<<4)+y;//如果在此处下子
					uchar eat=think.play(x, y);//吃子数
					// uchar mobility=think.mobility();//对手行动力
					
					predict[move]=0;
					
					//利用蒙特卡罗思想，开始随机下棋若干次
					for_n(i, 2000) {
						Game game(player, player, think);//举办一场比赛
						Score score=game.start();
						int diff=score.diff();//黑子数减去白子数之差
						if (self==BLACK) {//如果下子方是黑子，累加diff
							predict[move]+=diff;
						} else {//否则，累减（黑棋赢子就是白棋输子）
							predict[move]-=diff;
						}
					}
				}
			}
		}

		list<uchar> keys=predict.keys();
		
		//for debug
		log_warn("---------- predict.size()="<<predict.size());
		for_iter(it, list<uchar>, keys) {
			uchar move=(uchar)*it;
			uint x=move>>4, y=move&0x0F;
			log_warn("move="<<x<<","<<y<<" predict="<<predict[*it]);
		}
		
		//在所有走法中找出赢子数最大的走法
		uchar best_move=-1;
		int max_diff=min_sint4;
		for_iter(it, list<uchar>, keys) {
			uchar move=(uchar)*it;
			int diff=predict[*it];
			if (max_diff<diff) {
				max_diff=diff;
				best_move=move;
			}
		}
		
		assert(best_move!=-1);
		uint x=best_move>>4, y=best_move&0x0F;
		log_info(((self==BLACK)?"BLACK":"WHITE")<<" AIPlayer, play at ("<<x<<", "<<y<<")");
		board.play(x, y);
		return best_move;
	}
};

#endif /* AI_H_1372368194_48 */
