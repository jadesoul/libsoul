#coding:utf8

ss=[]
for i in range(1, 5):
	r=range(1, 1+i)
	a='template<%s>' % ', '.join(['class T%d' % j for j in r])
	b='inline string format(%s) {' % ', '.join(['const T%d& t%d' % (j, j) for j in r])
	c='\toss%s;' % ''.join(['<<t%d' % j for j in r])
	s='\n'.join([a, b, '\tostringstream oss;', c, '\treturn oss.str();', '}\n'])
	ss.append(s)
s='\n'.join(ss)

open('dump_format.h', 'w').write(s)
