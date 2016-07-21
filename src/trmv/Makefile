include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

TRMV_SRCS =\
	$(SRC_PATH)/BLAS_dtrmv_s.c\
	$(SRC_PATH)/BLAS_ztrmv_c.c\
	$(SRC_PATH)/BLAS_ctrmv_s.c\
	$(SRC_PATH)/BLAS_ztrmv_d.c\
	$(SRC_PATH)/BLAS_strmv_x.c\
	$(SRC_PATH)/BLAS_dtrmv_x.c\
	$(SRC_PATH)/BLAS_ctrmv_x.c\
	$(SRC_PATH)/BLAS_ztrmv_x.c\
	$(SRC_PATH)/BLAS_dtrmv_s_x.c\
	$(SRC_PATH)/BLAS_ztrmv_c_x.c\
	$(SRC_PATH)/BLAS_ctrmv_s_x.c\
	$(SRC_PATH)/BLAS_ztrmv_d_x.c \
	$(SRC_PATH)/BLAS_dtrmv_s-f2c.c\
	$(SRC_PATH)/BLAS_ztrmv_c-f2c.c\
	$(SRC_PATH)/BLAS_ctrmv_s-f2c.c\
	$(SRC_PATH)/BLAS_ztrmv_d-f2c.c\
	$(SRC_PATH)/BLAS_strmv_x-f2c.c\
	$(SRC_PATH)/BLAS_dtrmv_x-f2c.c\
	$(SRC_PATH)/BLAS_ctrmv_x-f2c.c\
	$(SRC_PATH)/BLAS_ztrmv_x-f2c.c\
	$(SRC_PATH)/BLAS_dtrmv_s_x-f2c.c\
	$(SRC_PATH)/BLAS_ztrmv_c_x-f2c.c\
	$(SRC_PATH)/BLAS_ctrmv_s_x-f2c.c\
	$(SRC_PATH)/BLAS_ztrmv_d_x-f2c.c

TRMV_OBJS = $(TRMV_SRCS:.c=.o)

all: $(TRMV_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<
