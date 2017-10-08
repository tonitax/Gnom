#define   PI        3.141592654

# define FLOAT double
# define PARAMFLOAT double_t


typedef enum  Rot_type {X,Y,Z,A};

typedef double VECTOR[3];
typedef double MATRIX[3][3];

void Rotation(enum Rot_type Rot, double a_deg, VECTOR *vector_in, VECTOR *vector_out);

void Product_M_V(MATRIX *matrix_in, VECTOR *vector_in, VECTOR *vector_out);

void Addition_V_V(VECTOR *vector_in1,  VECTOR *vector_in2, VECTOR *vector_out);

double Scalar(VECTOR *vector_in1,  VECTOR *vector_in2);

void Build_Householder(VECTOR *n,MATRIX *Hhm);

void Build_Refraction(VECTOR *n, MATRIX *RefraMx, double nr);

void Rifrazione(double nr, VECTOR *n, VECTOR *rin, VECTOR *rout);


FLOAT func1(FLOAT *xv);
FLOAT func2(FLOAT *xv);

FLOAT funch1(FLOAT *xv);
FLOAT funcv1(FLOAT *xv);

FLOAT funch2(FLOAT *xv);
FLOAT funcv2(FLOAT *xv);

FLOAT func_bfrc_x(FLOAT *xv);
FLOAT func_bfrc_y(FLOAT *xv);

FLOAT func1s(FLOAT *xv);
FLOAT func2s(FLOAT *xv);
FLOAT func3s(FLOAT *xv);
FLOAT func4s(FLOAT *xv);

FLOAT func1c(FLOAT *xv);
FLOAT func2c(FLOAT *xv);
FLOAT func3c(FLOAT *xv);
FLOAT func4c(FLOAT *xv);

FLOAT func1p(FLOAT *xv);
FLOAT func2p(FLOAT *xv);
FLOAT func3p(FLOAT *xv);
FLOAT func4p(FLOAT *xv);

FLOAT funcpc1(FLOAT *xv);
FLOAT funcpc2(FLOAT *xv);

FLOAT funcCC1(FLOAT *xv);
FLOAT funcCC2(FLOAT *xv);

long SolveNonlinearSystem(
	FLOAT			(**func)(FLOAT*),	/* Vector of functions */
	FLOAT			*x,					/* Vector of independent variables */
	register long	n,					/* Order of system */
	FLOAT			numsig,				/* Number of significant decimal digits */
	FLOAT			*maxit				/* Maximum number of iterations; return actual number */
	);