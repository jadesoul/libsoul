all:
	@git pull; git merge origin/desktop
	@test -d build || ( mkdir build ; cd build ; cmake ../src ) && cd build
	@make -sj install

clean:
	@rm -rf build lib bin