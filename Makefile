
CC            = g++
CFLAGS        = -IC:/matplotlib-cpp/matplotlib-cpp \
	-IC:/Python39/include \
	-IC:/Python39/Lib/site-packages/numpy/core/include \
	-IC:/Python39/Lib/site-packages/numpy/core/include/numpy
DEST          = C:
LDFLAGS       = -LC:/Python39/libs
LIBS          = -lpython39
OBJS          = TTdwarf.cpp
PROGRAM       = TTdwarf

all: $(PROGRAM) 

$(PROGRAM): $(OBJS)
	$(CC) -std=c++2a -o $(PROGRAM) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) 

clean:         rm -f *~ $(PROGRAM)

install: $(PROGRAM)
	install -s $(PROGRAM).exe $(DEST)
 
