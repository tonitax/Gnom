#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "Utilities.h"

MATRIX rm;

void Rotation(enum Rot_type Rot, double ang, VECTOR *vector_in, VECTOR *vector_out)
{
int i,j;
double a_rad;
double cos_a, sin_a;
double *mp;
 
    // a_rad = PI*ang/180.0;
	a_rad = ang;

    sin_a = sin(a_rad);
	cos_a = cos(a_rad);

    if (Rot != A) 
		{
		mp = (double *)&rm;
		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				*mp++ = (i==j) ? 1.0 : 0.0;
		}

	switch(Rot)
    {
		case X:
			rm[1][1] = rm[2][2] = cos_a;
			rm[1][2] = -sin_a;
			rm[2][1] = sin_a;
			break;

		case Y:
			rm[0][0] = rm[2][2] = cos_a;
			rm[0][2] = sin_a;
			rm[2][0] = -sin_a;
			break;

		case Z:
			rm[0][0] = rm[1][1] = cos_a;
			rm[0][1] = -sin_a;
			rm[1][0] = sin_a;
			break;

		case A:
			break;
	}
     

	Product_M_V(&rm, vector_in, vector_out);

	return;
}


void Product_M_V(MATRIX *matrix_in, VECTOR *vector_in, VECTOR *vector_out)
{
int i,j;
double *vpin, *vpout;
double *mpin;
double sum;
	
	mpin  = (double *)matrix_in;
	vpout = (double *)vector_out;

	for(i=0; i<3; i++)
	{
		vpin = (double *)vector_in;
		sum = 0.0;
		for(j=0; j<3; j++)
		{
		sum += *mpin++ * *vpin++;
		}
    *vpout++ = sum;
	}
}

void Addition_V_V(VECTOR *vector_in1,  VECTOR *vector_in2, VECTOR *vector_out)
{
int i;
double *vpin1, *vpin2, *vpout;
    
    vpin1 = (double *)vector_in1;
    vpin2 = (double *)vector_in2;
    vpout = (double *)vector_out;
	
	for(i=0; i<3; i++)
	{
	   *vpout++ = *vpin1++ + *vpin2++;	
	}
}


void Bisectrix_V_V(int dihedron, VECTOR *vector_in1,  VECTOR *vector_in2, VECTOR *vector_out)
{
double *vpin1, *vpin2, *vpout;
double ax,ay,az,bx,by,bz,cx,cy,cz;
double scalar, nf;
    
    vpin1 = (double *)vector_in1;
    vpin2 = (double *)vector_in2;
    vpout = (double *)vector_out;

	ax = *vpin1++;
	ay = *vpin1++;
	az = *vpin1;

	cx = *vpin2++;
	cy = *vpin2++;
	cz = *vpin2;

	bx = (dihedron > 0) ? (ax + cx) : (ax - cx); 
	by = (dihedron > 0) ? (ay + cy) : (ay - cy); 
	bz = (dihedron > 0) ? (az + cz) : (az - cz);

	scalar = ax*cx + ay*cy + az*cz;
	
	nf = (dihedron > 0) ? sqrt(2)*sqrt(1+scalar) : sqrt(2)*sqrt(1-scalar);
	
	*vpout++ = bx = bx/nf;
	*vpout++ = by = bx/nf;
	*vpout   = bz = bx/nf;

	return;
}



double Scalar(VECTOR *vector_in1,  VECTOR *vector_in2)
{
int i;
double *vpin1, *vpin2;
double sum;
    
    vpin1 = (double *)vector_in1;
    vpin2 = (double *)vector_in2;

	sum   = 0.0;

	for(i=0; i<3; i++)
	{
	   sum += *vpin1++ * *vpin2++;	
	}
	return(sum);
}


void Build_Householder(VECTOR *n, MATRIX *Hhm)
{
double *mp, *vp;
double nx,ny,nz;

    mp = (double *)Hhm;
	vp = (double *)n;

	nx = *vp++;
	ny = *vp++;
	nz = *vp;
	
    *mp++ = 1.0 - 2*nx*nx;
	*mp++ = -2*nx*ny;
	*mp++ = -2*nx*nz;

    *mp++ = -2*ny*nx;
	*mp++ = 1.0 - 2*ny*ny;
	*mp++ = -2*ny*nz;

    *mp++ = -2*nz*nx;
	*mp++ = -2*nz*ny;
	*mp   = 1.0 - 2*nz*nz;
	
	return;
}


void Build_Refraction(VECTOR *n, MATRIX *RefraMx, double nr)
{
double *mp, *vp;
double nx,ny,nz;

    mp = (double *)RefraMx;
	vp = (double *)n;

	nx = *vp++;
	ny = *vp++;
	nz = *vp;
	
    *mp++ = (1.0 - nx*nx)/nr;
	*mp++ = -(nx*ny)/nr;
	*mp++ = -(nx*nz)/nr;

    *mp++ = -(ny*nx)/nr;
	*mp++ = (1.0 - ny*ny)/nr;
	*mp++ = -(ny*nz)/nr;

    *mp++ = -(nz*nx)/nr;
	*mp++ = -(nz*ny)/nr;
	*mp   = (1.0 - nz*nz)/nr;
	
	return;
}


void Rifrazione(double nr, VECTOR *n, VECTOR *rin, VECTOR *rout)
{
MATRIX RefraM;
VECTOR rappo;
double T, s;
double *nvp, *rvp, *rva;

	//Dai coseni direttori della normale alla superfice di separazione nel punto di incidenza 
    //calcolo la matrice di rifrazione
	Build_Refraction(n,&RefraM,nr);

	//Applico la matrice di rifrazione ai coseni direttori del raggio incidente....
	Product_M_V(&RefraM,rin,&rappo);

	//Applico il termine additivo ... e trovo i coseni direttori del raggio rifratto

    s = Scalar(n,rin);
	T = sqrt(nr*nr + s*s - 1.0)  / nr;

	rvp = (double *)rout;
    rva = (double *)rappo;
    nvp = (double *)n;

	*rvp++ = *rva++ - *nvp++ * T;
	*rvp++ = *rva++ - *nvp++ * T;
	*rvp   = *rva   - *nvp   * T;

}