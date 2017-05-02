CC	:=	gcc

CFLAGS	:= -Wall -std=c99 -pedantic -O3
LDFLAGS := -lm

OUTDIR	:= build
TARGET_COMMON := percolation
TARGET_CRITICAL_POINT_BISECTION_SEARCH = $(TARGET_COMMON)_critical_point_bisection_search
TARGET_PROBABILITY_SWEEP = $(TARGET_COMMON)_probability_sweep
TARGET_WINDOWS_MASS = $(TARGET_COMMON)_windows_mass

SRCS_COMMON = $(filter-out critical_point_bisection_search.c probability_sweep.c windows_mass.c, $(wildcard *.c))
OBJS_COMMON = $(subst .c,.o,$(SRCS_COMMON))

all: critical_point_bisection_search probability_sweep windows_mass

critical_point_bisection_search: $(OBJS_COMMON) critical_point_bisection_search.o outputdir
	$(CC) -o $(OUTDIR)/$(TARGET_CRITICAL_POINT_BISECTION_SEARCH) $(OBJS_COMMON) $@.o $(LDFLAGS)

probability_sweep: $(OBJS_COMMON) probability_sweep.o outputdir
	$(CC) -o $(OUTDIR)/$(TARGET_PROBABILITY_SWEEP) $(OBJS_COMMON) $@.o $(LDFLAGS)

windows_mass: $(OBJS_COMMON) windows_mass.o outputdir
	$(CC) -o $(OUTDIR)/$(TARGET_WINDOWS_MASS) $(OBJS_COMMON) $@.o $(LDFLAGS)

outputdir:
	@mkdir -p $(OUTDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(OUTDIR)/$(TARGET_CRITICAL_POINT_BISECTION_SEARCH)
	$(RM) $(OUTDIR)/$(TARGET_PROBABILITY_SWEEP)
	$(RM) $(OUTDIR)/$(TARGET_WINDOWS_MASS)
