# Enunciado
El codi és el mateix que la practica P1.1.
El temps seqüencial a les màquines POP és de 64.5 segons.
Per als odroids cal encarar especificar els temp d'execució.

Es programarà amb MPI
L'execució es farà per els nombre de processos que indica la taula. Així son 11 execucions.
S'ha de respectar les dades que surten per la sortida estàndard i en la versió paral·lela ha de donar el mateix resultat.
El vector resultant ha de quedar emmagatzemat sencer al procés 0.
L'speedup en qualsevol configuració ha de ser superior a 1.5
L'speedup harmònic a les màquines POP ha de ser superior a 3.0

# Compilación

## Paralelo
```
mpicc -O3 kmeanCPM_paralelo.c -o kmeanCPM_paralelo
```

# Ejecución

## En los nodos 
```bash
salloc -p pop -N 8 -n 32 time mpirun -n 32 --npernode 4 --oversubscribe kmeanCPM_paralelo > paralelo.pop 2>&1 &
```

> Para ejecutar con 64 o 128 nodos (más de los disponibles):
```bash
salloc -p pop -N 8 -n 32 time mpirun -n 32 --mca mpi_yield_when_idle true  --oversubscribe kmeanCPM_paralelo > paralelo.pop 2>&1 &
```

>Explicación:
```
salloc
    * -p pop: reservar máquina llamada "pop"
    * -N 8: reservar 8 nodos
    * -n 32: reservar 32 procesadores (threads/cores)

mpirun
    * -n 32: ejecutar 32 procesos MPI
    * --npernode 4: numero de procesos por nodo
    * --oversubcribe: asignar mas de un proceso por nodo (Por si el parámetro --npernode da problemas)
    * --mca mpi_yield_when_idle true: evitar warnings de slurm sobre asignación de más nodos de los disponibles.
``` 