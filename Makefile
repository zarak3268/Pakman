SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
OUT_DIR=build

Pakman: $(OUT_DIR)/main.o GameManager.o Agent.o Pakman.o utils.o Animation.o Maze.o Tile.o Pellet.o
	g++ $(OUT_DIR)/main.o $(OUT_DIR)/GameManager.o $(OUT_DIR)/Agent.o $(OUT_DIR)/Pakman.o $(OUT_DIR)/utils.o $(OUT_DIR)/Animation.o $(OUT_DIR)/Maze.o $(OUT_DIR)/Tile.o $(OUT_DIR)/Pellet.o -o $(OUT_DIR)/Pakman $(SFMLFLAGS)

$(OUT_DIR)/main.o: main.cpp | $(OUT_DIR)
	g++ -c main.cpp -o $(OUT_DIR)/main.o

GameManager.o: GameManager.cpp
	g++ -c GameManager.cpp -o $(OUT_DIR)/GameManager.o

Agent.o: Agents/Agent.cpp
	g++ -c Agents/Agent.cpp -o $(OUT_DIR)/Agent.o

Pakman.o: Agents/Pakman/Pakman.cpp
	g++ -c Agents/Pakman/Pakman.cpp -o $(OUT_DIR)/Pakman.o

utils.o: utils/utils.cpp
	g++ -c utils/utils.cpp -o $(OUT_DIR)/utils.o

Animation.o: Animation/Animation.cpp
	g++ -c Animation/Animation.cpp -o $(OUT_DIR)/Animation.o

Maze.o: Maze/Maze.cpp
	g++ -c Maze/Maze.cpp -o $(OUT_DIR)/Maze.o

Tile.o: Maze/Tile.cpp
	g++ -c Maze/Tile.cpp -o $(OUT_DIR)/Tile.o

Pellet.o: Pellet/Pellet.cpp
	g++ -c Pellet/Pellet.cpp -o $(OUT_DIR)/Pellet.o

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm $(OUT_DIR)/*.o $(OUT_DIR)/Pakman