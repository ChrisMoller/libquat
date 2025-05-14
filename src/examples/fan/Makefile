   CPPFLAGS = -g
    LDFLAGS = 
       INCS =
       LIBS =

%.o:%.cc
	g++ -c $(CPPFLAGS) $<

testfan: testfan.o ../../Quat.o
	 g++ -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	rm -f testfan.o

veryclean: clean
	rm -f testfan

