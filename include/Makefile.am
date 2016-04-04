include_HEADERS = \
	libwtcdb.h

pkginclude_HEADERS = \
	libwtcdb/definitions.h \
	libwtcdb/error.h \
	libwtcdb/extern.h \
	libwtcdb/features.h \
	libwtcdb/types.h

EXTRA_DIST = \
	libwtcdb.h.in \
	libwtcdb/definitions.h.in \
	libwtcdb/features.h.in \
	libwtcdb/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libwtcdb.h
	/bin/rm -f libwtcdb/definitions.h
	/bin/rm -f libwtcdb/features.h
	/bin/rm -f libwtcdb/types.h
	/bin/rm -f Makefile

