app: main.cpp matrixdisp/palette.o matrixdisp/color.o matrixdisp/virtualdisp.o game.o gamesystem.o pinassign.o matrixdisp/matrixdisp.o soundlib/soundplayer.o soundlib/soundcontainer.o soundlib/wavecontainer.o matrixdisp/bmpcontainer.o enviroment.o soundmanager.o
	g++ -Wall -O2 -lwiringPi -lasound -pthread -std=c++11 -o app main.cpp matrixdisp/color.o matrixdisp/palette.o matrixdisp/matrixdisp.o matrixdisp/virtualdisp.o gamesystem.o game.o pinassign.o  soundlib/soundplayer.o soundlib/soundcontainer.o soundlib/wavecontainer.o matrixdisp/bmpcontainer.o enviroment.o soundmanager.o

matrixdisp/matrixdisp.o: matrixdisp/matrixdisp.h matrixdisp/matrixdisp.cpp
	g++ -Wall -std=c++11 -c matrixdisp/matrixdisp.cpp -o matrixdisp/matrixdisp.o

matrixdisp/color.o: matrixdisp/color.h matrixdisp/color.cpp
	g++ -Wall -c matrixdisp/color.cpp -o matrixdisp/color.o

matrixdisp/palette.o: matrixdisp/palette.h matrixdisp/palette.cpp
	g++ -Wall -c matrixdisp/palette.cpp -o matrixdisp/palette.o

matrixdisp/virtualdisp.o: matrixdisp/virtualdisp.h matrixdisp/virtualdisp.cpp
	g++ -Wall -std=c++11 -c matrixdisp/virtualdisp.cpp -o matrixdisp/virtualdisp.o

gamesystem.o: gamesystem.h gamesystem.cpp pinassign.o
	g++ -Wall -std=c++11 -c gamesystem.cpp -o gamesystem.o
game.o: game.h game.cpp pinassign.o
	g++ -Wall -std=c++11 -c game.cpp -o game.o

pinassign.o: pinassign.h pinassign.cpp
	g++ -Wall -c pinassign.cpp -o pinassign.o

soundlib/wavecontainer.o: soundlib/wavecontainer.h soundlib/wavecontainer.cpp
	g++ -Wall -std=c++11 -c soundlib/wavecontainer.cpp -o soundlib/wavecontainer.o

soundlib/soundcontainer.o: soundlib/soundcontainer.h soundlib/soundcontainer.cpp
	g++ -Wall -std=c++11 -c soundlib/soundcontainer.cpp -o soundlib/soundcontainer.o

soundlib/soundplayer.o: soundlib/soundplayer.h soundlib/soundplayer.cpp
	g++ -Wall -std=c++11 -c soundlib/soundplayer.cpp -o soundlib/soundplayer.o

matrixdisp/bmpcontainer.o: matrixdisp/bmpcontainer.h matrixdisp/bmpcontainer.cpp
	g++ -Wall -std=c++11 -c matrixdisp/bmpcontainer.cpp -o matrixdisp/bmpcontainer.o

enviroment.o: enviroment.h enviroment.cpp
	g++ -Wall -std=c++11 -c enviroment.cpp -o enviroment.o

soundmanager.o: soundmanager.h soundmanager.cpp
	g++ -Wall -std=c++11 -c soundmanager.cpp -o soundmanager.o