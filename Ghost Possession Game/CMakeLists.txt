
set(SOURCE_FILES 
"main.cpp" 
"src/States/State.h"
"src/States/States.h" 
"src/Game.h"
"src/Game.cpp" "src/States/Menu.h" "src/States/LevelSelect.h" "src/States/Menu.cpp"   "src/Tools/Objects/ScalingText.h" "src/States/Play.h" "src/States/Start.h" "src/States/Start.cpp" "src/States/LevelSelect.cpp")
set(SUB_NAME The_Ghost_Possession)

add_executable(${SUB_NAME} ${SOURCE_FILES})

if(CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET ${SUB_NAME} PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 016bea9491ccafc3529019fe1d403885a8b3a6ae
)
FetchContent_MakeAvailable(SFML)

target_link_libraries(${SUB_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)

set(CMAKE_AUTORCC ON)