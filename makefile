TARGET = lab_1
CC = gcc

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_SRC)*.c) 
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -g -o $(TARGET) -lm

$(PREF_OBJ)%.o : $(PREF_SRC)%.c 
	$(CC) -c $< -o $@

clean :
	rm $(TARGET) $(PREF_OBJ)*.o 
