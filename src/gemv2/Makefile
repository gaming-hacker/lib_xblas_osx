include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

GEMV2_SRCS =\
	$(SRC_PATH)/BLAS_dgemv2_d_s.c\
	$(SRC_PATH)/BLAS_dgemv2_s_d.c\
	$(SRC_PATH)/BLAS_dgemv2_s_s.c\
	$(SRC_PATH)/BLAS_zgemv2_z_c.c\
	$(SRC_PATH)/BLAS_zgemv2_c_z.c\
	$(SRC_PATH)/BLAS_zgemv2_c_c.c\
	$(SRC_PATH)/BLAS_cgemv2_c_s.c\
	$(SRC_PATH)/BLAS_cgemv2_s_c.c\
	$(SRC_PATH)/BLAS_cgemv2_s_s.c\
	$(SRC_PATH)/BLAS_zgemv2_z_d.c\
	$(SRC_PATH)/BLAS_zgemv2_d_z.c\
	$(SRC_PATH)/BLAS_zgemv2_d_d.c\
	$(SRC_PATH)/BLAS_sgemv2_x.c\
	$(SRC_PATH)/BLAS_dgemv2_x.c\
	$(SRC_PATH)/BLAS_cgemv2_x.c\
	$(SRC_PATH)/BLAS_zgemv2_x.c\
	$(SRC_PATH)/BLAS_dgemv2_d_s_x.c\
	$(SRC_PATH)/BLAS_dgemv2_s_d_x.c\
	$(SRC_PATH)/BLAS_dgemv2_s_s_x.c\
	$(SRC_PATH)/BLAS_zgemv2_z_c_x.c\
	$(SRC_PATH)/BLAS_zgemv2_c_z_x.c\
	$(SRC_PATH)/BLAS_zgemv2_c_c_x.c\
	$(SRC_PATH)/BLAS_cgemv2_c_s_x.c\
	$(SRC_PATH)/BLAS_cgemv2_s_c_x.c\
	$(SRC_PATH)/BLAS_cgemv2_s_s_x.c\
	$(SRC_PATH)/BLAS_zgemv2_z_d_x.c\
	$(SRC_PATH)/BLAS_zgemv2_d_z_x.c\
	$(SRC_PATH)/BLAS_zgemv2_d_d_x.c \
	$(SRC_PATH)/BLAS_dgemv2_d_s-f2c.c\
	$(SRC_PATH)/BLAS_dgemv2_s_d-f2c.c\
	$(SRC_PATH)/BLAS_dgemv2_s_s-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_z_c-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_c_z-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_c_c-f2c.c\
	$(SRC_PATH)/BLAS_cgemv2_c_s-f2c.c\
	$(SRC_PATH)/BLAS_cgemv2_s_c-f2c.c\
	$(SRC_PATH)/BLAS_cgemv2_s_s-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_z_d-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_d_z-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_d_d-f2c.c\
	$(SRC_PATH)/BLAS_sgemv2_x-f2c.c\
	$(SRC_PATH)/BLAS_dgemv2_x-f2c.c\
	$(SRC_PATH)/BLAS_cgemv2_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_x-f2c.c\
	$(SRC_PATH)/BLAS_dgemv2_d_s_x-f2c.c\
	$(SRC_PATH)/BLAS_dgemv2_s_d_x-f2c.c\
	$(SRC_PATH)/BLAS_dgemv2_s_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_z_c_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_c_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_c_c_x-f2c.c\
	$(SRC_PATH)/BLAS_cgemv2_c_s_x-f2c.c\
	$(SRC_PATH)/BLAS_cgemv2_s_c_x-f2c.c\
	$(SRC_PATH)/BLAS_cgemv2_s_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_z_d_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_d_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemv2_d_d_x-f2c.c

GEMV2_OBJS = $(GEMV2_SRCS:.c=.o)

all: $(GEMV2_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<
