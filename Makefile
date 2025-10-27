# --- Project Variables ---
CC = gcc
CFLAGS = -Wall -g
TARGET = social.exe
SRCS = main.c platform.c post.c comment.c reply.c
OBJS = $(SRCS:.c=.o) # Replaces .c extension with .o

# --- Targets ---

.PHONY: all clean run

# Default target: builds the executable
all: $(TARGET)

# Target to link all object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	@echo "Build successful: $(TARGET)"

# Implicit rule for compiling .c files into .o files
# $^ is all prerequisites (the .c file)
# $@ is the target (the .o file)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Target to run the application, reading input directly from the terminal (stdin)
run: $(TARGET)
	@echo "Running $(TARGET)... Enter commands below. Press Ctrl+D (or Ctrl+Z on Windows) when done."
	./$(TARGET)

# Target to remove compiled files (using Windows commands for robust cleanup)
clean:
	@echo "Cleaning up..."
	del $(OBJS) 2>NUL
	del $(TARGET) 2>NUL
	# Fallback for Unix/Git Bash environments
	rm -f $(OBJS) $(TARGET)
