CC	:=	gcc

CFLAGS	:= -Wall -ansi -pedantic -O3

OUTDIR	:= build
TARGET_COMMON := percolation
TARGET_MAIN = $(TARGET_COMMON)_main
TARGET_CRITICAL_POINT_SEARCH = $(TARGET_COMMON)_critical_point_search
TARGET_PROBABILITY_SWEEP = $(TARGET_COMMON)_probability_sweep

SRCS_COMMON = $(filter-out main.c critical_point_search.c probability_sweep.c, $(wildcard *.c))
OBJS_COMMON = $(subst .c,.o,$(SRCS_COMMON))

all: main critical_point_search probability_sweep

main: $(OBJS_COMMON) main.o outputdir
	$(CC) -o $(OUTDIR)/$(TARGET_MAIN) $(OBJS_COMMON) $@.o

critical_point_search: $(OBJS_COMMON) critical_point_search.o outputdir
	$(CC) -o $(OUTDIR)/$(TARGET_CRITICAL_POINT_SEARCH) $(OBJS_COMMON) $@.o

probability_sweep: $(OBJS_COMMON) probability_sweep.o outputdir
	$(CC) -o $(OUTDIR)/$(TARGET_PROBABILITY_SWEEP) $(OBJS_COMMON) $@.o

outputdir:
	@mkdir -p $(OUTDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(OUTDIR)/$(TARGET_MAIN)
	$(RM) $(OUTDIR)/$(TARGET_CRITICAL_POINT_SEARCH)
	$(RM) $(OUTDIR)/$(TARGET_PROBABILITY_SWEEP)
