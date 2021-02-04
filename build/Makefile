.PHONY: all run test clean

CC = g++
CFAGS = -std=c++17 -ggdb -g3

MAIN_FILE = ../src/main.cpp
SOURCES = ../src/Lexer.cpp ../src/Parser.cpp ../src/Token.cpp ../src/Node.cpp ../src/Evaluator.cpp
TESTS = ../tests/Tests.cpp ../tests/Parser.test.cpp ../tests/Lexer.test.cpp ../tests/Evaluator.test.cpp

MAIN_EXEC = run
MAIN_FILE_O = $(subst ../src/,,$(MAIN_FILE:.cpp=.o))
MAIN_OBJECTS = $(subst ../src/,,$(SOURCES:.cpp=.o))

TEST_EXEC = ../tests/runtests
TEST_CFLAGS = -lgtest -lgtest_main -pthread
TEST_OBJECTS = $(subst ../tests/,,$(TESTS:.cpp=.o))

# Syntax:
# [target]: [dependent....]
#   [command]
#
# $@ - name of target
# $< - name of first dependensy
# $^ - all dependensies
# %  - template

all: $(MAIN_FILE) $(SOURCES) run test

run: $(MAIN_FILE_O) $(MAIN_OBJECTS)
	$(CC) $(CFAGS) $^ -o $(MAIN_EXEC)

test: $(MAIN_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFAGS) $(TEST_CFLAGS) $^ -o $(TEST_EXEC)

clean:
	rm -rf *.o $(MAIN_EXEC) $(TEST_EXEC)

%.o: ../tests/%.cpp
	$(CC) $(CFAGS) -c $< -o $@

%.o : ../src/%.cpp
	$(CC) $(CFAGS) -c $< -o $@

