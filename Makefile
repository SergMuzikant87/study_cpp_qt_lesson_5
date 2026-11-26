CC := g++
MOC := /usr/lib/qt6/libexec/moc
COMPILE_FLAGS := -fPIC -I/usr/include/x86_64-linux-gnu/qt6 -Wall -O2 -pthread -std=c++20
LINKER_FLAGS := -lQt6Core -lQt6Gui -lQt6Widgets
SOURCE_FORDER := source/
OUTPUT_FORDER := output/
OBJECTS_FORDER := output/objects/
PROGRAMM_NAME := programm
PROGRAMM := $(OUTPUT_FORDER)$(PROGRAMM_NAME)
HEADERS := $(wildcard ./source/*.h)
SOURCES := $(wildcard ./source/*.cpp)
OBJECTS := $(patsubst ./source/%.cpp, ./output/objects/%.o, $(SOURCES))
OBJECTS += output/objects/window_start_moc.o output/objects/stopwatch_moc.o 

$(PROGRAMM): $(OBJECTS)
	$(CC) $^ -o $@ $(LINKER_FLAGS)

./output/objects/%.o : ./source/%.cpp
	$(CC) $(COMPILE_FLAGS) $(TARGET) -c $< -o $@
	
./source/%_moc.cpp : ./source/%.h
	$(MOC) $< -o $@
	
clean:
	rm -f $(OBJECTS_FORDER)*.o 
	rm -f $(PROGRAMM)
	rm -f $(SOURCE_FORDER)*_moc.cpp


