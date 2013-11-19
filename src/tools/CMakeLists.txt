cmake_minimum_required(VERSION 2.6)
project (jadesoul)

set(apps
	trim
	body
	caser
	sample
)

foreach(app ${apps})
	add_executable(${app} ${app}.cpp)
	install(TARGETS ${app} DESTINATION ${BIN_INSTALL_DIR})
endforeach(app)
