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
(C) 1999 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU) // Euskaltel

Nombre fuente................ es_hdic.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion: ............... Borja Etxebarria
............................. I?igo Salbidea

Version  dd/mm/aa  Autor     Comentario
-------  --------  --------  ----------
2.0.0	 22/03/04  inigos    nuevas categorias
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.1.0    15/12/99  borja     version inicial

======================== Contenido ========================
<DOC>
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <string.h>
#include "es_hdic.hpp"
#include "uti.h"
#include "chset.h"
#include "httsmsg.h"
#define  xDEBUGDIC
/**********************************************************/

KINDOF_DDEF(LangES_HDicDB,HDicDB);

/**********************************************************/
/* bits libres para el usuario. del 0 al 22.!!            */
/* HDICQERY_ENCODE(firstbit,nbits)                        */

BOOL LangES_HDicDB::flagParse( const CHAR *s, HDicRef &r )
{
	/* Para el POS */
	if (!strcmp(s,"spv")) r.setquery(HDIC_QUERY_ES_SUSP, 1); // Sustantivos Personales pre-post Verbo
	else if (!strcmp(s,"spi")) r.setquery(HDIC_QUERY_ES_SUSP, 2); // Sustantivos Personales Indiferentes
	else if (!strcmp(s,"spnv")) r.setquery(HDIC_QUERY_ES_SUSP, 3); // Sustantivos Personales No post Verbo
	else if (!strcmp(s,"demnv")) r.setquery(HDIC_QUERY_ES_DEMO, 1); // DEMostrativos No pre Verbo
	else if (!strcmp(s,"demi")) r.setquery(HDIC_QUERY_ES_DEMO, 2); // DEMostrativos Indiferentes
	else if (!strcmp(s,"adj")) r.setquery(HDIC_QUERY_ES_DEMO, 3); // Adjetivos
	else if (!strcmp(s,"posnv")) r.setquery(HDIC_QUERY_ES_POSE, 1); // POSesivos No pre Verbo
	else if (!strcmp(s,"posi")) r.setquery(HDIC_QUERY_ES_POSE, 2); // POSesivos Indiferentes
	else if (!strcmp(s,"rela")) r.setquery(HDIC_QUERY_ES_REL, 1); // RELativos
	else if (!strcmp(s,"relie")) r.setquery(HDIC_QUERY_ES_REL, 2); // RELativos
	else if (!strcmp(s,"inunv")) r.setquery(HDIC_QUERY_ES_INDNUM, 1); // INdefinidos y nUmerales No pre Verbo
	else if (!strcmp(s,"inui")) r.setquery(HDIC_QUERY_ES_INDNUM, 2); // INdefinidos y nUmerales Indiferentes
	else if (!strcmp(s,"carnv")) r.setquery(HDIC_QUERY_ES_CARD, 1); // CARdinales No pre verbo
	else if (!strcmp(s,"cari")) r.setquery(HDIC_QUERY_ES_CARD, 2); // CARdinales Indeferentes
	else if (!strcmp(s,"adv")) r.setquery(HDIC_QUERY_ES_ADVE, 1); // ADVerbios
	else if (!strcmp(s,"prep")) r.setquery(HDIC_QUERY_ES_PREP, 1); // PREPosiciones
	else if (!strcmp(s,"conj")) r.setquery(HDIC_QUERY_ES_CONJ, 1); // CONJunciones
	else if (!strcmp(s,"vers")) r.setquery(HDIC_QUERY_ES_VERB, 1); // VERbos Simples
	else if (!strcmp(s,"verc")) r.setquery(HDIC_QUERY_ES_VERB, 2); // VERbos Compuestos
	else if (!strcmp(s,"geru")) r.setquery(HDIC_QUERY_ES_VERB, 3); // GERUndios
	else if (!strcmp(s,"ppio")) r.setquery(HDIC_QUERY_ES_VERB, 4); // ParticiPIOs
	else if (!strcmp(s,"ir1c")) r.setquery(HDIC_QUERY_ES_VERB, 5); // Infinitivos Regulares 1? Conjugaci?n
	else if (!strcmp(s,"ir2c")) r.setquery(HDIC_QUERY_ES_VERB, 6); // Infinitivos Regulares 2? Conjugaci?n
	else if (!strcmp(s,"ir3c")) r.setquery(HDIC_QUERY_ES_VERB, 7); // Infinitivos Regulares 3? Conjugaci?n
	else if (!strcmp(s,"iicc")) r.setquery(HDIC_QUERY_ES_VERB, 8); // Infinitivos Irregulares Cualquier Conjugaci?n (verbos inventados para el "conjugador")
	else if (!strcmp(s,"otro")) r.setquery(HDIC_QUERY_ES_OTRO, 1); // Otros (SUStantivos, adjetivos... para desambig?ar raices de verbos)

	/* estos los necesita el normalizador de texto */
	else if (!strcmp(s,"abb")) r.setquery(HDIC_QUERY_ES_NOR,HDIC_ANSWER_ES_NOR_ABB);
	else if (!strcmp(s,"abbnf")) r.setquery(HDIC_QUERY_ES_NOR,HDIC_ANSWER_ES_NOR_ABBNF);
	else if (!strcmp(s,"unit")) r.setquery(HDIC_QUERY_ES_NOR,HDIC_ANSWER_ES_NOR_UNIT);
	else if (!strcmp(s,"acr")) r.setquery(HDIC_QUERY_ES_NOR,HDIC_ANSWER_ES_NOR_ACR);
	else return FALSE;
	return TRUE;


}

/**********************************************************/

/**********************************************************/
/* Busqueda en fichero compilado.

hacemos 4 busquedas binarias por este orden:
1. casesens con sustituciones
2. casesens sin sustituciones
3. caseinsens con sustituciones
4. caseinsens sin sustituciones
Cada una debe ser mas larga que la anterior para desbancarla.
Para caseinsens se utiliza {tokl} (lowercase) en vez de {tok}.
*/

HDicRef LangES_HDicDB::searchBin(char **exp)
{
	long hit[4];
	BOOL notFoundFr;
	size_t toklen_old;

	/* buscamos en los 4 bloques del fichero */
	hit[0]=tokbsearch(tok, b_base[0],b_n[0],b_blen[0]);
	hit[1]=tokbsearch(tok, b_base[1],b_n[1],b_blen[1]);
	hit[2]=tokbsearch(tokl,b_base[2],b_n[2],b_blen[2]);
	hit[3]=tokbsearch(tokl,b_base[3],b_n[3],b_blen[3]);

	INT i=0;

	/* nos quedamos con el mas largo (o sea empezamos por el ultimo bloque) */
	notFoundFr = FALSE;
	if (hit[3]>=0) i=3;
	else if (hit[2]>=0) i=2;
	else if (hit[1]>=0) i=1;
	else if (hit[0]>=0) i=0;
	else notFoundFr = TRUE;

	if (notFoundFr || (toklen != hitlen)) {
//Yon2. $$$$$ Aqui hacemos b?squeda parcial.
		pCHAR partialStr;
		pCHAR partialStrl;
		size_t parLen=toklen - 1;
		BOOL contSrch=TRUE;

#ifdef DEBUGDIC
		htts_warn ("Entro en la b?squeda parcial.");
#endif
		toklen_old = toklen;
		if(!parLen) contSrch=FALSE; //No buscar si no hay nada que buscar
		while (contSrch)	{
			partialStr = strdup(tok);
			partialStr[parLen]='\0';
			partialStrl = strdup(partialStr);
			chset_StrLower(partialStrl); // pasar a minusculas
			toklen = parLen;
			hitlen = 0;


			/* buscamos en los 4 bloques del fichero */
			hit[0]=tokbsearch(partialStr, b_base[0],b_n[0],b_blen[0]);
			hit[1]=tokbsearch(partialStr, b_base[1],b_n[1],b_blen[1]);
			hit[2]=tokbsearch(partialStrl, b_base[2],b_n[2],b_blen[2]);
			hit[3]=tokbsearch(partialStrl,b_base[3],b_n[3],b_blen[3]);

			/* nos quedamos con el mas largo (o sea empezamos por el ultimo bloque) */
			notFoundFr = FALSE;
			if (hit[3]>=0) i=3;
			else if (hit[2]>=0) i=2;
			else if (hit[1]>=0) i=1;
			else if (hit[0]>=0) i=0;
			else notFoundFr = TRUE;

			/* continuamos buscando? Solo nos sirve match total */
#ifdef DEBUGDIC
			htts_warn("Buscando: %s Len: %d Len: %d i: %d", partialStr, parLen, hitlen, i);
#endif
			/* liberamos las cadenas parciales */
			free(partialStr);
			free(partialStrl);

			if (hitlen == parLen) {
				notFoundFr = FALSE;
				contSrch = FALSE;
#ifdef DEBUGDIC
				htts_warn("Hemos encontrado un match parcial.");
				htts_warn("Found: %d %d %d %d", hit[3], hit[2],hit[1],hit[0]);
#endif
			}
			else {
				notFoundFr = TRUE;
#ifdef DEBUGDIC
				htts_warn("Not found: %d %d %d %d", hit[3], hit[2],hit[1],hit[0]);
#endif
			}
			parLen--;
			if (parLen == 0) contSrch = FALSE;
		}
		toklen = toklen_old;
		if (notFoundFr) {
#ifdef DEBUGDIC
			htts_warn("Nos salimos porque no encuentra nada.");
#endif
			return HDIC_REF_NULL;  // si no hay ningun hit, fuera!
		}
	}

	if (exp&&(*exp)) { free(*exp); *exp=NULL; } // liberar expansion antigua si la hay

	BOOL casesen[4]={TRUE,TRUE,FALSE,FALSE};
	hitlonger=casesen[i];
	// saltamos al campo HDicRef de la linea del hit
	fseek(fileBin,b_base[i]+b_blen[i]*hit[i]+sizeof(INT16)+b_slen[i],SEEK_SET);

	// Leemos el campo ref.
	HDicRef ref=HDIC_REF_NULL;
	UINT32 u32;
	if (!fread(&u32,sizeof(u32),1,fileBin)) return HDIC_REF_NULL;
	endian_fromlittle32(&u32); ref.bits=u32;

#ifdef DEBUGDIC
	htts_warn("HitLen: %d TokLen: %d Ref: %ud i: %d", hitlen, toklen, u32, i);
#endif
	ref.__setbits(HDIC_QUERY_CASE,casesen[i]); // metemos el campo casesens
	// salvar longitud del match. 0 si es full
	if (hitlen==toklen) ref.__setbits(HDIC_QUERY_MATCHLEN,0);
	else {
		ref.__setbits(HDIC_QUERY_MATCHLEN,hitlen);
		// si no entra en el campo de bits, lo ponemos a full (mejor que dejarlo indeterminado...)
		if (hitlen!=ref.__getbits(HDIC_QUERY_MATCHLEN)) ref.__setbits(HDIC_QUERY_MATCHLEN,0);
	}

	/* si el hit era en el primer o tercer bloque, hay sustitucion */
	if (exp&&((i==0)||(i==2))) {
		UINT16 u16;
		size_t len;
		if (fread(&u16,sizeof(u16),1,fileBin)) {
			endian_fromlittle16(&u16); len=u16;
			*exp=(CHAR*)malloc(sizeof(CHAR)*(len+1));
			if (!fread(*exp,sizeof(CHAR),len+1,fileBin)) {
				free(*exp); *exp=NULL;
			}
		}
	}
	return ref;
}

