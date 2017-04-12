CC	:=	gcc

CFLAGS	:= -Wall -ansi -pedantic -O3

OUTDIR	:= build
TARGET_COMMON := percolation
TARGET_MAIN = $(TARGET_COMMON)_main

SRCS_COMMON = $(filter-out main.c, $(wildcard *.c))
OBJS_COMMON = $(subst .c,.o,$(SRCS_COMMON))

main: $(OBJS_COMMON) main.o outputdir
	$(CC) -o $(OUTDIR)/$(TARGET_MAIN) $(OBJS_COMMON) $@.o

outputdir:
	@mkdir -p $(OUTDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(OUTDIR)/$(TARGET_MAIN)
