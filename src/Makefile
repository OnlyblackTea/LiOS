SRC_DIRS = $(shell find . -type d | grep / | sed 's/src\///g')
.PHONY: all $(SRC_DIRS)

all: $(SRC_DIRS)

$(SRC_DIRS):
	make -C $@