AUTOMAKE_OPTIONS = subdir-objects

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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

check_PROGRAMS = \
	wtcdb_test_cache_entry \
	wtcdb_test_crc \
	wtcdb_test_error \
	wtcdb_test_file \
	wtcdb_test_file_header \
	wtcdb_test_index_entry \
	wtcdb_test_io_handle \
	wtcdb_test_item \
	wtcdb_test_notify \
	wtcdb_test_support \
	wtcdb_test_tools_info_handle \
	wtcdb_test_tools_output \
	wtcdb_test_tools_signal

wtcdb_test_cache_entry_SOURCES = \
	wtcdb_test_cache_entry.c \
	wtcdb_test_functions.c wtcdb_test_functions.h \
	wtcdb_test_libbfio.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_cache_entry_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_crc_SOURCES = \
	wtcdb_test_crc.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_unused.h

wtcdb_test_crc_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_error_SOURCES = \
	wtcdb_test_error.c \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_unused.h

wtcdb_test_error_LDADD = \
	../libwtcdb/libwtcdb.la

wtcdb_test_file_SOURCES = \
	wtcdb_test_file.c \
	wtcdb_test_functions.c wtcdb_test_functions.h \
	wtcdb_test_getopt.c wtcdb_test_getopt.h \
	wtcdb_test_libbfio.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_libclocale.h \
	wtcdb_test_libcnotify.h \
	wtcdb_test_libuna.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

wtcdb_test_file_header_SOURCES = \
	wtcdb_test_file_header.c \
	wtcdb_test_functions.c wtcdb_test_functions.h \
	wtcdb_test_libbfio.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_file_header_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_index_entry_SOURCES = \
	wtcdb_test_functions.c wtcdb_test_functions.h \
	wtcdb_test_index_entry.c \
	wtcdb_test_libbfio.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_index_entry_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_io_handle_SOURCES = \
	wtcdb_test_io_handle.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_io_handle_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_item_SOURCES = \
	wtcdb_test_item.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_item_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_notify_SOURCES = \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_notify.c \
	wtcdb_test_unused.h

wtcdb_test_notify_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_support_SOURCES = \
	wtcdb_test_functions.c wtcdb_test_functions.h \
	wtcdb_test_getopt.c wtcdb_test_getopt.h \
	wtcdb_test_libbfio.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_libclocale.h \
	wtcdb_test_libcnotify.h \
	wtcdb_test_libuna.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_support.c \
	wtcdb_test_unused.h

wtcdb_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_tools_info_handle_SOURCES = \
	../wtcdbtools/info_handle.c ../wtcdbtools/info_handle.h \
	../wtcdbtools/wtcdbinput.c ../wtcdbtools/wtcdbinput.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_tools_info_handle.c \
	wtcdb_test_unused.h

wtcdb_test_tools_info_handle_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_tools_output_SOURCES = \
	../wtcdbtools/wtcdbtools_output.c ../wtcdbtools/wtcdbtools_output.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_macros.h \
	wtcdb_test_tools_output.c \
	wtcdb_test_unused.h

wtcdb_test_tools_output_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

wtcdb_test_tools_signal_SOURCES = \
	../wtcdbtools/wtcdbtools_signal.c ../wtcdbtools/wtcdbtools_signal.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_macros.h \
	wtcdb_test_tools_signal.c \
	wtcdb_test_unused.h

wtcdb_test_tools_signal_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libwtcdb.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libwtcdb

test_inputs_wtcdbinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) wtcdbinfo

test_inputs_wtcdbexport.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) wtcdbexport

test_library: \
	package.m4 \
	test_inputs_libwtcdb.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_tools: \
	package.m4 \
	test_inputs_wtcdbexport.at \
	test_inputs_wtcdbinfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

