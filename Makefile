all: update prepare install

update:
	@git pull ; git merge origin/desktop
	
prepare:
	@test -d build || ( mkdir build ; cd build ; cmake ../src )
	
install:
	@cd build ; make -sj install

clean:
	@rm -rf build lib bin