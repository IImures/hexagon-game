cmake_minimum_required(VERSION 3.25)
project(PJC_PRO1)

set(CMAKE_CXX_STANDARD 23)
set(BUILD_SHARED_LIBS FALSE)#!!

add_executable(PJC_PRO1 main.cpp Hexagon.h Hexagon.cpp Button.cpp ScoreWriter.h ScoreWriter.cpp GameBoard.h GameBoard.cpp Menu.h Menu.cpp ScoreMenu.h ScoreMenu.cpp)

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(PJC_PRO1
        sfml-system
        sfml-window
        sfml-graphics
        )
