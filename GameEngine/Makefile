
#Linux packages : freeglut3-dev, libglew-dev, assimp-utils, libassimp-dev, libsoil-dev

CXX=g++-8
DIR1 = .
DIR2 = ../Dependencies_x64/include
INC=$(DIR1) $(DIR2)
INC_PARAMS=$(foreach d, $(INC), -I$d)
CXXFLAGS=-Wall -Wno-unknown-pragmas $(INC_PARAMS) -std=c++17 -lstdc++fs
LIB=-lm -lGL -lglut -lGLEW -lGLU -lpthread -lassimp -lSOIL
OBJ=build/Main.o \
build/Demo.o \
build/BlobGame.o \
build/ShooterGame.o \
build/RigidBodyDemo.o build/CarDemo.o \
build/GameSelection.o build/GameBase.o build/GameMenu.o build/GameConfiguration.o build/KeyboardStatus.o build/MouseStatus.o \
build/ElementBufferObject.o build/GeometryBuffer.o build/VertexArrayObject.o build/FrameBuffer.o build/MultipleDataVBO.o build/VertexBufferObject.o build/FrameBufferObject.o build/RenderBuffer.o \
build/Color.o build/PhongMaterial.o \
build/BoundingBox.o build/Camera.o build/ScreenRenderQuad.o build/SkyboxGeometry.o build/Text.o \
build/Mesh.o build/PMeshObject.o build/TransformStack.o build/PHorizontalPlane.o build/PParticle.o build/PIrregularCube.o \
build/LightServer.o build/SceneServer.o build/ShaderServer.o build/TextureServer.o \
build/MeshShader.o build/ShaderParser.o build/ShaderSource.o build/VFXShader.o build/Shader.o build/ShaderProgram.o build/SkyboxShader.o \
build/CubeMap.o build/Texture2D.o \
build/Matrix3x3.o build/Matrix3x4.o build/Quaternion.o build/Vector3.o \
build/ParticleCable.o build/ParticleRod.o build/ParticleContact.o build/ParticleContactResolver.o build/PlaneContactGenerator.o \
build/ParticleForceRegistry.o build/ParticleGravity.o build/ParticleDrag.o build/BodyForceRegistry.o build/BodyGravity.o \
build/ParticleSpring.o build/ParticleAnchoredSpring.o build/ParticleBungee.o build/ParticleBuoyancy.o \
build/CParticle.o build/AParticle.o build/AHorizontalPlane.o build/ARigidBody.o \
build/CMeshObject.o build/EmptyNode.o build/CHorizontalPlane.o build/CCar.o build/CIrregularCube.o \
build/Paths.o

all: checkdirs Main

Main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIB)

build/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: Games/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: Games/Game1/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	
build/%.o: Games/Game2/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	
build/%.o: Games/Demo/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: Games/Game3/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: GraphicEngine/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: GraphicEngine/Buffers/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: GraphicEngine/Materials/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: GraphicEngine/SceneBase/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: GraphicEngine/SceneGraph/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: GraphicEngine/Servers/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: GraphicEngine/Shaders/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: GraphicEngine/Textures/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: Math/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: PhysicEngine/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	
build/%.o: PhysicEngine/Collisions/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	
build/%.o: PhysicEngine/Forces/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	
build/%.o: PhysicEngine/SpringForces/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: SceneGraph/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%.o: System/Src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	
checkdirs:
	@mkdir -p build/

clean:
	@rm -rf build/
	@rm -f Main
