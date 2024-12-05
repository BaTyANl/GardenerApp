LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := mylibrary
LOCAL_SRC_FILES := ../../../../src/mylib.c

include $(BUILD_SHARED_LIBRARY)