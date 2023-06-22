TARGET = ./main.o
HDRS_DIR = \
		headers
SRCS = \
		main.cpp \
		maze.cpp \
		structures.cpp \
		menu.cpp
.PHONY: all, build, clean, run

$(TARGET):
		g++ -I $(HDRS_DIR) -g $(SRCS) -o $(TARGET) -lGL -lGLU -lglut

all: clean build

build: $(TARGET)

clean: 
		rm -rf $(TARGET)

run: 
		$(TARGET)