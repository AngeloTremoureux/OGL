OPTIONS= -lGL -lGLU ../Build/external/glfw-3.1.2/src/libglfw3.a ../Build/external/libGLEW_1130.a -lGL -lGLU -lXrandr -lXext -lX11 -lrt -ldl -lrt -lm -lX11 -lpthread -lXrandr -lXinerama -lXi -lXcursor -ldl -lrt -lm -lXxf86vm
WARNINGS= -Wall -pedantic -Wextra
MACROS= #-DWNAF#-DFLAG#-DWNAF#-DPROBE# -DREALTIME -DPROC1  -DPROC0 #-DPROBEFILE -DREALTIME
INCLUDES= -I ../external/glew-1.13.0/include/ -I ../external/glfw-3.1.2/include/ -I ../external/glm-0.9.7.1/ -I ../
OPTIONS+= $(WARNINGS)
OPTIONS+= $(MACROS)

OPTIONS+= $(INCLUDES)


playground : playground.o shader.o
	g++ -o playground playground.o shader.o $(OPTIONS)

shader.o : ../common/shader.cpp ../common/shader.hpp
	g++ -c ../common/shader.cpp $(OPTIONS)

playground.o : playground.cpp shader.o
	g++ -c playground.cpp $(OPTIONS)
	
all : playground


clean :
	rm *.o -fv *~

cleanall : clean
	rm playground -f

