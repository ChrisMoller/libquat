
bin_PROGRAMS = quattest
quattest_SOURCES = quattest.cc Quat.h
quattest_CFLAGS = -std=c++11
quattest_DEPENDENCIES = Quat.o
quattest_LDADD = Quat.o

lib_LTLIBRARIES = libquat.la
libquat_la_SOURCES = Quat.hh Quat.cc

pkginclude_HEADERS = Quat.hh

DISTCLEANFILES = .deps/*.P

AUTOMAKE_OPTIONS = dejagnu


