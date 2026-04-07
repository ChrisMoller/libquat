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

plato: plato.o tetrahedron.o cube.o octahedron.o dodecahedron.o icosahedron.o
	g++ -o $@ $^ $(LIBS) $(LDFLAGS)

tetrahedron.o: tetrahedron.cc tetrahedron.hh

cube.o: cube.cc cube.hh

octahedron.o: octahedron.cc octahedron.hh

dodecahedron.o: dodecahedron.cc dodecahedron.hh

icosahedron.o: icosahedron.cc icosahedron.hh

clean:
	rm -f *.o

veryclean: clean
	rm -f plato
