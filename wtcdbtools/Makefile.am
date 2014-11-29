AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBWTCDB_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	wtcdbexport \
	wtcdbinfo

wtcdbexport_SOURCES = \
	export_handle.c export_handle.h \
	log_handle.c log_handle.h \
	wtcdbexport.c \
	wtcdboutput.c wtcdboutput.h \
	wtcdbtools_libbfio.h \
	wtcdbtools_libcerror.h \
	wtcdbtools_libcfile.h \
	wtcdbtools_libclocale.h \
	wtcdbtools_libcnotify.h \
	wtcdbtools_libcpath.h \
	wtcdbtools_libcsystem.h \
	wtcdbtools_libfdatetime.h \
	wtcdbtools_libfvalue.h \
	wtcdbtools_libuna.h \
	wtcdbtools_libwtcdb.h

wtcdbexport_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBUNA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

wtcdbinfo_SOURCES = \
	wtcdbinfo.c \
	wtcdboutput.c wtcdboutput.h \
	wtcdbtools_libcerror.h \
	wtcdbtools_libclocale.h \
	wtcdbtools_libcnotify.h \
	wtcdbtools_libcsystem.h \
	wtcdbtools_libfdatetime.h \
	wtcdbtools_libwtcdb.h

wtcdbinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on wtcdbexport ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(wtcdbexport_SOURCES)
	@echo "Running splint on wtcdbinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(wtcdbinfo_SOURCES)

