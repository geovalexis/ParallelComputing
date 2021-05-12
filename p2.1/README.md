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
salloc -p pop -N 8 -n 32 time mpirun -n 32 --npernode 4 --oversubscribe kmeanCPM_paralelo
```
