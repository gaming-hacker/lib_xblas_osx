include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

TPMV_SRCS =\
	$(SRC_PATH)/BLAS_dtpmv_s.c\
	$(SRC_PATH)/BLAS_ztpmv_c.c\
	$(SRC_PATH)/BLAS_ctpmv_s.c\
	$(SRC_PATH)/BLAS_ztpmv_d.c\
	$(SRC_PATH)/BLAS_stpmv_x.c\
	$(SRC_PATH)/BLAS_dtpmv_x.c\
	$(SRC_PATH)/BLAS_ctpmv_x.c\
	$(SRC_PATH)/BLAS_ztpmv_x.c\
	$(SRC_PATH)/BLAS_dtpmv_s_x.c\
	$(SRC_PATH)/BLAS_ztpmv_c_x.c\
	$(SRC_PATH)/BLAS_ctpmv_s_x.c\
	$(SRC_PATH)/BLAS_ztpmv_d_x.c \
	$(SRC_PATH)/BLAS_dtpmv_s-f2c.c\
	$(SRC_PATH)/BLAS_ztpmv_c-f2c.c\
	$(SRC_PATH)/BLAS_ctpmv_s-f2c.c\
	$(SRC_PATH)/BLAS_ztpmv_d-f2c.c\
	$(SRC_PATH)/BLAS_stpmv_x-f2c.c\
	$(SRC_PATH)/BLAS_dtpmv_x-f2c.c\
	$(SRC_PATH)/BLAS_ctpmv_x-f2c.c\
	$(SRC_PATH)/BLAS_ztpmv_x-f2c.c\
	$(SRC_PATH)/BLAS_dtpmv_s_x-f2c.c\
	$(SRC_PATH)/BLAS_ztpmv_c_x-f2c.c\
	$(SRC_PATH)/BLAS_ctpmv_s_x-f2c.c\
	$(SRC_PATH)/BLAS_ztpmv_d_x-f2c.c

TPMV_OBJS = $(TPMV_SRCS:.c=.o)

all: $(TPMV_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<
