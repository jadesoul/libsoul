all:
	#python scripts/gen_cmake_recursively.py tests ../include
	#python scripts/prepare_dirs.py build bin lib
	
	# file holder for compiling under visualstudio

	test -d build || ( mkdir build ; cd build ; cmake .. ) && cd build
	make -sj install

install:
	cd build ; make -s install ; cd -

clean:
	python scripts/clean_dirs.py build bin lib
	
