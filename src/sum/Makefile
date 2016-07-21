include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include
SUM_SRCS =\
	$(SRC_PATH)/BLAS_ssum_x.c\
	$(SRC_PATH)/BLAS_dsum_x.c\
	$(SRC_PATH)/BLAS_csum_x.c\
	$(SRC_PATH)/BLAS_zsum_x.c \
	$(SRC_PATH)/BLAS_ssum_x-f2c.c\
	$(SRC_PATH)/BLAS_dsum_x-f2c.c\
	$(SRC_PATH)/BLAS_csum_x-f2c.c\
	$(SRC_PATH)/BLAS_zsum_x-f2c.c

SUM_OBJS = $(SUM_SRCS:.c=.o)

all: $(SUM_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<

