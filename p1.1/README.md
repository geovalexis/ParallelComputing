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
```bash
cc -O3 kmeanCPM.c -o kmeanCPM
```

# Ejecución
## En GAT
```bash
srun -p gat time ./kmeanCPM 
```
