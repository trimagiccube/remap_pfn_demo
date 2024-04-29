SOURCE_FILE :=
# when kernel read this file ,the relative pathname is $(src)
# so you must write alloc_pages/remap_pfn_alloc_pages.c while not remap_pfn_alloc_pages.c
SOURCE_FILE += remap_pfn_alloc_pages.c

OBJECT = $(patsubst %.c,%.o,$(SOURCE_FILE))

obj-m += alloc_pages.o
alloc_pages-objs := $(OBJECT)
