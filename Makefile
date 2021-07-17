CC ?= g++
target = DinguxCommander

RESDIR ?= /storage/.config/distribution/configs/fm/res/
FILE_SYSTEM ?= /storage
PATH_DEFAULT ?= /media
PATH_DEFAULT_RIGHT ?= /storage/roms

ifeq ($(RG351V), 1)
	SCREENW := 640
	SCREENH := 480
	FONTSIZE := 19
	FONTTOUSE := $(RESDIR)/NotoSans-Regular.ttf
	H_PADDING_TOP := 2
	F_PADDING_TOP := 2
	MAXLINES := 16
	LINESPACE := $(shell echo $$(($(SCREENH)/$(MAXLINES))))
	HEADERH := $(LINESPACE)
	FOOTERH := $(LINESPACE)
	LINEH := $(LINESPACE)
	VIEWER_LINE_H := $(LINESPACE)
else
	SCREENW := 480
	SCREENH := 320
	FONTSIZE := 12
	FONTTOUSE := $(RESDIR)/NotoSans-Regular.ttf
	H_PADDING_TOP := 2
	F_PADDING_TOP := 2
	MAXLINES := 16
	LINESPACE := $(shell echo $$(($(SCREENH)/$(MAXLINES))))
	HEADERH := $(LINESPACE)
	FOOTERH := $(LINESPACE)
	LINEH := $(LINESPACE)
	VIEWER_LINE_H := $(LINESPACE)
endif

SRCS=$(wildcard ./*.cpp)
OBJS=$(patsubst %cpp,%o,$(SRCS))

INCLUDE =  $(shell sdl2-config --cflags)
LIB = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_gfx

all:$(OBJS)
	$(CC) $(OBJS) -o $(target) $(LIB)

%.o:%.cpp
	$(CC) -DRES_DIR="\"$(RESDIR)\"" -DODROID_GO_ADVANCE -DFILE_SYSTEM="\"$(FILE_SYSTEM)\"" -DFONT_SIZE=$(FONTSIZE) -DHEADER_H=$(HEADERH) -DHEADER_PADDING_TOP=$(H_PADDING_TOP) -DFOOTER_H=$(FOOTERH) -DFOOTER_PADDING_TOP=$(F_PADDING_TOP) -DLINE_HEIGHT=$(LINEH) -DPATH_DEFAULT="\"$(PATH_DEFAULT)\"" -DPATH_DEFAULT_RIGHT="\"$(PATH_DEFAULT_RIGHT)\"" -DFONT_TO_USE="\"$(FONTTOUSE)\"" -DVIEWER_LINE_HEIGHT=$(VIEWER_LINE_H) -c $< -o $@  $(INCLUDE) 

clean:
	rm $(OBJS) $(target) -f