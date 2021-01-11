.PHONY: all debug run test clean

CC=g++
CFAGS=-std=c++17 

MAIN_EXEC=run
MAIN_FILE=main.o
MAIN_OBJECTS=lexer.o parser.o token.o node.o evaluator.o

TEST_EXEC=../tests/runtests
TEST_CFLAGS=-lgtest -lgtest_main -pthread
TEST_OBJECTS=test.o parser.test.o lexer.test.o evaluator.test.o

DEBUG_EXEC=debug
DEBUG_CFLAGS=-ggdb -g3

all: run

run: $(MAIN_OBJECTS)
	$(CC) $(CFAGS) $^ $(MAIN_FILE) -o $(MAIN_EXEC)

debug: $(MAIN_OBJECTS)
	$(CC) $(CFAGS) $(DEBUG_CFLAGS) $(MAIN_FILE) $^ -o $(DEBUG_EXEC)

test: $(TEST_OBJECTS) $(MAIN_OBJECTS)
	$(CC) $(CFAGS) $(TEST_CFLAGS) $^ -o $(TEST_EXEC)

clean:
	rm -rf *.o $(MAIN_EXEC) $(TEST_EXEC) $(DEBUG_EXEC)


main.o: ../src/main.cpp
	$(CC) $(CFAGS) -c $< -o $@

lexer.o: ../src/Lexer.cpp
	$(CC) $(CFAGS) -c $< -o $@

parser.o: ../src/Parser.cpp
	$(CC) $(CFAGS) -c $< -o $@

token.o: ../src/Token.cpp
	$(CC) $(CFAGS) -c $< -o $@

node.o: ../src/Node.cpp
	$(CC) $(CFAGS) -c $< -o $@

evaluator.o: ../src/Evaluator.cpp
	$(CC) $(CFAGS) -c $< -o $@

test.o: ../tests/Tests.cpp
	$(CC) $(CFAGS) -c $< -o $@

parser.test.o: ../tests/Parser.test.cpp
	$(CC) $(CFAGS) -c $< -o $@

lexer.test.o: ../tests/Lexer.test.cpp
	$(CC) $(CFAGS) -c $< -o $@

evaluator.test.o: ../tests/Evaluator.test.cpp
	$(CC) $(CFAGS) -c $< -o $@

