# gbcompress makefile

ifndef TARGETDIR
TARGETDIR = /opt/gbdk
endif

ifeq ($(OS),Windows_NT)
	BUILD_OS := Windows_NT
else
	BUILD_OS := $(shell uname -s)
endif

# Target older macOS version than whatever build OS is for better compatibility
ifeq ($(BUILD_OS),Darwin)
	export MACOSX_DEPLOYMENT_TARGET=10.10
endif

CC = $(TOOLSPREFIX)gcc
CFLAGS = -ggdb -O -Wno-incompatible-pointer-types -DGBDKLIBDIR=\"$(TARGETDIR)\"
OBJ = main.o gbcompress.o rlecompress.o files.o files_c_source.o
ZX_OBJ = zx0_expand.o zx0_matchfinder.o zx0_shrink.o
ZX_LIB_OBJ =  trsort.o divsufsort.o divsufsort_utils.o sssort.o
BIN = gbcompress


all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: zx0/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: zx0/libdivsufsort/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJ) $(ZX_OBJ) $(ZX_LIB_OBJ)

clean:
	rm -f *.o $(BIN) *~
	rm -f tmp.*
	rm -f *.exe

# round trip the executable through compression and de-compression as a brief test
test:
	# Compression test on the executable itself
	@echo "----- Test: GB Compress -----"
	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress -v tmp.in tmp.cmp; ./gbcompress -v -d tmp.cmp tmp.dcmp; diff -s tmp.in tmp.dcmp
	rm -f tmp.cmp.c; rm -f tmp.dcmp.c; 	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress -v --cout --varname=some_array tmp.in tmp.cmp.c; ./gbcompress -v -d --cin tmp.cmp.c tmp.dcmp; diff -s tmp.in tmp.dcmp
	@echo "----- Test: RLE Compress -----"
	rm tmp.*
	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress --alg=rle -v tmp.in tmp.cmp; ./gbcompress  --alg=rle -v -d tmp.cmp tmp.dcmp; diff -s tmp.in tmp.dcmp
	rm -f tmp.cmp.c; rm -f tmp.dcmp.c; 	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress  --alg=rle -v --cout --varname=some_array tmp.in tmp.cmp.c; ./gbcompress --alg=rle -v -d --cin tmp.cmp.c tmp.dcmp; diff -s tmp.in tmp.dcmp
	@echo "----- Test: ZX0 Compress -----"
	rm tmp.*
	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress --alg=zx0 -v tmp.in tmp.cmp; ./gbcompress  --alg=zx0 -v -d tmp.cmp tmp.dcmp; diff -s tmp.in tmp.dcmp
	rm -f tmp.cmp.c; rm -f tmp.dcmp.c; 	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress  --alg=zx0 -v --cout --varname=some_array tmp.in tmp.cmp.c; ./gbcompress --alg=zx0 -v -d --cin tmp.cmp.c tmp.dcmp; diff -s tmp.in tmp.dcmp
	rm -f tmp.*
	# test_no_u16_align_end_of_buf.c
	@echo ""
	@echo "----- Test: GB Compress -----"
	rm -f tmp.*
	cp test_data/test_no_u16_align_end_of_buf.c tmp.in.c; ./gbcompress --cin -v --cout tmp.in.c tmp.cmp.c; ./gbcompress -v -d --cin --cout tmp.cmp.c tmp.dcmp.c; diff --ignore-blank-lines --ignore-space-change -s tmp.in.c tmp.dcmp.c
	@echo "----- Test: RLE Compress -----"
	rm -f tmp.*
	cp test_data/test_no_u16_align_end_of_buf.c tmp.in.c; ./gbcompress  --alg=rle --cin -v --cout tmp.in.c tmp.cmp.c; ./gbcompress --alg=rle -v -d --cin --cout tmp.cmp.c tmp.dcmp.c; diff --ignore-blank-lines --ignore-space-change -s tmp.in.c tmp.dcmp.c
	rm -f tmp.*
	@echo "----- Test: ZX0 Compress -----"
	rm -f tmp.*
	cp test_data/test_no_u16_align_end_of_buf.c tmp.in.c; ./gbcompress  --alg=zx0 --cin -v --cout tmp.in.c tmp.cmp.c; ./gbcompress --alg=zx0 -v -d --cin --cout tmp.cmp.c tmp.dcmp.c; diff --ignore-blank-lines --ignore-space-change -s tmp.in.c tmp.dcmp.c
	rm -f tmp.*



