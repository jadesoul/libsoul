template<class T1>
inline string format(const T1& t1) {
	ostringstream oss;
	oss<<t1;
	return oss.str();
}

template<class T1, class T2>
inline string format(const T1& t1, const T2& t2) {
	ostringstream oss;
	oss<<t1<<t2;
	return oss.str();
}

template<class T1, class T2, class T3>
inline string format(const T1& t1, const T2& t2, const T3& t3) {
	ostringstream oss;
	oss<<t1<<t2<<t3;
	return oss.str();
}

template<class T1, class T2, class T3, class T4>
inline string format(const T1& t1, const T2& t2, const T3& t3, const T4& t4) {
	ostringstream oss;
	oss<<t1<<t2<<t3<<t4;
	return oss.str();
}
