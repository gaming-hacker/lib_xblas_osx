# Top-level makefile for XBLAS.

include make.inc

SRC_DIR := src
TEST_DIR := testing
LIB_DIR := lib
$(shell if [[ ! -d $(LIB_DIR) ]]; then $(MKDIR) $(LIB_DIR); fi)
OBJ_DIR := obj
$(shell if [[ ! -d $(OBJ_DIR) ]]; then $(MKDIR) $(OBJ_DIR); fi)


all: libs

objects:
	@cd $(SRC_DIR)/common && $(MAKE) all
	@cd $(SRC_DIR)/dot && $(MAKE) all
	@cd $(SRC_DIR)/sum && $(MAKE) all
	@cd $(SRC_DIR)/axpby && $(MAKE) all
	@cd $(SRC_DIR)/waxpby && $(MAKE) all
	@cd $(SRC_DIR)/gemv && $(MAKE) all
	@cd $(SRC_DIR)/ge_sum_mv && $(MAKE) all
	@cd $(SRC_DIR)/gbmv && $(MAKE) all
	@cd $(SRC_DIR)/symv && $(MAKE) all
	@cd $(SRC_DIR)/spmv && $(MAKE) all
	@cd $(SRC_DIR)/sbmv && $(MAKE) all
	@cd $(SRC_DIR)/hemv && $(MAKE) all
	@cd $(SRC_DIR)/hpmv && $(MAKE) all
	@cd $(SRC_DIR)/hbmv && $(MAKE) all
	@cd $(SRC_DIR)/trmv && $(MAKE) all
	@cd $(SRC_DIR)/tpmv && $(MAKE) all
	@cd $(SRC_DIR)/trsv && $(MAKE) all
	@cd $(SRC_DIR)/tbsv && $(MAKE) all
	@cd $(SRC_DIR)/gemm && $(MAKE) all
	@cd $(SRC_DIR)/symm && $(MAKE) all
	@cd $(SRC_DIR)/hemm && $(MAKE) all
	@cd $(SRC_DIR)/gemv2 && $(MAKE) all
	@cd $(SRC_DIR)/symv2 && $(MAKE) all
	@cd $(SRC_DIR)/hemv2 && $(MAKE) all
	@cd $(SRC_DIR)/gbmv2 && $(MAKE) all

.PHONY:getObj
getObj:objects
	@cd $(OBJ_DIR) && $(FIND) ../src -depth -name "*.o" | xargs -I '{}' cp '{}' .
	@printf $(RED) && echo "<<---- Done objects $(shell (date +%H:%M:%S)) --->>"&& printf $(NC);

libs: objects static shared

static: header getObj
	@$(AR) $(ARFLAGS) $(LIB_DIR)/$(LIBSTATIC) $(shell find $(OBJ_DIR) -depth -name *.o)
	@printf $(RED) && echo "<<---- Done static $(shell (date +%H:%M:%S)) --->> "&& printf $(NC);
	@printf $(BLUE) && echo "<<---- Listing static lib $(shell (date +%H:%M:%S)) --->> "&& printf $(blue);
	@cd $(LIB_DIR) && $(AR) -t $(LIBSTATIC)

shared:header getObj
	@$(CC) $(SHAREDFLAGS) -install_name $(LIBDIR)/$(LIBSHARED) -o lib/$(LIBSHARED) $(shell find $(OBJ_DIR) -depth -name *.o)
	@printf $(RED) && echo "<<---- Done static $(shell (date +%H:%M:%S)) --->> "&& printf $(NC);
	@printf $(BLUE) && echo "<<---- Listing dynamic lib $(shell (date +%H:%M:%S)) --->> "&& printf $(blue);
	@cd $(LIB_DIR) && $(OTOOL) $(LIBSHARED)

.PHONY:header
header:
	@cat ./src/include/*.h  >> include/$(LIBNAME).h
	@printf $(RED) && echo "<<---- Done header $(shell (date +%H:%M:%S)) --->> "&& printf $(NC);

.PHONY:install
install:
	$(CP) ./include/$(LIBNAME).h $(INCDIR)/$(LIBNAME).h
	$(CP) $(LIB_DIR)/$(LIBSTATIC) $(LIBDIR)/$(LIBSTATIC)
	$(CP) $(LIB_DIR)/$(LIBSHARED) $(LIBDIR)/$(LIBSHARED)
	@printf $(RED) && echo "<<---- Done install $(shell (date +%H:%M:%S)) --->> "&& printf $(NC);

.PHONY:uninstall
uninstall:
	$(NUKE) ./include/$(LIBNAME).h
	$(NUKE) $(LIBDIR)/$(LIBSTATIC)
	$(NUKE) $(LIBDIR)/$(LIBSHARED)
	@printf $(RED) && echo "<<---- Done uninstall $(shell (date +%H:%M:%S)) --->> "&& printf $(NC);

# Cleaning stuff

.PHONY:clean
clean:
	@$(NUKE) $(OBJ_DIR)/*.o
	@$(FIND) src -depth -name "*.o" | xargs -I '{}' rm -f '{}'
	@$(NUKE) ./include/$(LIBNAME).h
	@printf $(RED) && echo "<<---- Done cleaning $(shell (date +%H:%M:%S)) --->> "&& printf $(NC);
# DO NOT DELETE
