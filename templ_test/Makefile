HOST_ARCH ?= $(shell uname -m)-linux-gun
CC    = gcc
AR    = ar rcs
LINK  = gcc
RM    = rm -f
WARNFLAGS += -g -Wno-strict-aliasing -Wno-unused-parameter
CFLAGS += -Wall $(WARNFLAGS)
LIBS += -lm -lpthread
LOCAL_TARGET := test
INCPATH = -I./

vpath %.c
vpath %.c ./bt_srcs

.PHONY: _all
_all : templ_tool

SOURCE_SRCS := main.c args.c
SRCS := $(SOURCE_SRCS)

TESTCASE_SRCS := t1.c t2.c
SRCS += $(TESTCASE_SRCS)

OBJS := $(patsubst %.c, %.o, $(SRCS))

.PHONY: templ_tool
templ_tool : $(LOCAL_TARGET)

$(LOCAL_TARGET) : $(OBJS)
	$(LINK) $(OBJS) $(LIBS) -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fPIC "$^" -o "$@"

.PHONY:clean
clean :
	$(RM) $(OBJS)
	$(RM) $(LOCAL_TARGET)


