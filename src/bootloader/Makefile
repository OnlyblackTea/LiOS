.PHONY:all

SRC_DIRS = $(shell find .. -type d | grep "/" | sed 's/..\///g')
include ../../configs.mk
_PREFIX = ../../$(PREFIX)/bootloader

C_SRCS = $(wildcard *.c)
C_OBJS = $(patsubst %.c,%.o,$(C_SRCS))
S_SRCS = $(wildcard *.s)
S_OBJS = $(patsubst %.s,%.o,$(S_SRCS))
OBJS = $(C_OBJS) $(S_OBJS)

all: $(OBJS)
	mkdir -p $(_PREFIX)
	mv *.o $(_PREFIX)/

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.s
	$(CC) $(CFLAGS) -c $< -o $@

check: 
	echo $(C_SRCS)
	echo $(C_OBJS)