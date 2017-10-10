#include <fcntl.h>
#include <io.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

FILE *fopen(),*fp;
char endbuf[] = {"ENDSEC\n  0\nEOF\n"};
char nfilei[20];
char nfileo[20];
char buffer[80];
char layer[12];
int  file1;
float x,y;


void Autocad(void)
{
//Open "c:\Output_dxf_2d.DXF" For Output As #3

//Print #3, 0
//Print #3, "SECTION"
//Print #3, 2
//Print #3, "HEADER"
sprintf(buffer,"0\nSECTION\n2\nHEADER\n");
write(file1,buffer,strlen(buffer));

//Print #3, 9
//Print #3, "$LTSCALE"
//Print #3, 40
//Print #3, 1
sprintf(buffer,"9\n$LTSCALE\n40\n1\n");
write(file1,buffer,strlen(buffer));

//Print #3, 9
//Print #3, "$PDMODE"
//Print #3, 70
//Print #3, 2
sprintf(buffer,"9\n$PDMODE\n70\n2\n");
write(file1,buffer,strlen(buffer));

//Print #3, 9
//Print #3, "$PDSIZE"
//Print #3, 40
//Print #3, 0.25
sprintf(buffer,"9\n$PDSIZE\n40\n0.25\n");
write(file1,buffer,strlen(buffer));

//Print #3, 0
//Print #3, "ENDSEC"
sprintf(buffer,"0\nENDSEC\n");
write(file1,buffer,strlen(buffer));

//Print #3, 0
//Print #3, "SECTION"
//Print #3, 2
//Print #3, "TABLES"
sprintf(buffer,"0\nSECTION\n2\nTABLES\n");
write(file1,buffer,strlen(buffer));

//Print #3, 0
//Print #3, "TABLE"
//Print #3, 2
//Print #3, "LTYPE"
//Print #3, 70
//Numero dei tipi di Linea
//Print #3, 4
sprintf(buffer,"0\nTABLE\n2\nLTYPE\n70\n4\n");
write(file1,buffer,strlen(buffer));

//Print #3, 0
//Continua
//Print #3, "LTYPE"
//Print #3, 2
//Print #3, "CONTINUOUS"
//Print #3, 70
//Print #3, 64
//Print #3, 3
//Print #3, "Solid line"
//Print #3, 72
//Print #3, 65
//Print #3, 73
//Print #3, 0
//Print #3, 40
//Print #3, "0.0"
sprintf(buffer,"0\nLTYPE\n2\nCONTINUOUS\n70\n64\n3\nSolid line\n72\n65\n73\n0\n40\n0.0\n");
write(file1,buffer,strlen(buffer));

//Print #3, 0
//Hidden
//Print #3, "LTYPE"
//Print #3, 2
//Print #3, "HIDDEN"
//Print #3, 70
//Print #3, 64
//Print #3, 3
sprintf(buffer,"0\nLTYPE\n2\nHIDDEN\n70\n64\n3\n");
write(file1,buffer,strlen(buffer));
//Print #3, "- - - - - - - - - - - - - - - - - - - - - - -"
sprintf(buffer,"- - - - - - - - - - - - - - - - - - - - - - -\n");
write(file1,buffer,strlen(buffer));

//Print #3, 72
//Print #3, 65
//Print #3, 73
//Print #3, 2
//Print #3, 40
//Print #3, "0.375"
//Print #3, 49
//Print #3, "0.25"
//Print #3, 49
//Print #3, "-0.125"
sprintf(buffer,"72\n65\n73\n2\n40\n0.375\n49\n0.25\n49\n-0.125\n");
write(file1,buffer,strlen(buffer));
//Print #3, 0
//Dot
//Print #3, "LTYPE"
//Print #3, 2
//Print #3, "DOT"
//Print #3, 70
//Print #3, 64
//Print #3, 3
sprintf(buffer,"0\nLTYPE\n2\nDOT\n70\n64\n3\n");
write(file1,buffer,strlen(buffer));

//Print #3, ". . . . . . . . . . . . . . . . . . . . . . . ."
sprintf(buffer,". . . . . . . . . . . . . . . . . . . . . . . .\n");
write(file1,buffer,strlen(buffer));

//Print #3, 72
//Print #3, 65
//Print #3, 73
//Print #3, 2
//Print #3, 40
//Print #3, "0.25"
//Print #3, 49
//Print #3, "0.0"
//Print #3, 49
//Print #3, "-0.25"
sprintf(buffer,"72\n65\n73\n2\n40\n0.25\n49\n0.0\n49\n-0.25\n");
write(file1,buffer,strlen(buffer));

//Print #3, 0
//Center
//Print #3, "LTYPE"
//Print #3, 2
//Print #3, "CENTER"
//Print #3, 70
//Print #3, 64
//Print #3, 3
sprintf(buffer,"0\nLTYPE\n2\nCENTER\n70\n64\n3\n");
write(file1,buffer,strlen(buffer));
//Print #3, "____ _ ____ _ ____ _ ____ _ ____ _ ____ _ ____"
sprintf(buffer,"____ _ ____ _ ____ _ ____ _ ____ _ ____ _ ____\n");
write(file1,buffer,strlen(buffer));

//Print #3, 72
//Print #3, 65
//Print #3, 73
//Print #3, 4
//Print #3, 40
//Print #3, "2.0"
//Print #3, 49
//Print #3, "1.25"
//Print #3, 49
//Print #3, "-0.25"
//Print #3, 49
//Print #3, "0.25"
//Print #3, 49
//Print #3, "-0.25"
sprintf(buffer,"72\n65\n73\n4\n40\n2.0\n49\n1.25\n49\n-0.25\n49\n0.25\n49\n-0.25\n");
write(file1,buffer,strlen(buffer));

//Print #3, 0
//Print #3, "ENDTAB"
sprintf(buffer,"0\nENDTAB\n");
write(file1,buffer,strlen(buffer));

//DA QUI TIPI DI PIANO
//Print #3, 0
//Print #3, "TABLE"
//Print #3, 2
//Print #3, "LAYER"
//Print #3, 70
//numero dei piani
//Print #3, 21
sprintf(buffer,"0\nTABLE\n2\nLAYER\n70\n23\n");
write(file1,buffer,strlen(buffer));

//piano 0
//Print #3, 0
//Print #3, "LAYER"
//Print #3, 2
//Print #3, "0"
//Print #3, 70
//Print #3, 64
//Print #3, 62
//Print #3, 7
//Print #3, 6
//Print #3, "CONTINUOUS"
sprintf(buffer,"0\nLAYER\n2\n0\n70\n64\n62\n7\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

//ALMUCANT
//Print #3, 0
//Print #3, "LAYER"
//Print #3, 2
//Print #3, "ALMUCANT"
//Print #3, 70
//Print #3, 64
//'colore linea (4=ciano)
//Print #3, 62
//Print #3, 4
//'tipo linea
//Print #3, 6
//Print #3, "CONTINUOUS"
sprintf(buffer,"0\nLAYER\n2\nALMUCANT\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nAZIMUT\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nCORNICE\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nCROCEMEOR\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nD_PARETE\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nDIURNEMNS\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nDIURNEZOD\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nEQUINOZIALE\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nLEMNIA\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nLEMNID\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nMERIDIANA\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nMOTTO1\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nMOTTO2\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nORARIE\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nORARIEFUSO\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nORE1\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nORE2\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nORIZZONTE\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nPIEDEGNOMON\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nPIEDESTILO\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nSOLISTIZI\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

sprintf(buffer,"0\nLAYER\n2\nSUSTILARE\n70\n64\n62\n4\n6\nCONTINUOUS\n");
write(file1,buffer,strlen(buffer));

//fine dei piani
//Print #3, 0
//Print #3, "ENDTAB"
sprintf(buffer,"0\nENDTAB\n");
write(file1,buffer,strlen(buffer));
 
//Inizio stili di testo
//Print #3, 0
//Print #3, "TABLE"
//Print #3, 2
//Print #3, "STYLE"
//Print #3, 70
//numero degli stili
//Print #3, 7
sprintf(buffer,"0\nTABLE\n2\nSTYLE\n70\n7\n");
write(file1,buffer,strlen(buffer));
 
//'stile standard <------------------------------------------------
//Print #3, 0
//Print #3, "STYLE"
//Print #3, 2
//Print #3, "STANDARD"
sprintf(buffer,"0\nSTYLE\n2\nSTANDARD\n");
write(file1,buffer,strlen(buffer));
//Print #3, 70
//Print #3, 64
//Print #3, 40
//Print #3, "0.0"
//Print #3, 41
//Print #3, "1.0"
//Print #3, 50
//Print #3, "0.0"
sprintf(buffer,"70\n64\n40\n0.0\n41\n1.0\n50\n0.0\n");
write(file1,buffer,strlen(buffer));
//Print #3, 71
//Print #3, 0
//Print #3, 42
//Print #3, "0.25"
//Print #3, 3
//Print #3, "TXT.shx"
//Print #3, 4
//Print #3, ""
sprintf(buffer,"71\n0\n42\n0.25\n3\nTXT.shx\n4\n\n");
write(file1,buffer,strlen(buffer));

//stile scriptc <-----------------------------------------  
sprintf(buffer,"0\nSTYLE\n2\nSCRIPTC\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"70\n64\n40\n0.0\n41\n1.0\n50\n0.0\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"71\n0\n42\n0.25\n3\nSCRIPTC.SHX\n4\n\n");
write(file1,buffer,strlen(buffer));

//stile romans <---------------------------------------
sprintf(buffer,"0\nSTYLE\n2\nROMANS\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"70\n64\n40\n0.0\n41\n1.0\n50\n0.0\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"71\n0\n42\n0.25\n3\nROMANS.SHX\n4\n\n");
write(file1,buffer,strlen(buffer));

//stile romant <---------------------------------------
sprintf(buffer,"0\nSTYLE\n2\nROMANT\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"70\n64\n40\n0.0\n41\n1.0\n50\n0.0\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"71\n0\n42\n0.25\n3\nROMANT.SHX\n4\n\n");
write(file1,buffer,strlen(buffer));

//stile italict <---------------------------------------
sprintf(buffer,"0\nSTYLE\n2\nITALICT\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"70\n64\n40\n0.0\n41\n1.0\n50\n0.0\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"71\n0\n42\n0.25\n3\nITALICT.SHX\n4\n\n");
write(file1,buffer,strlen(buffer));

//stile gothici <---------------------------------------
sprintf(buffer,"0\nSTYLE\n2\nGOTHICI\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"70\n64\n40\n0.0\n41\n1.0\n50\n0.0\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"71\n0\n42\n0.25\n3\nGOTHICI.SHX\n4\n\n");
write(file1,buffer,strlen(buffer));

// stile zodiac <---------------------------------------
sprintf(buffer,"0\nSTYLE\n2\nZODIAC\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"70\n64\n40\n0.0\n41\n1.0\n50\n0.0\n");
write(file1,buffer,strlen(buffer));
sprintf(buffer,"71\n0\n42\n0.25\n3\nSYASTRO.SHX\n4\n\n");
write(file1,buffer,strlen(buffer));

//Fine dei tipi di stile di testo
//Print #3, 0
//Print #3, "ENDTAB"
sprintf(buffer,"0\nENDTAB\n");
write(file1,buffer,strlen(buffer));

//Print #3, 0
//Print #3, "ENDSEC"
sprintf(buffer,"0\nENDSEC\n");
write(file1,buffer,strlen(buffer));


//Print #3, 0
//Print #3, "SECTION"
//Print #3, 2
//Print #3, "ENTITIES"
sprintf(buffer,"0\nSECTION\n2\nENTITIES\n");
write(file1,buffer,strlen(buffer));
}


main(argc,argv)
int argc;
char *argv[];
{
 
   strcpy(nfilei,argv[1]);
   strcat(nfilei,".out");
   if ((fp = fopen(nfilei,"r")) == NULL)
      {
      printf("-   FILE DI INGRESSO NON TROVATO   -");
      exit(1);
      }

   strcpy(nfileo,argv[1]);
   strcat(nfileo,".dxf");
   
   file1 = open(nfileo,O_WRONLY|O_CREAT, 666);
   if (file1 == -1) puts("FILE DI USCITA NON TROVATO"), exit(1);

   Autocad();

   for(;;)
      {
      if(fscanf(fp,"%s%f%f%s",buffer,&x,&y,layer) == EOF)
        {printf("FINE FILE");
         write(file1,endbuf,strlen(endbuf));
         exit(1);
        }

      sprintf(buffer,"POLYLINE\n  8\n%s\n 66\n     1\n  0\n",
                     layer);
      write(file1,buffer,strlen(buffer));
      sprintf(buffer,"VERTEX\n  8\n%s\n 10\n%f\n 20\n %f\n  0\n",
                     layer,x,y);
      write(file1,buffer,strlen(buffer));

      for(;;)
         {
         if(fscanf(fp,"%s%f%f%s",buffer,&x,&y,layer) == EOF) {printf("FINE FILE"); exit(1); }
         if ( buffer[0] == '*' ) break;
         sprintf(buffer,"VERTEX\n  8\n%s\n 10\n%f\n 20\n %f\n  0\n",
                        layer,x,y);
         write(file1,buffer,strlen(buffer));
         }

      sprintf(buffer,"SEQEND\n  8\n%s\n  0\n",
                     layer);
      write(file1,buffer,strlen(buffer));
      }
   fclose(fp);
   close(file1);
}



