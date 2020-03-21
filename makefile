ALL: build tidy

run: ALL
		./shfd

build: lib.o Utils.o main.o  ShellServer.o
		@echo -----------------------
		@echo "Building sshell..."
		@echo -----------------------

		g++ lib.o Utils.o main.o ShellServer.o -o shfd

main.o: ./src/main.cpp
		@echo -----------------------
		@echo Building main...
		@echo -----------------------

		g++ -c ./src/main.cpp

ShellServer.o: ./src/components/ShellServer.cpp
		@echo -----------------------
		@echo Building ShellServer...
		@echo -----------------------

		g++ -c ./src/components/ShellServer.cpp

lib.o: ./src/lib.cpp		
		@echo -----------------------
		@echo Building lib...
		@echo -----------------------

		g++ -c ./src/lib.cpp

Utils.o: ./src/Utils.cpp		
		@echo -----------------------
		@echo Building Utils...
		@echo -----------------------

		g++ -c ./src/Utils.cpp

tidy:   
	  @echo -----------------------
		@echo Tidying things up...
		@echo -----------------------
		rm -r *.o

clean:
		@echo -----------------------
		@echo "      CLEANING"
		@echo -----------------------

		rm -r *.o *.out shfd