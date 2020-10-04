cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(cotire)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

# need this to include the auto generated ui_mainwindow.h
# file from the qt5_wrap_ui call below.
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(project_sources 
	sources/main.cpp 
	sources/ProcessManager.cpp
	sources/lab1_qt.cpp)
	
set(project_headers 
	includes/lab1_qt.h
	includes/ProcessManager.h)
	
set(project_ui 
	ui/lab1_qt.ui)

set(project_resources
	resources/resources.qrc)

# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources ${project_headers})

qt5_add_resources(QT_RES ${project_resources})

add_executable(lab1
	${project_sources} 
	${project_headers}
	${ui_wrap} 
	${moc_sources}
	)
	
set(CMAKE_AUTOUIC_SEARCH_PATHS "ui")
	
set_target_properties(lab1 PROPERTIES AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS})

set_target_properties(lab1 PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "includes/stdafx.h")
cotire(lab1)
	
target_include_directories(lab1 PRIVATE "includes")
	
target_link_libraries(lab1 
	PUBLIC
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets)

# auto copy dlls if on windows
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)


# Startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "lab1")