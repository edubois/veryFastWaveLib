# Projet Very Fast Wavelet Codec.
ARCH = generic

SRC_DIR = src/
INCLUDE_DIR = $(SRC_DIR)include/
OBJ_DIR = obj/
CC = gcc
CFLAGS  = -Wall -ansi -pipe -mtune=$(ARCH) -msse2 
LDFLAGS = -lm 

ifeq ($(DEBUG),true)
   CFLAGS += -g
   LDFLAGS += -g
else
   CFLAGS += -O2
   LDFLAGS +=
endif

all : mkdirs vfwave_test fast_test1 slow_test1

install: all
	mv -f vf $(HOME)/bin

mkdirs:
	-mkdir obj bin

vfwave_test: $(OBJ_DIR)main.o $(OBJ_DIR)vfwl_image.o $(OBJ_DIR)vfwl_uquantizer.o $(OBJ_DIR)vfwl_codec.o 
	$(CC) $(OBJ_DIR)main.o $(OBJ_DIR)vfwl_uquantizer.o $(OBJ_DIR)vfwl_codec.o $(OBJ_DIR)vfwl_image.o -o vf $(CFLAGS) $(LDFLAGS)

slow_test1: $(SRC_DIR)slow_test1.c $(OBJ_DIR)vfwl_codec.o $(OBJ_DIR)vfwl_uquantizer.o $(OBJ_DIR)vfwl_image.o
	$(CC) $(SRC_DIR)slow_test1.c $(OBJ_DIR)vfwl_uquantizer.o $(OBJ_DIR)vfwl_codec.o $(OBJ_DIR)vfwl_image.o -o slow_test1 $(CFLAGS) $(LDFLAGS)

fast_test1: $(SRC_DIR)fast_test1.c $(OBJ_DIR)vfwl_codec.o $(OBJ_DIR)vfwl_uquantizer.o $(OBJ_DIR)vfwl_image.o
	$(CC) $(SRC_DIR)fast_test1.c $(OBJ_DIR)vfwl_uquantizer.o $(OBJ_DIR)vfwl_codec.o $(OBJ_DIR)vfwl_image.o -o fast_test1 $(CFLAGS) $(LDFLAGS)

$(OBJ_DIR)main.o : $(SRC_DIR)main.c $(SRC_DIR)vfwl_codec.c $(SRC_DIR)vfwl_image.c
	$(CC) -c $(CFLAGS) $(SRC_DIR)main.c -o $(OBJ_DIR)main.o

$(OBJ_DIR)vfwl_codec.o : $(SRC_DIR)vfwl_codec.c $(INCLUDE_DIR)vfwl_codec.h
	$(CC) -c $(CFLAGS) $(SRC_DIR)vfwl_codec.c -o $(OBJ_DIR)vfwl_codec.o

$(OBJ_DIR)vfwl_uquantizer.o: $(SRC_DIR)vfwl_uquantizer.c $(INCLUDE_DIR)vfwl_uquantizer.h
	$(CC) -c $(CFLAGS) $(SRC_DIR)vfwl_uquantizer.c -o $(OBJ_DIR)vfwl_uquantizer.o

$(OBJ_DIR)vfwl_image.o: $(SRC_DIR)vfwl_image.c $(INCLUDE_DIR)vfwl_image.h
	$(CC) -c $(CFLAGS) $(SRC_DIR)vfwl_image.c -o $(OBJ_DIR)vfwl_image.o

clean :
	rm -Rf *.o
