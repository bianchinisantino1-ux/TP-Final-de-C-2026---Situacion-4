CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LIBS = -lm
TARGET = simulador_artemis.exe
SRCS = src/main.c src/artemis.c src/validaciones.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	del /f /q $(TARGET) 2>nul || rm -f $(TARGET)
