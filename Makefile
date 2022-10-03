all: 
	@g++ -o main.exe main.cpp
	@./main
	@rm main.exe

clean:
	@rm main.exe