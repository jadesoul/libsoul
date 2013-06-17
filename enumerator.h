#ifndef ENUMERATOR_H_1356530078_88
#define ENUMERATOR_H_1356530078_88
/**
 * File: enumerator.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 21:54:38.883000
 * Written In: Peking University, beijing, China
 */

#include "bootstrap.h"

//interface of enumerable
class enumerable {
public:
	virtual inline void start() const=0;
	virtual inline const bool end() const=0;
	virtual inline const bool still() const=0;
	virtual inline void next()=0;
};

template<class container>
class enumerator : public enumerable {
public:
	typedef typename container::value_type value;
	typedef typename container::iterator iterator;
	typedef typename container::const_iterator citerator;
	typedef typename container::reverse_iterator riterator;
	typedef typename container::const_reverse_iterator criterator;
private:
	const container& con;
	iterator i;
public:
	inline enumerator(const container& c):con(c), i(con.begin()) {}
	inline citerator iter() const { return i; }
	inline value& val() { return *i; }
	inline const value& val() const { return *i; }
	inline void start() const { i=con.begin(); }
	inline const bool end() const { return i==con.end(); }
	inline const bool still() const { return i!=con.end(); }
	inline void next() { ++i; }
};

template<class container>
inline enumerator<container> enumerate(const container& con) {
	return enumerator<container>(con);
}

template<class container>
class renumerator : public enumerable {
public:
	typedef typename container::value_type value;
	typedef typename container::iterator iterator;
	typedef typename container::const_iterator citerator;
	typedef typename container::reverse_iterator riterator;
	typedef typename container::const_reverse_iterator criterator;
private:
	const container& con;
	riterator i;
public:
	inline renumerator(const container& c):con(c), i(con.rbegin()) {}
	inline citerator iter() const { return i; }
	inline value& val() { return *i; }
	inline const value& val() const { return *i; }
	inline void start() const { i=con.rbegin(); }
	inline const bool end() const { return i==con.end(); }
	inline const bool still() const { return i!=con.end(); }
	inline void next() { ++i; }
};

template<class container>
inline enumerator<container> renumerate(const container& con) {
	return enumerator<container>(con);
}

//#define for_in(type, i, con) for (value& i, enumerable& e=enumerator(con), uint id=0; e.still() && (1, i=e.val()); e.next(), ++id)
//#define for_rin(type, i, con) for (value& i, enumerable& e=renumerator(con), uint id=0; e.still() && (1, i=e.val()); e.next(), ++id)


#endif /* ENUMERATOR_H_1356530078_88 */
