# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = BODYED.exe
OBJFILES = BODYED.obj editor_BE.obj allocpal.obj ImProc_BE.obj Const_BE.obj set1_BE.obj \
   set2_BE.obj io_data.obj tool.obj mcopy.obj undo.obj temp.obj status.obj About_BE.obj set4_BE.obj
RESFILES = BODYED.res
RESDEPEN = $(RESFILES) editor_BE.dfm set1_BE.dfm set2_BE.dfm tool.dfm mcopy.dfm temp.dfm \
   status.dfm About_BE.dfm set4_BE.dfm
LIBFILES = 
DEFFILE = 
# ---------------------------------------------------------------------------
CFLAG1 = -O2 -Hc -w- -k- -r -vi -c -a4 -b- -w-par -w-inl -Vx -Ve -x
CFLAG2 = -Ic:\diplomka\dipl3;$(BCB)\projects;$(BCB)\projects\bodyeditor;$(BCB)\projects\bodyed1;.;$(BCB)\include;$(BCB)\include\vcl \
   -H=$(BCB)\lib\vcl.csm 
PFLAGS = -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE \
   -Uc:\diplomka\dipl3;$(BCB)\projects;$(BCB)\projects\bodyeditor;$(BCB)\projects\bodyed1;.;$(BCB)\lib\obj;$(BCB)\lib \
   -Ic:\diplomka\dipl3;$(BCB)\projects;$(BCB)\projects\bodyeditor;$(BCB)\projects\bodyed1;.;$(BCB)\include;$(BCB)\include\vcl \
   -$L- -$D- -JPHNV -M
RFLAGS = -ic:\diplomka\dipl3;$(BCB)\projects;$(BCB)\projects\bodyeditor;$(BCB)\projects\bodyed1;.;$(BCB)\include;$(BCB)\include\vcl 
LFLAGS = -Lc:\diplomka\dipl3;$(BCB)\projects;$(BCB)\projects\bodyeditor;$(BCB)\projects\bodyed1;.;$(BCB)\lib\obj;$(BCB)\lib \
   -aa -Tpe -x -w- -V4.0
IFLAGS = 
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) vcl.lib import32.lib cp32mt.lib 
# ---------------------------------------------------------------------------
.autodepend

$(PROJECT): $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES) 
!

.pas.hpp:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.pas.obj:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.cpp.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $* 

.c.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $**

.rc.res:
    $(BCB)\BIN\brcc32 $(RFLAGS) $<
#-----------------------------------------------------------------------------
