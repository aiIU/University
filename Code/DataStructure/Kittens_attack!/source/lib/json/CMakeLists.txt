project(nlohmann_json)

add_library(${PROJECT_NAME} STATIC 
	"nlohmann/json.hpp" 
	"nlohmann/dummy.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})