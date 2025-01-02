# Variables
CC=gcc            # C compiler
CXX=g++           # C++ compiler
CFLAGS=-I.        # Include path for headers
CXXFLAGS=-I.      # Include path for headers for C++
LDFLAGS=-lm       # Linker flags for libraries (math library)

# Dependencies
DEPS = PID.h CircularBuffer.h clockadj.h missing.h phc_ctl.h  

# Object files
OBJ = main.o PID.o CircularBuffer.o clockadj.o phc_ctl.o 

# Pattern rule for C source files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Pattern rule for C++ source files
%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Target for the final executable
main: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Clean target to remove built files
.PHONY: clean
clean:
	rm -f *.o main
