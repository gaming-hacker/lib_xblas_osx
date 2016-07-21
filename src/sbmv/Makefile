include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

SBMV_SRCS =\
	$(SRC_PATH)/BLAS_dsbmv_d_s.c\
	$(SRC_PATH)/BLAS_dsbmv_s_d.c\
	$(SRC_PATH)/BLAS_dsbmv_s_s.c\
	$(SRC_PATH)/BLAS_zsbmv_z_c.c\
	$(SRC_PATH)/BLAS_zsbmv_c_z.c\
	$(SRC_PATH)/BLAS_zsbmv_c_c.c\
	$(SRC_PATH)/BLAS_csbmv_c_s.c\
	$(SRC_PATH)/BLAS_csbmv_s_c.c\
	$(SRC_PATH)/BLAS_csbmv_s_s.c\
	$(SRC_PATH)/BLAS_zsbmv_z_d.c\
	$(SRC_PATH)/BLAS_zsbmv_d_z.c\
	$(SRC_PATH)/BLAS_zsbmv_d_d.c\
	$(SRC_PATH)/BLAS_ssbmv_x.c\
	$(SRC_PATH)/BLAS_dsbmv_x.c\
	$(SRC_PATH)/BLAS_csbmv_x.c\
	$(SRC_PATH)/BLAS_zsbmv_x.c\
	$(SRC_PATH)/BLAS_dsbmv_d_s_x.c\
	$(SRC_PATH)/BLAS_dsbmv_s_d_x.c\
	$(SRC_PATH)/BLAS_dsbmv_s_s_x.c\
	$(SRC_PATH)/BLAS_zsbmv_z_c_x.c\
	$(SRC_PATH)/BLAS_zsbmv_c_z_x.c\
	$(SRC_PATH)/BLAS_zsbmv_c_c_x.c\
	$(SRC_PATH)/BLAS_csbmv_c_s_x.c\
	$(SRC_PATH)/BLAS_csbmv_s_c_x.c\
	$(SRC_PATH)/BLAS_csbmv_s_s_x.c\
	$(SRC_PATH)/BLAS_zsbmv_z_d_x.c\
	$(SRC_PATH)/BLAS_zsbmv_d_z_x.c\
	$(SRC_PATH)/BLAS_zsbmv_d_d_x.c \
	\
	$(SRC_PATH)/BLAS_dsbmv_d_s-f2c.c\
	$(SRC_PATH)/BLAS_dsbmv_s_d-f2c.c\
	$(SRC_PATH)/BLAS_dsbmv_s_s-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_z_c-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_c_z-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_c_c-f2c.c\
	$(SRC_PATH)/BLAS_csbmv_c_s-f2c.c\
	$(SRC_PATH)/BLAS_csbmv_s_c-f2c.c\
	$(SRC_PATH)/BLAS_csbmv_s_s-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_z_d-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_d_z-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_d_d-f2c.c\
	$(SRC_PATH)/BLAS_ssbmv_x-f2c.c\
	$(SRC_PATH)/BLAS_dsbmv_x-f2c.c\
	$(SRC_PATH)/BLAS_csbmv_x-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_x-f2c.c\
	$(SRC_PATH)/BLAS_dsbmv_d_s_x-f2c.c\
	$(SRC_PATH)/BLAS_dsbmv_s_d_x-f2c.c\
	$(SRC_PATH)/BLAS_dsbmv_s_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_z_c_x-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_c_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_c_c_x-f2c.c\
	$(SRC_PATH)/BLAS_csbmv_c_s_x-f2c.c\
	$(SRC_PATH)/BLAS_csbmv_s_c_x-f2c.c\
	$(SRC_PATH)/BLAS_csbmv_s_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_z_d_x-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_d_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zsbmv_d_d_x-f2c.c

SBMV_OBJS = $(SBMV_SRCS:.c=.o)

all: $(SBMV_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<

