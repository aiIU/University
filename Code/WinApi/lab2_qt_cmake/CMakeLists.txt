cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(cotire)

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

set(SOURCES_DIR "sources")
set(project_sources 
	${SOURCES_DIR}/main.cpp 
	${SOURCES_DIR}/lab2_qt.cpp
	${SOURCES_DIR}/ThreadManager.cpp
	${SOURCES_DIR}/ThreadManagerWinImpl.cpp
	${SOURCES_DIR}/SyncManager.cpp
	${SOURCES_DIR}/SyncManagerWinImpl.cpp
	${SOURCES_DIR}/WinApiUtils.cpp)
	
set(HEADERS_DIR "includes")
set(project_headers
	${HEADERS_DIR}/stdafx.h
	${HEADERS_DIR}/lab2_qt.h
	${HEADERS_DIR}/ThreadManager.h
	${HEADERS_DIR}/ThreadManagerWinImpl.h
	${HEADERS_DIR}/SyncManager.h
	${HEADERS_DIR}/SyncManagerWinImpl.h
	${HEADERS_DIR}/WinApiUtils.h)
	
set(UI_DIR "ui")
set(project_ui ${UI_DIR}/lab2_qt.ui)

set(RESOURCES_DIR "resources")
set(project_resources
	${RESOURCES_DIR}/lab2_qt.qrc)
	
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources 
	${HEADERS_DIR}/lab2_qt.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} WIN32
	${project_sources} 
	${project_headers}
	${moc_sources}
	${project_ui}
	${project_resources})
		
target_link_libraries(${PROJECT_NAME} 
	PUBLIC
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets)
	
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${HEADERS_DIR}/stdafx.h)
cotire(${PROJECT_NAME})

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)

# Startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})