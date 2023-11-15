include_HEADERS = \
	libwtcdb.h

pkginclude_HEADERS = \
	libwtcdb/codepage.h \
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
	-rm -f libwtcdb.h
	-rm -f libwtcdb/definitions.h
	-rm -f libwtcdb/features.h
	-rm -f libwtcdb/types.h
	-rm -f Makefile

