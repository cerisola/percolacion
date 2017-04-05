CC	:=	gcc

CFLAGS	:= -Wall -ansi -pedantic

OUTDIR	:= build
TARGET	:= percolation

SRCS=$(wildcard *.c)
OBJS=$(subst .c,.o,$(SRCS))

all: $(OBJS)
	@mkdir -p $(OUTDIR)
	$(CC) -o $(OUTDIR)/$(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(OUTDIR)/$(TARGET)
