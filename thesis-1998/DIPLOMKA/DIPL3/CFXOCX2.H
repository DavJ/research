//C++ library with constants defines for CHARTFX component (translated from Cfxocx2.pas)
//

#ifndef CCC_SERIE

// Notification Codes

#define CCC_SERIE  0 
#define CCC_SERIEBK  1 
#define CCC_ONE  2 
#define CCC_ONEBK  3
#define CCC_BARHORZ  4 
#define CCC_BKGND  5 
#define CCC_2DBK  6
#define CCC_3DBK  7 

#define CCS_LEGEND  0
#define CCS_SERLEGEND  1

#define CCP_SERIE  0
#define CCP_ONE  1 



// Chart types
#define CT_3D  0x00000100 
#define CT_HORZ  0x00000200
#define CT_TOOL  0x00000400 
#define CT_PALETTE  0x00000800
#define CT_LEGEND  0x00001000
#define CT_TOGETHER  0x00002000 
#define CT_POINTS  0x00004000 
#define CT_SHOWZERO  0x00008000 
#define CT_EACHBAR  0x00010000 
#define CT_CLUSTER  0x00020000
#define CT_SHOWDATA  0x00040000 
#define CT_DLGGRAY  0x00080000
#define CT_PATTERN  0x00100000 
#define CT_SHOWVALUES  0x00200000
#define CT_MENU  0x00400000 
#define CT_SCATTERLINE	 0x00800000
#define CT_COLORLINE 	0x01000000 
#define CT_NOAREALINE  0x02000000
#define CT_NOBORDERS  0x04000000 
#define CT_PIEVALUES  0x08000000 

// Chart Styles 
#define CS_CHLINE  0x00000001 
#define CS_CHBAR  0x00000002
#define CS_CHSPLINE  0x00000004
#define CS_CHMARK  0x00000008
#define CS_CHPIE  0x00000010
#define CS_CHAREA  0x00000020 
#define CS_CHPARETO  0x00000040 
#define CS_CHSCATTER  0x00000080 
#define CS_CHHILOW  0x00000100 
#define CS_CHDEFAULT  0x00000FFF
#define CS_MINMAX  0x00001000 
#define CS_3D  0x00002000
#define CS_HORZ  0x00004000 
#define CS_TOGETHER  0x00008000
#define CS_SHOWPOINT  0x00010000 
#define CS_SCALE  0x00020000
#define CS_TITLES  0x00040000 
#define CS_FONTS  0x00080000
#define CS_EDITABLE  0x00100000 
#define CS_FILEEXPORT  0x00200000 
#define CS_FILEIMPORT  0x00400000
#define CS_SCROLLABLE  0x00800000
#define CS_PRINTABLE  0x01000000 
#define CS_3DVIEW  0x02000000
#define CS_GRID  0x04000000
#define CS_RESIZEABLE  0x08000000 
#define CS_TEMPLATE  0x10000000
#define CS_COPY  0x20000000 
#define CS_CLOSEABLE  0x40000000 
#define CS_ALL  0xFFFFFFFF 

// #defineants

// STYLE, TYPE
#define CHART_ADD  0 
#define CHART_SET  1
#define CHART_REMOVE  2 


// GAP
#define CHART_LEFTGAP  0
#define CHART_RIGHGAP  1
#define CHART_TOPGAP  2
#define CHART_BOTTOMGAP  3 
#define CHART_ALLGAP  4 

// Colors
#define CHART_WHITE  1 
#define CHART_BLACK  2
#define CHART_LTGRAY  3
#define CHART_DKGRAY  4 
#define CHART_RED  5
#define CHART_DKRED  6
#define CHART_BLUE  7
#define CHART_DKBLUE  8 
#define CHART_GREEN  9 
#define CHART_DKGREEN  10 
#define CHART_CYAN  11 
#define CHART_DKCYAN  12 
#define CHART_YELLOW  13
#define CHART_DKYELLOW  14
#define CHART_VIOLET  15
#define CHART_DKVIOLET  16 

// Line Styles
#define CHART_SOLID  0 
#define CHART_DASH  1
#define CHART_DOT  2 
#define CHART_DASHDOT  3 
#define CHART_DASHDOTDOT  4 


// Color Types  
#define CHART_FGROUND  0 
#define CHART_BGROUND  1 

// ChartStatus Property #defineants
#define CHART_GSVALUES  0x00000001 
#define CHART_GSLEGENDS  0x00000002
#define CHART_GSCOLORS  0x00000004 
#define CHART_GSPATTERNS  0x00000008 
#define CHART_GSPALETTE  0x00000010
#define CHART_GSPATTPAL  0x00000020 
#define CHART_GSREADTEMP  0x00000040 
#define CHART_GSREADFILE  0x00000080
#define CHART_GSGALLERY  0x00000100 
#define CHART_GSOPTIONS  0x00000200 

// FONTS  
#define CF_BOLD  0x00000100
#define CF_ITALIC  0x00000200
#define CF_UNDERLINE  0x00000400
#define CF_STRIKEOUT  0x00000800
#define CF_FDONTCARE  0x00000000 
#define CF_FROMAN  0x00001000 
#define CF_FSWISS  0x00002000 
#define CF_FMODERN  0x00003000 
#define CF_FSCRIPT  0x00004000 
#define CF_FDECORATIVE  0x00005000
#define CF_ARIAL  0x00000000 
#define CF_COURIER  0x00010000 
#define CF_COURIERNEW  0x00020000
#define CF_HELVETICA  0x00030000 
#define CF_MODERN  0x00040000
#define CF_ROMAN  0x00050000
#define CF_SCRIPT  0x00060000 
#define CF_SYMBOL  0x00070000 
#define CF_TIMES  0x00080000 
#define CF_TIMESNEWR  0x00090000 
#define CF_WINGDINGS  0x000A0000 


// Closedata actions
#define COD_SMOOTH  0x1000

// Status Item Styles
#define CHART_STLEFT  0x0000
#define CHART_STCENTER  0x0001
#define CHART_STRIGHT  0x0002

// HILOW #defineants
#define HLC_HIGH  0
#define HLC_CLOSE  1 
#define HLC_LOW  2 

#define OHLC_CLOSE  0
#define OHLC_HIGH  1 
#define OHLC_OPEN  2 
#define OHLC_LOW  3 

// SetTool #defineants
#define CST_IMPORT  0x00000001
#define CST_EXPORT  0x00000002
#define CST_COPYBITMAP  0x00000004
#define CST_COPYDATA  0x00000008
#define CST_PRINT  0x00000010
#define CST_SPACE1  0x00000020
#define CST_AREA  0x00000040
#define CST_BARHORZ  0x00000080
#define CST_BAR  0x00000100
#define CST_LINE  0x00000200
#define CST_MARK  0x00000400
#define CST_PIE  0x00000800
#define CST_SPLINE  0x00001000
#define CST_PARETO  0x00002000
#define CST_SCATTER  0x00004000
#define CST_HILOW  0x00008000
#define CST_SPACE2  0x00010000
#define CST_3D  0x00020000
#define CST_ROTATE  0x00040000
#define CST_CLUSTER  0x00080000
#define CST_SPACE3  0x00100000
#define CST_LEGEND  0x00200000
#define CST_VGRID  0x00400000
#define CST_HGRID  0x00800000
#define CST_SPACE4  0x01000000
#define CST_TITLES  0x02000000
#define CST_FONTS  0x04000000
#define CST_TOOLS  0x08000000
#define CST_OPTIONS  0x10000000
#define CST_FILE  (CST_IMPORT | CST_EXPORT)
#define CST_COPY  (CST_COPYBITMAP | CST_COPYDATA)
#define CST_FILEEDIT  (CST_FILE | CST_COPY | CST_PRINT)
#define CST_GALLERY  (CST_AREA | CST_BARHORZ | CST_BAR | CST_LINE | CST_MARK | CST_PIE | CST_SPLINE)
#define CST_GALLERYEXT  (CST_GALLERY | CST_PARETO | CST_SCATTER | CST_HILOW)
#define CST_VIEW  (CST_3D | CST_ROTATE | CST_CLUSTER)
#define CST_LEGGRID  (CST_LEGEND | CST_VGRID | CST_HGRID)
#define CST_OTHER  (CST_TITLES | CST_FONTS | CST_TOOLS | CST_OPTIONS)




#endif
