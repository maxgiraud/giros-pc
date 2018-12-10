CC=g++
CFLAGS=
LDFLAGS=
EXEC=g2b
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: release clean rebuild mrproper std

clean:
	rm -rv *.o

rebuild: clean all

mrproper: clean
	rm -rv $(EXEC)
