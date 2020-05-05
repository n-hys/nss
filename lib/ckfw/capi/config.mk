# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

#
#  Override TARGETS variable so that only shared libraries
#  are specifed as dependencies within rules.mk.
#

TARGETS        = $(SHARED_LIBRARY)
LIBRARY        =
IMPORT_LIBRARY =
PROGRAM        =

ifdef BUILD_IDG
    DEFINES += -DNSSDEBUG
endif

#
# To create a loadable module on Darwin, we must use -bundle.
#
ifeq ($(OS_TARGET),Darwin)
DSO_LDOPTS = -bundle
endif
