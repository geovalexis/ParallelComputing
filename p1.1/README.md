# Enunciado
Algorisme d'agregacions Kmean. A partir d'un vector inicialitzat amb dades aleatories, aplicar l'algorisme per obtenir 200 agrupacions dels 600.000 elements del vector.

Temps d'execució seqüencial amb les opcions "-O3" per N=600.000 i 200 centroides:

a Gat -> 65.15 segons,

a Roquer -> 21.25 segons

Es programarà amb OpenMP
Speedup mínim  a GAT: 3
La versió paral·lela ha de donar el mateix resultat que la seqüencial. (Cal comprovar els valors de sortida)
Cal executar el codi, forçant la creació de threads de 2 fins a 16.

# Compilación
## Secuencial
```bash
cc -O3 kmeanCPM.c -o kmeanCPM_secuencial
```
## Paralelo
```
cc -fopenmp kmeanCPM.c -p kmeanCPM_parallel
```

# Ejecución
## En local
```bash
time ./kmeanCPM_secuencial > secuencial.loc 2>&1 &
```
## En los nodos 
```bash
srun -p gat time ./kmeanCPM_secuencial > secuencial.gat 2>&1 & # En los nodos de GAT en este caso
```
