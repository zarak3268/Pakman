SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
OUT_DIR=build

Pakman: $(OUT_DIR)/main.o GameManager.o MainMenuState.o PlayState.o GameOverState.o Entity.o Character.o Pakman.o Ghost.o utils.o Animation.o Maze.o Tile.o Pellet.o
	g++ $(OUT_DIR)/main.o $(OUT_DIR)/GameManager.o $(OUT_DIR)/MainMenuState.o $(OUT_DIR)/PlayState.o $(OUT_DIR)/GameOverState.o $(OUT_DIR)/Character.o $(OUT_DIR)/Entity.o $(OUT_DIR)/Pakman.o $(OUT_DIR)/Ghost.o $(OUT_DIR)/utils.o $(OUT_DIR)/Animation.o $(OUT_DIR)/Maze.o $(OUT_DIR)/Tile.o $(OUT_DIR)/Pellet.o -o $(OUT_DIR)/Pakman $(SFMLFLAGS)

$(OUT_DIR)/main.o: main.cpp | $(OUT_DIR)
	g++ -c main.cpp -o $(OUT_DIR)/main.o

GameManager.o: GameManager.cpp
	g++ -c GameManager.cpp -o $(OUT_DIR)/GameManager.o

PlayState.o: GameState/PlayState.cpp
	g++ -c GameState/PlayState.cpp -o $(OUT_DIR)/PlayState.o

MainMenuState.o: GameState/MainMenuState.cpp
	g++ -c GameState/MainMenuState.cpp -o $(OUT_DIR)/MainMenuState.o

GameOverState.o: GameState/GameOverState.cpp
	g++ -c GameState/GameOverState.cpp -o $(OUT_DIR)/GameOverState.o

Entity.o: Entity/Entity.cpp
	g++ -c Entity/Entity.cpp -o $(OUT_DIR)/Entity.o

Character.o: Entity/Characters/Character.cpp
	g++ -c Entity/Characters/Character.cpp -o $(OUT_DIR)/Character.o

Pakman.o: Entity/Characters/Pakman/Pakman.cpp
	g++ -c Entity/Characters/Pakman/Pakman.cpp -o $(OUT_DIR)/Pakman.o

Ghost.o: Entity/Characters/Ghosts/Ghost.cpp
	g++ -c Entity/Characters/Ghosts/Ghost.cpp -o $(OUT_DIR)/Ghost.o

utils.o: utils/utils.cpp
	g++ -c utils/utils.cpp -o $(OUT_DIR)/utils.o

Animation.o: Animation/Animation.cpp
	g++ -c Animation/Animation.cpp -o $(OUT_DIR)/Animation.o

Maze.o: Maze/Maze.cpp
	g++ -c Maze/Maze.cpp -o $(OUT_DIR)/Maze.o

Tile.o: Maze/Tile.cpp
	g++ -c Maze/Tile.cpp -o $(OUT_DIR)/Tile.o

Pellet.o: Entity/Pellet/Pellet.cpp
	g++ -c Entity/Pellet/Pellet.cpp -o $(OUT_DIR)/Pellet.o

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm $(OUT_DIR)/*.o $(OUT_DIR)/Pakman