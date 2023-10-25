DIR_OBJ=FileObj
CPPFLAGS= -g -Wall -std=c++11

TEST_CPP=testFile.cpp
FILE_CPP=FileOperation.cpp
FILE_OPERATION_HPP=../../inc
FILE_OPERATION_CPP=../../src

OBJECT:=FileOperation.o testFile.o

TARGET=testFile

all: $(TARGET)

$(TARGET):$(OBJECT)
	g++ $(OBJECT) $(CPPFLAGS) -o $@

$(OBJECT):
	g++ -c $(FILE_OPERATION_CPP)/FileOperation.cpp  -I  $(FILE_OPERATION_HPP) -o  ./FileOperation.o $(CPPFLAGS)
	g++ -c $(TEST_CPP) -I  $(FILE_OPERATION_HPP) -o testFile.o $(CPPFLAGS)

clean:
	rm -rf *.o $(TARGET)

.PHONY:clean
