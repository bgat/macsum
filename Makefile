#
#

CROSS_COMPILE := $(DEB_HOST_GNU_TYPE)-

macsum : macsum.c
	$(CROSS_COMPILE)gcc -Wall -Os -o $@ $<

