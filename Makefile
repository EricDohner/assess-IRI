f77 = gfortran
CC = gcc

FFLAGS = -c -finit-local-zero -fno-automatic
# -fno-automatic
CFLAGS = -Werror

OBJS = irisub.o irifun.o iritec.o iridreg.o igrf.o cira.o iriflip.o# rocdrift.o
SUBOBJS = irifun.o iritec.o iridreg.o igrf.o cira.o iriflip.o# rocdrift.o
IRIOBJS = irifun.o iritec.o iridreg.o igrf.o cira.o iriflip.o# rocdrift.o
CALL_IRI = call_IRI.o
IRILIB = irilib.a
IRIEXE = call_IRI.exe

call_IRI: $(IRILIB) $(CALL_IRI) $(OBJS)
	$(CC) $(CFLAGS) -o call_IRI.exe $(CALL_IRI) $(IRILIB) -lgfortran -lm

IRIMAKE:
	f77 -o iri iritest.for irisub.for irifun.for iritec.for iridreg.for igrf.for cira.for iriflip.for rocdrift.for

irilib.a: $(OBJS)
	ar rcs irilib.a $(OBJS)

call_IRI.o: $(OBJS) $(IRILIB)
	gcc -c $(CFLAGS) call_IRI.c  -lm -lgfortran

irisub.o: $(SUBOBJS)
	$(f77) $(FFLAGS) irisub.for -lm
	
irifun.o:
	$(f77) $(FFLAGS) irifun.for -lm

iritec.o:
	$(f77) $(FFLAGS) iritec.for -lm

iridreg.o:
	$(f77) $(FFLAGS) iridreg.for -lm
	
igrf.o:
	$(f77) $(FFLAGS) igrf.for -lm
	
cira.o:
	$(f77) $(FFLAGS) cira.for -lm

iriflip.o:
	$(f77) $(FFLAGS) iriflip.for -lm
	
rocdrift.o:
	$(f77) $(FFLAGS) rocdrift.for -lm
	
run: $(IRIEXE)
	./call_IRI.exe
	
clean:
	rm *.exe *.o
