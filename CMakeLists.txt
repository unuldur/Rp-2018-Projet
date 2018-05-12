cmake_minimum_required(VERSION 3.9)
project(projet)

set(CMAKE_CXX_STANDARD 17)
set (Boost_NO_BOOST_CMAKE ON)

set(BOOST_ROOT "C:/Users/mario/boost_1_66_0")

FIND_PACKAGE( Boost 1.66 )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )

add_definitions(-pthread -Wall -Wextra -D _WIN32_WINNT=0x0A00 )

add_executable(projet main.cpp src/Individu.cpp src/Individu.h src/Fitness.h src/Graph.h src/SimpleFitness.cpp src/SimpleFitness.h src/local/Voisin.h src/local/SimpleVoisin.cpp src/local/SimpleVoisin.h src/local/RechercheLocal.cpp src/local/RechercheLocal.h src/generate/Generate.h src/generate/Steiner.cpp src/generate/Steiner.h src/parser/Parser.cpp src/parser/Parser.h src/Utils.cpp src/Utils.cpp src/Utils.h src/generate/ArbreCouvrantMin.cpp src/generate/ArbreCouvrantMin.h src/generate/RandomiseGeneration.cpp src/generate/RandomiseGeneration.h Main2.cpp src/genetic/Croisement.cpp src/genetic/Generation.cpp src/genetic/Genetic.cpp src/genetic/Mutation.cpp src/genetic/Remplacement.cpp src/genetic/Selection.cpp src/generate/GenerateRandom.cpp)

TARGET_LINK_LIBRARIES(projet LINK_PUBLIC ${Boost_LIBRARIES})
