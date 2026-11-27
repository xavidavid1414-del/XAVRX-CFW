# XAVRX CFW development diagnostic application
# This builds a normal 3DS homebrew .3dsx, NOT a custom firmware image.

.SUFFIXES:
ifeq ($(strip $(DEVKITARM)),)
$(error "DEVKITARM is not set. Install devkitARM through devkitPro.")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules

TARGET := xavrx-diagnostic
BUILD := build
SOURCES := source
DATA :=
INCLUDES := include
GRAPHICS :=
ARCH := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft
CFLAGS := -g -Wall -Wextra -O2 -mword-relocations -ffunction-sections $(ARCH) $(INCLUDE) -D__3DS__
CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11
ASFLAGS := -g $(ARCH)
LDFLAGS = -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)
LIBS := -lctru -lm
LIBDIRS := $(CTRULIB)

ifneq ($(BUILD),$(notdir $(CURDIR)))
export OUTPUT := $(CURDIR)/$(TARGET)
export TOPDIR := $(CURDIR)
export VPATH := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR := $(CURDIR)/$(BUILD)
CFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
export OFILES := $(CFILES:.c=.o)
export INCLUDE := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) $(foreach dir,$(LIBDIRS),-I$(dir)/include) -I$(CURDIR)/$(BUILD)
export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)
.PHONY: all clean
all:
	@[ -d $(BUILD) ] || mkdir -p $(BUILD)
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(TOPDIR)/Makefile
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).3dsx $(TARGET).elf $(TARGET).smdh $(TARGET).3dsx.map
else
.PHONY: all
DEPENDS := $(OFILES:.o=.d)
$(OUTPUT).3dsx: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)
-include $(DEPENDS)
endif
