cmake_minimum_required(VERSION 2.6)
project (reversi)

set(apps
	engine
	reversi
)

foreach(app ${apps})
	add_executable(${app} ${app}.cpp)
	install(TARGETS ${app} DESTINATION ${BIN_INSTALL_DIR})
endforeach(app)