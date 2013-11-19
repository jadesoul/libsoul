/**
 * File: id_crypt.cpp
 * Description: 对int64整数id加密，得到一串长度为16的字符串
 *		要求:
 *			id值的微小变化会导致加密串的剧烈变化
 *			加密结果仅仅依赖于密钥，且唯一
 *			根据密钥可以解密到原始id
 *			无法根据相邻id生成的串预测其他id的串
 *			增加扰乱，不能轻易被破解
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-07-20 18:14:25.003000
 * Written In: Peking University, beijing, China
 */

#include <jadesoul.hpp>

typedef unsigned long long i64;

//本加密解密算法的绝对密钥，改变此值将影响后面所有的参数
const static i64 top_secret_key=0xabcd9e7c8de5847a;

//用此值对所有的id在加密前进行异或
const static i64 big_key_mask=top_secret_key ^ 0x1423dcef7e64a8dc;

//循环移位初始值
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

// 对十六进制字符循环移位：
// 		循环右移1位，0->1, 1->2, 2->3, 3->4, ... , e->f, f->0
// 		循环左移2位，0->2, 1->3, 2->4, 3->5, ... , e->0, f->1
// 		循环左移1位，0->f, 1->0, 2->1, 3->2, ... , e->d, f->e
// 十六进制字符取值:
// 		0, 1, 2, 3, ...., 8, 9, a, b, c, d, e, f
char hex_chars[]="0123456789abcdef";

// 根据char获取在hex_chars中的索引
#define get_index(ch) ((ch>='a') ? ch-'a'+10 : ch-'0')
// int get_index(char ch) {
	// if (ch>='0' && ch<='9') return ch-'0';
	// if (ch>='a' && ch<='f') return ch-'a'+10;
	// assert(false);
// }

// 将int64整数展开成16进制表示形式
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

// 将16进制表示形式还原成int64整数
i64 hexstr2int(string s) {
	assert(s.size()==16);
	i64 n=0;
	//从左往右扫描找第一个非0字符
	int first=16;
	for (int i=0; i<16; ++i) {
		if (s[i]!='0') {
			first=i;
			break;
		}
	}
	if (first==16) return 0; //全是0
	
	for (int i=first; i<16; ++i) {
		n=16*n+get_index(s[i]);
	}
	return n;
}

// 循环移位
//		要求: 
//			ch 是 hex_chars 中的一个字符
//			n 取值范围：[ -15 ~ 15 ]
//		整数表示循环右移，负数表示循环左移
//		n>=0 循环右移 m=n%16 位
//		n<0 循环左移 m=(-n)%16 位
char rotate_shift(char ch, int n) {
	int index = get_index(ch);
	if (n<0) n+=16;	//循环左移1位等价于循环右移16-1=15位
	index = (index+n)%16;
	return hex_chars[index];
}

// 编码
string encode(i64 id) {
	cout<<int2hexstr(id)<<"\t";
	
	//将数字异或mask后展开成16进制串
	id=id ^ big_key_mask;
	string s=int2hexstr(id);
	cout<<s<<"\t";
	
	for (int i=15; i>=0; --i) {
		// 第15位使用循环移位初始值shift_start移位
		if (i==15) s[i]=rotate_shift(s[i], shift_start);
		// 第3, 7, 11位分别按照 s[12], s[13], s[14]对应的索引移位
		else if (i%4==3) s[i]=rotate_shift(s[i], get_index(s[(i-3)/4+12]));
		// 其他位使用下一位的字符索引作为key
		else s[i]=rotate_shift(s[i], get_index(s[i+1]));
	}
	cout<<s<<"\t";
	
	//从左到右对每个位按照对应的keys[i]移位加以扰乱
	//防止连续id编码结果中有较多连续相同值
	for (int i=0; i<16; ++i) s[i]=rotate_shift(s[i], keys[i]);
	cout<<s<<"\t";
	
	//做奇偶校验
	//	定义偶字符为：0, 2, 4, 6, 8, a, c, e
	//	定义奇字符为：1, 3, 5, 7, 9, b, d, f
	//	计算 a = 编码结果中偶字符的总数
	//	若a为奇数：对所有奇字符右移a-1位，仍不会改变总偶字符的总数
	//	若a为偶数：对所有偶字符右移a位，仍不会改变总偶字符的总数
	int even_cnt=0;//记录总偶字符个数
	bool even_index[16];//记录各个位是否是偶字符
	for (int i=0; i<16; ++i) {
		int index=get_index(s[i]);
		bool is_even=(index%2==0);
		even_index[i]=is_even;
		if (is_even) ++even_cnt;
	}
	if (even_cnt%2==1) {	//所有奇字符右移even_cnt-1位
		for (int i=0; i<16; ++i)
			if (! even_index[i]) s[i]=rotate_shift(s[i], even_cnt-1);
	} else {
		for (int i=0; i<16; ++i)//所有偶字符右移even_cnt位
			if (even_index[i]) s[i]=rotate_shift(s[i], even_cnt);
	}
	cout<<s<<"\t";
	
	cout<<hex_chars[even_cnt]<<"\t";
	
	// 奇偶校验位
	//最后把总偶字符个数a的十六进制形式插入到字符串的第a位
	//若a是偶数，则插入之前加1，防止改变整体的偶字符个数
	s.insert(s.begin()+even_cnt, hex_chars[even_cnt%2==0 ? even_cnt+1 : even_cnt]);
	cout<<s<<"\n";
	return s;
}

// 解码
i64 decode(string s) {
	cout<<s<<"\t";
	
	//计算偶数个数，找出奇偶校验位并扔掉
	int even_cnt=0;//记录总偶字符个数
	for (int i=0; i<17; ++i) if (get_index(s[i])%2==0) ++even_cnt;
	s.erase(s.begin()+even_cnt);//该位一定是奇数，扔掉
	cout<<s<<"\t";
	
	//重新计算各个位的奇偶情况
	bool even_index[16];//记录各个位是否是偶字符
	for (int i=0; i<16; ++i) even_index[i]=(get_index(s[i])%2==0);
	
	//对所有的奇数位置或偶数位置解密
	if (even_cnt%2==1) {
		for (int i=0; i<16; ++i) 
			if (! even_index[i]) s[i]=rotate_shift(s[i], -(even_cnt-1));
	}
	else {
		for (int i=0; i<16; ++i)
			if (even_index[i]) s[i]=rotate_shift(s[i], -even_cnt);
	}
	cout<<s<<"\t";
	
	//从左到右对每个位按照对应的keys[i]解密
	for (int i=0; i<16; ++i) s[i]=rotate_shift(s[i], -keys[i]);
	cout<<s<<"\t";
	
	
	for (int i=0; i<16; ++i) {
		if (i==15) s[i]=rotate_shift(s[i], -shift_start);
		else if (i%4==3) s[i]=rotate_shift(s[i], -get_index(s[(i-3)/4+12]));
		else s[i]=rotate_shift(s[i], -get_index(s[i+1]));
	}
	cout<<s<<"\t";
	
	// 将十六进制串转换成int64整数
	i64 id=hexstr2int(s);
	cout<<int2hexstr(id)<<"\t";
	
	//将数字异或mask后
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
