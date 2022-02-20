# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CVERSION = -std=c++11
CFLAGS  = -g -Wall

TARGET_NAME = wordle

all: $(TARGET_NAME)

$(TARGET_NAME): 
	$(CC) $(CVERSION) $(CFLAGS) -o $(TARGET_NAME) main.cpp

clean:
	$(RM) $(TARGET_NAME)
