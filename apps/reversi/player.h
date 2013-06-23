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
	virtual void play(Board& b)=0;
};

class HumanPlayer : public Player {
public:
	void play(Board& b) {
		uint x, y;
		do {
			cout<<"Please input point for play (x, y), x=";
			cin>>x;
			cout<<"y=";
			cin>>y;
			cout<<endl;
		} while (b.play(x, y, self)==0);
	}
};

class AIPlayer : public Player {
public:
	void play(Board& b) {
		//TODO
	}
};


#endif /* PLAYER_H_1371915057_31 */
