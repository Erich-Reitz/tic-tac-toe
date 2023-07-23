CXX := g++ 
CXXFLAGS := -Wall -Werror -Wextra -pedantic -Wconversion -Wcast-align -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wold-style-cast 
SRC_DIR = ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) 
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -lSDL2

ASTYLEOPS := --mode=c --attach-return-type --align-pointer=name  --indent=spaces=4 --max-code-length=140 --break-after-logical 

PROGRAM_NAME := tic-tac-toe

all: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(PROGRAM_NAME)

make_and_run: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(PROGRAM_NAME)
	./$(PROGRAM_NAME)

tic-tac-toe: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o ${PROGRAM_NAME} $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)
clean:
	rm -f ${PROGRAM_NAME} $(OBJ_FILES)

format:
	astyle --style=google ${ASTYLEOPS} ${SRC_DIR}/*.*pp -xe
	
	rm -f ${SRC_DIR}/*.orig

