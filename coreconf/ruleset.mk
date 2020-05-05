#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

#######################################################################
#                                                                     #
# Parameters to this makefile (set these in this file):               #
#                                                                     #
# a)                                                                  #
#	TARGETS	-- the target to create                               #
#			(defaults to $LIBRARY $PROGRAM)               #
# b)                                                                  #
#	DIRS	-- subdirectories for make to recurse on              #
#			(the 'all' rule builds $TARGETS $DIRS)        #
# c)                                                                  #
#	CSRCS, CPPSRCS -- .c and .cpp files to compile                #
#			(used to define $OBJS)                        #
# d)                                                                  #
#	PROGRAM	-- the target program name to create from $OBJS       #
#			($OBJDIR automatically prepended to it)       #
# e)                                                                  #
#	LIBRARY	-- the target library name to create from $OBJS       #
#			($OBJDIR automatically prepended to it)       #
# f)                                                                  #
#	JSRCS	-- java source files to compile into class files      #
#			(if you don't specify this it will default    #
#			 to *.java)                                   #
# g)                                                                  #
#	PACKAGE	-- the package to put the .class files into           #
#			(e.g. netscape/applet)                        #
#			(NOTE: the default definition for this may be #
#                              overridden if "jdk.mk" is included)    #
# h)                                                                  #
#	JMC_EXPORT -- java files to be exported for use by JMC_GEN    #
#			(this is a list of Class names)               #
# i)                                                                  #
#	JRI_GEN	-- files to run through javah to generate headers     #
#                  and stubs                                          #
#			(output goes into the _jri sub-dir)           #
# j)                                                                  #
#	JMC_GEN	-- files to run through jmc to generate headers       #
#                  and stubs                                          #
#			(output goes into the _jmc sub-dir)           #
# k)                                                                  #
#	JNI_GEN	-- files to run through javah to generate headers     #
#			(output goes into the _jni sub-dir)           #
#                                                                     #
#######################################################################

#
# CPU_TAG is now defined in the $(TARGET).mk files
#

ifndef COMPILER_TAG
    ifneq ($(DEFAULT_COMPILER), $(notdir $(firstword $(CC))))
#
# Temporary define for the Client; to be removed when binary release is used
#
	ifdef MOZILLA_CLIENT
	    COMPILER_TAG =
	else
	    COMPILER_TAG = _$(notdir $(firstword $(CC)))
	endif
    else
	COMPILER_TAG =
    endif
endif

ifeq ($(MKPROG),)
    MKPROG = $(CC)
endif

#
# This makefile contains rules for building the following kinds of
# objects:
# - (1) LIBRARY: a static (archival) library
# - (2) SHARED_LIBRARY: a shared (dynamic link) library
# - (3) IMPORT_LIBRARY: an import library, defined in $(OS_TARGET).mk
# - (4) PROGRAM: an executable binary
#
# A library is build by specifying the LIBRARY_NAME variable.
# If you want to build only a static library, set SHARED_LIBRARY = $(NULL)
# If you want to build only a shared library, set LIBRARY = $(NULL)
# You can specify the shared library major version via LIBRARY_VERSION.
#
# Normally you want to link to the shared library. In this case you must
# provide an export script, like:
#   MAPFILE = $(OBJDIR)/$(LIBRARY_NAME).def.
# Unfortunatly this variable is needed by the ARCH setup, so you have to set
# it explicitly in the manifest.mn.
#
# Per default, it's assumed the shared library provides resource specification
# in the file RES. You can set it to $(NULL), if that is not true.
#
# If you have an unversioned SHARED_LIBRARY, you must explicitly change or
# disable the static LIBRARY, as these normally clash on Windows.

ifdef LIBRARY_NAME
    ifndef LIBRARY
	LIBRARY := $(OBJDIR)/$(LIB_PREFIX)$(LIBRARY_NAME).$(LIB_SUFFIX)
    endif
    ifndef SHARED_LIBRARY
	SHARED_LIBRARY := $(OBJDIR)/$(DLL_PREFIX)$(LIBRARY_NAME)$(LIBRARY_VERSION)$(JDK_DEBUG_SUFFIX).$(DLL_SUFFIX)
    endif

    ifneq ($(SHARED_LIBRARY),)

    ifdef IMPORT_LIB_SUFFIX
    ifdef MAPFILE
    ifndef IMPORT_LIBRARY
	IMPORT_LIBRARY := $(OBJDIR)/$(IMPORT_LIB_PREFIX)$(LIBRARY_NAME)$(LIBRARY_VERSION)$(JDK_DEBUG_SUFFIX)$(IMPORT_LIB_SUFFIX)
    endif
    endif
    endif

    ifndef MAPFILE_SOURCE
	MAPFILE_SOURCE := $(LIBRARY_NAME).def
    endif

    ifeq (,$(filter-out WIN%,$(OS_TARGET)))
    ifndef RES
	RES := $(OBJDIR)/$(LIBRARY_NAME).res
    endif
    ifndef RESNAME
	RESNAME := $(LIBRARY_NAME).rc
    endif
    endif

    endif
endif

#
# Common rules used by lots of makefiles...
#

ifdef PROGRAM
    PROGRAM := $(addprefix $(OBJDIR)/, $(PROGRAM)$(JDK_DEBUG_SUFFIX)$(PROG_SUFFIX))
endif

ifdef PROGRAMS
    PROGRAMS := $(addprefix $(OBJDIR)/, $(PROGRAMS:%=%$(JDK_DEBUG_SUFFIX)$(PROG_SUFFIX)))
endif

ifndef TARGETS
    TARGETS = $(LIBRARY) $(SHARED_LIBRARY) $(PROGRAM)
endif

# Make both .cpp and .cc work.
CPPSRCS1 = $(CPPSRCS:.cpp=$(OBJ_SUFFIX))
CPPSRCS2 = $(CPPSRCS1:.cc=$(OBJ_SUFFIX))

ifndef OBJS
    SIMPLE_OBJS = $(JRI_STUB_CFILES) \
		$(addsuffix $(OBJ_SUFFIX), $(JMC_GEN)) \
		$(CSRCS:.c=$(OBJ_SUFFIX)) \
		$(CPPSRCS2) \
		$(ASFILES:$(ASM_SUFFIX)=$(OBJ_SUFFIX)) \
		$(BUILT_CSRCS:.c=$(OBJ_SUFFIX)) \
		$(BUILT_CPPSRCS:.cpp=$(OBJ_SUFFIX)) \
		$(BUILT_ASFILES:$(ASM_SUFFIX)=$(OBJ_SUFFIX))
    OBJS =	$(addprefix $(OBJDIR)/$(PROG_PREFIX), $(SIMPLE_OBJS))
endif

ifndef BUILT_SRCS
    BUILT_SRCS = $(addprefix $(OBJDIR)/$(PROG_PREFIX), \
		 $(BUILT_CSRCS) $(BUILT_CPPSRCS) $(BUILT_ASFILES))
endif

ifndef MAKE_OBJDIR
define MAKE_OBJDIR
if test ! -d $(@D); then $(NSINSTALL) -D $(@D); fi
endef
endif

ifndef PACKAGE
    PACKAGE = .
endif

ifdef NSBUILDROOT
    JDK_GEN_DIR  = $(SOURCE_XP_DIR)/_gen
    JMC_GEN_DIR  = $(SOURCE_XP_DIR)/_jmc
    JNI_GEN_DIR  = $(SOURCE_XP_DIR)/_jni
    JRI_GEN_DIR  = $(SOURCE_XP_DIR)/_jri
    JDK_STUB_DIR = $(SOURCE_XP_DIR)/_stubs
else
    JDK_GEN_DIR  = _gen
    JMC_GEN_DIR  = _jmc
    JNI_GEN_DIR  = _jni
    JRI_GEN_DIR  = _jri
    JDK_STUB_DIR = _stubs
endif

ALL_TRASH =	$(TARGETS) $(OBJS) $(OBJDIR) LOGS TAGS $(GARBAGE) \
		so_locations $(BUILT_SRCS) $(NOSUCHFILE)

ifdef NS_USE_JDK
    ALL_TRASH += $(JDK_HEADER_CFILES) $(JDK_STUB_CFILES) \
		 $(JMC_HEADERS) $(JMC_STUBS) $(JMC_EXPORT_FILES) \
		 $(JNI_HEADERS) \
		 $(JRI_HEADER_CFILES) $(JRI_STUB_CFILES) \
		 $(JDK_GEN_DIR) $(JMC_GEN_DIR) $(JNI_GEN_DIR) \
		 $(JRI_GEN_DIR) $(JDK_STUB_DIR)

ifdef JAVA_DESTPATH
    ALL_TRASH += $(wildcard $(JAVA_DESTPATH)/$(PACKAGE)/*.class)
ifdef JDIRS
    ALL_TRASH += $(addprefix $(JAVA_DESTPATH)/,$(JDIRS))
endif
else # !JAVA_DESTPATH
    ALL_TRASH += $(wildcard $(PACKAGE)/*.class) $(JDIRS)
endif

endif #NS_USE_JDK

ifdef NSS_BUILD_CONTINUE_ON_ERROR
# Try to build everything. I.e., don't exit on errors.
    EXIT_ON_ERROR		= +e
    IGNORE_ERROR		= -
    CLICK_STOPWATCH		= date
else
    EXIT_ON_ERROR		= -e
    IGNORE_ERROR		=
    CLICK_STOPWATCH		= true
endif

ifdef REQUIRES
    MODULE_INCLUDES := $(addprefix -I$(SOURCE_XP_DIR)/public/, $(REQUIRES))
    INCLUDES        += $(MODULE_INCLUDES)
    ifeq ($(MODULE), sectools)
	PRIVATE_INCLUDES := $(addprefix -I$(SOURCE_XP_DIR)/private/, $(REQUIRES))
	INCLUDES         += $(PRIVATE_INCLUDES)
    endif
endif

ifdef SYSTEM_INCL_DIR
    YOPT = -Y$(SYSTEM_INCL_DIR)
endif

MK_RULESET = included
