AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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
	@LIBWTCDB_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	wtcdbexport \
	wtcdbinfo

wtcdbexport_SOURCES = \
	export_handle.c export_handle.h \
	log_handle.c log_handle.h \
	wtcdbexport.c \
	wtcdbtools_getopt.c wtcdbtools_getopt.h \
	wtcdbtools_i18n.h \
	wtcdbtools_libbfio.h \
	wtcdbtools_libcerror.h \
	wtcdbtools_libcfile.h \
	wtcdbtools_libclocale.h \
	wtcdbtools_libcnotify.h \
	wtcdbtools_libcpath.h \
	wtcdbtools_libfdatetime.h \
	wtcdbtools_libuna.h \
	wtcdbtools_libwtcdb.h \
	wtcdbtools_output.c wtcdbtools_output.h \
	wtcdbtools_signal.c wtcdbtools_signal.h \
	wtcdbtools_unused.h

wtcdbexport_LDADD = \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

wtcdbinfo_SOURCES = \
	info_handle.c info_handle.h \
	wtcdbinfo.c \
	wtcdbinput.c wtcdbinput.h \
	wtcdbtools_getopt.c wtcdbtools_getopt.h \
	wtcdbtools_i18n.h \
	wtcdbtools_libbfio.h \
	wtcdbtools_libcerror.h \
	wtcdbtools_libcfile.h \
	wtcdbtools_libclocale.h \
	wtcdbtools_libcnotify.h \
	wtcdbtools_libcpath.h \
	wtcdbtools_libfdatetime.h \
	wtcdbtools_libuna.h \
	wtcdbtools_libwtcdb.h \
	wtcdbtools_output.c wtcdbtools_output.h \
	wtcdbtools_signal.c wtcdbtools_signal.h \
	wtcdbtools_unused.h

wtcdbinfo_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on wtcdbexport ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(wtcdbexport_SOURCES)
	@echo "Running splint on wtcdbinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(wtcdbinfo_SOURCES)

