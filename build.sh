g++ -c main.cpp Agents/Agent.cpp utils/utils.cpp
g++ main.o Agent.o utils.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system