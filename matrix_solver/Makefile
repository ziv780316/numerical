#=================================================
# Makefile settings
#=================================================
-include dependency.mk # - do not abort if file does not exist

.PHONY: tags create_dir verbose_info depend default all clean cscope qa# specify phony target, do not generate file as target name

.DEFAULT_GOAL=default # specify default target if there is no target specified

VPATH=include lib library bin# specify directory where to check target file update to date or not

SHELL=/bin/bash

#=================================================
# Compiler settings
#=================================================
CC         = gcc
CXX        = g++
FLEX       = flex 
FLEX_FLAG  = 
BISON      = bison 
LINKER     = $(CC)
DEFINES    = 
BUILD_TYPE = -O3
BLAS_VERSION = BLAS-3.8.0
LAPACK_VERSION = lapack-3.8.0
CFLAGS     = $(BUILD_TYPE) -Wfatal-errors -Wall -Wextra -std=gnu99 -fPIC 
CXXFLAGS   = $(BUILD_TYPE) -Wfatal-errors -Wall -Wextra -std=c++11 -fPIC
INCLUDE    = -I./include -I. -Isuitesparse/include
MOVE       = mv -f
ARCH       = ar
ARCHFLAGS  = cr

#=================================================
# Build target
#=================================================
BIN_DIR           := lib
UNIT_TEST_DIR     := unit_test
LIBRARY_DIR       := library
MATRIX_SOLVER_OBJ := matrix_solver.o 
LEX_YACC_TARGET   := 
UNIT_TEST_OBJ     := dense_matrix_vector_multiply.o
MATRIX_SOLVER_TARGET := libmatrix_solver.a
BLAS_TARGET 	  := libblas.a
LAPACK_TARGET     := liblapack.a
SUITESPARSE_TARGET:= libcxsparse.so libklu.so libcholmod.so

#=================================================
# Compile implicit rules
#=================================================
%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE) 
	@$(MOVE) $@ $(LIBRARY_DIR) # @ means do not echo command

%.e:%.c
	$(CC) -E $< -o $@ $(CFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR)

%.o:%.cxx
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR)

%.e:%.cxx
	$(CXX) -E $< -o $@ $(CXXFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR)

%.l.c:%.l
	$(FLEX) $(FLEX_FLAG) -o $@ $< 

%.y.c:%.y
	$(BISON) -v -y -Wall -o $@ $<

%.lxx.c:%.lxx
	$(FLEX) $(FLEX_FLAG) --c++ -o $@ $< 

%.yxx.c:%.yxx
	$(BISON) -v -y -Wall -o $@ $<

#=================================================
# Target rules
#=================================================
default: $(MATRIX_SOLVER_TARGET)

all: ut

ut: $(MATRIX_SOLVER_TARGET)
	$(MAKE) -C $(UNIT_TEST_DIR) BUILD_TYPE=$(BUILD_TYPE)

debug: BUILD_TYPE:=-g3 
debug: default

create_dir:
	@mkdir -p $(LIBRARY_DIR) $(BIN_DIR) $(UNIT_TEST_DIR)

verbose_info:
	@echo "*****************************"
	@echo "BUILD_TYPE = $(BUILD_TYPE)" 
	@echo "BLAS       = $(BLAS_VERSION)"
	@echo "LAPACK     = $(LAPACK_VERSION)"
	@echo "*****************************"

$(BLAS_TARGET): 
	$(MAKE) -C $(BLAS_VERSION) OPTS="$(BUILD_TYPE) -fno-underscoring" double complex16
	cd lib; ln -sf ../$(BLAS_VERSION)/$(BLAS_TARGET) $(BLAS_TARGET)
	cd lib; ln -sf ../$(BLAS_VERSION)/$(BLAS_TARGET:.a=.so) $(BLAS_TARGET:.a=.so)

$(LAPACK_TARGET): 
	$(MAKE) -C $(LAPACK_VERSION) OPTS="$(BUILD_TYPE) -fno-underscoring" TARGET="all" NOOPT="-fno-underscoring"
	cd lib; ln -sf ../$(LAPACK_VERSION)/$(LAPACK_TARGET) $(LAPACK_TARGET)
	cd lib; ln -sf ../$(LAPACK_VERSION)/$(LAPACK_TARGET:.a=.so) $(LAPACK_TARGET:.a=.so)

$(SUITESPARSE_TARGET): 
	cd suitesparse; bash build.sh
	cd lib; for sparse_lib in $(SUITESPARSE_TARGET); do ln -sf ../suitesparse/lib/$$sparse_lib $$sparse_lib; done

$(MATRIX_SOLVER_TARGET): verbose_info create_dir $(BLAS_TARGET) $(LAPACK_TARGET) $(SUITESPARSE_TARGET) $(MATRIX_SOLVER_OBJ)
		cd $(LIBRARY_DIR);\
		$(ARCH) $(ARCHFLAGS) $@ $(MATRIX_SOLVER_OBJ);\
		gcc -shared -o $(MATRIX_SOLVER_TARGET:.a=.so) ${MATRIX_SOLVER_OBJ};\
		$(MOVE) $()$@ ../$(BIN_DIR)

clean:
	rm -f dependency.mk
	rm -rf lib/*
	rm -rf $(LIBRARY_DIR)/*
	cd $(BLAS_VERSION); $(MAKE) clean
	cd $(LAPACK_VERSION); $(MAKE) clean
	cd $(UNIT_TEST_DIR); $(MAKE) clean

depend:
	rm -f dependency.mk
	for file in `find . -name "*.c" -o -name "*.cxx" -o -name "*.h" -o -name "*.hxx"`; do $(CC) -M $(INCLUDE) $$file >> dependency.mk; done

cscope:
	find . -name "*.c" -o -name "*.cxx" -o -name "*.h" -o -name "*.hxx" > cscope.files
	cscope -Rbq -i cscope.files

tags: 
	rm -f tags
	find $(BLAS_VERSION) -name "*.f" | xargs ctags --language-force=fortran -f /dev/stdout | sed -r 's/([a-z]\S+)(\s+.*(subroutine|function).*)/\U\1\E\2\n\L\1\E\2/I' >> tags
	find $(LAPACK_VERSION) -name "*.f" | xargs ctags --language-force=fortran -f /dev/stdout | sed -r 's/([a-z]\S+)(\s+.*(subroutine|function).*)/\U\1\E\2\n\L\1\E\2/I' >> tags
	find . -name "*.c" -o -name "*.h" | xargs ctags --append 

qa:
	./bin/$(MATRIX_SOLVER_TARGET) > output


