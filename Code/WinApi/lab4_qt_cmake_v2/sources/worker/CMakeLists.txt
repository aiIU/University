cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(Worker)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(WORKER_SOURCES 
	worker.cpp
	main.cpp)
		
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

qt5_wrap_ui(WORKER_UI 
	worker.ui)
	
qt5_wrap_cpp(WORKER_MOC 
	${WORKER_HEADERS_QT})

add_executable(${PROJECT_NAME} WIN32
	${WORKER_SOURCES}
	${WORKER_HEADERS}
	${WORKER_UI}
	${WORKER_MOC})
	
target_link_libraries(${PROJECT_NAME} 
	PUBLIC
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets)
	
target_include_directories(${PROJECT_NAME} PRIVATE ../includes/worker)

set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ../../includes/worker/stdafx.h)
cotire(${PROJECT_NAME})

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)