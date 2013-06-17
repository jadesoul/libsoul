cmake_minimum_required(VERSION 2.6)
project (jadesoul)

set(apps
	#txt2vcbsnt
	#vcbsnt2txt
	#vcbp2evcb
	chunkalign
)

foreach(app ${apps})
	add_executable(${app} ${app}.cpp)
	install(TARGETS ${app} DESTINATION ${BIN_INSTALL_DIR})
endforeach(app)

# add_executable(chunk chunkalign.cpp)
# install(TARGETS chunk DESTINATION ${BIN_INSTALL_DIR})
