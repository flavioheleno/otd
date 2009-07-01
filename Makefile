COMPILER = gcc
FLAGS = -O2 -Wall -lglut -lGL -lGLU

all: base towers monsters waves map geometry common console menu shots defenses targets texture files main
	$(COMPILER) $(FLAGS) -o otd *.o

clean:
	rm -f otd *.o *~

base:
	$(COMPILER) $(FLAGS) -c $@.c

towers:
	$(COMPILER) $(FLAGS) -c $@.c

monsters:
	$(COMPILER) $(FLAGS) -c $@.c

waves:
	$(COMPILER) $(FLAGS) -c $@.c

map:
	$(COMPILER) $(FLAGS) -c $@.c

geometry:
	$(COMPILER) $(FLAGS) -c $@.c

common:
	$(COMPILER) $(FLAGS) -c $@.c

console:
	$(COMPILER) $(FLAGS) -c $@.c

menu:
	$(COMPILER) $(FLAGS) -c $@.c

shots:
	$(COMPILER) $(FLAGS) -c $@.c

defenses:
	$(COMPILER) $(FLAGS) -c $@.c

targets:
	$(COMPILER) $(FLAGS) -c $@.c

texture:
	$(COMPILER) $(FLAGS) -c $@.c

files:
	$(COMPILER) $(FLAGS) -c $@.c

main:
	$(COMPILER) $(FLAGS) -c $@.c

run: all
	./otd
