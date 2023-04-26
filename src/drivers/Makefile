.PHONY:all

SRC_DIRS = $(shell find .. -type d | grep "/" | sed 's/..\///g')
include ../../configs.mk
_PREFIX = ../../$(PREFIX)/drivers

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(OBJS)
	mkdir -p $(_PREFIX)
	mv *.o $(_PREFIX)/

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@