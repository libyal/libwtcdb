MSVSCPP_FILES = \
	libbfio/libbfio.vcproj \
	libcdata/libcdata.vcproj \
	libcerror/libcerror.vcproj \
	libcfile/libcfile.vcproj \
	libclocale/libclocale.vcproj \
	libcnotify/libcnotify.vcproj \
	libcpath/libcpath.vcproj \
	libcsplit/libcsplit.vcproj \
	libcstring/libcstring.vcproj \
	libcsystem/libcsystem.vcproj \
	libcthreads/libcthreads.vcproj \
	libfdatetime/libfdatetime.vcproj \
	libfvalue/libfvalue.vcproj \
	libuna/libuna.vcproj \
	libwtcdb/libwtcdb.vcproj \
	wtcdb_test_error/wtcdb_test_error.vcproj \
	wtcdb_test_get_version/wtcdb_test_get_version.vcproj \
	wtcdb_test_open_close/wtcdb_test_open_close.vcproj \
	wtcdbexport/wtcdbexport.vcproj \
	wtcdbinfo/wtcdbinfo.vcproj \
	libwtcdb.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

