all: chess.exe

chess.exe: chess.o functions.o check.o valid_moves.o piece_identifier.o
	gcc chess.o functions.o check.o valid_moves.o piece_identifier.o -o chess.exe

chess.o: chess.c functions.h constants.h player.h
	gcc -c chess.c -o chess.o

functions.o: functions.c player.h constants.h check.h functions.h valid_moves.h piece_identifier.h
	gcc -c functions.c -o functions.o

check.o: check.c constants.h check.h functions.h valid_moves.h piece_identifier.h
	gcc -c check.c -o check.o

valid_moves.o: valid_moves.c constants.h valid_moves.h piece_identifier.h functions.h check.h
	gcc -c valid_moves.c -o valid_moves.o

piece_identifier.o: piece_identifier.c constants.h piece_identifier.h
	gcc -c piece_identifier.c -o piece_identifier.o

clean:
	rm -rf *.o chess.exe