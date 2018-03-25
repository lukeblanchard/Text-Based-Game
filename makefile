CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

OBJS = Player.o Space.o Android.o GoodDroid.o BadDroid.o Menu.o Die.o MoonBase.o EscapePod.o OpenSpace.o Game.o main.o 

SRCS = Player.cpp Space.cpp Android.cpp GoodDroid.cpp BadDroid.cpp Menu.cpp Die.cpp MoonBase.cpp EscapePod.cpp OpenSpace.cpp Game.cpp main.cpp

HEADERS = Player.hpp Space.hpp Android.hpp GoodDroid.hpp BadDroid.hpp Menu.hpp Die.hpp MoonBase.hpp EscapePod.hpp OpenSpace.hpp Game.hpp

#target: dependencies 
#	rule to build

main: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o main

${OBJS}: ${SRCS} 
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm -f main ${OBJS}
