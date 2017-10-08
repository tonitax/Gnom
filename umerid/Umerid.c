//PROGRAMMA APERTO PER IL CALCOLO DEGLI OROLOGI SOLARI 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "Utilities.h"

extern  MATRIX rm;

#define   DIM   365   /* Numero di punti per una lemniscata oraria */

FILE    *fp_prm, *fp_out;

typedef  struct ARES{
                double a1;
                double a2;
                double a3;
                double a4;
                };


double   hstepo;
double   hstepl;
double   diustep;
double   almmax;
double   almstep;
double   azmax;
double   azstep;
double   mextx;
double   mexty;
double   Xs,Ys,Zs;

int      zona=0;
int      flatland  = 0;   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< FLATLAND = 0 !!!!
char     datatype[20];

double delta1,hora1;
double delta2,hora2;
double deltaM,horaM;

FLOAT g;
FLOAT c;
FLOAT R;
FLOAT nr;
FLOAT elev_n;

extern FLOAT  (*func_array[])(FLOAT *xvect);
extern FLOAT  xvect[];

int lemni_flag,
    solistizi_flag,
    diurnezod_flag,
    diurnemns_flag,
    orarie_flag,
    orariefuso_flag,
    azimalmu_flag;

double xr;          /* Frazione del raggio per le cyl e le con */
double hrr;         /* rapporto altezza raggio per le superfici coniche */


double	f;			/* fattore di scala */
double	xv;			/* x vertice catenaria */ 
double	yv;			/* y vertice catenaria */

double  a1,b1,c1;   /* generici parametri */
double  a2,b2,c2;   /* generici parametri */
double  a3,b3,c3;   /* generici parametri */

double	d1;			/* distanza filo 1 */
double  d2;			/* distanza filo 2 */

int tipo;

double phi;        /* latitudine */
double deltalamda; /* delta longitudine dal meridiano standard (in ore)*/
double d;          /* declinazione del quadro */
double inc;        /* inclinazione del quadro */
double sigma;      /* angolo tra la sustilare e la retta di massima pendenza */
double epsilon;    /* elevazione dello stilo */
double tisigma;    /* ora sustilare */
double deltat;     /* distanza temporale (espressa in gradi) dalla tisigma */
double omega;      /* angolo delle linee orarie rispetto alla sustilare */
double beta;       /* angolo tra lo stilo e la sua ombra */
double B;          /* lunghezza ombra dello stilo */

double cosphi, sinphi, cosd, sind, cosdelta, sindelta, coshora, sinhora, sininc, cosinc;
double rx,ry,rz;


/* equazione del tempo corrispondenti alle date sulle quali vengono calcolati i punti*/
double epsm[] = {
 0.030463, 0.022206, 0.013949, 0.005701,-0.002531,-0.010735,
-0.018903,-0.027027,-0.035097,-0.043104,-0.051039,
-0.058876,-0.066644,-0.074315,-0.081881,-0.089335,-0.096668,-0.103873,-0.110942,-0.117869,-0.124646,
-0.131267,-0.137726,-0.144016,-0.150132,-0.156068,-0.161818,-0.167379,-0.172744,-0.177911,-0.182874,
-0.187630,-0.192175,-0.196507,-0.200622,-0.204518,-0.208193,-0.211645,-0.214872,-0.217873,-0.220646,
-0.223192,-0.225510,-0.227600,-0.229462,-0.231096,-0.232504,-0.233686,-0.234643,-0.235378,-0.235891,
-0.236186,-0.236264,-0.236128,-0.235780,-0.235224,-0.234463,-0.233499,-0.232338,-0.230981,-0.229434,
-0.227701,-0.225784,-0.223690,-0.221422,-0.218985,-0.216383,-0.213623,-0.210708,-0.207643,-0.203610,
-0.200229,-0.196714,-0.193073,-0.189311,-0.185432,-0.181442,-0.177348,-0.173155,-0.168867,-0.164492,
-0.160035,-0.155500,-0.150895,-0.146225,-0.141495,-0.136712,-0.131880,-0.127006,-0.122095,-0.117153,
-0.112186,-0.107199,-0.102197,-0.097187,-0.092174,-0.087163,-0.082160,-0.077170,-0.072199,-0.067251,
-0.062333,-0.057448,-0.052604,-0.047804,-0.043053,-0.038357,-0.033721,-0.029148,-0.024645,-0.020216,
-0.015865,-0.011598,-0.007417,-0.003328, 0.000665, 0.004557, 0.008346, 0.012026, 0.015594, 0.019047,
 0.022380, 0.025591, 0.028675, 0.031630, 0.034453, 0.037140, 0.039689, 0.042098, 0.044363, 0.046483,
 0.048455, 0.050277, 0.051949, 0.053467, 0.054831, 0.056039, 0.057091, 0.057986, 0.058722, 0.059300,
 0.059720, 0.059981, 0.060084, 0.060029, 0.059817, 0.059449, 0.058925, 0.058248, 0.057419, 0.056440,
 0.055312, 0.054038, 0.052621, 0.051064, 0.049368, 0.047538, 0.045576, 0.043487, 0.041274, 0.038941,
 0.036492, 0.033932, 0.031266, 0.028498, 0.025632, 0.022675, 0.019631, 0.016506, 0.013305, 0.010035,
 0.006700, 0.003308,-0.000137,-0.003627,-0.007157,-0.010721,-0.014311,-0.017922,-0.021547,-0.025179,
-0.028813,-0.032440,-0.036055,-0.039652,-0.043224,-0.046763,-0.050265,-0.053721,-0.057127,-0.060476,
-0.063762,-0.066978,-0.070119,-0.073178,-0.076151,-0.079031,-0.081814,-0.084493,-0.087065,-0.089523,
-0.091863,-0.094080,-0.096171,-0.098131,-0.099956,-0.101641,-0.103185,-0.104583,-0.105831,-0.106928,
-0.107871,-0.108656,-0.109282,-0.109747,-0.110049,-0.110186,-0.110157,-0.109962,-0.109598,-0.109066,
-0.108365,-0.107494,-0.106455,-0.105246,-0.103869,-0.102324,-0.100612,-0.098734,-0.096691,-0.094485,
-0.092118,-0.089590,-0.086905,-0.084064,-0.081069,-0.077924,-0.074630,-0.071191,-0.067609,-0.063888,
-0.060031,-0.056040,-0.051921,-0.047675,-0.043307,-0.038821,-0.034221,-0.029510,-0.024693,-0.019774,
-0.014757,-0.009647,-0.004447, 0.000836, 0.006199, 0.011638, 0.017147, 0.022721, 0.028355, 0.034046,
 0.039787, 0.045574, 0.051401, 0.057264, 0.063156, 0.069074, 0.075011, 0.080963, 0.086924, 0.092888,
 0.098850, 0.104805, 0.110746, 0.116670, 0.122569, 0.128439, 0.134273, 0.140067, 0.145814, 0.151508,
 0.157145, 0.162718, 0.168221, 0.173650, 0.178997, 0.184258, 0.189427, 0.194498, 0.199465, 0.204323,
 0.209065, 0.213688, 0.218184, 0.222548, 0.226776, 0.230860, 0.234797, 0.238581, 0.242206, 0.245668,
 0.248962, 0.252081, 0.255023, 0.257782, 0.260353, 0.262732, 0.264915, 0.266898, 0.268676, 0.270247,
 0.271605, 0.272748, 0.273673, 0.274376, 0.274856, 0.275108, 0.275131, 0.274922, 0.274480, 0.273804,
 0.272891, 0.271741, 0.270352, 0.268725, 0.266859, 0.264754, 0.262411, 0.259829, 0.257011, 0.253956,
 0.250668, 0.247147, 0.243396, 0.239418, 0.235214, 0.230789, 0.226146, 0.221288, 0.216220, 0.210946,
 0.205471, 0.199799, 0.193936, 0.187888, 0.181660, 0.175258, 0.168689, 0.161960, 0.155077, 0.148048,
 0.140879, 0.133579, 0.126155, 0.118615, 0.110967, 0.103220, 0.095382, 0.087462, 0.079468, 0.071410,
 0.063296, 0.055135, 0.046936, 0.038709
};


/* declinazioni del sole corrispondenti alle date sulle quali vengono calcolati i punti*/
double delta[] = {
-23.432321,-23.428992,-23.417819,-23.398804,-23.371955,-23.337281,
-23.294800,-23.244529,-23.186493,-23.120718,-23.047237,
-22.966771,-22.878043,-22.781725,-22.677866,-22.566516,-22.447729,-22.321563,-22.188079,-22.047343,-21.899421,
-21.744385,-21.582309,-21.413269,-21.237347,-21.054623,-20.865184,-20.669116,-20.466511,-20.257459,-20.042056,
-19.820398,-19.592582,-19.358710,-19.118883,-18.873204,-18.621779,-18.364713,-18.102114,-17.834090,-17.560752,
-17.282209,-16.998574,-16.709959,-16.416477,-16.118240,-15.815365,-15.507964,-15.196154,-14.880049,-14.559765,
-14.235417,-13.907122,-13.574995,-13.239152,-12.899708,-12.556780,-12.210483,-11.860933,-11.508243,-11.152530,
-10.793908,-10.432491,-10.068392, -9.701726, -9.332606, -8.961143,-8.587450, -8.211640, -7.833823, -7.358904,
 -6.976975, -6.593399, -6.208283, -5.821736, -5.433867, -5.044783,-4.654591, -4.263398, -3.871310, -3.478433,
 -3.084871, -2.690730, -2.296113, -1.901125, -1.505867, -1.110444, -0.714957, -0.319508,  0.075801,  0.470869,
  0.865596,  1.259882,  1.653626,  2.046729,  2.439093,  2.830618,  3.221206,  3.610758,  3.999178,  4.386367,
  4.772228,  5.156665,  5.539580,  5.920878,  6.300462,  6.678236,  7.054105,  7.427974,  7.799746,  8.169328,
  8.536625,  8.901542,  9.263984,  9.623859,  9.981072, 10.335529, 10.687138, 11.035805, 11.381438, 11.723943,
 12.063230, 12.399205, 12.731778, 13.060857, 13.386350, 13.708168, 14.026219, 14.340415, 14.650666, 14.956883,
 15.258977, 15.556860, 15.850445, 16.139646, 16.424375, 16.704548, 16.980079, 17.250884, 17.516881, 17.777986,
 18.034118, 18.285195, 18.531140, 18.771872, 19.007313, 19.237389, 19.462022, 19.681139, 19.894667, 20.102536,
 20.304674, 20.501013, 20.691486, 20.876028, 21.054575, 21.227065, 21.393438, 21.553635, 21.707601, 21.855279,
 21.996619, 22.131569, 22.260081, 22.382109, 22.497609, 22.606540, 22.708863, 22.804540, 22.893537, 22.975822,
 23.051366, 23.120143, 23.182126, 23.237296, 23.285633, 23.327121, 23.361745, 23.389496, 23.410364, 23.424345,
 23.431435, 23.431634, 23.424946, 23.411376, 23.390931, 23.363623, 23.329465, 23.288474, 23.240668, 23.186069,
 23.124701, 23.056590, 22.981767, 22.900262, 22.812110, 22.717347, 22.616013, 22.508147, 22.393795, 22.273001,
 22.145814, 22.012283, 21.872460, 21.726399, 21.574155, 21.415788, 21.251355, 21.080918, 20.904540, 20.722286,
 20.534221, 20.340412, 20.140929, 19.935841, 19.725221, 19.509140, 19.287673, 19.060894, 18.828880, 18.591707,
 18.349453, 18.102198, 17.850020, 17.593000, 17.331219, 17.064760, 16.793703, 16.518133, 16.238133, 15.953787,
 15.665180, 15.372396, 15.075521, 14.774641, 14.469841, 14.161209, 13.848831, 13.532793, 13.213184, 12.890090,
 12.563600, 12.233800, 11.900780, 11.564626, 11.225428, 10.883274, 10.538252, 10.190451,  9.839960,  9.486868,
  9.131263,  8.773236,  8.412874,  8.050268,  7.685507,  7.318680,  6.949878,  6.579190,  6.206705,  5.832515,
  5.456710,  5.079379,  4.700613,  4.320504,  3.939142,  3.556618,  3.173025,  2.788453,  2.402994,  2.016741,
  1.629786,  1.242222,  0.854143,  0.465640,  0.076809, -0.312257, -0.701463, -1.090714, -1.479916, -1.868971,
 -2.257785, -2.646261, -3.034300, -3.421807, -3.808683, -4.194829, -4.580147, -4.964536, -5.347897, -5.730129,
 -6.111131, -6.490802, -6.869038, -7.245737, -7.620795, -7.994109, -8.365574, -8.735085, -9.102536, -9.467820,
 -9.830832,-10.191464,-10.549607,-10.905154,-11.257996,-11.608022,-11.955125,-12.299192,-12.640114,-12.977780,
-13.312078,-13.642896,-13.970123,-14.293647,-14.613355,-14.929135,-15.240874,-15.548459,-15.851779,-16.150720,
-16.445171,-16.735019,-17.020153,-17.300461,-17.575833,-17.846157,-18.111325,-18.371227,-18.625755,-18.874802,
-19.118261,-19.356027,-19.587995,-19.814065,-20.034133,-20.248100,-20.455868,-20.657341,-20.852424,-21.041024,
-21.223051,-21.398417,-21.567036,-21.728823,-21.883699,-22.031585,-22.172406,-22.306088,-22.432563,-22.551764,
-22.663628,-22.768094,-22.865107,-22.954613,-23.036562,-23.110910,-23.177614,-23.236636,-23.287942,-23.331501,
-23.367287,-23.395279,-23.415457,-23.427808
				};

/* declinazioni zodiacali */
double deltaz[] = {-23.26, -20.0, -11.30, 0.0, 11.30, 20.0, 23.26};

/* declinazioni mensili */
double deltam[] = {-23.00, -17.09, -7.33,  4.34,  15.06,  22.04,
                    23.06,  18.00,  8.16, -3.13, -14.27, -21.49};

int j,k,m,n;
double x,y,t;
double orai,orau,ora;
char layer[20];

double rad_to_gra(alfa)   /* conversione radianti-gradi */
double alfa;
{
  alfa = (180.0/PI)*alfa;
  return(alfa);
}

double gra_to_rad(alfa)   /* conversione gradi-radianti */
double alfa;
{
  alfa = (PI/180.0)*alfa;
  return(alfa);
}

double minsec_to_ore(minsec)
double minsec;
{
double a,b,c;
       a = fabs(minsec);
       b = floor(a);
       c = a - b;                /* parte decimale (secondi) */
       a = a - c;                /* parte intera   (minuti)  */
       a = a*60.0 + 100*c;       /* minsec espresso in secondi */
       if (minsec < 0) a = -a;   /* riattribuisce il segno */
       a /= 3600.0;              /* conv. in ore */
       return(a);
}

double grapri_to_gradec(grapri)
double grapri;
{
double a,b,c;
       a = fabs(grapri);
       b = floor(a);
       c = a - b;                /* parte decimale (primi) */
       a = a - c;                /* parte intera   (gradi) */
       a = a*60.0 + 100*c;       /* grapri espresso in primi */
       if (grapri < 0) a = -a;   /* riattribuisce il segno */
       a /= 60.0;
       return(a);
}

void file_open(nome)
char *nome;
{
char nome_file[20];

   strcpy(nome_file,nome) ;
   strcat(nome_file,".prm");
   fp_prm = fopen(nome_file,"rt");
   if (fp_prm == NULL)
      {
      printf("ERRORE nella apertura di '%s' \n",nome_file);
      exit(1);
      }

   strcpy(nome_file,nome);
   strcat(nome_file,".out");
   fp_out = fopen(nome_file,"wt");
   if (fp_out == NULL)
      {
      printf("ERRORE nella apertura di '%s' \n",nome_file);
      exit(1);
      }
}

void init(nome)
char *nome;
{
char msg[180];

    strcpy(msg,nome);

    /* LETTURA PARAMETRI DA FILE */
    file_open(msg);

    fscanf(fp_prm,"%lf%s",&phi,msg);
    printf(" 1: %s\t%.3lf\n",msg,phi);

    fscanf(fp_prm,"%lf%s",&deltalamda,msg);
    printf(" 2: %s\t%.3lf\n",msg,deltalamda);

    fscanf(fp_prm,"%lf%s",&d,msg);
    printf(" 3: %s\t%.3lf\n",msg,d);

    fscanf(fp_prm,"%lf%s",&inc,msg);
    printf(" 4: %s\t%.3lf\n",msg,inc);

    fscanf(fp_prm,"%lf%s",&hstepo,msg);
    printf(" 5: %s\t%.3lf\n",msg,hstepo);

    fscanf(fp_prm,"%lf%s",&hstepl,msg);
    printf(" 6: %s\t%.3lf\n",msg,hstepl);

    fscanf(fp_prm,"%lf%s",&diustep,msg);
    printf(" 7: %s\t%.3lf\n",msg,diustep);

    fscanf(fp_prm,"%lf%s",&almmax,msg);
    printf(" 8: %s\t%.3lf\n",msg,almmax);

    fscanf(fp_prm,"%lf%s",&almstep,msg);
    printf(" 9: %s\t%.3lf\n",msg,almstep);

    fscanf(fp_prm,"%lf%s",&azmax,msg);
    printf("10: %s\t%.3lf\n",msg,azmax);

    fscanf(fp_prm,"%lf%s",&azstep,msg);
    printf("11: %s\t%.3lf\n",msg,azstep);

    fscanf(fp_prm,"%lf%s",&mextx,msg);
    printf("12: %s\t%.3lf\n",msg,mextx);

    fscanf(fp_prm,"%lf%s",&mexty,msg);
    printf("13: %s\t%.3lf\n",msg,mexty);

    fscanf(fp_prm,"%lf%s",&orai,msg);
    printf("14: %s\t%.3lf\n",msg,orai);

    fscanf(fp_prm,"%lf%s",&orau,msg);
    printf("15: %s\t%.3lf\n",msg,orau);

    fscanf(fp_prm,"%d%s",&lemni_flag,msg);
    printf("16: %s=%d\n",msg,lemni_flag);

    fscanf(fp_prm,"%d%s",&solistizi_flag,msg);
    printf("17: %s=%d\n",msg,solistizi_flag);

	fscanf(fp_prm,"%d%s",&diurnezod_flag,msg);
    printf("18: %s=%d\n",msg,diurnezod_flag);
  
	fscanf(fp_prm,"%d%s",&diurnemns_flag,msg);
    printf("19: %s=%d\n",msg,diurnemns_flag);
 
	fscanf(fp_prm,"%d%s",&orarie_flag,msg);
    printf("20: %s=%d\n",msg,orarie_flag);
 
	fscanf(fp_prm,"%d%s",&orariefuso_flag,msg); 
    printf("21: %s=%d\n",msg,orariefuso_flag);
 
	fscanf(fp_prm,"%d%s",&azimalmu_flag,msg);
    printf("22: %s=%d\n",msg,azimalmu_flag);

    fscanf(fp_prm,"%d%s",&tipo,msg);
    printf("23: %s=%d\n",msg,tipo);

    fscanf(fp_prm,"%lf%s",&a1,msg);
    printf("31: %s=%lf\n",msg,a1);

    fscanf(fp_prm,"%lf%s",&b1,msg);
    printf("32: %s=%lf\n",msg,b1);

    fscanf(fp_prm,"%lf%s",&c1,msg);
    printf("33: %s=%lf\n",msg,c1);

	printf("FINE LETTURA PARAMETRI\n");

/***
    //conico - cilindriche
	fscanf(fp_prm,"%lf%s",&xr,msg);
    printf("24: %s=%lf\n",msg,xr);

    fscanf(fp_prm,"%lf%s",&hrr,msg);
    printf("25: %s=%lf\n",msg,hrr);


    
	//bifilari piane
    fscanf(fp_prm,"%lf%s",&d1,msg);
    printf("26: %s=%lf\n",msg,d1);
    
    fscanf(fp_prm,"%lf%s",&d2,msg);
    printf("27: %s=%lf\n",msg,d2);

    fscanf(fp_prm,"%lf%s",&f,msg);
    printf("28: %s=%lf\n",msg,f);

    fscanf(fp_prm,"%lf%s",&xv,msg);
    printf("29: %s=%lf\n",msg,xv);

    fscanf(fp_prm,"%lf%s",&yv,msg);
    printf("30: %s=%lf\n",msg,yv);
	
    //generiche
    fscanf(fp_prm,"%lf%s",&a1,msg);
    printf("31: %s=%lf\n",msg,a1);

    fscanf(fp_prm,"%lf%s",&b1,msg);
    printf("32: %s=%lf\n",msg,b1);

    fscanf(fp_prm,"%lf%s",&c1,msg);
    printf("33: %s=%lf\n",msg,c1);

    fscanf(fp_prm,"%lf%s",&a2,msg);
    printf("34: %s=%lf\n",msg,a2);

    fscanf(fp_prm,"%lf%s",&b2,msg);
    printf("35: %s=%lf\n",msg,b2);

    fscanf(fp_prm,"%lf%s",&c2,msg);
    printf("36: %s=%lf\n",msg,c2);

    fscanf(fp_prm,"%lf%s",&a3,msg);
    printf("37: %s=%lf\n",msg,a3);

    fscanf(fp_prm,"%lf%s",&b3,msg);
    printf("38: %s=%lf\n",msg,b3);

    fscanf(fp_prm,"%lf%s",&c3,msg);
    printf("39: %s=%lf\n",msg,c3);
****/

	puts("\nPremi un tasto per continuare\n"); getch();

  	deltalamda /= 15.0;                       /* conv. in ore */

    phi = gra_to_rad(phi);

    d   = gra_to_rad(d);

	inc   = gra_to_rad(inc);

    /* Calcolo elevazione dello stilo */
    x = sin(inc)*sin(phi) - cos(inc)*cos(phi)*cos(d);
    x = asin(x);
    x = rad_to_gra(x);

    printf("\n\n(Elevazione stilo = %lf)\n",x);
    epsilon = gra_to_rad(x);

    /* Calcolo dell'angolo tra sustilare e verticale */
    x = sin(d)*cos(phi)/cos(epsilon);
    x = asin(x);
    x = rad_to_gra(x);

    printf("\n\n(Angolo tra sustilare e verticale = %lf)\n",x);
    sigma = gra_to_rad(x);

    /* Calcolo dell'ora sustilare */
    x = sin(d)*cos(inc)/cos(epsilon);
    x = asin(x);
    x = rad_to_gra(x);

    x = 180 + x;
//    x = 180 - x;

    x /= 15.0;

    printf("\n\n(Ora sustilare = %lf)\n",x);
    tisigma = x;

}


void compute_ray(double delta,double hora)
{
	cosphi = cos(phi);
	sinphi = sin(phi);
	cosd   = cos(d);
	sind   = sin(d);
	cosdelta = cos(delta);
	sindelta = sin(delta);
	coshora = cos(hora);
	sinhora = sin(hora);
	sininc = sin(inc);
	cosinc = cos(inc);
	
	rx=cosd*cosdelta*sinhora
		+cosphi*sind*sindelta
		-coshora*cosdelta*sind*sinphi;

	ry=-coshora*cosinc*cosdelta*cosphi
		-cosd*sininc*sindelta*cosphi
		+cosdelta*sind*sinhora*sininc
		+cosd*coshora*cosdelta*sininc*sinphi
		-cosinc*sindelta*sinphi;

	rz=-cosinc*cosdelta*sind*sinhora
		-coshora*cosdelta*cosphi*sininc
		+cosd*cosinc*cosphi*sindelta
		-cosd*coshora*cosinc*cosdelta*sinphi
		-sininc*sindelta*sinphi;

    return;
}


void compute_ray_1(double delta,double hora)
{
VECTOR r0, r1, r2, r3, r4, r5;
	
    r0[0] =   0;
    r0[1] =  -1;
    r0[2] =   0;

	Rotation(X, -delta, &r0, &r1);
	Rotation(Z, hora,   &r1, &r2);
	Rotation(X, phi,    &r2, &r3);
	Rotation(Y, d,      &r3, &r4);
	Rotation(X, inc,    &r4, &r5);

	rx = r5[0];
	ry = r5[1];
	rz = r5[2];

    return;
}

void compute_ray_2(double delta,double hora)
{
VECTOR r0, r1, r2, r3, r4, r5, ri;
	
    r0[0] =   0;                    
    r0[1] =  -1;
    r0[2] =   0;

	Rotation(X, -delta, &r0, &r1);
	Rotation(Z, hora,   &r1, &r2);
	Rotation(X, phi,    &r2, &r3);
	Rotation(Y, d,      &r3, &r4);

	Rotation(X, inc,    &r4, &ri);
	Rotation(Z, -sigma, &ri, &r5);

	
	rx = r5[0];
	ry = r5[1];
	rz = r5[2];

    return;
}


void compute_ray_3(double delta,double hora)
{
VECTOR r0, r1, r2;
VECTOR p0, p1, p2, p;
double sh2, ch2, scalar;

/**
	cosphi = cos(phi);
	sinphi = sin(phi);
	cosd   = cos(d);
	sind   = sin(d);
	cosdelta = cos(delta);
	sindelta = sin(delta);
	coshora = cos(hora);
	sinhora = sin(hora);
	sininc = sin(inc);
	cosinc = cos(inc);
**/
	

    r0[0] =   0;				//Posiziona il versore raggio solare a H = 0 e delta e phi
    r0[1] =  -1;
    r0[2] =   0;


	Rotation(X, phi-delta, &r0, &r1);
	Rotation(Y, d,   &r1, &r2);
	Rotation(X, inc, &r2, &r0);

    p0[0] =   0;				//Posiziona il versore asse polare a H = 0 e delta e phi
    p0[1] =   0;
    p0[2] =  -1;

	Rotation(X, phi, &p0, &p1);
	Rotation(Y, d,   &p1, &p2);
	Rotation(X, inc, &p2, &p);

	//ma si posso assegnare anche direttamente (ridefinisco rh0 e p per verifica):
//	r0[0] = -sind*sin(phi - delta);
//	r0[1] = -cosinc*cos(phi-delta)+cosd*sininc*sin(phi-delta);
//  r0[2] = -sininc*cos(phi-delta)-cosd*cosinc*sin(phi-delta);

//	p[0] = -sind*cos(phi);
//	p[1] = cosinc*sin(phi)+cosd*sininc*cos(phi);
//  p[2] = sininc*sin(phi)-cosd*cosinc*cos(phi);


	sh2 = sin(-hora/2);
	ch2 = cos(-hora/2);

	p[0] *= sh2;       //Attenua il versore asse polare  in funzione di H
	p[1] *= sh2;
	p[2] *= sh2;


	scalar = p[0]*r0[0] + p[1]*r0[1] + p[2]*r0[2];


    //    componente w1_______ w2_____________   w3_____________________________  
	rx = (2*ch2*ch2 - 1)*r0[0] + 2*scalar*p[0] + 2*ch2*(p[1]*r0[2] - p[2]*r0[1]);
	ry = (2*ch2*ch2 - 1)*r0[1] + 2*scalar*p[1] + 2*ch2*(p[2]*r0[0] - p[0]*r0[2]);
	rz = (2*ch2*ch2 - 1)*r0[2] + 2*scalar*p[2] + 2*ch2*(p[0]*r0[1] - p[1]*r0[0]);

    return;
}



void compute_ray_4(double delta,double hora)
{
VECTOR r0, r1, r2;
VECTOR p0, p1, p2, p;
double Cos,cosx,Sin,sinx,omc;

/**
	cosphi = cos(phi);
	sinphi = sin(phi);
	cosd   = cos(d);
	sind   = sin(d);
	cosdelta = cos(delta);
	sindelta = sin(delta);
	coshora = cos(hora);
	sinhora = sin(hora);
	sininc = sin(inc);
	cosinc = cos(inc);
**/

    r0[0] =   0;				//Posiziona il versore raggio solare a H = 0 e delta e phi
    r0[1] =  -1;
    r0[2] =   0;


	Rotation(X, phi-delta, &r0, &r1);
	Rotation(Y, d,   &r1, &r2);
	Rotation(X, inc, &r2, &r0);

    p0[0] =   0;				//Posiziona il versore asse polare a H = 0 e delta e phi
    p0[1] =   0;
    p0[2] =  -1;

	Rotation(X, phi, &p0, &p1);
	Rotation(Y, d,   &p1, &p2);
	Rotation(X, inc, &p2, &p);

	//ma si posso assegnare anche direttamente (ridefinisco rh0 e p per verifica):
//	r0[0] = -sind*sin(phi - delta);
//	r0[1] = -cosinc*cos(phi-delta)+cosd*sininc*sin(phi-delta);
//  r0[2] = -sininc*cos(phi-delta)-cosd*cosinc*sin(phi-delta);

//	p[0] = -sind*cos(phi);
//	p[1] = cosinc*sin(phi)+cosd*sininc*cos(phi);
//  p[2] = sininc*sin(phi)-cosd*cosinc*cos(phi);


	Cos = cos(hora);
	Sin = sin(hora);

	cosx = Cos;
	sinx = Sin;
	omc = 1-Cos;

/**
transform->matrix = R

> >   transform->matrix[0][0] = V1[X] * V1[X] * omc + cosx;
> >   transform->matrix[0][1] = V1[X] * V1[Y] * omc + V1[Z] * sinx;
> >   transform->matrix[0][2] = V1[X] * V1[Z] * omc - V1[Y] * sinx;
> >
> >   transform->matrix[1][0] = V1[X] * V1[Y] * omc - V1[Z] * sinx;
> >   transform->matrix[1][1] = V1[Y] * V1[Y] * omc + cosx;
> >   transform->matrix[1][2] = V1[Y] * V1[Z] * omc + V1[X] * sinx;
> >
> >   transform->matrix[2][0] = V1[X] * V1[Z] * omc + V1[Y] * sinx;
> >   transform->matrix[2][1] = V1[Y] * V1[Z] * omc - V1[X] * sinx;
> >   transform->matrix[2][2] = V1[Z] * V1[Z] * omc + cosx;
**/

	rm[0][0] = p[0]*p[0]*omc + cosx;
	rm[0][1] = p[0]*p[1]*omc + p[2] * sinx;
	rm[0][2] = p[0]*p[2]*omc - p[1] * sinx;
	
	rm[1][0] = p[0]*p[1]*omc - p[2] * sinx;
	rm[1][1] = p[1]*p[1]*omc + cosx;
	rm[1][2] = p[1]*p[2]*omc + p[0] * sinx;

	rm[2][0] = p[0]*p[2]*omc + p[1] * sinx;
	rm[2][1] = p[1]*p[2]*omc - p[0] * sinx;
	rm[2][2] = p[2]*p[2]*omc + cosx;

	Rotation(A, hora, &r0, &r1);
	
	rx = r1[0];
	ry = r1[1];
	rz = r1[2];

    return;
}

void compute_ray_5(double delta,double hora)
{
VECTOR r0, r1, r2;
VECTOR p0, p1, p2, p;
double s,Cos,cosx,Sin,sinx,omc;

/**
	cosphi = cos(phi);
	sinphi = sin(phi);
	cosd   = cos(d);
	sind   = sin(d);
	cosdelta = cos(delta);
	sindelta = sin(delta);
	coshora = cos(hora);
	sinhora = sin(hora);
	sininc = sin(inc);
	cosinc = cos(inc);
**/

    r0[0] =   0;				//Posiziona il versore raggio solare a H = 0 e delta = phi = 0 
    r0[1] =  -1;
    r0[2] =   0;


	Rotation(X, phi-delta, &r0, &r1);
	Rotation(Y, d,   &r1, &r2);
	Rotation(X, inc, &r2, &r0);

    p0[0] =   0;				//Posiziona il versore asse polare a H = 0 e delta e phi
    p0[1] =   0;
    p0[2] =  -1;

	Rotation(X, phi, &p0, &p1);
	Rotation(Y, d,   &p1, &p2);
	Rotation(X, inc, &p2, &p);

	//ma si posso assegnare anche direttamente (ridefinisco rh0 e p per verifica):
//	r0[0] = -sind*sin(phi - delta);
//	r0[1] = -cosinc*cos(phi-delta)+cosd*sininc*sin(phi-delta);
//  r0[2] = -sininc*cos(phi-delta)-cosd*cosinc*sin(phi-delta);

//	p[0] = -sind*cos(phi);
//	p[1] = cosinc*sin(phi)+cosd*sininc*cos(phi);
//  p[2] = sininc*sin(phi)-cosd*cosinc*cos(phi);


	Cos = cos(hora);
	Sin = sin(hora);

	cosx = Cos;
	sinx = Sin;
	omc = 1-Cos;
	s = r0[0]*p[0]+r0[1]*p[1]+r0[2]*p[2];

    rx = cosx*r0[0]+omc*s*p[0]+sinx*(r0[1]*p[2]-r0[2]*p[1]);
    ry = cosx*r0[1]+omc*s*p[1]+sinx*(r0[2]*p[0]-r0[0]*p[2]);
    rz = cosx*r0[2]+omc*s*p[2]+sinx*(r0[0]*p[1]-r0[1]*p[0]);

    return;
}


void compute_ray_monaco(double delta,double hora)
{
VECTOR r0, r1, r2, r3;
	
    r0[0] =   0;
    r0[1] =   0;
    r0[2] =   -1;

	Rotation(X, -delta, &r0, &r1);
	Rotation(Y, hora,   &r1, &r2);
	Rotation(X, phi,    &r2, &r3);

	rx = r3[0];
	ry = r3[1];
	rz = r3[2];

    return;
}

int piana_monaco(double delta,double hora)
{
double x,y,z;
double az,tau;
double Rs,R,Ri;
double tgamma, t2gamma, hv, p, lim;
double a,b,c, disc;
    
    Rs = a1;
    Ri = b1;
	p  = c1;

	lim = (Rs+Ri)/p;

	tgamma = (Rs - Ri)/p;
	hv = 2*Rs/tgamma;
	t2gamma = tgamma*tgamma;

    //printf("Rs = %lf, Ri = %lf, tgamma = %lf hv = %lf\n",Rs,Ri,tgamma,hv);
	//printf("...\n");

	compute_ray_monaco(delta,hora);

	az = asin(rx/sqrt(rx*rx+ry*ry));

	if ( (-rz/sqrt(rx*rx+ry*ry)) >= lim )
	  {
		tau = -p/rz;

		x = rx*tau - Rs*sin(az);
		y = ry*tau - Rs*cos(az);
		//z = rz*tau + p;
		z = 0;
	    Xs=0;
	    Ys=0;
	    Zs=0;
	  
		printf("tau = %lf, Xs= %lf, Ys = %lf\n",tau, Xs, Ys);
        flatland = 1;

	  } 
	else
	  {
        a = rx*rx +ry*ry -rz*rz/t2gamma;
		b = -2*hv*rz/t2gamma;
		c = -hv/t2gamma;

		disc = b*b - 4*a*c;
		if (disc < 0) return -1;

        tau = (-b + sqrt(disc)) / 2*a; 

	    x = rx*tau;
		y = ry*tau;
		z = rz*tau;

		
		Xs = x -2*Rs*sin(az);
	    Ys = y -2*Rs*cos(az);;
	    Zs = z;
	  
	  printf("tau = %lf, Xs= %lf, Ys = %lf  Zs = %lf\n",tau, Xs, Ys, Zs);
      flatland = 0;

	  }


	return 0;
}



int piana(double delta,double hora)
{
double x,y;
double hg;

    hg = a1;
    hg = -sin(epsilon);

//	compute_ray(delta,hora);
//	compute_ray_3(delta,hora);
//	compute_ray_4(delta,hora);
	compute_ray_5(delta,hora);


	if(rz>=0) return -1;


	x=-hg*rx/rz;
	y=-hg*ry/rz;

	Xs=x;
	Ys=y;
	 

        flatland = 1;

	return 0;
}



int piana_riflessa_1(double delta,double hora)
{
double x,y;
double hg;
VECTOR r0,r1,r2,r3;
MATRIX Hhm;
double alfa1,beta1,gamma1;
double alfa2,beta2,gamma2;
double alfa3,beta3,gamma3;

        alfa1  = a1;   //Legge i parametri di orientamento dello specchio
	beta1  = b1;
	gamma1 = c1;

        alfa2  = a2;   //Legge i parametri di orientamento dello specchio
	beta2  = b2;
	gamma2 = c2;

        alfa3  = a3;   //Legge i parametri di orientamento dello specchio
	beta3  = b3;
	gamma3 = c3;


	alfa1  = gra_to_rad(alfa1);
	beta1  = gra_to_rad(beta1);
	gamma1 = gra_to_rad(gamma1);

	alfa2  = gra_to_rad(alfa2);
	beta2  = gra_to_rad(beta2);
	gamma2 = gra_to_rad(gamma2);

	alfa3  = gra_to_rad(alfa3);
	beta3  = gra_to_rad(beta3);
	gamma3 = gra_to_rad(gamma3);


/**	
	alfa1  = (PI/2-phi)/2;  //epsilon/2;
	beta1  = 0;
	gamma1 = 0;

	alfa2  = 0;
	beta2  = -(PI-d);    
	gamma2 = 0; //sigma;

	alfa3  = 0;
	beta3  = 0;
	gamma3 = 0;
**/

	alfa1  = (PI/2-phi)/2;  //epsilon/2;
	beta1  = 0;
	gamma1 = 0;

	alfa2  = 0;
	beta2  = -(PI-d);    
	gamma2 = 0; //sigma;


    //Calcolo coseni direttori della normale allo specchio dopo aver applicato le rotazioni 
	//alfa  beta e gamma allo specchio
	r0[0] =  0;
	r0[1] =  0;
	r0[2] =  -1;

	Rotation(X,alfa1,&r0,&r1);
	Rotation(Y,beta1,&r1,&r2);
	Rotation(Z,gamma1,&r2,&r3);

	Rotation(X,alfa2,&r3,&r1);
	Rotation(Y,beta2,&r1,&r2);
	Rotation(Z,gamma2,&r2,&r3);

	Rotation(X,alfa3,&r3,&r1);
	Rotation(Y,beta3,&r1,&r2);
	Rotation(Z,gamma3,&r2,&r3);

	//Dai coseni direttori della normale allo specchio calcolo la matrice di riflessione
	Build_Householder(&r3,&Hhm);

	hg = 1;

	compute_ray_1(delta,hora);

	//Applico la matrice di riflessione ai coseni direttori del raggio proiettore....
	r0[0] =  rx;
	r0[1] =  ry;
	r0[2] =  rz;
	Product_M_V(&Hhm,&r0,&r1);

	//... e trovo i coseni direttori del raggio riflesso
	rx = r1[0];
	ry = r1[1];
	rz = r1[2];


	//Calcolo le curve come al solito mediante il punto di intersezione raggio (riflesso) superficie
	if(rz>=0) return -1;


	x=-hg*rx/rz;
	y=-hg*ry/rz;

	Xs=x;
	Ys=y;
	 

	return 0;
}


int piana_riflessa_2(double delta,double hora)
{
double x,y;
double hg;
VECTOR r0,r1;
MATRIX Hhm;
double qx,qy,qz,nf;
double hsus;
double versus1,versus2;
   
        qx = 0; //a1;       //Legge i coseni direttori del quadro
	qy = 0; //b1;
	qz = 1; //c1;

	versus1 = 0; //a2;
	versus2 = 1; //b2;


        hsus = tisigma; //Calcolo angolo orario sustilare
	hsus -=12;
	hsus *=15;
	hsus = gra_to_rad(hsus);
	hsus = -hsus;  //perché e' riflessa

	compute_ray_1(0,hsus); //Calcolo rx,ry,rz centrali



        nf=(versus1 == 0) ? sqrt(2)*sqrt(1+(rx*qx+ry*qy+rz*qz)):
	                    sqrt(2)*sqrt(1-(rx*qx+ry*qy+rz*qz)); //calcolo fattore di normalizzazione

	//calcolo i coseni direttori dello specchio e li carico nel vettore r0

	if(versus1 == 0)
	{
	r0[0] =  (qx+rx)/nf;
	r0[1] =  (qy+ry)/nf;
	r0[2] =  (qz+rz)/nf;
	}
	else
	{
	r0[0] =  (qx-rx)/nf;
	r0[1] =  (qy-ry)/nf;
	r0[2] =  (qz-rz)/nf;
	}

	if(versus2 == 0)
	{
	r0[0] =  -r0[0];
	r0[1] =  -r0[1];
	r0[2] =  -r0[2];
	}


	//Dai coseni direttori della normale allo specchio calcolo la matrice di riflessione
	Build_Householder(&r0,&Hhm);

	hg = 1;

	compute_ray_1(delta,hora);

	//Applico la matrice di riflessione ai coseni direttori del raggio proiettore....
	r0[0] =  rx;
	r0[1] =  ry;
	r0[2] =  rz;
	Product_M_V(&Hhm,&r0,&r1);

	//... e trovo i coseni direttori del raggio riflesso
	rx = r1[0];
	ry = r1[1];
	rz = r1[2];


	//Calcolo le curve come al solito mediante il punto di intersezione raggio (riflesso) superficie
	if(rz>=0) return -1;


	x=-hg*rx/rz;
	y=-hg*ry/rz;

	Xs=x;
	Ys=y;
	 

	return 0;
}



//La superficie di separazione del mezzo è un piano orizzontale
int piana_rifratta_1(double delta,double hora)
{
double x,y;
double hg;
VECTOR r0,r1,r2;
double nx, ny, nz, nr;

   if(rad_to_gra(delta) < -28.00 )  return -1;

    nx = a1;   //Leggo i coseni direttori di orientamento del piano di separazione mezzi
	ny = b1;
	nz = c1;
	
	nr    = a2;  // Leggo il coefficiente di rifrazione

	r0[0] = nx;
	r0[1] = ny;
	r0[2] = nz;

	compute_ray_1(delta,hora);
	r1[0] =  rx;
	r1[1] =  ry;
	r1[2] =  rz;

    Rifrazione(nr,&r0,&r1,&r2);

	rx = r2[0];
	ry = r2[1];
	rz = r2[2];
	

	//Calcolo le curve come al solito mediante il punto di intersezione raggio (rifratto) superficie
	if(rz>=0) return -1;

	hg = 1.0;

	x=-hg*rx/rz;
	y=-hg*ry/rz;

	Xs=x;
	Ys=y;
	 

	return 0;
}


//La superficie di separazione del mezzo è un piano orizzontale
//Il punto gnomonico è fuori dall'acqua
int piana_rifratta_2(double delta,double hora)
{
double x,y;
VECTOR r0,r1,r2;
double nx, ny, nz, nr;
double rx1, ry1, rz1, rx2, ry2, rz2;
double zg1, zg2;

 
    if(rad_to_gra(delta) < -28.00 ) return -1;

    nx = a1;   //Leggo i coseni direttori di orientamento del piano di separazione mezzi
	ny = b1;
	nz = c1;

	nr  = a2;  // Leggo il coefficiente di rifrazione

	zg1 = b2;  // Leggo la quota del punto gnomonico
	zg2 = c2;  // Leggo lo spessore del mezzo 
	           // Deve essere zg1 > zg2


	r0[0] = nx;
	r0[1] = ny;
	r0[2] = nz;

	compute_ray_1(delta,hora);
	rx1 = r1[0] =  rx;
	ry1 = r1[1] =  ry;
	rz1 = r1[2] =  rz;

    Rifrazione(nr,&r0,&r1,&r2);

	rx2 = r2[0];
	ry2 = r2[1];
	rz2 = r2[2];
	

	//Calcolo le curve come al solito mediante il punto di intersezione raggio (riflesso) superficie
	if(rz>=0) return -1;


	x = -((rx2*zg2)/rz2) + (rx1*(-zg1 + zg2))/rz1;

	y = -((ry2*zg2)/rz2) + (ry1*(-zg1 + zg2))/rz1;



	Xs=x;
	Ys=y;
	 

	return 0;
}

//La superficie di separazione del mezzo è una semisfera
int piana_rifratta_3(double delta,double hora)
{
double x,y;
VECTOR r0,r1,r2;
double nx, ny, nz;
double maxit;
double rx2,ry2,rz2;
double gamma, teta;

   if(rad_to_gra(delta) < -28.00 )  return -1;

    g  = a1;  // Leggo l'altezza del punto gnomonico
	c  = b1;  // Leggo distanza piede gnomone dal centro verso sud
	R  = c1;  // Leggo il raggio della semisfera
	nr = a2;  // Leggo il coefficiente di rifrazione


	compute_ray_1(delta,hora);
	r1[0] =  rx;
	r1[1] =  ry;
	r1[2] =  rz;

	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;

    //Calcolo i coseni direttori della normale alla superficie nel punto di incidenza
	maxit  = 1000;     //numero massimo di iterazioni
	xvect[0]  = PI/2;  //valore iniziale di gamma (angolo raggio incidente - normale)
	xvect[1]  = 0.0;   //valore iniziale di beta (angolo raggio rifratto - normale)
							//calcolo l'inclinazione del raggio incidente rispetto
							//al piano del quadro
	elev_n = acos(sqrt(rx2+ry2));

    func_array[0] = func1; //carico le equazioni del sistema da risolvere
	func_array[1] = func2;

	SolveNonlinearSystem(&func_array[0],&xvect[0],2,4,&maxit);

	gamma = xvect[0];                      //Prendo gamma calcolato (elevazione della normale)
	teta  = asin(rx / sqrt(rx2+ry2));      //Calcolo la direzione del piano di rifrazione

	nx = -cos(gamma)*sin(teta);         //Calcolo le componenti del versore n
	ny = -cos(gamma)*cos(teta);
	nz = sin(gamma);
	
	r0[0] = nx;
	r0[1] = ny;
	r0[2] = nz;

    Rifrazione(nr,&r0,&r1,&r2);         //Calcolo le componenti del raggio rifratto

	rx = r2[0];
	ry = r2[1];
	rz = r2[2];
	

	//Calcolo le curve come al solito mediante il punto di intersezione raggio (riflesso) superficie
	if(rz>=0) return -1;

	x=-g*rx/rz;
	y=-g*ry/rz;

	Xs=x;
	Ys=y;
	 

	return 0;
}

//La superficie di separazione del mezzo è una semisfera (metodo generale)
int piana_rifratta_4(double delta,double hora)
{
double x,y;
VECTOR r0,r1,r2;
double nx, ny, nz;
double maxit;

    if(rad_to_gra(delta) < -28.00 )  return -1;

    g  = a1;  // Leggo l'altezza del punto gnomonico
	c  = b1;  // Leggo distanza piede gnomone dal centro verso sud
	R  = c1;  // Leggo il raggio della semisfera
	nr = a2;  // Leggo il coefficiente di rifrazione


	compute_ray_1(delta,hora);


    //Calcolo i coseni direttori della normale alla superficie nel punto di incidenza (pinc)
	maxit     = 1000;  //numero massimo di iterazioni
	xvect[0]  = 0.0;   //valore iniziale di x,y,z (punto di incidenza)
	xvect[1]  = -R;  
	xvect[2]  = 0.0;  
							//Cerco le coordinate del punto di incidenza utile.
	func_array[0] = func1s; //carico le equazioni del sistema da risolvere
	func_array[1] = func2s;
	func_array[2] = func3s;
//	func_array[3] = func4s;

	SolveNonlinearSystem(&func_array[0],&xvect[0],3,4,&maxit);


	nx = xvect[0]/R;                     //Calcolo le componenti del versore n
	ny = xvect[1]/R;
	nz = xvect[2]/R;
	
	r0[0] = nx;                          //Carico il vettore normale alla sfera nel pinc. 
	r0[1] = ny;
	r0[2] = nz;

	r1[0] =  rx;						 //Carico i coseni direttori del raggio incidente 
	r1[1] =  ry;
	r1[2] =  rz;

    Rifrazione(nr,&r0,&r1,&r2);         //Calcolo i coseni direttori del raggio rifratto

	rx = r2[0];
	ry = r2[1];
	rz = r2[2];
	

	//Calcolo le curve come al solito mediante il punto di intersezione raggio (rifratto) superficie
	if(rz>=0) return -1;

	x=-g*rx/rz;
	y=-c-g*ry/rz;

	Xs=x;
	Ys=y;
	 

	return 0;
}



//La superficie di separazione del mezzo è una cilindro trasversale
int piana_rifratta_5(double delta,double hora)
{
double x,y;
VECTOR r0,r1,r2;
double nx, ny, nz;
double maxit;
double rx2,ry2,rz2;
double gamma;

   if(rad_to_gra(delta) < -28.00 )  return -1;

    g  = a1;  // Leggo l'altezza del punto gnomonico
	c  = b1;  // Leggo distanza piede gnomone dal centro verso sud
	R  = c1;  // Leggo il raggio del cilindro
	nr = a2;  // Leggo il coefficiente di rifrazione


	compute_ray_1(delta,hora);
	r1[0] =  rx;
	r1[1] =  ry;
	r1[2] =  rz;

	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;

    //Calcolo i coseni direttori della normale alla superficie nel punto di incidenza
	maxit  = 1000;     //numero massimo di iterazioni
	xvect[0]  = PI/2;  //valore iniziale di gamma (angolo raggio incidente - normale)
	xvect[1]  = 0.0;   //valore iniziale di beta (angolo raggio rifratto - normale)
							//calcolo l'inclinazione del raggio incidente rispetto
							//al piano del quadro
	elev_n = acos(ry/sqrt(ry2+rx2));

    func_array[0] = func1; //carico le equazioni del sistema da risolvere
	func_array[1] = func2;

	SolveNonlinearSystem(&func_array[0],&xvect[0],2,4,&maxit);

	gamma = xvect[0];                      //Prendo gamma calcolato (elevazione della normale)

	nx = 0;						        //Calcolo le componenti del versore n
	ny = -cos(gamma);
	nz = sin(gamma);
	
	r0[0] = nx;
	r0[1] = ny;
	r0[2] = nz;

    Rifrazione(nr,&r0,&r1,&r2);         //Calcolo le componenti del raggio rifratto

	rx = r2[0];
	ry = r2[1];
	rz = r2[2];
	

	//Calcolo le curve come al solito mediante il punto di intersezione raggio (riflesso) superficie
	if(rz>=0) return -1;

	x=-g*rx/rz;
	y=-g*ry/rz;

	Xs=x;
	Ys=y;
	 

	return 0;
}


//La superficie di separazione del mezzo è una cilindro (metodo generale)
int piana_rifratta_6(double delta,double hora)
{
double x,y;
VECTOR r0,r1,r2;
double nx, ny, nz;
double maxit;

    if(rad_to_gra(delta) < -28.00 )  return -1;

    g  = a1;  // Leggo l'altezza del punto gnomonico
	c  = b1;  // Leggo distanza piede gnomone dal centro verso sud
	R  = c1;  // Leggo il raggio della cilindro
	nr = a2;  // Leggo il coefficiente di rifrazione


	compute_ray_1(delta,hora);


    //Calcolo i coseni direttori della normale alla superficie nel punto di incidenza (pinc)
	maxit     = 1000;  //numero massimo di iterazioni
	xvect[0]  = 0.0;   //valore iniziale di x,y,z (punto di incidenza)
	xvect[1]  = -R;  
	xvect[2]  = 0.0;  
							//Cerco le coordinate del punto di incidenza utile.
	func_array[0] = func1c; //carico le equazioni del sistema da risolvere
	func_array[1] = func2c;
	func_array[2] = func3c;
//	func_array[3] = func4c;

	SolveNonlinearSystem(&func_array[0],&xvect[0],3,4,&maxit);


	nx = 0.0;                            //Calcolo le componenti del versore n
	ny = xvect[1]/R;
	nz = xvect[2]/R;
	
	r0[0] = nx;                          //Carico il vettore normale alla sfera nel pinc. 
	r0[1] = ny;
	r0[2] = nz;

	r1[0] =  rx;						 //Carico i coseni direttori del raggio incidente 
	r1[1] =  ry;
	r1[2] =  rz;

    Rifrazione(nr,&r0,&r1,&r2);         //Calcolo i coseni direttori del raggio rifratto

	rx = r2[0];
	ry = r2[1];
	rz = r2[2];
	

	//Calcolo le curve come al solito mediante il punto di intersezione raggio (rifratto) superficie
	if(rz>=0) return -1;

	x=-g*rx/rz;
	y=-c-g*ry/rz;

	Xs=x;
	Ys=y;
	 

	return 0;
}


//La superficie di separazione del mezzo è un piano (metodo generale)
int piana_rifratta_7(double delta,double hora)
{
double x,y;
VECTOR r0,r1,r2;
double nx, ny, nz;
double maxit;

    if(rad_to_gra(delta) < -28.00 )  return -1;

    g  = a1;  // Leggo l'altezza del punto gnomonico
	c  = b1;  // Leggo distanza piede gnomone dal centro verso sud
	R  = c1;  // Leggo l'altezza del piano
	nr = a2;  // Leggo il coefficiente di rifrazione


	compute_ray_1(delta,hora);


    //Calcolo i coseni direttori della normale alla superficie nel punto di incidenza (pinc)
	maxit     = 1000;  //numero massimo di iterazioni
	xvect[0]  = 0.0;   //valore iniziale di x,y,z (punto di incidenza)
	xvect[1]  = 0.0;  
	xvect[2]  = R;  
							//Cerco le coordinate del punto di incidenza utile.
	func_array[0] = func1p; //carico le equazioni del sistema da risolvere
	func_array[1] = func2p;
	func_array[2] = func3p;
//	func_array[3] = func4p;

	SolveNonlinearSystem(&func_array[0],&xvect[0],3,4,&maxit);


	nx = 0;                              //Calcolo le componenti del versore n
	ny = 0;
	nz = 1;
	
	r0[0] = nx;                          //Carico il vettore normale alla sfera nel pinc. 
	r0[1] = ny;
	r0[2] = nz;

	r1[0] =  rx;						 //Carico i coseni direttori del raggio incidente 
	r1[1] =  ry;
	r1[2] =  rz;

    Rifrazione(nr,&r0,&r1,&r2);         //Calcolo i coseni direttori del raggio rifratto

	rx = r2[0];
	ry = r2[1];
	rz = r2[2];
	

	//Calcolo le curve come al solito mediante il punto di intersezione raggio (rifratto) superficie
	if(rz>=0) return -1;

	x=-g*rx/rz;
	y=-c-g*ry/rz;

	Xs=x;
	Ys=y;
	 

	return 0;
}



int bif_saturno_1(double delta,double hora)
{
double x,y,z,Teta,Phi;
VECTOR xvect;
double maxit;
double rx2,ry2,rz2;
double rh,rv,R;
double th,tv,sh,sv,xgh,ygh,zgh,xgv,ygv,zgv;
double xh,yh,zh,xv,yv,zv;

   if(rad_to_gra(delta) < -28.00 )  return -1;

    rh  = a1;  // Leggo raggio anello trasversale
	rv  = b1;  // Leggo raggio anello sagittale
	R   = c1;  // Leggo il raggio della sfera


	compute_ray_1(delta,hora);

	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;

    func_array[0] = funch1; //carico le equazioni del sistema da risolvere
	func_array[1] = funcv1;

	maxit  = 1000;         //numero massimo di iterazioni
	xvect[0] = a2;         //Valori iniziali per th e tv
	xvect[1] = b2;

	SolveNonlinearSystem(&func_array[0],&xvect[0],2,4,&maxit);

	th = xvect[0];         //Prendo i parametri th e tv calcolati
	tv = xvect[1];

	sh = -asin((rx*(th - tv))/rh);

	xgh = rh*sin(sh);
	ygh = 0;
	zgh = rh*cos(sh);

	xh = rx*th + xgh;
	yh = ry*th + ygh;
	zh = rz*th + zgh;

	sv = asin((ry*(th - tv))/rv);

	xgv = 0;
	ygv = rv*sin(sv);
	zgv = rv*cos(sv);

	xv = rx*tv + xgv;
	yv = ry*tv + ygv;
	zv = rz*tv + zgv;

	//Calcolo le curve come al solito mediante il punto di intersezione raggio superficie
    //if(rz>=0) return -1;
    
	flatland = 1;
    
    if (flatland == 1)
		{
		x = xh;
		y = yh;
		z = zh;

		Teta = asin(x/sqrt(x*x+z*z));
		Phi  = asin(y/R);
		Xs = R*Teta;
		Ys = R*tan(Phi);
    if (fabs(Teta) >= PI/2)
                      return -1;
		}
	 else
		{
		Xs = xh;
		Ys = yh;
		Zs = zh;
		}


	return 0;
}


int bif_saturno_2(double delta,double hora)
{
double x,y,z,Teta,Phi;
VECTOR xvect;
double maxit;
double rx2,ry2,rz2;
double xh,yh,zh, xv,yv,zv, xgh,ygh,zgh, xgv,ygv,zgv;
double rh,rv,R;
double rh2,rv2,sh2,sv2,R2;
double th,tv,sh,sv;
double temp;


   if(rad_to_gra(delta) < -28.00 )  return -1;

    rh  = a1;  // Leggo raggio anello trasversale
	rv  = b1;  // Leggo raggio anello sagittale
	R   = c1;  // Leggo il raggio della sfera


	compute_ray_1(delta,hora);


    func_array[0] = funch2; //carico le equazioni del sistema da risolvere
	func_array[1] = funcv2;

	maxit  = 1000;         //numero massimo di iterazioni
	xvect[0] = a2;         //Valori iniziali per sh e sv
	xvect[1] = b2;

	SolveNonlinearSystem(&func_array[0],&xvect[0],2,4,&maxit);

	sh = xvect[0];         //Prendo i parametri sh e sv calcolati
	sv = xvect[1];

	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;

 	rh2 = rh*rh;
	rv2 = rv*rv;
	R2  = R*R;

	sh2 = sh*sh;
	sv2 = sv*sv;

/**
th = -rx*sh - rz*Sqrt[(rh - sh)*(rh + sh)] # Sqrt[R^2 - rh^2 + (rx*sh + rz*Sqrt[(rh - sh)*(rh + sh)])^2]
tv = -ry*sv - rz*Sqrt[(rv - sv)*(rv + sv)] # Sqrt[R^2 - rv^2 + (ry*sv + rz*Sqrt[(rv - sv)*(rv + sv)])^2]
**/

	temp = (rx*sh + rz*sqrt((rh2 - sh2)));
	th = -rx*sh - rz*sqrt((rh2 - sh2)) - sqrt(R2 - rh2 + temp*temp);

	temp = (ry*sv + rz*sqrt((rv2 - sv2)));
	tv = -ry*sv - rz*sqrt((rv2 - sv2)) - sqrt(R2 - rv2 + temp*temp);

	
	//Calcolo le curve come al solito mediante il punto di intersezione raggio superficie
	xgh = sh;
	ygh = 0;
	zgh = sqrt(rh2 - sh2);

	xh = rx*th + xgh;
	yh = ry*th + ygh;
	zh = rz*th + zgh;

	//oppure
	xgv = 0;
	ygv = sv;
	zgv = sqrt(rv2 - sv2);

	xv = rx*tv + xgv;
	yv = ry*tv + ygv;
	zv = rz*tv + zgv;


	flatland = 1;
    
    if (flatland == 1)
		{
		x = xh;
		y = yh;
		z = zh;

		Teta = asin(x/sqrt(x*x+z*z));
		Phi  = asin(y/R);
		Xs = R*Teta;
		Ys = R*tan(Phi);
//    if (fabs(Teta) >= PI/2)
//		                      return -1;

	    temp = 10*R;
        if ( (tv >= temp) || (th >= temp) )
		                         return -1;
		}
	 else
		{
		Xs = xh;
		Ys = yh;
		Zs = zh;
		}

	return 0;
}

int bif_parabola_catenaria_muro_inc_dec(double delta,double hora)
{
double x1,y1,z1,t1;
double x2,y2,z2,t2;
double s1,s2,t;
double Yc,d1,yv,f;
double Yp,a,b,c,G;
double bo, bc, incp;

VECTOR xvect;
double maxit;


   if(rad_to_gra(delta) < -28.00 )  return -1;

    bo    = a1;  // Leggo lunghezza muro dall'origine all'acqua
	bc    = b1;  // Leggo distanza del bersaglio del getto dalla linea muro-acqua 
    incp  = c1;  // Leggo inclinazione muro (0 = verticale)

    d1= a2;  // Solo per DEBUG
	yv= b2;
	f = c2;

    incp = gra_to_rad(incp);

    b = tan(incp);       //Alzo getto
	G = bo*sin(incp)+bc; //Gittata
	c = bo*cos(incp);    //Altezza getto
	a = (b*G+c)/(G*G);   //Potenza getto

	compute_ray_1(delta,hora);

    func_array[0] = funcpc1; //carico le equazioni del sistema da risolvere
	func_array[1] = funcpc2;

	maxit  = 1000;         //numero massimo di iterazioni

    s1 = 0; //( (asin(rx) - d) < 0.0) ? 100.0 : -100.0;
	s2 = d1; //(b/(2*a))+0.1;

	xvect[0] = s1;         //Valori iniziali per s1 e s2
	xvect[1] = s2;

	SolveNonlinearSystem(&func_array[0],&xvect[0],2,4,&maxit);

	s1 = xvect[0];         //Prendo i parametri s1 e s2 calcolati
	s2 = xvect[1];

/**
    if(fabs(s1) > 50)
	        	return -1;

    if(s2 < 0)
	        	return -1;

    if(fabs(s2) > 20)
	        	return -1;
**/

	Yp = -a*s2*s2 + b*s2;

	Yc = f*cosh((s1-xv)/f)+yv-f;   

    /** t1 = -((d1 - f*Tan[i] + yv*Tan[i] + f*Cosh[(s1 - xv)/f]*Tan[i])/(rz + ry*Tan[i]))**/
    t1 = -((d1 +Yc*tan(incp))/(rz + ry*tan(incp)));
	
	/** t2 = -((s2 + b*s2*Tan[i] - a*s2^2*Tan[i])/(rz + ry*Tan[i]))**/
	t2 = -((s2 +Yp*tan(incp))/(rz + ry*tan(incp)));


	t = t2;

	if(t < 0) return -1;
    if(fabs(t) > 20) return -1;
	//if (ry > 0) return -1;

 
    x1=rx*t1+s1; 
	y1=ry*t1+Yc;
	z1=rz*t1;


    x2=rx*t2; 
	y2=ry*t2+Yp;
	z2=rz*t2+s2;


	flatland = 1;
    
    if (flatland == 1)
		{
		Xs = x2;
		Ys = y2/cos(incp);
		}
	 else
		{
		Xs = x2;
		Ys = y2;
		Zs = z2;
		}

	return 0;
}


int bif_cat_cat(double delta,double hora)
{
/*** PROCEDURA.

//Equazioni delle catenarie
Yc1 = f1*Cosh[(s1 - xv1)/f1] + zv1 - f1  //"est-ovest" catenaria lungo l'asse X
Yc2 = f2*Cosh[(s2 - yv2)/f2] + zv2 - f2  //"nord-sud " catenaria lungo l'asse Y

//Equazioni delle ombre dei fili (fare sistema per trovare l'incrocio)
e1 = s1 - (rx*(-f1 + zv1 + f1*Cosh[s1/f1]))/rz + (rx*(-f2 + zv2 + f2*Cosh[s2/f2]))/rz
e2 = s2 - (ry*(-f2 + zv2 + f2*Cosh[s2/f2]))/rz + (ry*(-f1 + zv1 + f1*Cosh[s1/f1]))/rz

//Trovato s1 calcolare t1
t1 = -((-f1 + zv1 + f1*Cosh[s1/f1])/rz)

oppure

//Trovato s2 calcolare t2
t2 = -((-f2 + zv2 + f2*Cosh[s2/f2])/rz)

//... e poi sostituire in

x1 = rx*t1 + s1
y1 = ry*t1
z1 = rz*t1 + Yc1(s1)

  ... o in

x2 = rx*t2
y2 = ry*t2 + s2
z1 = rz*t2 + Yc2(s2)

***/

double x1,y1,z1,t1;
double x2,y2,z2,t2;
double s1,s2,t;
double Yc1,zv1,f1;
double Yc2,zv2,f2;
double xv1,xv2;

VECTOR xvect;
double maxit;

    xv1 = xv2 = 0.0;

   if(rad_to_gra(delta) < -28.00 )  return -1;

    zv1= b1;
    f1 = c1;
    
    zv2= b2;
    f2 = c2;


    compute_ray_1(delta,hora);

    func_array[0] = funcCC1; //carico le equazioni del sistema da risolvere
    func_array[1] = funcCC2;

    maxit  = 1000;         //numero massimo di iterazioni

    s1 = a3; //init val s1
    s2 = b3; //init val s2

	xvect[0] = s1;         //Valori iniziali per s1 e s2
	xvect[1] = s2;

	SolveNonlinearSystem(&func_array[0],&xvect[0],2,4,&maxit);

	s1 = xvect[0];         //Prendo i parametri s1 e s2 calcolati
	s2 = xvect[1];

/**
    if(fabs(s1) > 50)
	        	return -1;

    if(s2 < 0)
	        	return -1;

    if(fabs(s2) > 20)
	        	return -1;
**/


    Yc1 = f1*cosh((s1)/f1)+zv1-f1;   
    Yc2 = f2*cosh((s2)/f2)+zv2-f2;   

//Trovato s1 calcolare t1 = -((-f1 + zv1 + f1*Cosh[s1/f1])/rz)

    t1 = -Yc1/rz;

    //oppure

//Trovato s2 calcolare t2 = -((-f2 + zv2 + f2*Cosh[s2/f2])/rz)

    t2 = -Yc2/rz;


    //Controllo antimostri
    t = t1;

    if(t < 0) return -1;
    if(fabs(t) > 20) return -1;

    //Sostituzioni
    x1 = rx*t1 + s1;
    y1 = ry*t1;
    z1 = rz*t1 + Yc1;

    x2 = rx*t2;
    y2 = ry*t2 + s2;
    z2 = rz*t2 + Yc2;

;
    Xs = x1;
    Ys = y1;

    return 0;
}


int bif_saturno_3_semplice(double delta,double hora)  //Troppo semplice :-) !!!
{
double x,y,z,Teta,Phi;
double Psi,lamda;
double rx2,ry2,rz2;
double xh,yh,zh, xv,yv,zv;
double tv, th;
double rh,rv,R;
double rh2,rv2,R2;


   if(rad_to_gra(delta) < -28.00 )  return -1;

    rh  = a1;  // Leggo raggio anello trasversale
	rv  = b1;  // Leggo raggio anello sagittale
	R   = c1;  // Leggo il raggio della sfera


	compute_ray_1(delta,hora);


	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;

 	rh2 = rh*rh;
	rv2 = rv*rv;
	R2  = R*R;

	tv = -rv*rz - sqrt(R2 - rv2*(rx2 + ry2));

	xv = rx*tv;
	yv = ry*tv;
	zv = rz*tv + rv;
	
	th = -rh*rz - sqrt(R2 - rh2*(rx2 + ry2));

	xh = rx*th;
	yh = ry*th;
	zh = rz*th + rh;

	Psi   = asin(yh/R);
// oppure Psi = atan(yh/sqrt(xh*xh+zh*zh));
	lamda = asin(xv/sqrt(xv*xv+zv*zv));

    x = R*cos(Psi)*sin(lamda);
	y = R*sin(Psi);
	z = R*cos(Psi)*cos(lamda);

	// Disegno
		
	flatland = 1;
    
    if (flatland == 1)
	{                                 //Proiezione cilindrica
		Phi  = asin(y/R);
		Teta = asin(x/sqrt(x*x+z*z));
		Xs = R*Teta;
		Ys = R*tan(Phi);
		}
	 else
		{                               //Sfera            
		Xs = x;
		Ys = y;
		Zs = z;
		}

	return 0;
}


int sferica_gen(double delta,double hora)
{
double x,y,z,Teta,Phi;
double xg,yg,zg;
double R;
double rx2,ry2,rz2;
double R2, xg2,yg2,zg2;
double t1,t2,t;
double A,B;
int    f;
double val1, val2,val3,val4,val5;
val1=val2=val3=val4=val5=0;

  	f    = (int)a1;       // Se 1 uso t1 se 2 uso t2
	R    = b1;            // Leggo raggio sfera
        flatland = (int)c1;   // Leggo flatland
        xg   = a2;            // Leggo coordinate di G
	yg   = b2;  
	zg   = c2;
	
//	xg = 0.0;
//	yg = R*sin(phi);
//	zg = R*cos(phi);

	compute_ray_1(delta,hora);


	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;

	xg2 = xg*xg;
	yg2 = yg*yg;
	zg2 = zg*zg;

	R2  = R*R;

//t = -(rx*xg + ry*yg + rz*zg) + Sqrt[ (rx*xg + ry*yg + rz*zg)^2 -(-R^2 + xg^2 + yg^2 + zg^2) ]

	A = (rx*xg + ry*yg + rz*zg);
	B = (xg2 + yg2 + zg2 - R2);

	t1 = -A+sqrt(A*A-B);
        t2 = -A-sqrt(A*A-B);

	//Con f=1 sceglie la soluzione "vicina" e con f=2 quella "lontana"
	//t = (f == 1) ? min(t1,t2) : max(t1,t2);
        t = (f == 1) ? t1 : t2;

	x = rx*t + xg;
	y = ry*t + yg;
	z = rz*t + zg;

    //per DEBUG
        val1 = t1;
	val2 = t2;
	val3 = sqrt(A*A-B);
	val4 = A;
	val5 = B;
	//printf("%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n",val1,val2,val3,val4,val5); 

	// Disegno
//	flatland = 1;
    
    if (flatland == 1)
		{                                 //Proiezione cilindrica
			Phi  = asin(y/R);

			if(f == 1)   ///// ERA f == 1
			{
				if (z <= 0.0)
				{
					Teta = asin(x/sqrt(x*x+z*z));
				}
				else
				{
					Teta = PI/2 + acos(fabs(x)/sqrt(x*x+z*z));
					Teta = (x >= 0.0) ? Teta : -Teta;
				}
			}
			else
			{
				if (z <= 0.0)
				{
					Teta = asin(x/sqrt(x*x+z*z));
				}
				else
				{
					Teta = PI/2 + acos(fabs(x)/sqrt(x*x+z*z));
					Teta = (x >= 0.0) ? Teta : -Teta;
				}
			}

			Xs = R*Teta;
			Ys = R*tan(Phi);



	//        if ( fabs(t) >= 2*R  ) // Per usare gli antimostri...
	//		              return -1; // ...occorre migliorare il tracciamento
	// oppure
	//		if( (A*A - B) < 0) 
	//			      return -1;
			
		}
	 else
		{                               //Sfera            
//		Xs = x;
//		Ys = y;
//		Zs = z;

                Xs = x;      //Per Ghia che simula su AutoCAD e SketchUp
                Ys = -z;
                Zs = y;
		}

	return 0;
}





int bif_retta_catenaria(double delta,double hora)
{
double x,y;

/*
    // Usare i questi parametri generici anziché quelli dedicati sul file dei parametri 
    d1 = a1;
	d2 = b1;
	
	xv = a2;
	yv = b2;
	f  = c2;
*/
	compute_ray(delta,hora);

	if (rz>=0) return -1;

	x=-d2*rx/rz;
	y=-d1*ry/rz+f*cosh(   (1/f)*((d1-d2)/rz - xv)   )+yv -f;

	Xs=x;
	Ys=y;

	return 0;
}


int bif_rettaH_parabola(double delta,double hora)
{
double x,z;
double a;

/*
    // Usare i questi parametri generici anziché quelli dedicati sul file dei parametri 
    d1 = a1;
	d2 = b1;
    a  = c1;
	
	xv = a2;
	yv = b2;
	f  = c2;
*/
	a=1.0/4.0;


	compute_ray(delta,hora);


    if (ry>=0.0) return -1;
	if (rx == 0.0)
	{
		rx = (rx>=0.0) ? 0.0001 : -0.0001;
	}

    x = -((d1*rx)/ry);	
    z = -((d1*rz)/ry)-(ry*rz)/(2*a*rx*rx)-(sqrt(4*a*(d1 - d2)*rx*rx + ry*ry)*rz)/(2*a*rx*rx);
		
	Xs=x;
	Ys=z;

	return 0;
}


int bif_rettaverticale_cerchio(double delta,double hora)
{
double x,y;
double R;

	compute_ray(delta,hora);

	R = 1.0;

	
    if(rz >= 0)  return -1;

	if (d1 > 0)
	{
	x = -((d2*rx)/rz) + (R*rx)/sqrt(rx*rx + ry*ry);
	y = -((d2*ry)/rz) + (R*ry)/sqrt(rx*rx + ry*ry);
	}
	else
	{
	x = -((d2*rx)/rz) - (R*rx)/sqrt(rx*rx + ry*ry);
	y = -((d2*ry)/rz) - (R*ry)/sqrt(rx*rx + ry*ry);
	}
	
	Xs=-x;
	Ys=-y;

	return 0;
}


int bif_retta_cerchio_generale_1(double delta,double hora)
{
double R;
double x,y;
double rx2,ry2,rz2;
double N, D;
double t1,s1;
double eps;


   if(rad_to_gra(delta) < -28.00 )  return -1;

	R    = 1.0;

	eps = -epsilon;

	//dmax = 23.5;
	//dmax = gra_to_rad(dmax);
	//eps = eps+dmax;

	compute_ray_2(delta,hora);


	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;


	N = sqrt(2)*R*(rz*cos(2*eps)+ry*sin(2*eps));
        D = (sqrt(1 -(rx2+ry2-rz2)*cos(2*eps) +2*ry*rz*sin(2*eps) ));

        s1 = -N/D;
	t1 = -s1*sin(eps)/rz;

 
//	if (t1 <= 0)
//	  return -1; 

    
	x = rx*t1;
	y = ry*t1 - s1*cos(eps);


	Xs = x*cos(sigma)-y*sin(sigma);
	Ys = x*sin(sigma)+y*cos(sigma);

	return 0;
}





int bif_2_rette(double delta,double hora)
{
double x,y;
//double s1,t1;
double s2,t2;

	compute_ray(delta,hora);

	if(rz>=0) return -1;

	//s1 = -((-b2*d1*rx + b2*d2*rx + a2*d1*ry - a2*d2*ry)/(-b2*c1*rx + b1*c2*rx + 
    //        a2*c1*ry - a1*c2*ry - a2*b1*rz + a1*b2*rz));
	//t1 = -((d1 + c1*s1)/rz);
	
	//x=rx*t1+a1*s1;
	//y=ry*t1+b1*s1;

	s2 = -((-b1*d1*rx + b1*d2*rx + a1*d1*ry - a1*d2*ry)/(-b2*c1*rx + b1*c2*rx + 
		    a2*c1*ry - a1*c2*ry - a2*b1*rz + a1*b2*rz));
	t2 = -((d2 + c2*s2)/rz);

	x=rx*t2+a2*s2;
	y=ry*t2+b2*s2;
	

	Xs=x;
	Ys=y;

	return 0;

}



int bif_2_rette_Rouxel(double delta,double hora)
{
double x,y;
//double s1,t1;
//double s2,t2;
double psi,  cospsi;
double d2;


    psi = b1;
	d2  = c1;

	psi    = gra_to_rad(psi);
	cospsi = cos(psi);


	compute_ray(delta,hora);

	if(rz>=0) return -1;

/**
	xpm = (d2*rx*Cos[phi]*(-rz + rx*Cos[phi]*Sec[psi]))/(rz*(-ry*Cos[phi] + rz*Sin[phi]))
	ypm = d2 - (d2*rx*Cos[phi]*Sec[psi])/rz
**/
	
	x = (d2*rx*cosphi*(-rz + rx*cosphi/cospsi))/(rz*(-ry*cosphi + rz*sinphi));
	y = d2 - (d2*rx*cosphi/cospsi)/rz;

/***
	xam = -((d2*rx*Cos[phi]*(rz + rx*Cos[phi]*Sec[psi]))/(rz*(-ry*Cos[phi] + rz*Sin[phi])))
	yam = d2 + (d2*rx*Cos[phi]*Sec[psi])/rz
***/

	//x = -(d2*rx*cosphi*(rz + rx*cosphi/cospsi))/(rz*(-ry*cosphi + rz*sinphi));
	//y = d2 + (d2*rx*cosphi/cospsi)/rz;

	Xs=x;
	Ys=y;

	return 0;

}



int  cyl_volta(double delta,double hora)  // Cilindro a volta (Palazzo Spada)
{
double x,y,z;
double R;
double t;

	compute_ray(delta,hora);

	ry=-ry;

	if (rz > 0) return -1;
	if (ry < 0) return -1;


	R = 1.0;

	t = -2*R*rz / (ry*ry+rz*rz);

	x = rx*t;
	y = ry*t;
	z = rz*t+R;


	Xs = -x;

	if((z>=0)&&(y>=0))
	{
	Ys = R*asin(fabs(y)/R);
	}
	else if((z<0)&&(y>=0))
	{
	Ys = R*(0.5*PI + acos(fabs(y)/R));
	}
	else if((z<0)&&(y<0))
	{
	Ys = -R*(0.5*PI + asin(fabs(y)/R));
	}
	else 
	{
	Ys = -R*(asin(fabs(y)/R));
	}

	return 0;
}

int cyl_gen(double delta,double hora)  // Cilindro verticale. foro sulla base superiore a R*xr (al centro se xr=0)
{
double x,y,z;
double R;
double t;

	compute_ray(delta,hora);

	rx=-rx;
	rz=-rz;

	R = 1.0;

	t = (-R*rz*xr+R*sqrt(rx*rx+rz*rz-rx*rx*xr*xr)) / (rx*rx+rz*rz);

	x = rx*t;
	y = ry*t;
	z = rz*t+R*xr;


    Ys=y;

	if((z>=0)&&(x>=0))
	{
	Xs = R*asin(fabs(x)/R);
	}
	else if((z<0)&&(x>=0))
	{
	Xs= R*(0.5*PI + acos(fabs(x)/R));
	}
	else if((z<0)&&(x<0))
	{
	Xs = -R*(0.5*PI + acos(fabs(x)/R));
	}
	else 
	{
	Xs = -R*(asin(fabs(x)/R));
	}

	return 0;
}


int con_genSGR(double delta,double hora)  // Cono capovolto a calice altezza A raggio R
{
double x,y,z;
double R, A;
double t;

double R2, A2, xr2;
double rx2,ry2,rz2;

double SA,r,arc;
double theta, rho;
int signx;

	compute_ray(delta,hora);

	rx=-rx;
	rz=-rz;
 
	R = 1.0;
	A = hrr*R;

	R2=R*R; A2=A*A; rx2=rx*rx; ry2=ry*ry; rz2=rz*rz; xr2=xr*xr;

	t = (A*R*(R*ry-A*rz*xr+sqrt(-2*A*R*ry*rz*xr+R2*ry2*xr2+A2*(rx2+rz2-rx2*xr2))))/(A2*(rx2+rz2)-R2*ry2);

	x = rx*t;
	y = ry*t;
	z = rz*t+R*xr;

	SA = atan(R/A);

	signx = (x >= 0.0) ? 1 : -1;

	r     = R*(A+y)/A;

	arc   = z>=0.0 ? r*asin(x/r) : signx*(0.5*PI*r + r*acos(fabs(x)/r));
	
	rho   = (A+y)/cos(SA);
	theta = arc / rho;

	Xs = rho*sin(theta);
	Ys = rho*cos(theta);

	/** Per debug
    r = 180.0/PI;
    if(z<0)
	{
 	printf("rx = %lf \try = %lf \trz = %lf  \tx = %lf \ty = %lf \tz = %lf\n",rx,ry,rx,x,y,z);
	printf("arc = %lf \trho = %lf \ttheta = %lf\n\n",r*arc,rho,r*theta);
	}
	**/

	return 0;
}


int con_genSRG(double delta,double hora)  // Cono dritto altezza A raggio R
{
double x,y,z;
double R, A, k;
double t,t1,t2;

double R2, A2, xr2;
double rx2,ry2,rz2;

double SA,r,arc;
double theta, rho;
int signx;

	compute_ray(delta,hora);

    //rx=-rx;
	//ry=-ry;
	//rz=-rz;

	k = hrr;
 
	R = 1.0;
	A = k*R;

	R2=R*R; A2=A*A; rx2=rx*rx; ry2=ry*ry; rz2=rz*rz; xr2=xr*xr;

    t1 = (k*R)/(ry - k*sqrt(rx2 + rz2));
    t2 = (k*R)/(ry + k*sqrt(rx2 + rz2));


	//printf("t1=%.4lf \tt2=%.4lf \tabst1=%0.4lf \tabst2=%0.4lf\n",t1,t2,fabs(t1),fabs(t2) );

	t=t1;

	x = rx*t;
	y = ry*t;
	z = rz*t;

	SA = atan(R/A);

	signx = (x >= 0.0) ? 1 : -1;

	r     = R*(A-y)/A;

	arc   = z>=0.0 ? r*asin(x/r) : signx*(0.5*PI*r + r*acos(fabs(x)/r));
	
	rho   = (A-y)/cos(SA);
	theta = arc / rho;

	Xs = rho*sin(theta);
	Ys = rho*cos(theta);

	/** Per debug
    r = 180.0/PI;
    if(z<0)
	{
 	printf("rx = %lf \try = %lf \trz = %lf  \tx = %lf \ty = %lf \tz = %lf\n",rx,ry,rx,x,y,z);
	printf("arc = %lf \trho = %lf \ttheta = %lf\n\n",r*arc,rho,r*theta);
	}
	**/

	return 0;
}



int con_fc(double delta,double hora)  // Conica con foro centrale
{
double x,y,z;
double R, H, r, SA;
double a,b,c,t;
double rho, theta, arc;
int signy;

	cosphi = cos(phi);
	sinphi = sin(phi);
	cosd   = cos(d);
	sind   = sin(d);
	cosdelta = cos(delta);
	sindelta = sin(delta);
	coshora = cos(hora);
	sinhora = sin(hora);
	sininc = sin(inc);
	cosinc = cos(inc);

	a = sindelta*cosphi + cosdelta*coshora*sinphi;
	b = -cosdelta*sinhora;
	c = sindelta*sinphi - cosdelta*coshora*cosphi;

	R = 1.0;
	H = 2.0;

	SA = atan(R/H);

	t = H*R / (H*sqrt(a*a+b*b)-c*R );

	x = a*t;
	y = b*t;
	z = c*t;

	signy = (y >= 0.0) ? 1 : -1;

	r     = R*(H+z)/H;

	arc   = x>=0.0 ? r*asin(y/r) : signy*(0.5*PI*r + r*acos(fabs(y)/r));
	
	rho   = (H+z)/cos(SA);
	theta = arc / rho;

	Xs = rho*sin(theta);
	Ys = rho*cos(theta);

	return 0;
}


int con_op(double delta,double hora)  // Conica con occhiello posteriore 
{
double x,y,z;
double R, H, r, SA;
double a,b,c,t;
double rho, theta, arc;
int signy;

	cosphi = cos(phi);
	sinphi = sin(phi);
	cosd   = cos(d);
	sind   = sin(d);
	cosdelta = cos(delta);
	sindelta = sin(delta);
	coshora = cos(hora);
	sinhora = sin(hora);
	sininc = sin(inc);
	cosinc = cos(inc);

	a = sindelta*cosphi + cosdelta*coshora*sinphi;
	b = -cosdelta*sinhora;
	c = sindelta*sinphi - cosdelta*coshora*cosphi;

	R = 1.0;
	H = 6.0;

	SA = atan(R/H);

	t = (2*R*(a+c*R/H)) / ( (a*a+b*b)-(c*c*R*R)/(H*H));

	x = a*t-R;
	y = b*t;
	z = c*t;

	signy = (y >= 0.0) ? 1 : -1;

	r     = R*(H+z)/H;

	arc   = x>=0.0 ? r*asin(y/r) : signy*(0.5*PI*r + r*acos(fabs(y)/r));
	
	rho   = (H+z)/cos(SA);
	theta = arc / rho;

	Xs = rho*sin(theta);
	Ys = rho*cos(theta);

	return 0;
}


int con_ans(double delta,double hora)
{
double x,y,z;
double hg,dv,p;
double t1,t2,t;
double yg, zg;
double yg2,zg2;
double k,k2;
double rx2,ry2,rz2;
double dis, disa, disa2;
int segnoyg, segnox, segnoy;
double r,gamma, l;
double rho,theta;

	compute_ray(delta,hora);

    /*
	Questo che segue serve per calolare yg e zg dati:
	dv = posizione del piede dell'ortostilo lungo la generatrice
	hg = altezza dell'ortostilo
	p  = pendenza della generatrice => (90 - p) semiapertura cono
	*/
	dv = a2;  //a2,b2,c2 sono variabili di ingresso che contengono dv,hg e p
	hg = b2;
	p  = c2;

	p   = gra_to_rad(p);

    //col segno di dv comunico che voglio yg > 0 o yg < 0
	segnoyg = (dv >= 0) ? 1 : -1;
	dv  = fabs(dv);

	/* Qui calcolo diversamente yg e zg ma la formula e' equivalente a quella del fax */
    yg = (segnoyg == 1) ? (dv*cos(p) + hg*sin(p)) : -(dv*cos(p) + hg*sin(p));
    zg = - (dv*sin(p) -hg*cos(p));

     /* fine calcolo yg, zg */
	 // (ovviamente non occorre calcolarlo  ogni ciclo 
	 //  ma può essere fatto una tantum fuori dal ciclo)
	
	k   = 1.0/tan(p);
	k2  = k*k;
	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;

	yg2 = yg*yg;
	zg2 = zg*zg;
	
	disa  = rz*yg-ry*zg;
	disa2 = disa*disa;

	dis = k2*disa2 + rx2*(k2*zg2-yg2);

	
	if( dis  >=0 )
	{
		t1 = ( rz*zg*k2-ry*yg-sqrt(dis) ) / (rx2+ry2-k2*rz2);
		t2 = ( rz*zg*k2-ry*yg+sqrt(dis) ) / (rx2+ry2-k2*rz2);

		t = t1;  /* t1 propaga il raggio in avanti */

		x = rx*t;
		y = ry*t + yg;
		z = rz*t + zg;


        /* Questo che segue serve solo per lo sviluppo del cono su un piano */
		segnoy = (y >= 0) ? 1 : -1;
		y  = fabs(y);

		r     = sqrt(x*x + y*y);
		gamma = (segnoy == 1) ? PI/2 + asin(y/r) : acos(y/r);
		l     = r*gamma;


		rho   = sqrt(x*x + y*y + z*z);
		theta = l/rho;

		segnox = (x >= 0) ? 1 : -1;
		
		Xs = segnox*rho*sin(theta);
		Ys = segnoy*rho*cos(theta);
	}
	return(0);
}
	

int bullnose_completa(double delta, double hora)
{
double x,y,z;
double alfa, xg, zg, zc, p;
double ratio;
double rx2,rz2;
double t, teastwall, tcylinder, twestwall;
double R, hg;
double m, s, Le,Lw, L, elle;
int    segnox, segnoz;
double theta;

int  zona_attuale;


double gamma;


    /*
	Questo che segue  serve solo per calcolare xg, zg e zc 
	e poteva essere fatto fuori dal ciclo:
	xg, zg = coordinate dell'ortostilo (yg = 0)
	hg = base triangolo sustilare
	p  = declinazione all'indietro delle pareti verticali
	*/

	cosphi = cos(phi);
	sinphi = sin(phi);
	cosd   = cos(d);
	sind   = sin(d);
	sininc = sin(inc);
	cosinc = cos(inc);

    alfa  = a1; //a1, a2,b2,c2 sono variabili di ingresso che contengono R,hg e p
    gamma = b1;

	R    = a2;  
	hg   = b2;
	p    = c2;

	alfa  = gra_to_rad(alfa);
    gamma = gra_to_rad(gamma);
	p    = gra_to_rad(p);
    m    = tan(p);
	s    = R*sin(alfa);

	zc   = -( R*cos(alfa)+m*s );
	hg   = hg; //valore fornito da b2

	//zg   = R + zc + hg*cosd;      //Caso B
	//xg   = hg*sind;

    //zg = (R+hg)*cos(gamma)+zc;    //Caso A
	//xg = (R+hg)*sin(gamma);


	// Caso A gamma = d, dh = 0, dg = 0 
	// Caso B gamma = 0, dh = d, dg = atan ( hg*sind / (R+hg*cosd) )
	zg = R*cos(gamma) + hg*cosd + zc;  
    xg = R*sin(gamma) + hg*sind;       


	Le   = (xg-s) / (zg + m*s);   // confine cilindro-piano del rapporto rx/rz 
    Lw   = (xg+s) / (zg + m*s);

	elle = R*alfa;           // lunghezza semiarco

	compute_ray(delta,hora);  // calcola rx,ry e rz

    ratio = (rx / rz);

	zona_attuale = zona;

    if ( (rz < 0.0) && ( fabs(ratio) < tan( (PI/2) - p)) ) 
	{


	rx2=rx*rx;
	rz2=rz*rz;

	teastwall = -((m*xg + zg)/(m*rx + rz));
    tcylinder = (-rx*xg+rz*(zc-zg)-sqrt(R*R*(rx2 + rz2)-(rz*xg+rx*zc-rx*zg)*(rz*xg+rx*zc-rx*zg)))/(rx2+rz2);
	twestwall = -((m*xg - zg)/(m*rx - rz));

	if (ratio > Lw)
		{
		t = twestwall;
		x = rx*t + xg;
		y = ry*t;
		z = rz*t + zg;
		
		Xs = -elle + (x+s) / cos(p);
		Ys = y;
		zona_attuale = 1;
		}
	else if (ratio < Le)
		{
		t = teastwall;
		x = rx*t + xg;
		y = ry*t;
		z = rz*t + zg;
		
		Xs = elle + (x-s) / cos(p);
		Ys = y;
		zona_attuale = 3;
		} 
	else                 
		{
		t = tcylinder;
		x = rx*t + xg;
		y = ry*t;
		z = rz*t + zg;
		
		/* Questo che segue serve solo per lo sviluppo del bullnose su un piano */
		segnox = (x >= 0)  ? 1 : -1;
		segnoz = (z >= zc) ? 1 : -1;  //segno di z rispetto zc
		
		theta  = (segnoz == 1) ?  asin(x/R) : (segnox)*(PI/2 + asin(fabs(z)/R));
		
		segnox = (x >= 0) ? 1 : -1;
		
		Xs = R*theta;
		Ys = y;
		
		zona_attuale = 2;
		}
	
	
	return 0;  //FINE se non faccio la ricerca dicotomica esce qui.


	/* Test di attraversamento zona */
	if ( (zona == 0) || (zona == zona_attuale) )
		{
		delta1 = delta;
		hora1  = hora;
		zona   = zona_attuale;
		return 0;
		}
	else  // il raggio ha cambiato zona
		{
		int trans;
		
		/* Ricerca dicotomica del punto di attraversamento */        

		trans = zona*10+zona_attuale; //Così 21 significa 2->1, 23 significa 2->3

		delta2 = delta;
		hora2  = hora;

        L = ( fabs(ratio-Le) < fabs(ratio-Lw) ) ? Le : Lw;

		while( R*fabs(ratio-L) > 0.001 )
			{
			deltaM = (delta1+delta2)/2;
			horaM  = (hora1+hora2)/2;
            compute_ray(deltaM,horaM);  // calcola di nuovo rx,ry e rz

			ratio = rx/rz;
			switch(trans)
				{
				case 12:
					if(ratio < Lw)
					{
					delta2  = deltaM; 
					hora2   = horaM;
					}
					else
					{
					delta1 = deltaM; 
					hora1  = horaM;
					}
					break;
				case 21:
					if(ratio > Lw)
					{
					delta2  = deltaM; 
					hora2   = horaM;
					}
					else
					{
					delta1 = deltaM; 
					hora1  = horaM;
					}
					break;
				case 23:
					if(ratio < Le)
					{
					delta2  = deltaM; 
					hora2   = horaM;
					}
					else
					{
					delta1 = deltaM; 
					hora1  = horaM;
					}
					break;
				case 32:
					if(ratio > Le)
					{
					delta2  = deltaM; 
					hora2   = horaM;
					}
					else
					{
					delta1 = deltaM; 
					hora1  = horaM;
					}
					break;
			    default:
					printf("Non dovrebbe mai accadere\n");
					getch();
					exit(1);
				}

			}

		return 1;
		}
	}

	return -1;
   
}



int bullnose_ridotta(double delta, double hora)
{
double x,y,z;
double xg, zg, zc;
double rx2,rz2,xg2;
double t,t1,t2;
double R, hg;
int    segnox, segnoz;
double theta;



    /*
	Questo che segue  serve solo per calcolare xg, zg e zc 
	e poteva essere fatto fuori dal ciclo:
	xg, zg = coordinate dell'ortostilo (yg = 0)
	hg = base triangolo sustilare
	*/

	cosphi = cos(phi);
	sinphi = sin(phi);
	cosd   = cos(d);
	sind   = sin(d);
	sininc = sin(inc);
	cosinc = cos(inc);

    //a2,b2 sono variabili di ingresso che contengono R,hg

	R    = a2;  
	hg   = b2;


	hg   = hg; //valore fornito da b2

	zg   = hg*cosd;      //Caso B
	xg   = hg*sind;
	xg2 = xg*xg;

	compute_ray(delta,hora);  // calcola rx,ry e rz

	rx2=rx*rx;
	rz2=rz*rz;

	//t1 = -((rx*xg + rz*(R + zg) + Sqrt[(rx*xg + rz*(R + zg))^2 - (rx^2 + rz^2)*(xg^2 + zg*(2*R + zg))])/(rx^2 + rz^2))
	//t2 = (-(rx*xg + rz*(R + zg)) + Sqrt[(rx*xg + rz*(R + zg))^2 - (rx^2 + rz^2)*(xg^2 + zg*(2*R + zg))])/(rx^2 + rz^2)
	t1 = -((rx*xg + rz*(R + zg) + sqrt((rx*xg + rz*(R + zg))*(rx*xg + rz*(R + zg)) - (rx2 + rz2)*(xg2 + zg*(2*R + zg))))/(rx2 + rz2));
	t2 = (-(rx*xg + rz*(R + zg)) + sqrt((rx*xg + rz*(R + zg))*(rx*xg + rz*(R + zg)) - (rx2 + rz2)*(xg2 + zg*(2*R + zg))))/(rx2 + rz2);

	t = t1;
	x = rx*t + xg;
	y = ry*t;
	z = rz*t + zg;
	
	// Questo che segue serve solo per lo sviluppo della bullnose su un piano

	zc = -R;
	segnox = (x >= 0)  ? 1 : -1;
	segnoz = (z >= zc) ? 1 : -1;  //segno di z rispetto zc
	
	theta  = (segnoz == 1) ?  asin(x/R) : (segnox)*(PI/2 + asin((fabs(z)-R)/R));
	
	Xs = R*theta;
	Ys = y;

	return 0;
}



// Cilindro verticale: L'ombra dell'orlo si proietta all'interno 
// e viene vista in trasparenza da nord
 
int cyl_a_cornice(double delta,double hora) 
{
double x,y,z;
double xc, yc, zc;
double R;
double t;
double Teta;
double A,B;

	compute_ray_1(delta,hora);

	R = 1.0;

        //Calcola Teta imponendo hx * (dxc/dTeta) + hy * (dyc/dTeta) + hz * (dzc/dTeta) = 0
        //Ove h è il versore della normale al piano orario H e cioé:
        // hx = cos(H)    hy = sin(H)*cos(phi)     hz = sin(H)*sin(phi)

        //Nel facile caso della cornice a cerchio si ha:
        
        Teta = atan(   -1.0/( tan(hora)*sin(phi) )   );

            
        xc = R  * sin(Teta);
        yc = 0.0;
        zc = -R * cos(Teta);

        A = rx*rx + rz*rz;
        B = rx*xc + rz*zc;
 
  
        t = -2*B/A;            // controllare il segno
 
	x = rx*t + xc;
	y = ry*t;
	z = rz*t+ zc;

        if (flatland == 1)
            {
            Ys=y;
	    if((z<=0)&&(x>=0))
	        {
	        Xs = R*asin(fabs(x)/R);
	        }
	    else if((z>0)&&(x>=0))
	        {
	        Xs= R*(0.5*PI + acos(fabs(x)/R));
	        }
	    else if((z>0)&&(x<0))
	        {
	        Xs = -R*(0.5*PI + acos(fabs(x)/R));
	        }
	    else 
	        {
	        Xs = -R*(asin(fabs(x)/R));
	        }
            }
        else
            {
            Xs = x;      //Per Ghia che simula su AutoCAD e SketchUp
            Ys = -z;
            Zs = y;
            }
 
	return 0;
}

// Tronco_Cono rovesciato verticale: L'ombra dell'orlo si proietta all'interno 
// e viene vista in trasparenza da nord
 
int con_a_cornice(double delta,double hora) 
{
double x,y,z;
double xc, yc, zc;
double RT,RB,a,K,Ac;
double t,t1,t2;
double Teta;
double A,B,discr;
double theta,rho,r,SA,arc;
int    signx;

	compute_ray_1(delta,hora);

	RT = a1;  //raggio superiore
        RB = b1;  //raggio inferiore
        a  = c1;  //altezza 

 
        //Calcola Teta imponendo hx * (dxc/dTeta) + hy * (dyc/dTeta) + hz * (dzc/dTeta) = 0
        //Ove h è il versore della normale al piano orario H e cioé:
        // hx = cos(H)    hy = sin(H)*cos(phi)     hz = sin(H)*sin(phi)

        //Nel facile caso della cornice a cerchio si ha:
        
        Teta = atan(   -1.0/( tan(hora)*sin(phi) )   );

            
        xc = RT  * sin(Teta);
        yc = 0.0;
        zc = -RT * cos(Teta);


        K = a/(RT-RB);
        Ac = K*RT;



        A = Ac*Ac*(rx*rx + rz*rz) - RT*RT*ry*ry;

        B = Ac*(Ac*(rx*xc + rz*zc) - RT*RT*ry);

        //C = RT*RT - xc*xc - zc*zc;
               
        discr = B*B; //+ A*C;

        t1 = (-B + sqrt(discr))/A;
        t2 = (-B - sqrt(discr))/A;

        t = t1;
        
	x = rx*t + xc;
	y = ry*t;
	z = rz*t+ zc;

        if (flatland == 1)
            {
            Xs = x;    //PER DEBUG
            Ys = y;
            return 0;

            SA = atan(RT/Ac);

            signx = (x >= 0.0) ? 1 : -1;            

            r = RT*(Ac+y)/Ac;

	    arc   = z<=0.0 ? r*asin(x/r) : signx*(0.5*PI*r + r*acos(fabs(x)/r));
	
	    rho   = (Ac+y)/cos(SA);
	    theta = arc / rho;

	    Xs = rho*sin(theta);
	    Ys = rho*cos(theta);
            }
        else
            {
            Xs = x;      //Per Ghia che simula su AutoCAD e SketchUp
            Ys = -z;
            Zs = y;
            }
 
	return 0;
}



/**** INIZIO CALCOLO ****/
int point(double d,double h)
{
int rc;
 
	switch (tipo)
	{
		case 0: rc = piana(d,h);
				break;
		case 1: rc = piana_riflessa_1(d,h);
				break;
		case 2: rc = piana_riflessa_2(d,h);
				break;
		case 3: rc = piana_rifratta_1(d,h);
				break;
		case 4: rc = piana_rifratta_2(d,h);
				break;
		case 5: rc = piana_rifratta_3(d,h);
				break;
		case 6: rc = piana_rifratta_4(d,h);
				break;
		case 7: rc = piana_rifratta_5(d,h); //piana_rifratta_6(d,h);
				break;
		case 8: rc = piana_rifratta_7(d,h);
				break;
		case 9: rc = bif_retta_cerchio_generale_1(d,h);
				break;
		case 11: rc = bif_saturno_1(d,h);
				break;
		case 12: rc = bif_saturno_2(d,h);
				break;
		case 13: rc = bif_saturno_3_semplice(d,h);
				break;
		case 14: rc = sferica_gen(d,h);
				break;
		case 15: rc = bif_retta_catenaria(d,h);
				break;
		case 16: rc = bif_2_rette(d,h);
				break;
		case 17: rc = bif_2_rette_Rouxel(d,h);
				break;
		case 18: rc = bif_rettaverticale_cerchio(d,h);
				break;
		case 19: rc = bif_parabola_catenaria_muro_inc_dec(d,h);
				break;
		case 20: rc = bullnose_ridotta(d,h);
				break;	
		case 21: rc = con_genSRG(d,h);
				break;
		case 22: rc = con_ans(d,h);
				break;
		case 23: rc = bif_cat_cat(d,h);
				break;
		case 24: rc = cyl_a_cornice(d,h);
				break;
		case 25: rc = con_a_cornice(d,h);
				break;
		case 26: rc = piana_monaco(d,h);
				break;
 	}

	switch(rc)
	{
		case -1:
			break;
		case 0:
			if(flatland == 1)
			    fprintf(fp_out,"%s\t%lf\t%lf\t%s\n",datatype,Xs,Ys,layer);
            else
			    fprintf(fp_out,"%s\t\t%lf\t\t%lf\t\t%lf\t\t%s\n",datatype,Xs,Ys,Zs,layer);
			break;
		case 1:
			zona = 0;                     //reset
			rc = point(deltaM,horaM);
			zona = 0;
			rc = point(d,h); 
			break;
	}


    strcpy(datatype,"Not specified");
	return rc;

}

void lemnid()
{
int iora;
double dec;

    for (ora = orai; ora < orau; ora += hstepl)
    {
    t = ora + deltalamda - 12;

    /*Calcolo di una lemniscata oraria */
    zona = 0;
    for (k = 0; k <= DIM/2; k++)
        {													
        sprintf(datatype,"LEMNID_%02d:%02d",(int)ora,(int)(100*(ora-(int)ora)*60/100));
//        deltat = t + minsec_to_ore(epsm[k]);
        deltat = t + (epsm[k]);
        deltat *= 15.0;                            /* conv. in gradi */
        deltat = gra_to_rad(deltat);               /* conv. in rad.  */

//        dec = grapri_to_gradec(delta[k]);             /* conv. in gradec */
        dec = (delta[k]);                               /* conv. in gradec */
        dec = gra_to_rad(dec);                          /* conv. in rad.   */

 
        iora = (int)ora;
		if( (ora-iora) != 0.0  )
			strcpy(layer,"LEMNID");
		else
			strcpy(layer,"ORARIELD");
 
		if ( point(dec,deltat) == -1 ) break;
        }
    fprintf(fp_out,"* 0 0 %s\n",layer);
    }
}

void lemnia()
{
int iora;
double dec;

    strcpy(layer,"LEMNIA");
    for (ora = orai; ora < orau; ora += hstepl)
    {
    t = ora + deltalamda - 12;

    /*Calcolo di una lemniscata oraria */
    zona = 0;
    for (k = DIM-1; k >= DIM/2; k--)
        {
        sprintf(datatype,"LEMNID_%02d:%02d",(int)ora,(int)(100*(ora-(int)ora)*60/100));
//        deltat = t + minsec_to_ore(epsm[k]);
        deltat = t + (epsm[k]);
        deltat *= 15.0;                            /* conv. in gradi */
        deltat = gra_to_rad(deltat);               /* conv. in rad.  */

//        dec = grapri_to_gradec(delta[k]);           /* conv. in gradec */
        dec = (delta[k]);                             /* conv. in gradec */
        dec = gra_to_rad(dec);                        /* conv. in rad.   */

        iora = (int)ora;
		if( (ora-iora) != 0.0  )
			strcpy(layer,"LEMNIA");
		else
			strcpy(layer,"ORARIELA");

        if ( point(dec,deltat) == -1 ) break;
        }
    fprintf(fp_out,"* 0 0 %s\n",layer);
    }
}


void diurna(declinazione)
double declinazione;
{
double dec;


     /* Calcolo di una linea diurna */
     zona = 0;
     for(ora = tisigma; ora > orai-0.5; ora -= diustep)
       {
       sprintf(datatype,"DIURNA(%.2f)",declinazione);
	   t = ora - 12;       
       deltat = t;
       deltat *= 15.0;                            /* conv. in gradi */
       deltat = gra_to_rad(deltat);               /* conv. in rad. */
       dec = grapri_to_gradec(-declinazione);        /* conv. in gradec */
       dec = gra_to_rad(dec);                          /* conv. in rad. */

       if ( point(dec,deltat) == -1 ) break;
       }

     fprintf(fp_out,"* 0 0 %s\n",layer);

	 zona = 0;
     for(ora = tisigma; ora < orau+0.5; ora += diustep)
       {
       sprintf(datatype,"DIURNA(%.2f)",declinazione);
	   t = ora - 12;       
       deltat = t;
       deltat *= 15.0;                            /* conv. in gradi */
       deltat = gra_to_rad(deltat);               /* conv. in rad. */
       dec = grapri_to_gradec(-declinazione);        /* conv. in gradec */
       dec = gra_to_rad(dec);                        /* conv. in rad. */

	   if ( point(dec,deltat) == -1 ) break;
       }

     fprintf(fp_out,"* 0 0 %s\n",layer);
}

void solistizi()
{
    strcpy(layer,"SOLISTIZI");
    diurna(deltaz[0]);
    diurna(deltaz[6]);
}

void diurnezod()
{
int k;
    strcpy(layer,"DIURNEZOD");
    for (k = 0; k < 7; k++)
        {
        diurna(deltaz[k]);
        }
}

void diurnemns()
{
int k;
    strcpy(layer,"DIURNEMNS");
    for(k = 0; k < 12; k++)
     {
     //diurna(deltam[k]); 
     }
	diurna(-14.1333); //nascita di Filippo Rappoli 14/08=14.1333  (ovvero 24/08=10.8500)
}

void oraria(double delta)
{
        sprintf(datatype,"ORAVERA(%.2f)",t);

        deltat = t - 12;
        deltat *= 15.0;                            /* conv. in gradi */
        deltat = gra_to_rad(deltat);               /* conv. in rad. */

        delta = gra_to_rad(delta);                          /* conv. in rad. */
       
        if ( point(delta,deltat) == -1 ) 
			return;

}

void orariafuso(double delta)
{
        sprintf(datatype,"ORAFUSO(%.2f)",t);

        deltat = t + deltalamda - 12;
        deltat *= 15.0;                            /* conv. in gradi */
        deltat = gra_to_rad(deltat);               /* conv. in rad. */

        delta = gra_to_rad(delta);                          /* conv. in rad. */
       
        if ( point(delta,deltat) == -1 ) 
			return;

}



void orarie()
{
double delta;

     strcpy(layer,"ORARIE");
     /* Calcolo delle linee orarie */
     for(ora = orai; ora < orau; ora += hstepo)
       {
	   t = ora; 
           zona = 0;
		   for(delta = -24.0 ; delta < 24; delta += 1.0)
		   {
			   oraria(delta);
		   }
		   fprintf(fp_out,"* 0 0 %s\n",layer);
       }
}

void orariefuso()
{
double delta;

     strcpy(layer,"ORARIEFUSO");
     /* Calcolo delle linee orarie */
     for(ora = orai; ora < orau; ora += hstepo)
       {
	   t = ora; 
           zona = 0;
		   for(delta = -24.0 ; delta < 30; delta += 1.0)
		   {
			   orariafuso(delta);
		   }
		   fprintf(fp_out,"* 0 0 %s\n",layer);
       }
}

void mezzore()
{
int k;

     strcpy(layer,"MEZZORE");
     /* Calcolo delle linee orarie */
     for(ora = orai+0.5; ora < orau-0.5; ora += hstepo)
       {
		   t = ora;
       
           zona = 0;
		   for(k= 0; k < DIM/2; k++)
		   {
			   oraria(k);
		   }
		   fprintf(fp_out,"* 0 0 %s\n",layer);
       }
}

void linee_notevoli()
{
    strcpy(layer,"ORIZZONTE");
/* Tracciamento Orizzonte */
     fprintf(fp_out,"Inizio %lf\t%lf\t%s\n",-mextx,0.0,layer );
     fprintf(fp_out,"Fine   %lf\t%lf\t%s\n", mextx,0.0,layer );
     fprintf(fp_out,"* 0 0 %s\n",layer);

    strcpy(layer,"MERIDIANA");
/* Tracciamento Meridiana */
     x = -cos(epsilon)*sin(sigma);
     fprintf(fp_out,"Inizio %lf\t%lf\t%s\n",x,0.0,layer );
     fprintf(fp_out,"Fine   %lf\t%lf\t%s\n",x,-mexty,layer );
     fprintf(fp_out,"* 0 0 %s\n",layer);

    strcpy(layer,"D_PARETE");
/* Tracciamento Azimut di Declinazione parete */
     x = 0.0;
     fprintf(fp_out,"Inizio  %lf\t%lf\t%s\n",x,0.0,layer );
     fprintf(fp_out,"Fine    %lf\t %lf\t%s\n",x,-mexty,layer );
     fprintf(fp_out,"* 0 0 %s\n",layer);

    strcpy(layer,"SUSTILARE");
/* Tracciamento Sustilare */
//     t = tisigma;
//     oraria(DIM/2);
     
     x =  -cos(phi) * sin(d);     y =   sin(phi);
     fprintf(fp_out,"Inizio  %lf   %lf\t%s\n",x,y,layer );
     x += mextx * sin(sigma);  y -= mextx * cos(sigma);
     fprintf(fp_out,"Fine    %lf     %lf\t%s\n",x,y,layer );
     fprintf(fp_out,"* 0 0 %s\n",layer);

     strcpy(layer,"EQUINOZIALE");
/* Calcolo della linea equinoziale */
    diurna(deltaz[3]);
}

void trian()
{
double  xa,ya;
double  xb,yb;
double  xc,yc;

 /* Tracciamento Triangolo stilare */
     xa =   0.0;                   ya =   0.0;
     xb =  -cos(phi) * sin(d);     yb =   sin(phi);

     xc = fabs(sin(epsilon)*cos(sigma));
     xc = (d > 0) ? xa + xc : xa - xc;
     yc = ya +fabs(sin(epsilon)) * fabs(sin(sigma));

     strcpy(layer,"TRIANSUS");
     fprintf(fp_out,"puntoA %lf\t%lf\t%s\n",xa,ya,layer);  
     fprintf(fp_out,"puntoB %lf\t%lf\t%s\n",xb,yb,layer);
     fprintf(fp_out,"puntoC %lf\t%lf\t%s\n",xc,yc,layer);
     fprintf(fp_out,"puntoA %lf\t%lf\t%s\n",xa,ya,layer);
     fprintf(fp_out,"* 0 0 %s\n",layer);

	 printf("\n\n<Lati triangolo sustilare: % .4f, % .4f, % .4f>\n", 1.00, cos(epsilon),fabs(sin(epsilon)));

}


void punti_notevoli()
{
/* Tracciamento Centro Stilo */
     strcpy(layer,"PIEDEGNOMON");
     fprintf(fp_out,"Hl -0.1   0.0\t%s\n",layer);
     fprintf(fp_out,"Hl  0.1   0.0\t%s\n",layer);
     fprintf(fp_out,"* 0 0 %s\n",layer);
     fprintf(fp_out,"Vl  0.0   0.1\t%s\n",layer);
     fprintf(fp_out,"Vl  0.0  -0.1\t%s\n",layer);
     fprintf(fp_out,"* 0 0 %s\n",layer);

/* Tracciamento Piede Gnomone (intersezione Sustilare-Orizzonte) */
     strcpy(layer,"PIEDESTILO");
     x = -tan(sigma)*sin(phi);
     y = sin(phi);
     fprintf(fp_out,"Hl %lf %lf\t%s\n",-0.1+x,y,layer);
     fprintf(fp_out,"Hl %lf %lf\t%s\n", 0.1+x,y,layer);
     fprintf(fp_out,"* 0 0 %s\n",layer);
     fprintf(fp_out,"Vl %lf %lf\t%s\n",x,  0.1+y,layer );
     fprintf(fp_out,"Vl %lf %lf\t%s\n",x, -0.1+y,layer );
     fprintf(fp_out,"* 0 0 %s\n",layer);


/* Tracciamento (intersezione Meridiana-Orizzonte) */
     strcpy(layer,"CROCEMEOR");
//     x = 0.0;
//     y = -sin(phi);
     x = -tan(sigma)*sin(phi);
     y = 0.0;
     fprintf(fp_out,"Hl %lf %lf\t%s\n",-0.1+x,y,layer);
     fprintf(fp_out,"Hl %lf %lf\t%s\n", 0.1+x,y,layer);
     fprintf(fp_out,"* 0 0 %s\n",layer);
     fprintf(fp_out,"Vl %lf %lf\t%s\n",x,  0.1+y,layer );
     fprintf(fp_out,"Vl %lf %lf\t%s\n",x, -0.1+y,layer );
     fprintf(fp_out,"* 0 0 %s\n",layer);
  }

void azimut()
{
double a;
double o;
double z, tz;
double le,lw;

     strcpy(layer,"AZIMUT");

     le  =  -azmax;
     lw  =   azmax;
     //o   =  -sin(phi);
	 o = 0.0;

     for(a = 0.0; a <= lw; a += azstep)
        {
        z  = gra_to_rad(a);
        tz = cos(phi)*cos(d)*tan(d+z);

        if( (fabs(tz) < mextx) )
          {
          fprintf(fp_out,"Az %lf\t%lf\t%s\n",tz,     o, layer );
          fprintf(fp_out,"Az %lf\t%lf\t%s\n",tz,-mexty,layer );
          fprintf(fp_out,"* 0 0 %s\n",layer);
          }
        else break;
        }

     for(a = 0.0; a >= le; a -= azstep)
        {
        z  = gra_to_rad(a);
        tz = cos(phi)*cos(d)*tan(d+z);

        if( (fabs(tz) < mextx) )
          {
          fprintf(fp_out,"Az %lf\t%lf\t%s\n",tz,     o, layer );
          fprintf(fp_out,"Az %lf\t%lf\t%s\n",tz,-mexty,layer );
          fprintf(fp_out,"* 0 0 %s\n",layer);
          }
        else break;
        }
}

void almucant()
{
double a,b;
double o;
double h, th, z, tz;
double le,lw;
double ca;

     strcpy(layer,"ALMUCANT");

     le  =  -azmax;
     lw  =   azmax;
     //o   =  -sin(phi);
	 o = 0.0;

if(1){

     for(b = 0; b <= almmax; b += almstep)
        {
        h = gra_to_rad(b);

        for(a = d; a <= lw; a += 1.0)
           {
           z  = gra_to_rad(a);
           tz = cos(phi)*cos(d)*tan(d+z);
           ca = cos(phi)*cos(d);
		   th = -sqrt(ca*ca+tz*tz)*tan(h);
           if( (fabs(tz) < mextx) && (fabs(o + th) < mexty) )
                fprintf(fp_out,"Alm %lf %lf\t%s\n",tz,o + th,layer);
           else break;
           }
        fprintf(fp_out,"* 0 0 %s\n",layer);

        for(a = d; a >= le; a -= 1.0)
           {
           z  = gra_to_rad(a);
           tz = cos(phi)*cos(d)*tan(d+z);
           ca = cos(phi)*cos(d);
		   th = -sqrt(ca*ca+tz*tz)*tan(h);
           if( (fabs(tz) < mextx) && (fabs(o + th) < mexty) )
                fprintf(fp_out,"Alm %lf %lf\t%s\n",tz,o + th,layer);
           else break;
           }
        fprintf(fp_out,"* 0 0 %s\n",layer);
        }
}

        if(1){
		h = PI/2 - phi + gra_to_rad(grapri_to_gradec(23.26));

        for(a = d; a <= lw; a += 1.0)
           {
           z  = gra_to_rad(a);
           tz = cos(phi)*cos(d)*tan(d+z);
           ca = cos(phi)*cos(d);
		   th = -sqrt(ca*ca+tz*tz)*tan(h);
           if( (fabs(tz) < mextx) && (fabs(o + th) < mexty) )
                fprintf(fp_out,"Alm %lf %lf\t%s\n",tz,o + th,layer);
           else break;
           }
        fprintf(fp_out,"* 0 0 %s\n",layer);

        for(a = d; a >= le; a -= 1.0)
           {
           z  = gra_to_rad(a);
           tz = cos(phi)*cos(d)*tan(d+z);
           ca = cos(phi)*cos(d);
		   th = -sqrt(ca*ca+tz*tz)*tan(h);
           if( (fabs(tz) < mextx) && (fabs(o + th) < mexty) )
                fprintf(fp_out,"Alm %lf %lf\t%s\n",tz,o + th,layer);
           else break;
           }
        fprintf(fp_out,"* 0 0 %s\n",layer);
        }

        if(1){
		h = PI/2 - phi - gra_to_rad(grapri_to_gradec(23.26));

        for(a = d; a <= lw; a += 1.0)
           {
           z  = gra_to_rad(a);
           tz = cos(phi)*cos(d)*tan(d+z);
           ca = cos(phi)*cos(d);
		   th = -sqrt(ca*ca+tz*tz)*tan(h);
           if( (fabs(tz) < mextx) && (fabs(o + th) < mexty) )
                fprintf(fp_out,"Alm %lf %lf\t%s\n",tz,o + th,layer);
           else break;
           }
        fprintf(fp_out,"* 0 0 %s\n",layer);

        for(a = d; a >= le; a -= 1.0)
           {
           z  = gra_to_rad(a);
           tz = cos(phi)*cos(d)*tan(d+z);
           ca = cos(phi)*cos(d);
		   th = -sqrt(ca*ca+tz*tz)*tan(h);
           if( (fabs(tz) < mextx) && (fabs(o + th) < mexty) )
                fprintf(fp_out,"Alm %lf %lf\t%s\n",tz,o + th,layer);
           else break;
           }
        fprintf(fp_out,"* 0 0 %s\n",layer);
        }
}

/*** FUNZIONI PER I SISTEMI ****/
//Cerco le coordinate del punto di incidenza utile per la rifratta 4
FLOAT func1s(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;

    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;
    f  = x*x + y*y + z*z - R*R;
	return f;
}

FLOAT func2s(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;
FLOAT nx, ny, nz;
FLOAT bx,by,bz;
FLOAT xg,yg,zg;
FLOAT appo;

    xg = 0;
	yg = -c;
	zg = g;


    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;

	nx = x/R;
	ny = y/R;
	nz = z/R;

/***
bx = (-ay*ny*nx - az*nz*nx - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nx + ax*(1 - x^2))/nr
by = (-ax*nx*ny - az*nz*ny - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*ny + ay*(1 - y^2))/nr
bz = (-ax*nx*nz - ay*ny*nz - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nz + az*(1 - z^2))/nr
***/

	appo = (rx*nx+ry*ny+rz*nz);
	bx = (-ry*ny*nx - rz*nz*nx - sqrt(nr*nr + appo*appo - 1)*nx + rx*(1 - nx*nx))/nr;
	by = (-rx*nx*ny - rz*nz*ny - sqrt(nr*nr + appo*appo - 1)*ny + ry*(1 - ny*ny))/nr;
	bz = (-rx*nx*nz - ry*ny*nz - sqrt(nr*nr + appo*appo - 1)*nz + rz*(1 - nz*nz))/nr;


//    f  = (bx/(x-xg)) - (by/(y-yg));
    f  = ((x-xg)/bx) - ((y-yg)/by);
	return f;
}

FLOAT func3s(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;
FLOAT nx, ny, nz;
FLOAT bx,by,bz;
FLOAT xg,yg,zg;
FLOAT appo;

    xg = 0;
	yg = -c;
	zg = g;


    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;

	nx = x/R;
	ny = y/R;
	nz = z/R;

/***
bx = (-ay*ny*nx - az*nz*nx - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nx + ax*(1 - x^2))/nr
by = (-ax*nx*ny - az*nz*ny - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*ny + ay*(1 - y^2))/nr
bz = (-ax*nx*nz - ay*ny*nz - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nz + az*(1 - z^2))/nr
***/

	appo = (rx*nx+ry*ny+rz*nz);
	bx = (-ry*ny*nx - rz*nz*nx - sqrt(nr*nr + appo*appo - 1)*nx + rx*(1 - nx*nx))/nr;
	by = (-rx*nx*ny - rz*nz*ny - sqrt(nr*nr + appo*appo - 1)*ny + ry*(1 - ny*ny))/nr;
	bz = (-rx*nx*nz - ry*ny*nz - sqrt(nr*nr + appo*appo - 1)*nz + rz*(1 - nz*nz))/nr;


//    f  = (bx/(x-xg)) - (bz/(z-zg));
    f  = ((x-xg)/bx) - ((z-zg)/bz);
	return f;
}


FLOAT func4s(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;
FLOAT nx, ny, nz;
FLOAT bx,by,bz;
FLOAT xg,yg,zg;
FLOAT appo;

    xg = 0;
	yg = -c;
	zg = g;


    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;

	nx = x/R;
	ny = y/R;
	nz = z/R;

/***
bx = (-ay*ny*nx - az*nz*nx - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nx + ax*(1 - x^2))/nr
by = (-ax*nx*ny - az*nz*ny - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*ny + ay*(1 - y^2))/nr
bz = (-ax*nx*nz - ay*ny*nz - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nz + az*(1 - z^2))/nr
***/

	appo = (rx*nx+ry*ny+rz*nz);
	bx = (-ry*ny*nx - rz*nz*nx - sqrt(nr*nr + appo*appo - 1)*nx + rx*(1 - nx*nx))/nr;
	by = (-rx*nx*ny - rz*nz*ny - sqrt(nr*nr + appo*appo - 1)*ny + ry*(1 - ny*ny))/nr;
	bz = (-rx*nx*nz - ry*ny*nz - sqrt(nr*nr + appo*appo - 1)*nz + rz*(1 - nz*nz))/nr;


//    f  = (by/(y-yg)) - (bz/(z-zg));
    f  = ((y-yg)/by) - ((z-zg)/bz);
	return f;
}



//Cerco le coordinate del punto di incidenza utile per la rifratta 6
FLOAT func1c(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;

    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;
    f  = y*y + z*z - R*R;
	return f;
}

FLOAT func2c(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;
FLOAT nx, ny, nz;
FLOAT bx,by,bz;
FLOAT xg,yg,zg;
FLOAT appo;

    xg = 0;
	yg = -c;
	zg = g;


    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;

	nx = 0.0;
	ny = y/R;
	nz = z/R;

/***
bx = (-ay*ny*nx - az*nz*nx - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nx + ax*(1 - x^2))/nr
by = (-ax*nx*ny - az*nz*ny - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*ny + ay*(1 - y^2))/nr
bz = (-ax*nx*nz - ay*ny*nz - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nz + az*(1 - z^2))/nr
***/

	appo = (rx*nx+ry*ny+rz*nz);
	bx = (-ry*ny*nx - rz*nz*nx - sqrt(nr*nr + appo*appo - 1)*nx + rx*(1 - nx*nx))/nr;
	by = (-rx*nx*ny - rz*nz*ny - sqrt(nr*nr + appo*appo - 1)*ny + ry*(1 - ny*ny))/nr;
	bz = (-rx*nx*nz - ry*ny*nz - sqrt(nr*nr + appo*appo - 1)*nz + rz*(1 - nz*nz))/nr;


    f  = ((x-xg)/bx) - ((y-yg)/by);
	return f;
}

FLOAT func3c(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;
FLOAT nx, ny, nz;
FLOAT bx,by,bz;
FLOAT xg,yg,zg;
FLOAT appo;

    xg = 0;
	yg = -c;
	zg = g;


    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;

	nx = 0.0;
	ny = y/R;
	nz = z/R;

/***
bx = (-ay*ny*nx - az*nz*nx - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nx + ax*(1 - x^2))/nr
by = (-ax*nx*ny - az*nz*ny - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*ny + ay*(1 - y^2))/nr
bz = (-ax*nx*nz - ay*ny*nz - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nz + az*(1 - z^2))/nr
***/

	appo = (rx*nx+ry*ny+rz*nz);
	bx = (-ry*ny*nx - rz*nz*nx - sqrt(nr*nr + appo*appo - 1)*nx + rx*(1 - nx*nx))/nr;
	by = (-rx*nx*ny - rz*nz*ny - sqrt(nr*nr + appo*appo - 1)*ny + ry*(1 - ny*ny))/nr;
	bz = (-rx*nx*nz - ry*ny*nz - sqrt(nr*nr + appo*appo - 1)*nz + rz*(1 - nz*nz))/nr;


    f  = ((y-yg)/by) - ((z-zg)/bz);
	return f;
}



//Cerco le coordinate del punto di incidenza utile per la rifratta 7
FLOAT func1p(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;

    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;
    f  = R;
	return f;
}

FLOAT func2p(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;
FLOAT nx, ny, nz;
FLOAT bx,by,bz;
FLOAT xg,yg,zg;
FLOAT appo;

    xg = 0;
	yg = -c;
	zg = g;


    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;

	nx = 0.0;
	ny = 0.0;
	nz = 1;

/***
bx = (-ay*ny*nx - az*nz*nx - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nx + ax*(1 - x^2))/nr
by = (-ax*nx*ny - az*nz*ny - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*ny + ay*(1 - y^2))/nr
bz = (-ax*nx*nz - ay*ny*nz - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nz + az*(1 - z^2))/nr
***/

	appo = (rx*nx+ry*ny+rz*nz);
	bx = (-ry*ny*nx - rz*nz*nx - sqrt(nr*nr + appo*appo - 1)*nx + rx*(1 - nx*nx))/nr;
	by = (-rx*nx*ny - rz*nz*ny - sqrt(nr*nr + appo*appo - 1)*ny + ry*(1 - ny*ny))/nr;
	bz = (-rx*nx*nz - ry*ny*nz - sqrt(nr*nr + appo*appo - 1)*nz + rz*(1 - nz*nz))/nr;


    f  = ((x-xg)/bx) - ((y-yg)/by);
	return f;
}

FLOAT func3p(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT x,y,z;
FLOAT nx, ny, nz;
FLOAT bx,by,bz;
FLOAT xg,yg,zg;
FLOAT appo;

    xg = 0;
	yg = -c;
	zg = g;


    fp = xvect;
    x  = *fp++;
	y  = *fp++;
	z  = *fp;

	nx = 0.0;
	ny = 0.0;
	nz = 1;

/***
bx = (-ay*ny*nx - az*nz*nx - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nx + ax*(1 - x^2))/nr
by = (-ax*nx*ny - az*nz*ny - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*ny + ay*(1 - y^2))/nr
bz = (-ax*nx*nz - ay*ny*nz - Sqrt[nr^2 + (ax*nx + ay*ny + az*nz)^2 - 1]*nz + az*(1 - z^2))/nr
***/

	appo = (rx*nx+ry*ny+rz*nz);
	bx = (-ry*ny*nx - rz*nz*nx - sqrt(nr*nr + appo*appo - 1)*nx + rx*(1 - nx*nx))/nr;
	by = (-rx*nx*ny - rz*nz*ny - sqrt(nr*nr + appo*appo - 1)*ny + ry*(1 - ny*ny))/nr;
	bz = (-rx*nx*nz - ry*ny*nz - sqrt(nr*nr + appo*appo - 1)*nz + rz*(1 - nz*nz))/nr;


    f  = ((y-yg)/by) - ((z-zg)/bz);
	return f;
}


//Cerco le coordinate del punto di incidenza utile.per la rifratta 3
FLOAT func1(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT beta,gamma;
FLOAT g1;

    fp = xvect;
    gamma  = *fp++;
	beta  = *fp;
	g1 = g - c*tan(gamma - beta);
	f = g1*sin((PI/2) +gamma -beta) - R*sin(beta) ;
//	printf("func1 = %lf (gamma = %lf, beta = %lf)\n",f,gamma,beta);
	return f;
}

FLOAT func2(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT beta,gamma;

    fp = xvect;
    gamma  = *fp++;
	beta  = *fp;
	f  = sin(gamma - elev_n) - nr*sin(beta);
//	printf("func2 = %lf (gamma = %lf, beta = %lf) (elev = %lf) \n",f,gamma,beta,elev_n);
	return f;
}


FLOAT funch1(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT th,tv;
FLOAT th2,thmtv,thmtv2;
FLOAT R2, par1, par2; 
FLOAT rh2,rx2,ry2;
FLOAT rh;          

    fp  = xvect;
    th  = *fp++;
	tv  = *fp;

    rh  = a1;
	R   = c1;

	rh2 = rh*rh;
	R2  = R*R;

	th2    = th*th;
	thmtv  = (th - tv);
	thmtv2 = thmtv*thmtv;

	rx2 = rx*rx;
	ry2 = ry*ry;
	rh2 = rh*rh,
	R2  = R*R;

//    eh = -R^2 + ry^2*th^2 + (Sqrt[1 - (rx^2*(th - tv)^2)/rh^2]*rh + rz*th)^2 + (rx*th - rx*(th - tv))^2

   	par1 = (sqrt(1 - (rx2*thmtv2)/rh2)*rh + rz*th);
	par2 = (rx*th - rx*thmtv)*(rx*th - rx*thmtv);

	f = -R2 + ry2*th2 + par1*par1 + par2*par2;

	return f;
}


// Calcolo incrocio ombre per la bifilare sferica saturno 1
FLOAT funcv1(FLOAT *xvect)
{
FLOAT *fp, f;
FLOAT th,tv;
FLOAT tv2,thmtv,thmtv2;
FLOAT R2, par1, par2; 
FLOAT rv2,rx2,ry2;
FLOAT rv;          


    fp  = xvect;
    th  = *fp++;
	tv  = *fp;

    rv  = b1;
	R   = c1;

	tv2    = tv*tv;
	thmtv  = (th - tv);
	thmtv2 = thmtv*thmtv;

	rx2 = rx*rx;
	ry2 = ry*ry;
	rv2 = rv*rv,
	R2  = R*R;

// ev = -R^2 + rx^2*tv^2 + (Sqrt[1 - (ry^2*(th - tv)^2)/rv^2]*rv + ry*tv)^2 + (ry*(th - tv) + ry*tv)^2

   	par1 = (sqrt(1 - (ry2*thmtv2)/rv2)*rv + ry*tv);
	par2 = (ry*thmtv + ry*tv)*(ry*thmtv + ry*tv);

	f = -R2 + rx2*tv2 + par1*par1 + par2*par2;

	return f;
}


FLOAT funch2(FLOAT *xvect)
{
FLOAT *fp, f;
double rx2,ry2,rz2;
double xhh,yhh,zhh, xvv,yvv,zvv, xgh,ygh,zgh, xgv,ygv,zgv;
double rh,rv,R;
double rh2,rv2,sh2,sv2,R2;
double th,tv,sh,sv;
double temp;

    fp  = xvect;
    sh  = *fp++;
	sv  = *fp;

    rh  = a1;
	rv  = b1;
	R   = c1;

	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;

	rh2 = rh*rh;
	rv2 = rv*rv;
	R2  = R*R;

	sh2 = sh*sh;
	sv2 = sv*sv;

/**
th = -rx*sh - rz*Sqrt[(rh - sh)*(rh + sh)] # Sqrt[R^2 - rh^2 + (rx*sh + rz*Sqrt[(rh - sh)*(rh + sh)])^2]
tv = -ry*sv - rz*Sqrt[(rv - sv)*(rv + sv)] # Sqrt[R^2 - rv^2 + (ry*sv + rz*Sqrt[(rv - sv)*(rv + sv)])^2]
**/

	temp = (rx*sh + rz*sqrt((rh2 - sh2)));
	th = -rx*sh - rz*sqrt((rh2 - sh2)) - sqrt(R2 - rh2 + temp*temp);

	temp = (ry*sv + rz*sqrt((rv2 - sv2)));
	tv = -ry*sv - rz*sqrt((rv2 - sv2)) - sqrt(R2 - rv2 + temp*temp);

	
	//Calcolo le curve come al solito mediante il punto di intersezione raggio superficie
	xgh = sh;
	ygh = 0;
	zgh = sqrt(rh2 - sh2);

	xhh = rx*th + xgh;
	yhh = ry*th + ygh;
	zhh = rz*th + zgh;

	//ed anche
	xgv = 0;
	ygv = sv;
	zgv = sqrt(rv2 - sv2);

	xvv = rx*tv + xgv;
	yvv = ry*tv + ygv;
	zvv = rz*tv + zgv;

	f = xhh - xvv;

	return f;
}


// Calcolo incrocio ombre per la bifilare sferica saturno 2
FLOAT funcv2(FLOAT *xvect)
{
FLOAT *fp, f;
double rx2,ry2,rz2;
double xhh,yhh,zhh, xvv,yvv,zvv, xgh,ygh,zgh, xgv,ygv,zgv;
double rh,rv,R;
double rh2,rv2,sh2,sv2,R2;
double th,tv,sh,sv;
double temp;

    fp  = xvect;
    sh  = *fp++;
	sv  = *fp;

    rh  = a1;
	rv  = b1;
	R   = c1;

	rx2 = rx*rx;
	ry2 = ry*ry;
	rz2 = rz*rz;

	rh2 = rh*rh;
	rv2 = rv*rv;
	R2  = R*R;

	sh2 = sh*sh;
	sv2 = sv*sv;

/**
th = -rx*sh - rz*Sqrt[(rh - sh)*(rh + sh)] # Sqrt[R^2 - rh^2 + (rx*sh + rz*Sqrt[(rh - sh)*(rh + sh)])^2]
tv = -ry*sv - rz*Sqrt[(rv - sv)*(rv + sv)] # Sqrt[R^2 - rv^2 + (ry*sv + rz*Sqrt[(rv - sv)*(rv + sv)])^2]
**/

	temp = (rx*sh + rz*sqrt((rh2 - sh2)));
	th = -rx*sh - rz*sqrt((rh2 - sh2)) - sqrt(R2 - rh2 + temp*temp);

	temp = (ry*sv + rz*sqrt((rv2 - sv2)));
	tv = -ry*sv - rz*sqrt((rv2 - sv2)) - sqrt(R2 - rv2 + temp*temp);

	
	//Calcolo le curve come al solito mediante il punto di intersezione raggio superficie
	xgh = sh;
	ygh = 0;
	zgh = sqrt(rh2 - sh2);

	xhh = rx*th + xgh;
	yhh = ry*th + ygh;
	zhh = rz*th + zgh;

	//ed anche
	xgv = 0;
	ygv = sv;
	zgv = sqrt(rv2 - sv2);

	xvv = rx*tv + xgv;
	yvv = ry*tv + ygv;
	zvv = rz*tv + zgv;

	f = yhh - yvv;

	return f;
}


//Calcolo incrocio ombre la bif_Soler (parabola+catenaria su piano inclinato).
FLOAT funcpc1(FLOAT *xvect)
{
FLOAT *fp, fres;
double s1,s2;
double Yp,a,b,c,G;
double Yc,xv,yv,f;
double bo, bc,incp;
double temp;


    fp  = xvect;
    s1  = *fp++;
	s2  = *fp;

    bo    = a1;  // Leggo lunghezza muro dall'origine all'acqua
	bc    = b1;  // Leggo distanza del bersaglio del getto dalla liea muro-acqua 
    incp  = c1;  // Leggo inclinazione muro (0 = verticale)
	d1	= a2;  // Leggo lunghezza colonnina di sostegno catenaria
	yv  = b2;
	f   = c2;  // Leggo fattore di scala calcolato iterativamente per rispettare
			   // le coordinate dei vincoli di aggancio della catenaria

    incp = gra_to_rad(incp);

	b = tan(incp);       //Alzo getto
	G = bo*sin(incp)+bc; //Gittata
	c = bo*cos(incp);    //Altezza getto
	a = (b*G+c)/(G*G);  //Potenza getto

	xv = 0;
	//d1 = b/(2*a);


	Yp = -a*s2*s2 + b*s2;

	Yc = f*cosh((s1-xv)/f)+yv-f;

/**
x1-x2:
s1 + rx*(s2 + Yp*tan(incp))/temp - rx*(d1+Yc*tan(incp) )/temp;

s1 + (rx*(s2 + b*s2*Tan[i] - a*s2^2*Tan[i]))/(rz + ry*Tan[i]) - (rx*(d1 - f*Tan[i] + yv*Tan[i] + f*Cosh[(s1 - xv)/f]*Tan[i]))/
   (rz + ry*Tan[i])
**/

 
	temp = (rz + ry*tan(incp));
	fres = s1 + rx*(s2 + Yp*tan(incp)) / temp - rx*(d1+Yc*tan(incp)) / temp;
 
	return fres;
}


FLOAT funcpc2(FLOAT *xvect)
{
FLOAT *fp, fres;
double s1,s2;
double Yp,a,b,c,G;
double Yc,xv,yv,f;
double bo, bc,incp;
double temp;


    fp  = xvect;
    s1  = *fp++;
	s2  = *fp;

    bo    = a1;  // Leggo lunghezza muro dall'origine all'acqua
	bc    = b1;  // Leggo distanza del bersaglio del getto dalla liea muro-acqua 
    incp  = c1;  // Leggo inclinazione muro (0 = verticale)
	d1	= a2;  // Leggo lunghezza colonnina di sostegno catenaria
	yv  = b2;
	f   = c2;  // Leggo fattore di scala calcolato iterativamente per rispettare
		      // le coordinate dei vincoli di aggancio della catenaria
    
	incp = gra_to_rad(incp);

    b = tan(incp);       //Alzo getto
	G = bo*sin(incp)+bc; //Gittata
	c = bo*cos(incp);    //Altezza getto
	a = (b*G+c)/(G*G);  //Potenza getto


	xv = 0;
	//d1 = b/(2*a);
	
	Yp = -a*s2*s2 + b*s2;

	Yc = f*cosh((s1-xv)/f)+yv-f;

/**
y1-y2:
       Yc - Yp + ry*(s2 +Yp*tan(incp))/temp - ry*(d1 + Yc*tan(incp))/temp;

-f - b*s2 + a*s2^2 + yv + f*Cosh[(s1 - xv)/f] + (ry*(s2 + b*s2*Tan[i] - a*s2^2*Tan[i]))/(rz + ry*Tan[i]) - 
  (ry*(d1 - f*Tan[i] + yv*Tan[i] + f*Cosh[(s1 - xv)/f]*Tan[i]))/(rz + ry*Tan[i])
**/
	temp = (rz + ry*tan(incp));
	fres = Yc - Yp + ry*(s2 +Yp*tan(incp))/temp - ry*(d1 + Yc*tan(incp))/temp;
	return fres;

}


FLOAT funcCC1(FLOAT *xvect)
{
FLOAT *fp, fres;
double s1,s2;
double Yc1,zv1,f1;
double Yc2,zv2,f2;
double xv1,xv2;

    xv1 = xv2 = 0.0;
    
    fp  = xvect;
    s1  = *fp++;
    s2  = *fp;

    zv1  = b1;
    f1   = c1;  // Leggo fattore di scala calcolato iterativamente per rispettare
			   // le coordinate dei vincoli di aggancio della catenaria
    zv2  = b2;
    f2   = c2;  // Leggo fattore di scala calcolato iterativamente per rispettare
			   // le coordinate dei vincoli di aggancio della catenaria

    Yc1 = f1*cosh((s1)/f1)+zv1-f1;
    Yc2 = f2*cosh((s2)/f2)+zv2-f2;

//e1 = s1 - (rx*(-f1 + zv1 + f1*Cosh[s1/f1]))/rz + (rx*(-f2 + zv2 + f2*Cosh[s2/f2]))/rz
  fres = s1 - rx*Yc1/rz + rx*Yc2/rz;

  return(fres);
}

FLOAT funcCC2(FLOAT *xvect)
{
FLOAT *fp, fres;
double s1,s2;
double Yc1,zv1,f1;
double Yc2,zv2,f2;
double xv1,xv2;

    xv1 = xv2 = 0.0;
    
    fp  = xvect;
    s1  = *fp++;
    s2  = *fp;

    zv1  = b1;
    f1   = c1;  // Leggo fattore di scala calcolato iterativamente per rispettare
			   // le coordinate dei vincoli di aggancio della catenaria
    zv2  = b2;
    f2   = c2;  // Leggo fattore di scala calcolato iterativamente per rispettare
			   // le coordinate dei vincoli di aggancio della catenaria

    Yc1 = f1*cosh((s1)/f1)+zv1-f1;
    Yc2 = f2*cosh((s2)/f2)+zv2-f2;

//e2 = s2 - (ry*(-f2 + zv2 + f2*Cosh[s2/f2]))/rz + (ry*(-f1 + zv1 + f1*Cosh[s1/f1]))/rz
  fres = -s2 - ry*Yc1/rz + ry*Yc2/rz;
  return(fres);
}



/**** MAIN ****/

main(argc,argv)
int argc;
char *argv[];
{
	
    init(argv[1]);         // Input parametri iniziali 

    if(lemni_flag)
      {
      lemnid();            // Calcolo lemniscate discendenti 
      lemnia();            // Calcolo lemniscate ascendenti  
      }

    if(solistizi_flag)
		{
    	solistizi();         // Calcolo dei solistizi di inverno e d'estate
		}

    if(diurnezod_flag)
      {
      diurnezod();         // Calcolo linee diurne zodiacali 
      }

    if(diurnemns_flag)
      {
      diurnemns();         // Calcolo linee diurne mensili   
      }

    if(orarie_flag)
      {
      orarie();            //Calcolo rette orarie 
      }

    if(orariefuso_flag)
      {
      orariefuso();        //Calcolo rette orarie del fuso 
      }

    if(azimalmu_flag)
      {
      azimut();            // Calcolo delle rette azimutali 
      almucant();          // Calcolo delle curve ad altezza costante 
      }

    //punti_notevoli();      // Calcolo dei punti   notevoli (piede gnom. ecc.) 
    //linee_notevoli();      // Calcolo delle linee notevoli (orizz. merid. ecc.)
    //trian();               // Calcolo del triangolo stilare	
}


