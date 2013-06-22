#ifndef BOARD_H_1371483294_09
#define BOARD_H_1371483294_09
/**
 * File: board.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-06-17 23:34:54.092000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>

//棋子状态
typedef uchar color;
static const color EMPTY=0;
static const color WHITE=1;
static const color BLACK=2;
static const color ACTIVE=3;

//8个方向
static const uint RIGHT=0;
static const uint RIGHT_DOWN=1;
static const uint DOWN=2;
static const uint LEFT_DOWN=3;
static const uint LEFT=4;
static const uint LEFT_UP=5;
static const uint UP=6;
static const uint RIGHT_UP=7;

//在各个方向上根据当前坐标计算下一个坐标，根据横纵坐标增量表计算
static const uint INC_X[8]={1, 1, 0, -1, -1, -1, 0, 1};
static const uint INC_Y[8]={0, -1, -1, -1, 0, 1, 1, 1};
#define SET_NEXT(i, j, d) i+=INC_X[d]; j+=INC_Y[d];

//获取对手的颜色
#define OPPO(x) (ACTIVE-x)

class Board { 
public:
	color map[8][8];

	Board() {
		init_board_map();
		update_possible_moves(BLACK);//黑子先下
	}
	 
	//构造初始局面
	inline void init_board_map() {
		memset(this, EMPTY, sizeof(*this));
		map[3][4]=map[4][3]=BLACK;
		map[4][4]=map[3][3]=WHITE;
	}

	//清除局面上所有的ACTIVE状态
	inline void clear_active_states() {
		color* base=&map[0][0];
		for_n(i, 64) if (base[i]==ACTIVE) base[i]=EMPTY;
	}

	//给定上一次落子方的颜色
	//重新生成（更新）局面上所有的ACTIVE状态
	inline void update_possible_moves(color s) {
		clear_active_states();//先清除状态
		for_n(i, 8) {
			for_n(j, 8) {
				color& c=map[i][j];
				if (s!=c) continue;
				//向八个方向探索是否可以吃子

			}
		}
	}

	void dump(ostream& o=cout) {
		for_n(i, 8) {
			for_n(j, 8) {
				color& c=map[i][j];
				if (c==EMPTY) o<<'.';
				else if (c==BLACK) o<<'X';
				else if (c==WHITE) o<<'O';
				else o<<'A';
				o<<' ';
			}
			o<<endl;
		}
	}

	//设置指定位置的棋子颜色
	inline void set(uint i, uint j, color c) {
		map[i][j]=c;
	}

	//在指定的位置放置指定颜色的棋子，检查是否合法
	//若不合法则返回下子失败，否则返回成功
	bool play(uint i, uint j, color p) {
		Board& me=*this;
		//落子点必须是ACTIVE状态
		color& c=map[i][j];
		if (c!=ACTIVE) return false;
		//如果落子成功，则更新新的对手落子点
		me.set(i, j, p);
		color o=OPPO(p);
		update_possible_moves(o);
		return true;
	}

	friend inline ostream& operator<<(ostream& o, Board& b) { 
		b.dump(o);
		return o;
	}
};

class BoardTest {
public:
	BoardTest() {
		//cout<<"sizeof(Board)="<<sizeof(Board)<<endl;
		//set();
		play();
	}

	void play() {
		Board b;
		b.dump();
		b.set(0, 7, BLACK);
		cout<<"b.set(0, 7, BLACK);"<<endl;
		b.dump();
		cout<<"b.set(6, 2, WHITE)="<<b.play(6, 2, WHITE)<<endl;
		b.dump();
	}

	void set() {
		Board b;
		b.dump();
		b.set(0, 7, BLACK);
		cout<<"b.set(0, 7, BLACK);"<<endl;
		b.dump();
		b.set(6, 2, WHITE);
		cout<<"b.set(6, 2, WHITE);"<<endl;
		b.dump();
	}
};

#endif /* BOARD_H_1371483294_09 */
