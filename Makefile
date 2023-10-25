DIR_INC=./inc
DIR_SRC=./src
DIR_OBJ=./obj
DIR_BIN=.
MAIN_O=$(DIR_OBJ)/main.o
# DIR_LIB=./lib

# LIBS=-lsw3 -lswofdsdk

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC}))

TARGET=main
BIN_TARGET=$(DIR_BIN)/$(TARGET)
INCLUDE=-I ${DIR_INC}
CFLAGS = -g -Wall -std=c++11

All:${DIR_OBJ} ${BIN_TARGET} ${MAIN_O}

${BIN_TARGET}:${OBJ} ${MAIN_O}
	g++ ${CFLAGS} ${INCLUDE} ${OBJ} ${MAIN_O} -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp 
	g++ ${CFLAGS} ${INCLUDE} -c $< -o $@

${MAIN_O}:main.cpp
	g++ ${CFLAGS} ${INCLUDE} -c $< -o $@

${DIR_OBJ}:
	mkdir -p $@

.PHONY:clean
clean:
	rm -rf ${DIR_OBJ}/*.o ${BIN_TARGET}