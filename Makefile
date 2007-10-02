# ***************************************************** -*- Makefile -*-
#
# File:      Makefile
# Version:   $Rev$
# Author(s): Andreas Huggel (ahu) <ahuggel@gmx.net>
# History:   15-Jan-04, ahu: created
#
# Description:
#  Simple top-level makefile that mainly forwards to makefiles in 
#  subdirectories.
#
# Restrictions:
#  Requires GNU make.
#

########################################################################
# This is a generated file. Do NOT change any settings here.
# Run ./configure with the appropriate options to regenerate this file
# and possibly others.
########################################################################

SHELL = /bin/sh
ENABLE_XMP = 1

.PHONY: all doc config xmpsdk                        \
        mostlyclean clean distclean maintainer-clean \
        install uninstall

all install: config/config.mk xmpsdk
	cd src && $(MAKE) $(MAKECMDGOALS)
	cd po && $(MAKE) $(MAKECMDGOALS)

uninstall: config/config.mk
	cd src && $(MAKE) $(MAKECMDGOALS)
	cd po && $(MAKE) $(MAKECMDGOALS)

doc: config/config.mk
	cd doc && $(MAKE) $(MAKECMDGOALS)

config:
	cd config && $(MAKE) -f config.make $(MAKECMDGOALS)

xmpsdk: config/config.mk
	if test "x$(ENABLE_XMP)" = "x1"; then cd xmpsdk/src && $(MAKE) $(MAKECMDGOALS); fi;

mostlyclean clean: config/config.mk
	cd src && $(MAKE) $(MAKECMDGOALS)
	cd doc && $(MAKE) $(MAKECMDGOALS)
	cd xmpsdk/src && $(MAKE) $(MAKECMDGOALS)
	cd config && $(MAKE) -f config.make $(MAKECMDGOALS)
	cd po && $(MAKE) $(MAKECMDGOALS)

# `make distclean' also removes files created by configuring 
# the program. Running `make all distclean' prepares the project 
# for packaging.
distclean: clean
	rm -f config.log config.status libtool
	rm -f *~ *.bak *#

# This removes almost everything, including the configure script!
maintainer-clean: distclean
	rm -f configure

config/config.mk: 
	$(error File config/config.mk does not exist. Did you run ./configure?)
