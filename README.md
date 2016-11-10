# IJC
Language C projects
#Hodnoceni
DU1 - 10/15
\[C2]   Double/invalid free/fclose -- steg_decode.cc; l.33 a l.34
\[Z1]   ppm_read nedetekuje neplatne PPM soubory
\[Z1]   Chybne obrazky zpusobuji segfault
\[Z1]   Castecne nefunkcni DU1_ makra -- pri testu bit-array.h ve specialnim unit testu.

--------------------------------------------------
Celkove hodnoceni:
--------------------------------------------------
10 b
--------------------------------------------------
Doporuceni
--------------------------------------------------
V error.c pouzivate parameter args pred volanim va_start -- mohlo by vest k chybe.
Doporucuji priste neodladit program pouze nad jednim vzorovym obrazkem
Zkuste si adaptovat styl komentovani kodu a jeho struktury podle generatoru dokumentace (napr. Doxygen)


DU2 - 12/15
\[C1]           Memory leak ()
\[Z1]  \[htable] Unit testy na htable selhavaji kvuli nekoretne ulozenym hodnotam.
\[Z1]  \[tail]   Castecne chybny vypis (chybne radky, radky navic,...)
\==========================================================
Hodnoceni =  12 bodu
\==========================================================

\==========================================================
Doporuceni
\==========================================================
wordcount.c:26 Promenna s neni uvolnena

