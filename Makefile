run: 
		./main.exe
build: 
		g++ main.cpp -o main.exe
all:
		make build 
		make run
del: 
		rm ./main.exe