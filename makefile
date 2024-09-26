targets = .\build\snake.exe
sources = main.c banner.c
objects = .\build\main.o .\build\banner.o .\build\snake.o

$(targets): $(objects)
	gcc -o $@ $(objects)

.\build\main.o: .\src\main.c
	gcc -o $@ -c $<

.\build\banner.o: .\src\banner.c
	gcc -o $@ -c $<

.\build\snake.o: snake.rc
	windres -o $@ -i $<