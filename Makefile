# MAIN SOURCE FILE
files = src/main.c

# OTHER SOURCE FILES (assets/)
files += src/assets/*

# HEADER FILES (include/)
files += include/*

# OTHER (lib/)
	# ENGODATABASE
	files += lib/*/*/*

# OUTPUT FILE GENERATION
main : $(files)
	@echo Compiling...
	gcc $(files) -o out/ClearTemp

	@echo Output file generated.

# OUTPUT FILE REMOVING
clean:
	@echo Removing...
	rm -rf out/*

	@echo Output files cleared!