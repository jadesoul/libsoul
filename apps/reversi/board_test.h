#ifndef BOARD_TEST_H_1372368713_26
#define BOARD_TEST_H_1372368713_26
/**
 * File: board_test.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-06-28 05:31:53.264000
 * Written In: Peking University, beijing, China
 */

#include "board.h"

class BoardTest {
public:
	BoardTest() {
		//cout<<"sizeof(Board)="<<sizeof(Board)<<endl;
		// set();
		play();
	}

	void play() {
		Board b;
		b.dump();
		cout<<"b.play(2, 3)="<<b.play(2, 3)<<endl;
		b.dump();
		cout<<"b.play(2, 4)="<<b.play(2, 4)<<endl;
		b.dump();
		cout<<"b.play(4, 5)="<<b.play(4, 5)<<endl;
		b.dump();
		
		cout<<"b.play(0, 0)="<<b.play(0, 0)<<endl;
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

#endif /* BOARD_TEST_H_1372368713_26 */
