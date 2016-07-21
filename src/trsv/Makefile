include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

TRSV_SRCS =\
	$(SRC_PATH)/BLAS_dtrsv_s.c\
	$(SRC_PATH)/BLAS_ztrsv_c.c\
	$(SRC_PATH)/BLAS_ctrsv_s.c\
	$(SRC_PATH)/BLAS_ztrsv_d.c\
	$(SRC_PATH)/BLAS_strsv_x.c\
	$(SRC_PATH)/BLAS_dtrsv_x.c\
	$(SRC_PATH)/BLAS_dtrsv_s_x.c\
	$(SRC_PATH)/BLAS_ctrsv_x.c\
	$(SRC_PATH)/BLAS_ztrsv_x.c\
	$(SRC_PATH)/BLAS_ztrsv_c_x.c\
	$(SRC_PATH)/BLAS_ctrsv_s_x.c\
	$(SRC_PATH)/BLAS_ztrsv_d_x.c \
	$(SRC_PATH)/BLAS_dtrsv_s-f2c.c\
	$(SRC_PATH)/BLAS_ztrsv_c-f2c.c\
	$(SRC_PATH)/BLAS_ctrsv_s-f2c.c\
	$(SRC_PATH)/BLAS_ztrsv_d-f2c.c\
	$(SRC_PATH)/BLAS_strsv_x-f2c.c\
	$(SRC_PATH)/BLAS_dtrsv_x-f2c.c\
	$(SRC_PATH)/BLAS_dtrsv_s_x-f2c.c\
	$(SRC_PATH)/BLAS_ctrsv_x-f2c.c\
	$(SRC_PATH)/BLAS_ztrsv_x-f2c.c\
	$(SRC_PATH)/BLAS_ztrsv_c_x-f2c.c\
	$(SRC_PATH)/BLAS_ctrsv_s_x-f2c.c\
	$(SRC_PATH)/BLAS_ztrsv_d_x-f2c.c

TRSV_OBJS = $(TRSV_SRCS:.c=.o)

all: $(TRSV_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<
