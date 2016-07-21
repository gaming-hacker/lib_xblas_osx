include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

AXPBY_SRCS =\
	$(SRC_PATH)/BLAS_daxpby_s.c\
	$(SRC_PATH)/BLAS_caxpby_s.c\
	$(SRC_PATH)/BLAS_zaxpby_c.c\
	$(SRC_PATH)/BLAS_zaxpby_d.c\
	$(SRC_PATH)/BLAS_saxpby_x.c\
	$(SRC_PATH)/BLAS_daxpby_x.c\
	$(SRC_PATH)/BLAS_caxpby_x.c\
	$(SRC_PATH)/BLAS_zaxpby_x.c\
	$(SRC_PATH)/BLAS_daxpby_s_x.c\
	$(SRC_PATH)/BLAS_zaxpby_c_x.c\
	$(SRC_PATH)/BLAS_caxpby_s_x.c\
	$(SRC_PATH)/BLAS_zaxpby_d_x.c \
	$(SRC_PATH)/BLAS_daxpby_s-f2c.c\
	$(SRC_PATH)/BLAS_caxpby_s-f2c.c\
	$(SRC_PATH)/BLAS_zaxpby_c-f2c.c\
	$(SRC_PATH)/BLAS_zaxpby_d-f2c.c\
	$(SRC_PATH)/BLAS_saxpby_x-f2c.c\
	$(SRC_PATH)/BLAS_daxpby_x-f2c.c\
	$(SRC_PATH)/BLAS_caxpby_x-f2c.c\
	$(SRC_PATH)/BLAS_zaxpby_x-f2c.c\
	$(SRC_PATH)/BLAS_daxpby_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zaxpby_c_x-f2c.c\
	$(SRC_PATH)/BLAS_caxpby_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zaxpby_d_x-f2c.c

AXPBY_OBJS = $(AXPBY_SRCS:.c=.o)

all: $(AXPBY_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<

