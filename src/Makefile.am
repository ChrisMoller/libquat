
bin_PROGRAMS = quattest rot
quattest_SOURCES = quattest.cc Quat.h
quattest_CFLAGS = -std=c++11
quattest_DEPENDENCIES = Quat.o
quattest_LDADD = Quat.o

rot_SOURCES = rot.cc Quat.h
rot_CFLAGS = -std=c++11
rot_DEPENDENCIES = Quat.o
rot_LDADD = Quat.o

lib_LTLIBRARIES = libquat.la
libquat_la_SOURCES = Quat.hh Quat.cc

pkginclude_HEADERS = Quat.hh

DISTCLEANFILES = .deps/*.P

AUTOMAKE_OPTIONS = dejagnu
