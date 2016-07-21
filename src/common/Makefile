include ../../make.inc

HEADER_PATH = ../include
COMM_OBJS = BLAS_error.o blas_malloc.o BLAS_fpinfo_x.o BLAS_fpinfo_x-f2c.o

all: $(COMM_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<

