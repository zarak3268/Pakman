g++ -c main.cpp Agents/Agent.cpp utils/utils.cpp Animation/Animation.cpp
g++ main.o Agent.o utils.o Animation.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system