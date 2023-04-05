SOURCE_FILE =
# when kernel read this file ,the relative pathname is $(src)
# so you must write alloc_pages/remap_pfn_alloc_pages.c while not remap_pfn_alloc_pages.c
SOURCE_FILE += pfn_kmalloc/remap_pfn_kmalloc.c

OBJECT = $(patsubst %.c,%.o,$(SOURCE_FILE))

obj-m += pfn_kmalloc.o
pfn_kmalloc-y := $(OBJECT)
