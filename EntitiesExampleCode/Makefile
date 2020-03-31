# Feel free to edit this as needed
#
program = main 

CXXFLAGS = -std=c++17 -Wall List.cpp Entities.cpp

all: $(program)

$(program): main.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

run: $(program)
	./$(program)

clean:
	$(RM) -f $(program)
