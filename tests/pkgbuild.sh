#!/bin/sh
# Script to build a MacOS pkg
#
# Version: 20241015

set -e

make install DESTDIR=${PWD}/osx-pkg
mkdir -p ${PWD}/osx-pkg/usr/share/doc/libwtcdb
cp AUTHORS COPYING COPYING.LESSER NEWS README ${PWD}/osx-pkg/usr/share/doc/libwtcdb

VERSION=`sed '5!d; s/^  \[//;s/\],$//' configure.ac`
pkgbuild --root osx-pkg --identifier com.github.libyal.libwtcdb --version ${VERSION} --ownership recommended ../libwtcdb-${VERSION}.pkg

