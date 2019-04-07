BUILD_DIR := build
TARGET := tarefa_c

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all clean run format

all: tarefa_c

$(BUILD_DIR):
	@echo "Creating build directory"
	@mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	gcc -g -Wall -Wextra -o $@ -c $^

clean:
ifeq ($(OS), Windows_NT)
	rm -r $(BUILD_DIR) *.exe
else
	rm -r $(BUILD_DIR) tarefa_c
endif

tarefa_c: $(OBJECTS)
	gcc -g -Wall -Wextra -o tarefa_c $(OBJECTS)

run: all
ifeq ($(OS), Windows_NT)
	start powershell -NoExit ./tarefa_c
else
	./tarefa_c 
endif

