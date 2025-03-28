AUTOMAKE_OPTIONS = dejagnu
SUBDIRS = src
dist_doc_DATA = README.md
EXTRA_DIST = autogen.sh src test
#RUNTESTFLAGS = --tool test TEST=`pwd`/src/test --srcdir $$srcdir/test
RUNTESTFLAGS = -tool test   --srcdir "." 

save:
	gitpush

cov:
	make check
	make -C src cov
