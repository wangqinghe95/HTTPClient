DIR_INC=./inc -I../FilesSystem/include -I../Logger/include -I../Json/include
DIR_SRC=./src
DIR_OBJ=./obj
DIR_BIN=.

MAIN_CPP=main.cpp
# DIR_LIB=./lib

DIR_SRC_FilesSystem := ../FilesSystem/src
DIR_SRC_LOGGER := ../Logger/src
DIR_SRC_JSON := ../Json/src

# LIBS=-lsw3 -lswofdsdk

SRC := $(wildcard ${DIR_SRC}/*.cpp)
SRC += $(wildcard ${DIR_SRC_FilesSystem}/*.cpp)
SRC += $(wildcard ${DIR_SRC_LOGGER}/*.cpp)
SRC += $(wildcard ${DIR_SRC_JSON}/*.cpp)
SRC += $(MAIN_CPP)
OBJ := $(patsubst %.cpp, %.o, $(SRC))

TARGET := HTTPClient
BIN_TARGET = $(DIR_BIN)/$(TARGET)
INCLUDE = -I ${DIR_INC}
CFLAGS = -g -Wall -std=c++11

All:${DIR_OBJ} ${TARGET}

${TARGET}:${OBJ}
	g++ ${CFLAGS} ${OBJ} -o $@
	mv $^ $(DIR_OBJ)

%.o : %.cpp 
	g++ ${CFLAGS} ${INCLUDE} -c $< -o $@

${DIR_OBJ}:
	mkdir -p $@

.PHONY:clean
clean:
	rm -rf ${DIR_OBJ}/*.o ${BIN_TARGET}