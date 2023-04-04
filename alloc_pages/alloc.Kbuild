SOURCE_FILE =
SOURCE_FILE += remap_pfn_alloc_pages.c

OBJECT = $(patsubst %.c,%.o,$(SOURCE_FILE))

obj-m += alloc_pages.o
alloc_pages-y := $(OBJECT)
