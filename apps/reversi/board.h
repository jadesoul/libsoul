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

typedef uchar color;
const static color EMPTY=0;
const static color WHITE=1;
const static color BLACK=2;
const static color ACTIVE=3;

class Board {
public:
	color map[8][8];

	Board() {
		memset(this, EMPTY, sizeof(*this));
		map[3][4]=map[4][3]=BLACK;
		map[4][4]=map[3][3]=WHITE;
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

	inline void set(uint i, uint j, color c) { map[i][j]=c; }

	friend inline ostream& operator<<(ostream& o, Board& b) { 
		b.dump(o);
		return o;
	}

	static void test() {
		cout<<sizeof(Board)<<endl;
		Board b;
		b.dump();
	}
};


#endif /* BOARD_H_1371483294_09 */
