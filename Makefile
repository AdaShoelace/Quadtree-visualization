CC := clang++
TARGET := test
SFML_FLAGS := -lsfml-system -lsfml-window -lsfml-graphics

all: gridrectangle.o
	$(CC) -o $(TARGET) main.cpp gridrectangle.o $(SFML_FLAGS)

gridrectangle.o:
	$(CC) -c gridrectangle.cpp

clean:
	rm $(TARGET)

cleanall:
	rm $(TARGET) gridrectangle.o
