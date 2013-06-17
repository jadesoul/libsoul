all: mylib ctype

mylib:
	g++ mylib.cpp -shared -I ../../../include -o mylib.so


ctype:
	h2xml mylib.h -I $(PWD) -o mylib.xml
	xml2py -vcd mylib.xml -l $(PWD)/mylib.so -o mylib.py

