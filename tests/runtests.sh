#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libwtcdb/.libs/libwtcdb.1.dylib" ] && [ -f ./pywtcdb/.libs/pywtcdb.so ]
then
    install_name_tool -change /usr/local/lib/libwtcdb.1.dylib "${PWD}/libwtcdb/.libs/libwtcdb.1.dylib" ./pywtcdb/.libs/pywtcdb.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

