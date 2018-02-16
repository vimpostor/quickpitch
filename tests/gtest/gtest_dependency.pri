isEmpty(GOOGLETEST_DIR):GOOGLETEST_DIR=$$(GOOGLETEST_DIR)

isEmpty(GOOGLETEST_DIR) {
    warning("Using googletest src dir specified at Qt Creator wizard")
    message("set GOOGLETEST_DIR as environment variable or qmake variable to get rid of this message")
	GOOGLETEST_DIR = /usr/src
}

!isEmpty(GOOGLETEST_DIR): {
	GTEST_SRCDIR = $$GOOGLETEST_DIR/gtest
	GMOCK_SRCDIR = $$GOOGLETEST_DIR/gmock
}

isEmpty(GOOGLETEST_INCDIR) {
	warning("Using googletest inc dir specified at Qt Creator wizard")
	message("set GOOGLETEST_INCDIR as environment variable or qmake variable to get rid of this message")
	GOOGLETEST_INCDIR = /usr/include
}

!isEmpty(GOOGLETEST_INCDIR): {
	GTEST_INCDIR = $$GOOGLETEST_INCDIR/gtest
	GMOCK_INCDIR = $$GOOGLETEST_INCDIR/gmock
}

requires(exists($$GTEST_SRCDIR):exists($$GMOCK_SRCDIR))

requires(exists($$GTEST_INCDIR):exists($$GMOCK_INCDIR))

!exists($$GOOGLETEST_DIR):message("No googletest src dir found - set GOOGLETEST_DIR to enable.")

!exists($$GOOGLETEST_INCDIR):message("No googletest inc dir found - set GOOGLETEST_INCDIR to enable.")

DEFINES += \
    GTEST_LANG_CXX11

INCLUDEPATH *= \
    $$GTEST_SRCDIR \
	$$GTEST_INCDIR \
    $$GMOCK_SRCDIR \
	$$GMOCK_INCDIR

SOURCES += \
	$$GTEST_SRCDIR/src/gtest-all.cc \
	$$GMOCK_SRCDIR/gmock-all.cc
