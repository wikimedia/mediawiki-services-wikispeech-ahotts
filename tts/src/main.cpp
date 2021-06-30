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

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "htts.hpp"
#include "strl.hpp"
#include "caudio.hpp"

int main(int argc, char * argv[]){

///////////////////////////////////////////
// READ INPUT ARGUMENTS

	//define the input defaults arguments
	//ELHUYAR included PhoFile and WordFile
	KVStrList pro("InputFile=input.txt Lang=eu OutputFile=output.wav PhoFile=null WordFile=null DataPath=data_tts Speed=100 SetDur=n help=n");
	StrList files;

	//define the type of each argument
	//InputFile=s --> string
	//Lang=selection
	//ELHUYAR included PhoFile and WordFile
	clargs2props(argc, argv, pro, files,
			"InputFile=s Lang={eu} OutputFile=s PhoFile=s WordFile=s DataPath=s Speed=s help=b SetDur=b");

	//Read the values of the input arguments
	if (pro.bval("help")){
		printf("usage: ./tts -InputFile=input.txt -Lang=eu -OutputFile=output.wav -DataPath=data_tts -Speed=100\n");
		return -1;
	}
	const char *input_file = pro.val("InputFile");
	const char *output_file = pro.val("OutputFile");
	//ELHUYAR included PhoFile and WordFile
	const char *pho_file = pro.val("PhoFile");
	const char *wrd_file = pro.val("WordFile");
	const char *lang = pro.val("Lang");
	const char *speed=pro.val("Speed");
	const char *data_path=pro.val("DataPath");
	bool SetDur=pro.bbval("SetDur");
	
///////////////////////////////////////////

///////////////////////////////////////////
// DEFINE A NEW TTS
	HTTS *tts = new HTTS;
	tts->set("PthModel", "Pth1"); //not used but must be defined
	tts->set("Method", "HTS"); //HTS -> HMM-based method
	//ELHUYAR included PhoFile and WordFile
	tts->set("PhoFile", pho_file); //HTS -> HMM-based method
	tts->set("WordFile", wrd_file); //HTS -> HMM-based method
///////////////////////////////////////////

///////////////////////////////////////////
// SELECT A DICTIONARY DEPENDING ON THE LANGUAGE
// Language (Lang) must be set before creating the tts (see below)
	if (!strcmp(lang,"eu")){
		//Catalan, english and galician languages use Basque Lang to create the TTS
		//...the actual language is set with "input_multilingual" function
		tts->set("Lang", "eu");
		char dic_path[1024];
		sprintf(dic_path, "%s/dicts/eu_dicc", data_path);
		tts->set("HDicDBName",dic_path);
	}else
	{
		fprintf(stderr,"ERROR: Language %s not suported.\n\tUse one of the following languages: eu\n", lang);
		return -1;
	}
///////////////////////////////////////////

///////////////////////////////////////////
// CREATE THE TTS OBJECT
	if (!tts->create()) {
	        delete tts;
        	return 0;
    }
///////////////////////////////////////////


///////////////////////////////////////////
// OTHER CONFIGURATIONS (after the tts object is created)
	//all the voice models are stored in the folder data_files/voices
	//the path of data_files is set by data_path variable
	char voice_path[1024];
   	if (!strcmp(lang,"eu")){
		//if(!strcmp(gender,"F"))
			sprintf(voice_path, "%s/voices/aholab_eu_female/", data_path);//Female Basque Voice
		//else
		//	sprintf(voice_path, "%s/voices/aholab_eu_male/", data_path);//Male Basque Voice
	}
	else {fprintf(stderr,"ERROR: Not supported language.\n Plase select one of the available ones: eu}\n");return -1;}
	// SET THE VOICE PATH
	tts->set("voice_path", voice_path);

	if(SetDur)
		tts->set("vp", "yes");
	//MODIFY THE SPEED-RATE OF THE VOICE
	else if(speed!=NULL && strcmp(speed,"100")){
		int f;
		sscanf(speed,"%d",&f);
		if(f>=25 && f<=300){
			char *tmp_speed = new char [5];
			sprintf(tmp_speed, "%.2f", f/100.0);
				tts->set("r",tmp_speed);
			//}
			delete []tmp_speed;
		}else{fprintf(stderr,"WARNING: parametro -Speed=%d ignored\n\tits value must be an integer between 25 and 300\n",f);}
	}
//////////////////////////////////

	char *str; //To read the input file
	int tamanio; //size of the input file

///////////////////////////////////////////
// CREATE AN OUTPUT WAV FILE

	//ELHUYAR included PhoFile and Wordfile
	if(strcmp(pho_file,"null")){
		FILE* fpho;
		fpho=fopen(pho_file,"w");
		fclose(fpho);
	}
	if(strcmp(wrd_file,"null")){
		FILE* fwrd;
		fwrd=fopen(wrd_file,"w");
		fclose(fwrd);
	}
	CAudioFile fout;
	fout.open(output_file,"w", "SRate=16000.0 NChan=1 FFormat=Wav"); //Mono, 16kHz
///////////////////////////////////////////

///////////////////////////////////////////
// PROCESS THE INPUT FILE
// For Basque and Spanish it reads the text from a string
    
		FILE* f1;
		f1=fopen(input_file,"rb");
		if(f1!=NULL){
			fseek(f1,0,SEEK_END);
			tamanio= ftell(f1);
			rewind(f1);
			// ELHUYAR bukaeran gauzak ez sartzeko
			str=new char[tamanio+1];
			fread(str,sizeof(char),tamanio,f1);
			// ELHUYAR bukaeran gauzak ez sartzeko
			str[tamanio]=0;
			fclose(f1);
		}else {
			fprintf(stderr,"ERROR: Can't open the input file %s\n",input_file);
			return -1;
		}
	///////////////////////////////////////////
	// INSERT TEXT IN THE TTS OBJECT
		if(tts->input_multilingual(str, lang, data_path, FALSE)){ //FALSE => str contains the input text
			short *samples;
			int len=0;
			//PROCESS A SENTENCE FROM THE TEXT AND GET "len" samples
			// ELHUYAR included cumulative duration for multi-sentence sentences
			float cumulative_duration=0;
			while((len = tts->output_multilingual(lang, &samples, cumulative_duration)) != 0){
				//samples are stored in the audio file, but could also be directed to the soundcard
				fout.setBlk(samples, len);
				free(samples);
			}
		}
	///////////////////////////////////////////

	
///////////////////////////////////////////

	//CLOSE THE AUDIOFILE
	fout.close();

	if(str!=NULL)delete[]str;

	//DELETE THE TTS OBJECT
	delete tts;
	return 1;
}


