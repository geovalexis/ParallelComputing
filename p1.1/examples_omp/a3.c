#define N 10000000

int a[N],b[N];
long long s=0;

int jo,nthr,porcio;

main()
{
int i,ini,fi;

/* inicialitzacio, no en paral.lel */

for(i=0;i<N;i++)
{
 a[i]=1;
 b[i]=2;
}

#pragma omp parallel shared(a,b) private(i,jo,nthr,porcio,ini,fi)
{
 jo = omp_get_thread_num();
 nthr = omp_get_num_threads();
 porcio= N/nthr;


 ini=jo*porcio;
 fi=(jo+1)*porcio;

 printf("jo: %d, porcio: %d des de %d fins %d\n",jo,porcio,ini,fi);
	 
 for (i=ini;i<fi;i++)
 b[i] += a[i];
}

 printf("Valor i %d, de b[i] %d \n",i-1,b[i-1]);

for (i=0;i<N;i++)
 s+=b[i];


 printf("Valor %d, de b %d suma total: %ld\n",i-1,b[i-1],s);


}


