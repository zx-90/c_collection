#!/user/bin/make -f

#
# Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
# All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

# -----------------------------------------------------------------------------
# Base functions.
# -----------------------------------------------------------------------------

# Find subdirs of parent dir
# $(1) - parent dir
find_dirs = $(shell ls -1d $(1)/*)

# Find all files recursively.
# $(1) - dir for find
# $(2) - file mask
rfind_files = $(shell find $(1) -name $(2))

# Change/adding/deleting prefixes or/and suffixes.
# $(1) - data
# $(2) - old prefix
# $(3) - new prefix
# $(4) - old suffix
# $(5) - new suffix
replace = $(1:$(2)%$(4)=$(3)%$(5))

# Get list of object files by source dir
# $(1) - source dir
get_object_list = $(call replace,$(call rfind_files,$(1),*.c),,$(BUILD_DIR)/,c,o)

# -----------------------------------------------------------------------------
# Variables
# -----------------------------------------------------------------------------

# Base commands.
MK_DIR = mkdir -p
RM_DIR = rm -f -R

# Structure.
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = _build
RUN_DIR = _run

# Source
INCLUDE_DIR = $(SRC_DIR)
TEST_PROJECT_DIRS = $(call find_dirs,$(TEST_DIR))

# Object
BUILD_SRC_DIR = $(BUILD_DIR)/$(SRC_DIR)
BUILD_TEST_DIR = $(BUILD_DIR)/$(TEST_DIR)
BUILD_SRC_FILES = $(call get_object_list,$(SRC_DIR))
BUILD_TEST_FILES = $(call get_object_list,$(TEST_DIR))
BUILD_SRC_SUBDIRS = $(patsubst %/,%,$(sort $(dir $(BUILD_SRC_FILES))))
BUILD_TEST_SUBDIRS = $(patsubst %/,%,$(sort $(dir $(BUILD_TEST_FILES))))
C_COMPILER = gcc -x c $(call replace,$(INCLUDE_DIR),,-I,,) $(BUILD_SRC_FILES)

# Run
RUN_FILES = $(call replace,$(TEST_PROJECT_DIRS),$(TEST_DIR),$(RUN_DIR),,)
C_LINKER = gcc $(call replace,$(INCLUDE_DIR),,-I,,)

# -----------------------------------------------------------------------------
# Aims.
# -----------------------------------------------------------------------------

.SECONDEXPANSION:

all: $(BUILD_SRC_SUBDIRS) $(BUILD_SRC_FILES) $(BUILD_TEST_SUBDIRS) $(BUILD_TEST_FILES) $(RUN_DIR) $(RUN_FILES)

$(RUN_DIR)/% : $$(call get_object_list,$$(TEST_DIR)/%) $(BUILD_SRC_FILES)
	$(C_LINKER) $^ -o $@

$(RUN_DIR):
	$(MK_DIR) $@

$(BUILD_SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(C_COMPILER) -c $< -o $@

$(BUILD_TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(C_COMPILER) -c $< -o $@

$(BUILD_SRC_SUBDIRS):
	$(MK_DIR) $@

$(BUILD_TEST_SUBDIRS):
	$(MK_DIR) $@

clean:
	$(RM_DIR) $(BUILD_DIR)
	$(RM_DIR) $(RUN_DIR)

