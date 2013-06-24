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

class Player {
public:
	color self;
	color oppo;
	
	Player(color turn):self(turn), oppo(OPPO(self)) {}
	virtual void play(Board& b)=0;//调用此函数前，需确保有子可下
};

class HumanPlayer : public Player {
public:
	HumanPlayer(color turn): Player(turn) {}
	
	void play(Board& b) {
		assert(self==b.turn);
		uint x, y;
		do {
			
			b.dump();
			if (self==BLACK) cout<<"BLACK ";
			else cout<<"WHITE ";
			cout<<"HumanPlayer, Please input point for play:"<<endl;
			cout<<"x=";
			cin>>x;
			cout<<"y=";
			cin>>y;
			cout<<endl;
			cout<<"(x, y)=("<<x<<", "<<y<<")"<<endl;
			
		} while (x<8 AND y<8 AND b.play(x, y)==0);
	}
};

class AIPlayer : public Player {
public:
	AIPlayer(color turn): Player(turn) {}
	
	void play(Board& b) {
		//TODO
	}
};


#endif /* PLAYER_H_1371915057_31 */
