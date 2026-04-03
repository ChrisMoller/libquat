   CFLAGS = -g \
             `pkg-config --cflags  glfw3` \
             `pkg-config --cflags  gl` \
             `pkg-config --cflags  glu` \
             `pkg-config --cflags  gsl` \
             `pkg-config --cflags  glm` \
             `pkg-config --cflags  ftgl` \
             `pkg-config --cflags  freetype2`
     INCS = -I../src
  LDFLAGS = 
     LIBS = -L../src/.libs -lquat -Wl,-rpath,../src/.libs \
             `pkg-config --libs  glfw3` \
             `pkg-config --libs  gl` \
             `pkg-config --libs  glu` \
             `pkg-config --libs  gsl` \
             `pkg-config --libs  glm` \
             `pkg-config --libs  ftgl` \
             `pkg-config --libs  freetype2`

%.o:%.cc
	g++ -c $(CFLAGS) $(INCS) $<

tryglfw2: tryglfw2.o cube.o icosahedron.o
	g++ -o $@ $^ $(LIBS) $(LDFLAGS)

cube.o: cube.cc cube.hh

icosahedron.o: icosahedron.cc icosahedron.hh

clean:
	rm -f *.o

veryclean: clean
	rm -f tryglfw tryglfw2
