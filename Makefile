# Copyright Keita Miyaoka
#
# matplotlib-cpp
# Python39
# g++ -o TTdwarf.exe .\TTdwarf.cpp
# -IC:\matplotlib-cpp\ -IC:\Python39\include\ 
# -IC:\Python39\Lib\site-packages\numpy\core\include
# -IC:\Python39\Lib\site-packages\numpy\core\include\numpy
# -LC:\Python39\libs -lpython39
#
 
#Basic Rule:
#Target: Source File
#            Command

CC            = g++
CFLAGS        = -IC:/Users/11235/OneDrive/Documents/Workfolder/C++/matplotlib-cpp/matplotlib-cpp \
	-IC:/Users/11235/AppData/Local/Programs/Python/Python39/include \
	-IC:/Users/11235/AppData/Local/Programs/Python/Python39/Lib/site-packages/numpy/core/include \
	-IC:/Users/11235/AppData/Local/Programs/Python/Python39/Lib/site-packages/numpy/core/include/numpy
DEST          = C:/Users/11235/
LDFLAGS       = -LC:/Users/11235/AppData/Local/Programs/Python/Python39/libs
LIBS          = -lpython39
OBJS          = TTdwarf.cpp
PROGRAM       = TTdwarf

all: $(PROGRAM) 

$(PROGRAM): $(OBJS)
	$(CC) -std=c++2a -o $(PROGRAM) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) 

clean:         rm -f *~ $(PROGRAM)

install: $(PROGRAM)
	install -s $(PROGRAM).exe $(DEST)
 
#$@ means Target e.g. $(PROGRAM)
#$< means Source e.g. $(OBJS)
#ALL: main.o sub.o
#    $(CC) $(CFLAGS) -o main main.o sub.o
#main.o: main.cpp
#    $(CC) $(CFLAGS) -o main.o -c main.cpp
#sub.o: sub.cpp sub.h
#    $(CC) $(CFLAGS) -o sub.o -c sub.cpp