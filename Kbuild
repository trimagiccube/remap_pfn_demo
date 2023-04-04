# when in the top Kbuild ,you should include the other modules Kbuild
# and write relative pathname with below
include $(src)/alloc_pages/alloc.Kbuild

# put this EXTRA_CFLAGS to top Kbuild so that all modules could see it
# EXTRA_CFLAGS BASE is defined by kernel
# and every c file will use it when compile
DRIVER_EXTRA_CFLAGS =
DRIVER_EXTRA_CFLAGS += -I$(src)

DRIVER_EXTRA_CFLAGS += -Wall -MD $(DEFINES) $(INCLUDES) -Wno-cast-qual -Wno-error -Wno-format-extra-args

DRIVER_EXTRA_CFLAGS += -Wno-unused-function

DRIVER_EXTRA_CFLAGS += -fno-strict-aliasing

ifeq ($(ARCH),arm64)
 DRIVER_EXTRA_CFLAGS += -mstrict-align
endif

DRIVER_EXTRA_CFLAGS += -ffreestanding

ifeq ($(ARCH),arm64)
 DRIVER_EXTRA_CFLAGS += -mgeneral-regs-only -march=armv8-a
endif

ifeq ($(ARCH),x86_64)
 DRIVER_EXTRA_CFLAGS += -mno-red-zone -mcmodel=kernel
endif

ifeq ($(ARCH),powerpc)
 DRIVER_EXTRA_CFLAGS += -mlittle-endian -mno-strict-align -mno-altivec
endif

DRIVER_EXTRA_CFLAGS += $(call cc-option,-Werror=undef,)

EXTRA_CFLAGS += $(DRIVER_EXTRA_CFLAGS)
$(warning $(DRIVER_EXTRA_CFLAGS))
