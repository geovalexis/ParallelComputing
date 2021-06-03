#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define frand(M) (M*(((double)rand())/RAND_MAX))

#define N 5000000

double X[N];
double Y[N];

/* rank del proces    */
int    el_meu_rank;
/* numero de processos        */
int    p;
/* rank de l'emissor */
int    font;
/* rank del receptor */
int    desti;
/* etiqueta dels missatges */
int    etiq = 0;  
/* estat de la recepcio       */
MPI_Status  estat;



double cost (int nn, double vx[], double vy[], double t0, double t1)
 {
  int i;
  double val, recv_sum, sum=0.0;
  int elements_per_proc = N/p;
  int ini_proc = el_meu_rank*elements_per_proc;
  int end_proc = (el_meu_rank+1)*elements_per_proc;
  /* En caso de que N no sea divisible por el nº de procesos, asignar el resto al ultimo proceso */	
  if ((N % p) != 0) {
    if (el_meu_rank==p-1) {
      end_proc = N;
    }
  }
  
  for(i=ini_proc;i<end_proc;i++)
   {
    val = t0 + t1*vx[i] - vy[i];
    sum += val * val;
   }
  MPI_Allreduce(&sum, &recv_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  recv_sum /= 2*nn;
  return(recv_sum);
}

int gradientDescent (int nn, double vx[], double vy[], double alpha, double *the0, double *the1)
 {
  int i;
  double val;
  double z0,z1;
  double c=0,ca;
  double t0=*the0, t1=*the1;
  double a_n = alpha/nn;
  int iter = 0;
  double error = 0.000009; // cinc decimals
 
  int elements_per_proc = N/p;
  int ini_proc = el_meu_rank*elements_per_proc;
  int end_proc = (el_meu_rank+1)*elements_per_proc;
  /* En caso de que N no sea divisible por el nº de procesos, asignar el resto al ultimo proceso */	
  if ((N % p) != 0) {
    if (el_meu_rank==p-1) {
      end_proc = N;
    }
  }

  do
   {
    z0 = z1 = 0.0;
    for(i=ini_proc;i<end_proc;i++)
     {
      val = t0 + t1*vx[i] - vy[i];
      z0 += val;
      z1 += val * vx[i];
     }
    double send_vector_z[2] = {z0, z1};
    double recv_vector_z[2];
    MPI_Allreduce(send_vector_z, recv_vector_z, 2, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    t0 -= recv_vector_z[0] * a_n;
    t1 -= recv_vector_z[1] * a_n;
    iter++;
    ca = c;
    c = cost(nn,vx,vy,t0,t1);
   }
  while (fabs(c - ca) > error);
  *the0 = t0;
  *the1 = t1;
  return(iter);
}

int main(int num_args, char* args[ ])
{
int i;
double ct;
double theta0=0, theta1=1;

  /* Inicialitzar MPI */
  MPI_Init(&num_args, &args);
  /* Obtenir el rank del proces  */
  MPI_Comm_rank(MPI_COMM_WORLD, &el_meu_rank);
  /* Obtenir el numero total de processos */
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  srand(1);
  for (i=0;i<N;i++) 
   {
    X[i] = frand(13);
    Y[i] = frand(9) + ((1.66 + (frand(0.9))) *  X[i]) * X[i] ;
   }

  //for (i=0;i<N;i++) printf("%g %g\n",X[i],Y[i]);
 
  i=gradientDescent (N, X, Y, 0.01, &theta0, &theta1);
  ct=cost(N,X,Y,theta0,theta1);
  if (el_meu_rank==0)
    printf ("(%d) Theta; %g, %g  cost: %g\n",i,theta0,theta1,ct);

  MPI_Finalize();
  return(0);
}
