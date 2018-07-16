CC := clang++
TARGET := test
SFML_FLAGS := -lsfml-system -lsfml-window -lsfml-graphics

all: qtree.o
	$(CC) -o $(TARGET) main.cpp  qtree.o $(SFML_FLAGS)

qtree.o:
	$(CC) -c qtree.cpp

run:
	./$(TARGET)

clean:
	rm $(TARGET)

cleanall:
	rm $(TARGET) qtree.o
