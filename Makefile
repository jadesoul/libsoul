all:
	@test -d build || ( mkdir build ; cd build ; cmake ../src ) && cd build
	@make -sj install

install:
	@cd build ; make -s install ; cd -

clean:
	@rm -rf build lib bin