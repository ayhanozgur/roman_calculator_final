CC=gcc

DDIR = build
ODIR = bin
LDIR = lib
TDIR = test
GDIR = gui

DEPS = romancalc.h
OBJ = romancalc.o test_gui.o 
LIB = libromancalc.a 

INCLUDE_DIRECTORIES = src include lib test gui
vpath % $(INCLUDE_DIRECTORIES)

CFLAGS += $(addprefix -I ,$(INCLUDE_DIRECTORIES)) 

all:$(ODIR)/test_gui 

$(ODIR)/test_gui:$(LIB)
	$(CC) -o $@ $^ $(CFLAGS)

$(DDIR)/*.o: $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LDIR)/libromancalc.a: $(OBJ)
	ar rs $@ $^

test:romancalc_test
	./romancalc_test

romancalc_test: romancalc_test.o romancalc.o
	gcc -o romancalc_test romancalc.o romancalc_test.o -lcheck $(CFLAGS)

romancalc_test.o: romancalc_test.c romancalc.h
	gcc -Wall -c $(TDIR)/romancalc_test.c $(CFLAGS)

romancalc_test.c: $(TDIR)/romancalc_test.check
	checkmk $(TDIR)/romancalc_test.check >$(TDIR)/romancalc_test.c 











 


	












 