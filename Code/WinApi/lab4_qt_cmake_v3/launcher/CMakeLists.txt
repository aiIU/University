project(launcher)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

set(PROJECT_SOURCES
	source/LauncherGui.cpp
	source/Launcher.cpp
	source/main.cpp
	source/GeneratorId.cpp)
	
set(PROJECT_HEADERS
	include/LauncherGui.h
	include/Launcher.h
	include/GeneratorId.h)
	
qt5_wrap_ui(PROJECT_UI 
	ui/LauncherGui.ui)
	
qt5_wrap_cpp(PROJECT_MOC 
	include/LauncherGui.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
	
add_executable(${PROJECT_NAME} WIN32
	${PROJECT_SOURCES}
	${PROJECT_HEADERS}
	${PROJECT_UI}
	${PROJECT_MOC})
	
target_link_libraries(${PROJECT_NAME} 
	PUBLIC
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets
	mylib)
	
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common/mylib/include)
	
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${CMAKE_CURRENT_SOURCE_DIR}/../common/stdafx.h)
cotire(${PROJECT_NAME})

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)