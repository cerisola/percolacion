CC	:=	gcc

CFLAGS	:= -Wall

OUTDIR	:= build
TARGET	:= percolation

all:
	@mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) main.c -o $(OUTDIR)/$(TARGET)

clean:
	$(RM) $(OUTDIR)/$(TARGET)
