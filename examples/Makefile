   CFLAGS = -g \
             `pkg-config --cflags  glfw3` \
             `pkg-config --cflags  gl` \
             `pkg-config --cflags  glu` \
             `pkg-config --cflags  gsl` \
             `pkg-config --cflags  glm `
     INCS = -I../src
  LDFLAGS = 
     LIBS = -L../src/.libs -lquat -Wl,-rpath,../src/.libs \
             `pkg-config --libs  glfw3` \
             `pkg-config --libs  gl` \
             `pkg-config --libs  glu` \
             `pkg-config --libs  gsl` \
             `pkg-config --libs  glm`

#     LIBS = -L../src/.libs -lquat -Wl,-rpath,/../src/.libs
#     LIBS = -L../src/.libs -lquat -Wl,-rpath,/../src/.libs

%.o:%.cc
	g++-15 -c $(CFLAGS) $(INCS) $<

tryglfw2: tryglfw2.o cube.o icosahedron.o
	g++-15 -o $@ $^ $(LIBS) $(LDFLAGS)

cube.o: cube.cc cube.hh

icosahedron.o: icosahedron.cc icosahedron.hh

clean:
	rm -f *.o

veryclean: clean
	rm -f tryglfw tryglfw2
