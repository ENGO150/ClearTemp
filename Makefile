all: main

# MAIN
files = src/main.cpp

# TOOLS
files += src/tools/*

# INCLUDE
files += include/*

main:
	@echo Compiling...
	g++ $(files) -std=c++2a -o out/ClearTemp

	@echo Output file generated.

clean:
	@echo Removing output...
	rm -rf out/*

	@echo Removing logs...
	rm -rf logs/*

	@echo Output files cleared!