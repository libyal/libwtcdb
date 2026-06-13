#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libwtcdb/.libs/libwtcdb.1.dylib && test -f ./pywtcdb/.libs/pywtcdb.so
then
	install_name_tool -change /usr/local/lib/libwtcdb.1.dylib ${PWD}/libwtcdb/.libs/libwtcdb.1.dylib ./pywtcdb/.libs/pywtcdb.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

