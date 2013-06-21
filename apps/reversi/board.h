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
static const color EMPTY=0;
static const color WHITE=1;
static const color BLACK=2;
static const color ACTIVE=3;

//��ȡ���ֵ���ɫ
#define OPPO(x) (ACTIVE-x)

class Board { 
public:
	color map[8][8];

	Board() {
		init_board_map();
		update_possible_moves(BLACK);//��������
	}
	 
	//�����ʼ����
	inline void init_board_map() {
		memset(this, EMPTY, sizeof(*this));
		map[3][4]=map[4][3]=BLACK;
		map[4][4]=map[3][3]=WHITE;
	}

	//������������е�ACTIVE״̬
	inline void clear_active_states() {
		color* base=&map[0][0];
		for_n(i, 64) if (base[i]==ACTIVE) base[i]=EMPTY;
	}

	//������һ�����ӷ�����ɫ
	//�������ɣ����£����������е�ACTIVE״̬
	inline void update_possible_moves(color c) {
		
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
	//

	//����ָ��λ�õ�������ɫ
	inline void set(uint i, uint j, color c) {
		map[i][j]=c;
	}

	//��ָ����λ�÷���ָ����ɫ�����ӣ�����Ƿ�Ϸ�
	//�����Ϸ��򷵻�����ʧ�ܣ����򷵻سɹ�
	bool play(uint i, uint j, color p) {
		Board& me=*this;
		//���ӵ������ACTIVE״̬
		color& c=map[i][j];
		if (c!=ACTIVE) return false;
		//������ӳɹ���������µĶ������ӵ�
		me.set(i, j, p);
		color o=OPPO(p);
		clear_active_states();
		update_possible_moves(o);
		return true;
	}

	friend inline ostream& operator<<(ostream& o, Board& b) { 
		b.dump(o);
		return o;
	}

	static void test() {

	}
};

class BoardTest {
public:
	BoardTest() {
		//cout<<"sizeof(Board)="<<sizeof(Board)<<endl;
		//test_set();
		test_play();
	}

	void test_play() {
		Board b;
		b.dump();
		b.set(0, 7, BLACK);
		cout<<"b.set(0, 7, BLACK);"<<endl;
		b.dump();
		cout<<"b.set(6, 2, WHITE)="<<b.play(6, 2, WHITE)<<endl;
		b.dump();
	}

	void test_set() {
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
