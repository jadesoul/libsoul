/**
 * File: id_crypt.cpp
 * Description: ��int64����id���ܣ��õ�һ������Ϊ16���ַ���
 *		Ҫ��:
 *			idֵ��΢С�仯�ᵼ�¼��ܴ��ľ��ұ仯
 *			���ܽ��������������Կ����Ψһ
 *			������Կ���Խ��ܵ�ԭʼid
 *			�޷���������id���ɵĴ�Ԥ������id�Ĵ�
 *			�������ң��������ױ��ƽ�
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-07-20 18:14:25.003000
 * Written In: Peking University, beijing, China
 */

#include <jadesoul.hpp>

typedef unsigned long long i64;

//�����ܽ����㷨�ľ�����Կ���ı��ֵ��Ӱ��������еĲ���
const static i64 top_secret_key=0xabcd9e7c8de5847a;

//�ô�ֵ�����е�id�ڼ���ǰ�������
const static i64 big_key_mask=top_secret_key ^ 0x1423dcef7e64a8dc;

//ѭ����λ��ʼֵ
const static int shift_start=top_secret_key % 16; 

const int keys[16]={
	(shift_start * 3 + 1) % 16,
	(shift_start * 2 + 3) % 16,
	(shift_start * 4 + 2) % 16,
	(shift_start * 2 + 4) % 16,
	
	(shift_start * 1 + 7) % 16,
	(shift_start * 5 + 10) % 16,
	(shift_start * 2 + 5) % 16,
	(shift_start * 4 + 11) % 16,
	
	(shift_start * 3 + 13) % 16,
	(shift_start * 1 + 8) % 16,
	(shift_start * 5 + 9) % 16,
	(shift_start * 3 + 2) % 16,
	
	(shift_start * 4 + 8) % 16,
	(shift_start * 2 + 11) % 16,
	(shift_start * 6 + 7) % 16,
	(shift_start * 3 + 6) % 16,
};

// ��ʮ�������ַ�ѭ����λ��
// 		ѭ������1λ��0->1, 1->2, 2->3, 3->4, ... , e->f, f->0
// 		ѭ������2λ��0->2, 1->3, 2->4, 3->5, ... , e->0, f->1
// 		ѭ������1λ��0->f, 1->0, 2->1, 3->2, ... , e->d, f->e
// ʮ�������ַ�ȡֵ:
// 		0, 1, 2, 3, ...., 8, 9, a, b, c, d, e, f
char hex_chars[]="0123456789abcdef";

// ����char��ȡ��hex_chars�е�����
#define get_index(ch) ((ch>='a') ? ch-'a'+10 : ch-'0')
// int get_index(char ch) {
	// if (ch>='0' && ch<='9') return ch-'0';
	// if (ch>='a' && ch<='f') return ch-'a'+10;
	// assert(false);
// }

// ��int64����չ����16���Ʊ�ʾ��ʽ
string int2hexstr(i64 n) {
	string hex;
	while (n!=0) {
		int mod=n%16;
		hex.insert(hex.begin(), hex_chars[mod]);
		n /= 16;
	}
	while (hex.size()<16) hex.insert(hex.begin(), '0');
	return hex;
}

// ��16���Ʊ�ʾ��ʽ��ԭ��int64����
i64 hexstr2int(string s) {
	assert(s.size()==16);
	i64 n=0;
	//��������ɨ���ҵ�һ����0�ַ�
	int first=16;
	for (int i=0; i<16; ++i) {
		if (s[i]!='0') {
			first=i;
			break;
		}
	}
	if (first==16) return 0; //ȫ��0
	
	for (int i=first; i<16; ++i) {
		n=16*n+get_index(s[i]);
	}
	return n;
}

// ѭ����λ
//		Ҫ��: 
//			ch �� hex_chars �е�һ���ַ�
//			n ȡֵ��Χ��[ -15 ~ 15 ]
//		������ʾѭ�����ƣ�������ʾѭ������
//		n>=0 ѭ������ m=n%16 λ
//		n<0 ѭ������ m=(-n)%16 λ
char rotate_shift(char ch, int n) {
	int index = get_index(ch);
	if (n<0) n+=16;	//ѭ������1λ�ȼ���ѭ������16-1=15λ
	index = (index+n)%16;
	return hex_chars[index];
}

// ����
string encode(i64 id) {
	cout<<int2hexstr(id)<<"\t";
	
	//���������mask��չ����16���ƴ�
	id=id ^ big_key_mask;
	string s=int2hexstr(id);
	cout<<s<<"\t";
	
	for (int i=15; i>=0; --i) {
		// ��15λʹ��ѭ����λ��ʼֵshift_start��λ
		if (i==15) s[i]=rotate_shift(s[i], shift_start);
		// ��3, 7, 11λ�ֱ��� s[12], s[13], s[14]��Ӧ��������λ
		else if (i%4==3) s[i]=rotate_shift(s[i], get_index(s[(i-3)/4+12]));
		// ����λʹ����һλ���ַ�������Ϊkey
		else s[i]=rotate_shift(s[i], get_index(s[i+1]));
	}
	cout<<s<<"\t";
	
	//�����Ҷ�ÿ��λ���ն�Ӧ��keys[i]��λ��������
	//��ֹ����id���������н϶�������ֵͬ
	for (int i=0; i<16; ++i) s[i]=rotate_shift(s[i], keys[i]);
	cout<<s<<"\t";
	
	//����żУ��
	//	����ż�ַ�Ϊ��0, 2, 4, 6, 8, a, c, e
	//	�������ַ�Ϊ��1, 3, 5, 7, 9, b, d, f
	//	���� a = ��������ż�ַ�������
	//	��aΪ���������������ַ�����a-1λ���Բ���ı���ż�ַ�������
	//	��aΪż����������ż�ַ�����aλ���Բ���ı���ż�ַ�������
	int even_cnt=0;//��¼��ż�ַ�����
	bool even_index[16];//��¼����λ�Ƿ���ż�ַ�
	for (int i=0; i<16; ++i) {
		int index=get_index(s[i]);
		bool is_even=(index%2==0);
		even_index[i]=is_even;
		if (is_even) ++even_cnt;
	}
	if (even_cnt%2==1) {	//�������ַ�����even_cnt-1λ
		for (int i=0; i<16; ++i)
			if (! even_index[i]) s[i]=rotate_shift(s[i], even_cnt-1);
	} else {
		for (int i=0; i<16; ++i)//����ż�ַ�����even_cntλ
			if (even_index[i]) s[i]=rotate_shift(s[i], even_cnt);
	}
	cout<<s<<"\t";
	
	cout<<hex_chars[even_cnt]<<"\t";
	
	// ��żУ��λ
	//������ż�ַ�����a��ʮ��������ʽ���뵽�ַ����ĵ�aλ
	//��a��ż���������֮ǰ��1����ֹ�ı������ż�ַ�����
	s.insert(s.begin()+even_cnt, hex_chars[even_cnt%2==0 ? even_cnt+1 : even_cnt]);
	cout<<s<<"\n";
	return s;
}

// ����
i64 decode(string s) {
	cout<<s<<"\t";
	
	//����ż���������ҳ���żУ��λ���ӵ�
	int even_cnt=0;//��¼��ż�ַ�����
	for (int i=0; i<17; ++i) if (get_index(s[i])%2==0) ++even_cnt;
	s.erase(s.begin()+even_cnt);//��λһ�����������ӵ�
	cout<<s<<"\t";
	
	//���¼������λ����ż���
	bool even_index[16];//��¼����λ�Ƿ���ż�ַ�
	for (int i=0; i<16; ++i) even_index[i]=(get_index(s[i])%2==0);
	
	//�����е�����λ�û�ż��λ�ý���
	if (even_cnt%2==1) {
		for (int i=0; i<16; ++i) 
			if (! even_index[i]) s[i]=rotate_shift(s[i], -(even_cnt-1));
	}
	else {
		for (int i=0; i<16; ++i)
			if (even_index[i]) s[i]=rotate_shift(s[i], -even_cnt);
	}
	cout<<s<<"\t";
	
	//�����Ҷ�ÿ��λ���ն�Ӧ��keys[i]����
	for (int i=0; i<16; ++i) s[i]=rotate_shift(s[i], -keys[i]);
	cout<<s<<"\t";
	
	
	for (int i=0; i<16; ++i) {
		if (i==15) s[i]=rotate_shift(s[i], -shift_start);
		else if (i%4==3) s[i]=rotate_shift(s[i], -get_index(s[(i-3)/4+12]));
		else s[i]=rotate_shift(s[i], -get_index(s[i+1]));
	}
	cout<<s<<"\t";
	
	// ��ʮ�����ƴ�ת����int64����
	i64 id=hexstr2int(s);
	cout<<int2hexstr(id)<<"\t";
	
	//���������mask��
	id=id ^ big_key_mask;
	cout<<int2hexstr(id)<<"\n";
	return id;
}

int main () {
	// cout<<"---------------int2hexstr test---------------------"<<endl;
	// for (i64 i=0; i<3; ++i) {
		// cout<<"int2hexstr["<<i<<"]="<<int2hexstr(i)<<endl;
	// }
	// cout<<"---------------hexstr2int test---------------------"<<endl;
	// cout<<"hexstr2int="<<hexstr2int("0000000000000000")<<endl;
	// cout<<"hexstr2int="<<hexstr2int("0000000000000001")<<endl;
	// cout<<"hexstr2int="<<hexstr2int("0000000000000002")<<endl;
	// cout<<"hexstr2int="<<hexstr2int("000000000000000a")<<endl;
	// cout<<"hexstr2int="<<hexstr2int("00000000000000fe")<<endl;
	// cout<<"hexstr2int="<<hexstr2int("00000000f43662a2")<<endl;
		// cout<<"---------------xor test---------------------"<<endl;
	// i64 id=0;
	// cout<<"id="<<id<<"\tint2hexstr="<<int2hexstr(id)<<endl;
	// cout<<"big_key_mask="<<big_key_mask<<"\tint2hexstr="<<int2hexstr(big_key_mask)<<endl;
	// id=id ^ big_key_mask;
	// string s=int2hexstr(id);
	// cout<<"id="<<id<<"\tint2hexstr="<<s<<endl;
	// id=hexstr2int(s);
	// cout<<"hexstr2int="<<id<<"\tint2hexstr="<<int2hexstr(id)<<endl;
	// id=id ^ big_key_mask;
	// cout<<"id="<<id<<"\tint2hexstr="<<int2hexstr(id)<<endl;
	
	cout<<"---------------encode test---------------------"<<endl;
	for (i64 i=0; i<3; ++i) encode(i);
	for (i64 i=0x1278092571263716; i<0x7687236482342312; i+=0x112bdfe221876382) encode(i);
	
	cout<<"---------------decode test---------------------"<<endl;
	decode("d4889ab6a2b8b25de");
	decode("4bff0172d19f29c45");
	decode("b266789480b6903bc");
	decode("64a798a139a9c978e");//1278092571263716
}
