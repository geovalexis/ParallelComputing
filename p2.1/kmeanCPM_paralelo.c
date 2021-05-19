#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define N 600000 //muestras
#define G 200	 //centroides

long V[N];
long R[G];
int A[G];


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

void kmean(int fN, int fK, long fV[], long fR[], int fA[])
{
	int i, j, min, iter = 0;
	long dif, t;
	long fS[G];
	int fD[N];
	int elements_per_proc = N/p;
	int ini_proc = el_meu_rank*elements_per_proc;
	int end_proc = (el_meu_rank+1)*elements_per_proc;
	/* En caso de que N no sea divisible por el nº de procesos, asignar el resto al ultimo proceso */
	
	int recvcounts[p],	displs[p];
	for (int x = 0; x < p; x++) {
		recvcounts[x]=elements_per_proc;
		displs[x]=x*elements_per_proc;
	}

	if ((N % p) != 0) {
		if (el_meu_rank==p-1) {
			end_proc = N;
		}
		recvcounts[p-1]=elements_per_proc + N%p;
	}

	int send_buffer_fD[end_proc-ini_proc];

	do
	{	
		int cont = 0;
		for (i = ini_proc ; i < end_proc; i++)
		{
			min = 0;
			dif = abs(fV[i] - fR[0]);
			for (j = 1; j < fK; j++)
				if (abs(fV[i] - fR[j]) < dif)
				{
					min = j;
					dif = abs(fV[i] - fR[j]);
				}
			send_buffer_fD[cont] = min;
			cont++;
		}
		
		MPI_Allgatherv(send_buffer_fD,end_proc-ini_proc,MPI_INT, fD, recvcounts, displs, MPI_INT, MPI_COMM_WORLD);

		for (i = 0; i < fK; i++)
			fS[i] = fA[i] = 0;

		for (i = 0; i < fN; i++)
		{
			fS[fD[i]] += fV[i];
			fA[fD[i]]++;
		}

		dif = 0;
		for (i = 0; i < fK; i++)
		{
			t = fR[i];
			if (fA[i])
				fR[i] = fS[i] / fA[i];
			dif += abs(t - fR[i]);
		}
		iter++;
	} while (dif);

	if (el_meu_rank==0)
		printf("iter %d\n", iter);
}

void qs(int ii, int fi, long fV[], int fA[])
{
	int i, f, j;
	long pi, pa, vtmp, vta, vfi, vfa;

	pi = fV[ii];
	pa = fA[ii];
	i = ii + 1;
	f = fi;
	vtmp = fV[i];
	vta = fA[i];

	while (i <= f)
	{
		if (vtmp < pi)
		{
			fV[i - 1] = vtmp;
			fA[i - 1] = vta;
			i++;
			vtmp = fV[i];
			vta = fA[i];
		}
		else
		{
			vfi = fV[f];
			vfa = fA[f];
			fV[f] = vtmp;
			fA[f] = vta;
			f--;
			vtmp = vfi;
			vta = vfa;
		}
	}
	fV[i - 1] = pi;
	fA[i - 1] = pa;

	if (ii < f)
		qs(ii, f, fV, fA);
	if (i < fi)
		qs(i, fi, fV, fA);
}

int main(int num_args, char* args[ ])
{
	int i;

	/* Inicialitzar MPI */
   MPI_Init(&num_args, &args);
    /* Obtenir el rank del proces  */
   MPI_Comm_rank(MPI_COMM_WORLD, &el_meu_rank);
    /* Obtenir el numero total de processos */
   MPI_Comm_size(MPI_COMM_WORLD, &p);

   if (el_meu_rank==0){
		// Inicialización
		for (i = 0; i < N; i++)
			V[i] = (rand() % rand()) / N;

		// primers candidats
		for (i = 0; i < G; i++)
			R[i] = V[i];
   }
	
	MPI_Bcast(R, G, MPI_LONG, 0, MPI_COMM_WORLD);
	MPI_Bcast(V, N, MPI_LONG, 0, MPI_COMM_WORLD);	

	// calcular els G mes representatius
	kmean(N, G, V, R, A);

	if (el_meu_rank==0){
		qs(0, G - 1, R, A);
		for (i = 0; i < G; i++)
			printf("R[%d] : %ld te %d agrupats\n", i, R[i], A[i]);
	}

	MPI_Finalize();
	return (0);
}
