# CMakeList.txt : CMake project for possesion test, include source and define
# project specific logic here.
#

set(SOURCE_FILES "main.cpp" "src/Game.h" "src/States/State.h" "src/States/PlayGround.h" "src/States/PlayGround.cpp" "src/States/States.h" "src/Game.cpp" "src/Entities/Player.h" "src/Entities/Entities.h" "src/Interfaces/Interfaces.h" "src/Interfaces/IPhysicsObject.h" "src/Entities/Player.cpp" "src/Objects/Box.h" "src/Objects/Objects.h" "src/constants.h" "src/Interfaces/IPossessable.h" "src/Objects/PossessableBox.h" "src/Objects/PossessableBox.cpp")
add_executable(CMakeTarget ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 016bea9491ccafc3529019fe1d403885a8b3a6ae
)
FetchContent_MakeAvailable(SFML)

target_link_libraries(CMakeTarget PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

message("----------Current source directory----------")
message(${CMAKE_CURRENT_SOURCE_DIR})
message("----------Current source directory----------")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)