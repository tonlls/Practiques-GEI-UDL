CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -g -std=c++11
LDFLAGS= -g -std=c++11

src = $(wildcard *.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)

SRCS= $(wildcard *.cpp)
#WordCount.cpp  MapReduce.cpp Map.cpp rutines.cpp 
OBJS=$(subst .cpp,.o,$(SRCS))

all: WordCount

WordCount: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) $(CPPFLAGS) -o $@ -c $< 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
