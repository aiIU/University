cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(worker)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

set(PROJECT_SRC 
	main.cpp
	worker.cpp)
	
set(PROJECT_HEADERS
	../stdafx.h
	worker.h)

qt5_wrap_ui(PROJECT_UI 
	worker.ui)
	
qt5_wrap_cpp(PROJECT_MOC 
	worker.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
	
add_executable(${PROJECT_NAME} WIN32
	${PROJECT_SRC}
	${PROJECT_HEADERS}
	${PROJECT_UI}
	${PROJECT_MOC})
	
target_link_libraries(${PROJECT_NAME} 
	PUBLIC
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets)
	
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${CMAKE_CURRENT_SOURCE_DIR}/../stdafx.h)
cotire(${PROJECT_NAME})

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)