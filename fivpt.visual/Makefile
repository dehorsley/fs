OBJECTS = fivpt.o antcn.o dpoin.o errot.o fgaus.o fit2.o \
fitot.o fivp.o gooff.o jr2as.o local.o matcn.o matin.o \
offco.o offot.o onsor.o orign.o prfot.o reoff.o scmds.o \
site.o sorce.o tsys.o unslp.o volts.o wtsys.o mcbcn.o xoffot.o \
fivptplt.o

# g77 compiler is not standard for field system, but need for lpgplot.
FC = /usr/bin/g77

LIBS = ../polb/polb.a ../fslb/fslb.a ../lnfch/lnfch.a ../newlb/newlb.a \
../flib/flib.a ../fclib/fclib.a ../clib/clib.a ../fmpsee/fmpsee.a \
../port/port.a ../rtelb/rtelb.a

ifdef PRE_FS_LINUX_5
LDLIBS += -L/usr/X11R6/lib -lX11 -lpgplot
else
LDLIBS += -lpgplot -L/usr/X11R6/lib -lX11 -lpng -lz -lm
endif

../bin/fivpt: $(OBJECTS) $(LIBS)

include ../include.mk
