all: main

main: main.cpp player.h bullet.h enemies.h functions.h
	sudo apt-get install -y libncurses5-dev libncursesw5-dev
	g++ main.cpp -lncurses -Ofast -o main

clean:
	rm -f main
