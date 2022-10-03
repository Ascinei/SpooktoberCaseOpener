all: 
	@g++ -o main.exe main.cpp
	@./main
	@rm main.exe

build:
	@g++ -o main.exe main.cpp

clean:
	@rm main.exe