CXX = g++
CXXFLAGS = -Wall -lncurses -DNDEBUG -D_NCURSE -D_LEVEL
EXEC = cc3k 
OBJECTS = main.o action.o boardDisplay.o character.o floor.o game.o gameSession.o gold.o hoard.o inputHandler.o item.o listener.o mapGenerator.o messageDisplay.o menuDisplay.o npc.o object.o player.o playerImpl.o potion.o randomizer.o stairs.o statsCollector.o tile.o

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

main.o: main.cc gameSession.h

action.o: action.cc action.h tile.h floor.h coord.h character.h npc.h playerImpl.h

boardDisplay.o: boardDisplay.cc boardDisplay.h display.h

character.o: character.cc character.h object.h defaultStat.h

floor.o: floor.cc floor.h boardDisplay.h tile.h

game.o: game.cc game.h gameSession.h menuDisplay.h

gameSession.o: gameSession.cc gameSession.h inputHandler.h messageDisplay.h statsCollector.h player.h floor.h boardDisplay.h mapGenerator.h

gold.o: gold.h gold.cc item.h

hoard.o: hoard.h hoard.cc gold.h item.h

inputHandler.o: inputHandler.cc inputHandler.h listener.h

item.o: item.cc item.h object.h playerImpl.h

listener.o: listener.cc listener.h

mapGenerator.o: mapGenerator.cc mapGenerator.h coord.h floor.h listener.h tile.h statsCollector.h player.h npc.h statsCollector.h randomizer.h gold.h hoard.h

messageDisplay.o: messageDisplay.cc messageDisplay.h

menuDisplay.o: menuDisplay.cc menuDisplay.h

npc.o: npc.cc npc.h character.h action.h defaultStat.h

object.o: object.cc object.h tile.h

player.o: player.cc player.h playerImpl.h

playerImpl.o: playerImpl.cc playerImpl.h defaultStat.h character.h action.h

potion.o: potion.cc potion.h item.h

randomizer.o: randomizer.cc randomizer.h

statsCollector.o: statsCollector.cc statsCollector.h listener.h

stairs.o: stairs.cc stairs.h character.h playerImpl.h

tile.o: tile.cc tile.h object.h character.h

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}

