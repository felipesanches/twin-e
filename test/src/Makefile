CXX = g++
CXXFLAGS = -g -lgtest -lpthread
INCS = -I./ -I../../src -I/usr/include/gtest
OBJS = \
       ../../src/movements.o \
       movements_test.o


testAll: $(OBJS)
	$(CXX) $(OBJS) $(INCS) $(CXXFLAGS) -o testAll

.c.o: $(OBJS)
	$(CXX) -c $< -o $@ $(INCS) $(CXXFLAGS) 

clean:
	rm testAll *.o testAll.xml
