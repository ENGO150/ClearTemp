all: main

files = src/main.cpp

main: $(files)
	@echo Compiling...
	g++ $(files) -o out/ClearTemp

	@echo Output file generated.

clean:
	@echo Removing output...
	rm -rf out/*

	@echo Removing logs...
	rm -rf logs/*

	@echo Output files cleared!