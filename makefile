.PHONY: clean build

targets = .\build\snake.exe
sources = main.c banner.c
objects = .\build\main.o .\build\banner.o .\build\snake.o

$(targets): $(objects)
	@gcc -o $@ $(objects)
	@echo [100%%] Done

.\build\main.o: .\src\main.c
	@gcc -o $@ -c $<
	@echo [ 25%%]main.c  to  main.o

.\build\banner.o: .\src\banner.c
	@gcc -o $@ -c $<
	@echo [ 50%%] banner.c  to  banner.o

.\build\snake.o: snake.rc
	@windres -o $@ -i $<
	@echo [ 75%%] snake.rc  to  snake.o

clean:
	@del build\*.o
	@del build\snake.exe
	@echo [100%%] Done

build:
	@mkdir build