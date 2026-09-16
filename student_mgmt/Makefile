# ============================================================
#  Makefile  –  Student Information Management System
#  Usage:
#    make          → build
#    make run      → build & run
#    make clean    → remove binary and .csv
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra
TARGET   = student_mgmt
SRC      = src/main.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC) include/*.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "Build successful → ./$(TARGET)"

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) students.csv
	@echo "Cleaned."
