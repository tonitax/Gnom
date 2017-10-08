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

main(argc,argv)
int argc;
char *argv[];
{
char nfilei[20];
char nfileo[20];
char buffer[80];
char layer[12];
int  file1;
float x,y;


   strcpy(nfilei,argv[1]);
   strcat(nfilei,".out");
   if ((fp = fopen(nfilei,"r")) == NULL)
      {
      printf("-   FILE DI INGRESSO NON TROVATO   -");
      exit(1);
      }

   strcpy(nfileo,argv[1]);
   strcat(nfileo,".dxf");
   file1 = open(nfileo,O_APPEND|O_TEXT|O_RDWR);
   if (file1 == -1) puts("FILE DI USCITA NON TROVATO"), exit(1);

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
}



