debug/disptest: matrixdisp/matrixdisp.o matrixdisp/color.o matrixdisp/palette.o matrixdisp/pinassign.h
	g++ -Wall -02 -o debug/disptest test.cpp matrixdisp/matrixdisp.o matrixdisp/color.o matrixdisp/palette.o matrixdisp/pinassign.h

matrixdisp/color.o: matrixdisp/color.cpp matrixdisp/color.h
	g++ -c matrixdisp/color.cpp matrixdisp/color.h

matrixdisp/palette.o: matrixdisp/palette.cpp matrixdisp/palette.h
	g++ -c matrixdisp/palette.cpp matrixdisp/palette.h

matrixdisp/matrixdisp.o: matrixdisp/matrixdisp.cpp matrixdisp/matrixdisp.h
	g++ -c matrixdisp/matrixdisp.cpp matrixdisp/matrixdisp.h