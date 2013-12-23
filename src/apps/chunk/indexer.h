#ifndef INDEXER_H_1357305974_09
#define INDEXER_H_1357305974_09
/**
 * File: indexer.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-04 21:26:14.090000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "common.h"

//索引器，将一个值转成成编号索引，并可以在值和索引之间转换

template<class value, class index>
class indexer {
protected:
	dict<value, index> val2id;
	list<value> vals;
	
	virtual void clear() {
		val2id.clear();
		vals.clear();
	}
	
	virtual const index add(const value& val) {
		index id=(index)vals.size();
		vals.append(val);
		val2id[val]=id;
		return id;
	}
	
	//当id不存在时的默认值，可以在子类中重新定义
	virtual const value& get_default_value() const=0;
	
	//根据编号获取值，编号不存在则返回默认值
	const value& get_value(const index& id) const {
		if (id<vals.size()) return vals[id];
		else return get_default_value();
	}
	
	//如果值在已知列表中不存在，则插入，产生新的编号返回
	const index get_index(const value& val) {
		index id;
		if (!val2id.get(val, id)) id=add(val);
		return id;
	}
	
	//子类可以重载此函数实现特定的初始化
	virtual void init() {
		clear();
	}
	
public:
	indexer() {
		init();
	}
	
	inline const uint size() const { return vals.size(); }
	inline const bool has_value(const value& val) const { return val2id.find(val)!=val2id.end(); }
	
	virtual void load(istream& in) {
		indexer& me=*this;
		value val;
		while (in>>val) me(val);
	}

	inline const value& operator [] (const index& id) const {
		return get_value(id);
	}
	inline const index operator () (const value& val) {
		return get_index(val);
	}
};

#endif /* INDEXER_H_1357305974_09 */
