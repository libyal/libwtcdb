AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libnotify \
	@LIBUNA_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = libwtcdb.la

libwtcdb_la_SOURCES = \
	libwtcdb.c \
	libwtcdb_array_type.c libwtcdb_array_type.h \
	libwtcdb_crc.c libwtcdb_crc.h \
	libwtcdb_debug.c libwtcdb_debug.h \
	libwtcdb_definitions.h \
	libwtcdb_error.c libwtcdb_error.h \
	libwtcdb_extern.h \
	libwtcdb_file.c libwtcdb_file.h \
	libwtcdb_item.c libwtcdb_item.h \
	libwtcdb_item_value.c libwtcdb_item_value.h \
	libwtcdb_io_handle.c libwtcdb_io_handle.h \
	libwtcdb_libbfio.h \
	libwtcdb_libfdatetime.h \
	libwtcdb_libfvalue.h \
	libwtcdb_libuna.h \
	libwtcdb_notify.c libwtcdb_notify.h \
	libwtcdb_support.c libwtcdb_support.h \
	libwtcdb_types.h \
	wtcdb_cache_entry.h \
	wtcdb_file_header.h \
	wtcdb_index_entry.h

libwtcdb_la_LIBADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libnotify/libnotify.la \
	@LIBUNA_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFVALUE_LIBADD@

libwtcdb_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libwtcdb_definitions.h.in \
	libwtcdb.rc \
	libwtcdb.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libwtcdb_definitions.h
	/bin/rm -f libwtcdb.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libwtcdb ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libwtcdb_la_SOURCES) 

