
#Linux packages : freeglut3-dev, libglew-dev

CXX=g++
DIR1 = .
DIR2 = ../Dependencies_x64/include
INC=$(DIR1) $(DIR2)
INC_PARAMS=$(foreach d, $(INC), -I$d)
CXXFLAGS=-Wall $(INC_PARAMS)
LIB=-lm -lGL -lglut -lGLEW -lGLU -lpthread
OBJ=build/Main.o build/GameSelection.o build/GameBase.o build/GameMenu.o build/ShooterGame.o build/GameConfiguration.o build/KeyboardStatus.o build/CParticle.o build/Vector3.o build/AParticle.o build/PParticle.o \
build/Camera.o 

all: checkdirs Main

Main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIB)

build/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: Games/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: GraphicEngine/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	
build/%.o: PhysicEngine/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	
build/%.o: Games/Game1/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

checkdirs:
	@mkdir -p build/

clean:
	@rm -rf build/
	@rm -f Main
