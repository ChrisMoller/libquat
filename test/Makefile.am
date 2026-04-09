bin_PROGRAMS = test

          AM_CXXFLAGS = -I../src

      test_SOURCES = test.cc tests.m4
 test_DEPENDENCIES = test.o tests.h
        test_LDADD = -L../src/.libs -lquat -lgsl -lgslcblas -lm

tests.h: tests.m4
	m4 < $< > $@

CLEANFILES = tests.h
