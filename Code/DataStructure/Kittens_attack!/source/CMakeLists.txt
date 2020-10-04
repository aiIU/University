project(Kittens)

# create common for all subprojects variables storing path and dir to precompiled header
set(PCH_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PCH_FILE ${PCH_DIR}/pch.h)

add_subdirectory(lib)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(resources)

# configure Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)
	
set(CMAKE_AUTOMOC_MOC_OPTIONS ${CMAKE_AUTOMOC_MOC_OPTIONS} "-b" "${PCH_FILE}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#-----------------------------

# setup main source and precompiled header
set(sources 
	${sources}
	Kittens.cpp
	pch.cpp
	pch.h
)

add_executable(${PROJECT_NAME} WIN32 ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE include ${PCH_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	nlohmann_json
)

# add compile and link options for perfomance optimizations
target_compile_options(${PROJECT_NAME} PRIVATE -Wall /W4 /std:c++17 /GL)
target_link_options(${PROJECT_NAME} PRIVATE /LTCG:incremental)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${PROJECT_NAME}d)

# copy qt5 dll and pdb files to target build dir:
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )

set_precompiled_header(${PROJECT_NAME} ${PCH_FILE})