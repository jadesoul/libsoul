#coding:utf8
import pyximport; pyximport.install()
import edit_distance

if __name__=='__main__':
	# print edit_distance.edit_distance(1, 'abc')
	print edit_distance.edit_distance('1', 'abc')
	print edit_distance.edit_distance('a', 'abc')
    