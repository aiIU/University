project(mylib)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(PROJECT_SOURCES
	source/utils.cpp
	source/ipc.cpp
	source/sync.cpp)
	
set(PROJECT_HEADERS
	include/utils.h
	include/ipc.h
	include/sync.h)
		
add_library (${PROJECT_NAME} STATIC 
	${PROJECT_SOURCES}
	${PROJECT_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${CMAKE_CURRENT_SOURCE_DIR}/../stdafx_lib.h)
cotire(${PROJECT_NAME})
