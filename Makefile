# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

# all sources, objs, and header files

TARGET = tp2.out
SRC = $(wildcard $(SRC_FOLDER)/*.cc)
OBJ = $(patsubst $(SRC_FOLDER)/%.cc, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cc
	@mkdir -p $(OBJ_FOLDER)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all: $(OBJ)
	@mkdir -p $(BIN_FOLDER)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

clean:
	@rm -rf $(OBJ_FOLDER) $(BIN_FOLDER)

.PHONY: all clean
