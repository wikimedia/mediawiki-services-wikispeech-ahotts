/******************************************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

AhoTTS: A Text-To-Speech system for Basque* and Spanish*,
developed by Aholab Signal Processing Laboratory at the
University of the Basque Country (UPV/EHU). Its acoustic engine is based on
hts_engine' and it uses AhoCoder* as vocoder.
(Read COPYRIGHT_and_LICENSE_code.txt for more details)
--------------------------------------------------------------------------------

Linguistic processing for Basque and Spanish, Vocoder (Ahocoder) and
integration by Aholab UPV/EHU.

*AhoCoder is an HNM-based vocoder for Statistical Synthesizers
http://aholab.ehu.es/ahocoder/

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyrights:
	1997-2015  Aholab Signal Processing Laboratory, University of the Basque
	 Country (UPV/EHU)
    *2011-2015 Aholab Signal Processing Laboratory, University of the Basque
	  Country (UPV/EHU)

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Licenses:
	GPL-3.0+
	*GPL-3.0+
	'Modified BSD (Compatible with GNU GPL)

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GPL-3.0+
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 .
 This package is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 .
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 .
 On Debian systems, the complete text of the GNU General
 Public License version 3 can be found in /usr/share/common-licenses/GPL-3.

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/******************************************************************************/
/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ isofilt.c
Nombre paquete............... normalizador
Lenguaje fuente.............. C
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.5	 02/10/07  Inaki     A�adir u con dieresis y simbolo Euro
0.0.4    02/05/01  Yon2.     lost <string.h>
0.0.3    06/04/01  Yon2.     Cedilla Bug.
0.0.2    03/11/00  Yon2.     Tres cuartos missed.
0.0.1    25/10/00  Yon2.     Aniadir funciones para acceder
                             a la tabla y filtrar buffers.
0.0.0    17/10/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

Matriz de 256 elementos que filtra caracteres de la tabla
ISO 8859/Latin 1.
Los caracteres que no son de inter�s los convierte a
espacios, y los que tengan un sustituto se convierten.

Los menores de 32, caracteres de escape se sustituyen todos
por espacios. Incluidos el CR, el LF y el tabulador.
Del 127 al 160 son caracteres de control que tambi�n se eliminan.

No editar este archivo desde DOS con BC la p�gina de c�digos
es totalmente diferente. Es evidente que para poder ver este
archivo correctamente se necesita una tabla de caracteres en uso
ISO 8859/Latin 1

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <string.h>

#include "isofilt.h"




/**********************************************************/
//Hay que hacer cosas raras con los punteros pues los CHAR
//tienen signo, y si entramos en la tabla con mayores de 128
//estamos entrando con negativos.!!!!!!
/**********************************************************/

CHAR char_fltr(CHAR i)
{
	void *j = &i;
	//printf("\n char:%c numero:%d --> char:char:%c numero:%d <-", i,i,(CHAR)iso8859filter[ *((pUCHAR)j)],(CHAR)iso8859filter[ *((pUCHAR)j)]);
	return (CHAR)iso8859filter[ *((pUCHAR)j)];           
}

/**********************************************************/


/**********************************************************/


pCHAR buff_fltr(pCHAR buffer)
{
  INT i, len;
    
	len = strlen(buffer);
 	for(i=0;i< len; i++) 
		buffer[i]=char_fltr(buffer[i]);

	return buffer;
}
/**********************************************************/
                
                
                

/**********************************************************/


INT iso8859filter[256] = { 
/* [000] C */ ' ', /* [001] C */ ' ', /* [002] C */ ' ', /* [003] C */ ' ', 
/* [004] C */ ' ', /* [005] C */ ' ', /* [006] C */ ' ', /* [007] C */ ' ', 
/* [008] C */ ' ', /* [009] C */ ' ', /* [010] C */ ' ', /* [011] C */ ' ', 
/* [012] C */ ' ', /* [013] C */ ' ', /* [014] C */ ' ', /* [015] C */ ' ', 
/* [016] C */ ' ', /* [017] C */ ' ', /* [018] C */ ' ', /* [019] C */ ' ', 
/* [020] C */ ' ', /* [021] C */ ' ', /* [022] C */ ' ', /* [023] C */ ' ', 
/* [024] C */ ' ', /* [025] C */ ' ', /* [026] C */ ' ', /* [027] C */ ' ', 
/* [028] C */ ' ', /* [029] C */ ' ', /* [030] C */ ' ', /* [031] C */ ' ', 
/* [032] C */ ' ', /* [033] ! */ '!', /* [034] " */ '"', /* [035] # */ '#', 
/* [036] $ */ '$', /* [037] % */ '%', /* [038] & */ '&', /* [039] ' */ '\'', 
/* [040] ( */ '(', /* [041] ) */ ')', /* [042] * */ '*', /* [043] + */ '+', 
/* [044] , */ ',', /* [045] - */ '-', /* [046] . */ '.', /* [047] / */ '/', 
/* [048] 0 */ '0', /* [049] 1 */ '1', /* [050] 2 */ '2', /* [051] 3 */ '3', 
/* [052] 4 */ '4', /* [053] 5 */ '5', /* [054] 6 */ '6', /* [055] 7 */ '7', 
/* [056] 8 */ '8', /* [057] 9 */ '9', /* [058] : */ ':', /* [059] ; */ ';', 
/* [060] < */ '<', /* [061] = */ '=', /* [062] > */ '>', /* [063] ? */ '?', 
/* [064] @ */ '@', /* [065] A */ 'A', /* [066] B */ 'B', /* [067] C */ 'C', 
/* [068] D */ 'D', /* [069] E */ 'E', /* [070] F */ 'F', /* [071] G */ 'G', 
/* [072] H */ 'H', /* [073] I */ 'I', /* [074] J */ 'J', /* [075] K */ 'K', 
/* [076] L */ 'L', /* [077] M */ 'M', /* [078] N */ 'N', /* [079] O */ 'O', 
/* [080] P */ 'P', /* [081] Q */ 'Q', /* [082] R */ 'R', /* [083] S */ 'S', 
/* [084] T */ 'T', /* [085] U */ 'U', /* [086] V */ 'V', /* [087] W */ 'W', 
/* [088] X */ 'X', /* [089] Y */ 'Y', /* [090] Z */ 'Z', /* [091] [ */ '[', 
/* [092] \ */ '\\', /* [093] ] */ ']', /* [094] ^ */ '^', /* [095] _ */ '_', 
/* [096] ` */ ' ', /* [097] a */ 'a', /* [098] b */ 'b', /* [099] c */ 'c', 
/* [100] d */ 'd', /* [101] e */ 'e', /* [102] f */ 'f', /* [103] g */ 'g', 
/* [104] h */ 'h', /* [105] i */ 'i', /* [106] j */ 'j', /* [107] k */ 'k', 
/* [108] l */ 'l', /* [109] m */ 'm', /* [110] n */ 'n', /* [111] o */ 'o', 
/* [112] p */ 'p', /* [113] q */ 'q', /* [114] r */ 'r', /* [115] s */ 's', 
/* [116] t */ 't', /* [117] u */ 'u', /* [118] v */ 'v', /* [119] w */ 'w', 
/* [120] x */ 'x', /* [121] y */ 'y', /* [122] z */ 'z', /* [123] { */ '{', 
/* [124] | */ '|', /* [125] } */ '}', /* [126] ~ */ '~', /* [127] C */ ' ', 

/* Prueba para Windows, por problemas con caracteres extendidos */

#if defined(WIN324) //INAKI, para q siempre use lo de linux   /* para consola win95 */
/* [128]   */ ' ', /* [129] � */ '�', /* [130]   */ '�', /* [131]   */ ' ',
/* [132]   */ ' ', /* [133]   */ ' ', /* [134]   */ ' ', /* [135] � */ '�', 
/* [136]   */ ' ', /* [137]   */ ' ', /* [138]   */ ' ', /* [139]   */ ' ', 
/* [140]   */ ' ', /* [141]   */ ' ', /* [142]   */ ' ', /* [143]   */ ' ', 
/* [144]   */ ' ', /* [145]   */ ' ', /* [146]   */ ' ', /* [147]   */ ' ', 
/* [148]   */ ' ', /* [149]   */ ' ', /* [150]   */ ' ', /* [151]   */ ' ', 
/* [152]   */ ' ', /* [153]   */ ' ', /* [154] � */ '�', /* [155]   */ ' ', 
/* [156]   */ ' ', /* [157]   */ ' ', /* [158]   */ ' ', /* [159]   */ ' ', 
/* [160] � */ '�', /* [161] � */ '�', /* [162] � */ '�', /* [163] � */ '�', 
/* [164] � */ '�', /* [165] � */ '�', /* [166] � */ '�', /* [167] � */ '�', 
/* [168] � */ '�', /* [169] � */ ' ', /* [170] � */ '�', /* [171] � */ '�', 
/* [172] � */ '�', /* [173] � */ '�', /* [174] � */ '\'',/* [175] � */ '\'', 
/* [176]   */ '�', /* [177]   */ ' ', /* [178]   */ ' ', /* [179]   */ ' ', 
/* [180]   */ ' ', /* [181] � */ '�', /* [182]   */ ' ', /* [183]   */ ' ', 
/* [184] � */ '�', /* [185]   */ ' ', /* [186]   */ ' ', /* [187]   */ ' ', 
/* [188]   */ ' ', /* [189]   */ ' ', /* [190]   */ ' ', /* [191]   */ ' ', 
/* [192]   */ ' ', /* [193]   */ ' ', /* [194]   */ ' ', /* [195]   */ ' ', 
/* [196]   */ ' ', /* [197]   */ ' ', /* [198]   */ ' ', /* [199]   */ ' ', 
/* [200]   */ ' ', /* [201]   */ ' ', /* [202]   */ ' ', /* [203]   */ ' ', 
/* [204]   */ ' ', /* [205]   */ ' ', /* [206]   */ ' ', /* [207]   */ ' ', 
/* [208]   */ ' ', /* [209]   */ ' ', /* [210]   */ ' ', /* [211]   */ ' ', 
/* [212] � */ '�', /* [213]   */ ' ', /* [214] � */ '�', /* [215]   */ ' ', //213 euro?????
/* [216]   */ ' ', /* [217]   */ ' ', /* [218]   */ ' ', /* [219]   */ ' ', 
/* [220]   */ ' ', /* [221]   */ ' ', /* [222]   */ ' ', /* [223]   */ ' ', 
/* [224] � */ '�', /* [225]   */ ' ', /* [226]   */ ' ', /* [227]   */ ' ', 
/* [228]   */ ' ', /* [229]   */ ' ', /* [230]   */ ' ', /* [231]   */ ' ', 
/* [232]   */ ' ', /* [233] � */ '�', /* [234]   */ ' ', /* [235]   */ ' ', 
/* [236]   */ ' ', /* [237]   */ ' ', /* [238]   */ ' ', /* [239]   */ ' ', 
/* [240]   */ ' ', /* [241]   */ ' ', /* [242]   */ ' ', /* [243]   */ ' ', 
/* [244]   */ ' ', /* [245]   */ ' ', /* [246]   */ ' ', /* [247]   */ ' ', 
/* [248]   */ ' ', /* [249]   */ ' ', /* [250]   */ ' ', /* [251]   */ ' ', 
/* [252]   */ ' ', /* [253]   */ ' ', /* [254]   */ ' ', /* [255]   */ ' '
};


#else //INAKI: 128 --> simbolo Euro 
/* [128] � */ '�', /* [129] C */ ' ', /* [130] C */ ' ', /* [131] C */ ' ',
/* [132] C */ ' ', /* [133] C */ ' ', /* [134] C */ ' ', /* [135] C */ ' ', 
/* [136] C */ ' ', /* [137] C */ ' ', /* [138] C */ ' ', /* [139] C */ ' ', 
/* [140] C */ ' ', /* [141] C */ ' ', /* [142] C */ ' ', /* [143] C */ ' ', 
/* [144] C */ ' ', /* [145] C */ ' ', /* [146] C */ ' ', /* [147] C */ ' ', 
/* [148] C */ ' ', /* [149] C */ ' ', /* [150] C */ ' ', /* [151] C */ ' ', 
/* [152] C */ ' ', /* [153] C */ ' ', /* [154] C */ ' ', /* [155] C */ ' ', 
/* [156] C */ ' ', /* [157] C */ ' ', /* [158] C */ ' ', /* [159] C */ ' ', 
/* [160] � */ ' ', /* [161] � */ '�', /* [162] � */ ' ', /* [163] � */ '�', 
/* [164] � */ ' ', /* [165] � */ '�', /* [166] � */ ' ', /* [167] � */ ' ', 
/* [168]   */ ' ', /* [169] � */ ' ', /* [170] � */ '�', /* [171] � */ '\'', 
/* [172] � */ ' ', /* [173] � */ ' ', /* [174]   */ ' ', /* [175] � */ ' ', 
/* [176] � */ '�', /* [177] � */ '�', /* [178] � */ '�', /* [179] � */ ' ', 
/* [180] � */ ' ', /* [181] � */ ' ', /* [182] � */ ' ', /* [183] � */ ' ', 
/* [184] � */ '�', /* [185] � */ ' ', /* [186] � */ '�', /* [187] � */ '\'', 
/* [188] � */ '�', /* [189] � */ '�', /* [190] � */ '�', /* [191] � */ '�', 
/* [192] � */ '�', /* [193] � */ '�', /* [194] � */ 'A', /* [195] � */ 'A', 
/* [196] � */ 'A', /* [197] � */ 'A', /* [198] � */ ' ', /* [199] � */ 'C', 
/* [200] � */ '�', /* [201] � */ '�', /* [202] � */ 'E', /* [203] � */ 'E', 
/* [204] � */ '�', /* [205] � */ '�', /* [206] � */ 'I', /* [207] � */ 'I', 
/* [208] � */ ' ', /* [209] � */ '�', /* [210] � */ '�', /* [211] � */ '�', 
/* [212] � */ 'O', /* [213] � */ 'O', /* [214] � */ 'O', /* [215] � */ '�', 
/* [216] � */ ' ', /* [217] � */ '�', /* [218] � */ '�', /* [219] � */ 'U', 
/* [220] � */ '�', /* [221] � */ 'Y', /* [222] � */ ' ', /* [223] � */ '�', 
/* [224] � */ '�', /* [225] � */ '�', /* [226] � */ 'a', /* [227] � */ 'a', 
/* [228] � */ 'a', /* [229] � */ 'a', /* [230] � */ ' ', /* [231] � */ 'c', 
/* [232] � */ '�', /* [233] � */ '�', /* [234] � */ 'e', /* [235] � */ 'e', 
/* [236] � */ '�', /* [237] � */ '�', /* [238] � */ 'i', /* [239] � */ 'i', 
/* [240] � */ 'o', /* [241] � */ '�', /* [242] � */ '�', /* [243] � */ '�', 
/* [244] � */ 'o', /* [245] � */ 'o', /* [246] � */ 'o', /* [247] � */ '�', 
/* [248] � */ ' ', /* [249] � */ '�', /* [250] � */ '�', /* [251] � */ 'u', 
/* [252] � */ '�', /* [253] � */ 'y', /* [254] � */ ' ', /* [255] � */ 'y'
};
/**********************************************************/
#endif
/**********************************************************/
