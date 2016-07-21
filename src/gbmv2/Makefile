include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

GBMV2_SRCS =\
	$(SRC_PATH)/BLAS_dgbmv2_d_s.c\
	$(SRC_PATH)/BLAS_dgbmv2_s_d.c\
	$(SRC_PATH)/BLAS_dgbmv2_s_s.c\
	$(SRC_PATH)/BLAS_zgbmv2_z_c.c\
	$(SRC_PATH)/BLAS_zgbmv2_c_z.c\
	$(SRC_PATH)/BLAS_zgbmv2_c_c.c\
	$(SRC_PATH)/BLAS_cgbmv2_c_s.c\
	$(SRC_PATH)/BLAS_cgbmv2_s_c.c\
	$(SRC_PATH)/BLAS_cgbmv2_s_s.c\
	$(SRC_PATH)/BLAS_zgbmv2_z_d.c\
	$(SRC_PATH)/BLAS_zgbmv2_d_z.c\
	$(SRC_PATH)/BLAS_zgbmv2_d_d.c\
	$(SRC_PATH)/BLAS_sgbmv2_x.c\
	$(SRC_PATH)/BLAS_dgbmv2_x.c\
	$(SRC_PATH)/BLAS_cgbmv2_x.c\
	$(SRC_PATH)/BLAS_zgbmv2_x.c\
	$(SRC_PATH)/BLAS_dgbmv2_d_s_x.c\
	$(SRC_PATH)/BLAS_dgbmv2_s_d_x.c\
	$(SRC_PATH)/BLAS_dgbmv2_s_s_x.c\
	$(SRC_PATH)/BLAS_zgbmv2_z_c_x.c\
	$(SRC_PATH)/BLAS_zgbmv2_c_z_x.c\
	$(SRC_PATH)/BLAS_zgbmv2_c_c_x.c\
	$(SRC_PATH)/BLAS_cgbmv2_c_s_x.c\
	$(SRC_PATH)/BLAS_cgbmv2_s_c_x.c\
	$(SRC_PATH)/BLAS_cgbmv2_s_s_x.c\
	$(SRC_PATH)/BLAS_zgbmv2_z_d_x.c\
	$(SRC_PATH)/BLAS_zgbmv2_d_z_x.c\
	$(SRC_PATH)/BLAS_zgbmv2_d_d_x.c \
	$(SRC_PATH)/BLAS_dgbmv2_d_s-f2c.c\
	$(SRC_PATH)/BLAS_dgbmv2_s_d-f2c.c\
	$(SRC_PATH)/BLAS_dgbmv2_s_s-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_z_c-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_c_z-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_c_c-f2c.c\
	$(SRC_PATH)/BLAS_cgbmv2_c_s-f2c.c\
	$(SRC_PATH)/BLAS_cgbmv2_s_c-f2c.c\
	$(SRC_PATH)/BLAS_cgbmv2_s_s-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_z_d-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_d_z-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_d_d-f2c.c\
	$(SRC_PATH)/BLAS_sgbmv2_x-f2c.c\
	$(SRC_PATH)/BLAS_dgbmv2_x-f2c.c\
	$(SRC_PATH)/BLAS_cgbmv2_x-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_x-f2c.c\
	$(SRC_PATH)/BLAS_dgbmv2_d_s_x-f2c.c\
	$(SRC_PATH)/BLAS_dgbmv2_s_d_x-f2c.c\
	$(SRC_PATH)/BLAS_dgbmv2_s_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_z_c_x-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_c_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_c_c_x-f2c.c\
	$(SRC_PATH)/BLAS_cgbmv2_c_s_x-f2c.c\
	$(SRC_PATH)/BLAS_cgbmv2_s_c_x-f2c.c\
	$(SRC_PATH)/BLAS_cgbmv2_s_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_z_d_x-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_d_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zgbmv2_d_d_x-f2c.c

GBMV2_OBJS = $(GBMV2_SRCS:.c=.o)

all: $(GBMV2_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<
