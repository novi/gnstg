# Makefile
# Ito Yusuke
# 2008/10/17


# Target file name
TARGET = gnstg


# Source file list
SRCS = main.c GNSTChara.c GNSTPlayer.c  GNGeometory.c GNAnim.c GNShape.c GNSTEnemy.c GNSTMap.c GNSTCharaDraw.c GNSTBackg.c GNMotion.c GNSTInfoView.c GNFont.c GNNumberView.c 



# Object file list
OBJS = ${SRCS:.c=.o}


# Header file list
HEADERS =


# Compiler and linker settings
CC = gcc
CCFLAGS = -Wall -I/usr/include/opengl -O2
LD = gcc
LDFLAGS =
LIBS =  res/icon.o -lglut32 -lglu32 -lopengl32 


###

$(TARGET) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

.c.o :
	$(CC) $(CCFLAGS) -c $<

$(OBJS) : $(HEADERS) Makefile

clean :
	rm -f $(TARGET) $(TARGET).exe $(OBJS) core *~

