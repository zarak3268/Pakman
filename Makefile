SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
OUT_DIR=build

Pakman: $(OUT_DIR)/main.o Agent.o utils.o Animation.o
	g++ $(OUT_DIR)/main.o $(OUT_DIR)/Agent.o $(OUT_DIR)/utils.o $(OUT_DIR)/Animation.o -o $(OUT_DIR)/Pakman $(SFMLFLAGS)

$(OUT_DIR)/main.o: main.cpp | $(OUT_DIR)
	g++ -c main.cpp -o $(OUT_DIR)/main.o

Agent.o: Agents/Agent.cpp
	g++ -c Agents/Agent.cpp -o $(OUT_DIR)/Agent.o

utils.o: utils/utils.cpp
	g++ -c utils/utils.cpp -o $(OUT_DIR)/utils.o

Animation.o: Animation/Animation.cpp
	g++ -c Animation/Animation.cpp -o $(OUT_DIR)/Animation.o

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm $(OUT_DIR)/*.o $(OUT_DIR)/Pakman