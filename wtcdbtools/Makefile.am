AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libsystem \
	@LIBUNA_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@ \
	@LIBWTCDB_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	wtcdbexport \
	wtcdbinfo

wtcdbexport_SOURCES = \
	export_handle.c export_handle.h \
	log_handle.c log_handle.h \
	wtcdbexport.c \
	wtcdboutput.c wtcdboutput.h

wtcdbexport_LDADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libwtcdb/libwtcdb.la \
	../libsystem/libsystem.la \
	@LIBUNA_LIBADD@ \
	@MEMWATCH_LIBADD@

wtcdbinfo_SOURCES = \
	wtcdbinfo.c \
	wtcdboutput.c wtcdboutput.h

wtcdbinfo_LDADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libwtcdb/libwtcdb.la \
	../libsystem/libsystem.la \
	@LIBUNA_LIBADD@ \
	@MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on wtcdbexport ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(wtcdbexport_SOURCES) 
	@echo "Running splint on wtcdbinfo ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(wtcdbinfo_SOURCES) 

