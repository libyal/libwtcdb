#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libwtcdb/.libs/libwtcdb.1.dylib && test -f ./pywtcdb/.libs/pywtcdb.so;
then
	install_name_tool -change /usr/local/lib/libwtcdb.1.dylib ${PWD}/libwtcdb/.libs/libwtcdb.1.dylib ./pywtcdb/.libs/pywtcdb.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

