# Variables
CC=gcc            # C compiler
CXX=g++           # C++ compiler
CFLAGS=-I.        # Include path for headers
CXXFLAGS=-I.      # Include path for headers for C++
LDFLAGS=-lm       # Linker flags for libraries (math library)

# Dependencies
DEPS = PID.h CircularBuffer.h clockadj.h missing.h phc_ctl.h dmtimer.h cpts.h     # Header dependencies

# Object files
OBJ = main.o PID.o CircularBuffer.o clockadj.o phc_ctl.o dmtimer.o cpts.o # Object files

# Pattern rule for C source files compile with C++
%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

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
