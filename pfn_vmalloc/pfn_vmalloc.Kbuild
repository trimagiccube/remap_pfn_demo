SOURCE_FILE =
# when kernel read this file ,the relative pathname is $(src)
# so you must write alloc_pages/remap_pfn_alloc_pages.c while not remap_pfn_alloc_pages.c
SOURCE_FILE += pfn_vmalloc/remap_pfn_vmalloc.c

OBJECT = $(patsubst %.c,%.o,$(SOURCE_FILE))

obj-m += pfn_vmalloc.o
pfn_vmalloc-y := $(OBJECT)
