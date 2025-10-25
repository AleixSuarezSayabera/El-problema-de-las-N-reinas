// Programa: vuit_reines.c
// Autor: Aleix Suárez Sayabera
// NIU: 1672360
// Data: 31-05-2024
// Descripció: Programa amb 5 algorismes diferents per estudiar les solucions al problema de les n reines
//Proves amb els algorismes:
//El primer algorisme, aleatori1, decideix si un vector és solució per n més gran que 100.
//L'algorisme aleatori2, que busca una solució al problema de forma aleatoria,ha arribat a trobar solucions 
//de fins a n=23, on el temps varia bastant degut a l'aleatorietat de l'algorisme.
//Amb l'algrosime aleatori3, que busca totes les solucions de forma aleatoria, he arribat a trobar totes les 
//solucions per a un tauler de mida 13x13 en un temps 3 minuts i 43 segons, on per al mateix tauler backtrack en triga 10 segons.
//L'algorisme backtrack, ha arribat a trobar solucions d'un tauler 15x15 en 5 minuts i 51 segons.
//L'últim algorisme, matriu, ha arribat a calcular les diferents matrius de solucions per a un tauler de mida 13x13 en 54 segons.


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

bool es_solucio(int *vector, int n);
int* vector_aleatori(int n);
void totes_les_solucions_aleatories(int n, const char*);
int backtracking(int *, int , int , int *, const char*);

void aleatori1(int, const char*, const char*);
void aleatori2(int, const char*, const char*);
void aleatori3(int, const char*, const char*);
void backtrack(int,const char*, const char*);
void matriu_compta_solucions(int, const char*, const char*);

bool acceptable(int *, int , int , int );
void tractar_solucio(int *, int, const char*);
int backtracking(int *, int , int , int *, const char*);
void backtracking_especial(int *, int , int , int, int , int *, int *, int *, int *);
bool inv_per_r2(int *, int);
bool inv_per_r(int *, int);
int* llegir_vector(const char*, int);
int es_duplicada(int*, int**, int, int);
void fer_simetries(int*, int, int**);
int es_duplicada_simetries(int* , int* , int );

long long int solucions_totals[] = {1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596, 2279184, 14772512, 95815104, 666090624, 4968057848};

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "vuit_reines mida algorisme fitxer_entrada.txt fitxer_sortida.txt\n");
        return -1;
    }

    int n = atoi(argv[1]);
    const char *algorisme = argv[2];
    const char *fitxer_entrada = argv[3];
    const char *fitxer_sortida = argv[4];

    if (n == 2 || n == 3) {
        fprintf(stderr, "Error: el tauler %dx%d no té solució.\n", n, n);
        return -1;
    }

    if (strcmp(algorisme, "aleatori1") == 0) {
        aleatori1(n, fitxer_entrada, fitxer_sortida);
    } 
    else if (strcmp(algorisme, "aleatori2") == 0) {
        aleatori2(n, fitxer_entrada, fitxer_sortida);
    } 
    else if (strcmp(algorisme, "aleatori3") == 0) {
        aleatori3(n, fitxer_entrada, fitxer_sortida);
    } 
    else if (strcmp(algorisme, "backtrack") == 0) {
        backtrack(n, fitxer_entrada, fitxer_sortida);
    } 
    else if (strcmp(algorisme, "matriu") == 0) {
        matriu_compta_solucions(n, fitxer_entrada, fitxer_sortida);
    } 
    else {
        fprintf(stderr, "Algorisme desconegut: %s\n", algorisme);
        return -1;
    }

    return 0;
}

void aleatori1(int n, const char* nom, const char* nom_sortida) {
    int *vector = llegir_vector(nom, n);
    FILE *file = fopen(nom_sortida, "a");
    if (file == NULL) {
        printf("Error a l'obrir el document\n");
        free(vector);
        return;
    }

    fprintf(file, "dim=%d (aleatori1)\n", n);
    fprintf(file, "El vector v=(%d",vector[0]);
    for (int i = 1; i < n; i++) {
        fprintf(file, ",%d", vector[i]);
    }
    fprintf(file, ")\n");
    if (es_solucio(vector,n)){
        fprintf(file,"és solució");
        fclose(file);
    }
    else {
        fprintf(file,"no és solució");
        fclose(file);
    }
    printf("El tauler és de mida %dx%d (aleatori1)\n", n, n);
    printf("El vector v=(%d",vector[0]);
    for (int i = 1; i < n; i++) {
        printf(",%d", vector[i]);
    }
    printf(") ");
    if (es_solucio(vector,n)){
        printf("és solució");
    }
    else {
        printf("no és solució");
    }
    free(vector); 
}

void aleatori2(int n, const char* nom, const char* nom_sortida) {
    int* vector;
    srand(time(NULL));
    do {
        vector = vector_aleatori(n);
    } while (!es_solucio(vector, n));

    FILE *file = fopen(nom_sortida, "a");
    if (file == NULL) {
        printf("Error a l'obrir el document\n");
        free(vector);
        return;
    }

    fprintf(file, "dim=%d (aleatori2)\n", n);
    fprintf(file, "El vector v=(%d",vector[0]);
    for (int i = 1; i < n; i++) {
        fprintf(file, ",%d", vector[i]);
    }
    fprintf(file, ")\n");
    fprintf(file,"és solució");
    fclose(file);

    printf("El tauler és de mida %dx%d (aleatori2)\n", n, n);
    printf("El vector v=(%d",vector[0]);
    for (int i = 1; i < n; i++) {
        printf(",%d", vector[i]);
    }
    printf(") ");
    printf("és solució");
    free(vector); 
    return;
    }

void aleatori3(int n, const char* nom, const char* nom_sortida) {
    totes_les_solucions_aleatories(n,nom_sortida);
    printf("El tauler és de mida %dx%d (aleatori3)\n", n, n);
}

void backtrack(int n, const char* nom, const char* nom_sortida) {
    int *tauler = (int *)malloc(n * sizeof(int));
    if (tauler == NULL) {
        printf("Error de memoria.\n");
        exit(1);
    }
    FILE *file = fopen(nom_sortida ,"a");
    if (file == NULL) {
        printf("Error al obrir el document\n");
        return;
    }
    fprintf(file, "dim=%d (backtrack)\n", n);
    int columna = 0;
    int k = 0;
    int s = backtracking(tauler,columna,n,&k, nom_sortida);
    printf("El tauler és de mida %dx%d (backtrack)\n", n, n);
    printf("s'han trobat %d solucions\n", s);
    free(tauler);
}

void matriu_compta_solucions(int n, const char* nom, const char* nom_sortida) {
    int **M2 = (int **)malloc(n * sizeof(int *));
    int **M4 = (int **)malloc(n * sizeof(int *));
    int **M8 = (int **)malloc(n * sizeof(int *));
    int **MS = (int **)malloc(n * sizeof(int *));

    if (M2 == NULL || M4 == NULL || M8 == NULL || MS == NULL) {
        printf("No hi ha memòria per a les matrius\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        M2[i] = (int *)malloc(n * sizeof(int));
        M4[i] = (int *)malloc(n * sizeof(int));
        M8[i] = (int *)malloc(n * sizeof(int));
        MS[i] = (int *)malloc(n * sizeof(int));
        if (M2[i] == NULL || M4[i] == NULL || M8[i] == NULL || MS[i] == NULL) {
            printf("No hi ha memòria per a les matrius\n");
            exit(1); 
        }
    }
    
    for (int ff = 0; ff < n; ff++) {
        for (int cf = 0; cf < n; cf++) {
            int *tauler = (int *)malloc(n * sizeof(int));
            int m2 = 0;
            int m4 = 0;
            int m8 = 0;
            int k = 0;
            backtracking_especial(tauler, 0, n, cf, ff, &m2, &m4, &m8, &k);
            M2[ff][cf] = m2;
            M4[ff][cf] = m4;
            M8[ff][cf] = m8;
            MS[ff][cf] = k;
            free(tauler);
        }
    }
    
    int *vector = (int *)malloc(3 * sizeof(int));
    if (vector == NULL) {
        printf("Error de memòria\n");
        exit(1); 
    }
    vector[0] = 0;
    vector[1] = 0;
    vector[2] = 0;
    for (int i = 0; i < n; i++) {
        vector[0] += M2[0][i];
        vector[1] += M4[0][i];
        vector[2] += M8[0][i];
    }
    vector[0] = vector[0]/2;
    vector[1] = vector[1]/4;
    vector[2] = vector[2]/8;
    FILE *file = fopen(nom_sortida, "a");
    if (file == NULL) {
        printf("Error a l'obrir el document\n");
        free(vector);
        return;
    }
    fprintf(file, "Matriu MS=\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file,"%d ", MS[i][j]);
        }
        fprintf(file,"\n");
    }
    fprintf(file,"\n");
    fprintf(file,"Matriu M2=\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file,"%d ", M2[i][j]);
        }
        fprintf(file,"\n");
    }
    fprintf(file,"\n");
    fprintf(file,"Matriu M4=\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file,"%d ", M4[i][j]);
        }
        fprintf(file,"\n");
    }
    fprintf(file,"\n");
    fprintf(file,"Matriu M8=\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file,"%d ", M8[i][j]);
        }
        fprintf(file,"\n");
    }
    fprintf(file,"\n");
    fprintf(file, "vector de solucions essencials\n");
    fprintf(file, "VS=(%d,%d,%d)\n",vector[0],vector[1],vector[2]);
    fprintf(file,"\n");
    fprintf(file,"nombre de solucions essencials=%d\n",vector[0]+vector[1]+vector[2]);
    fprintf(file,"nombre total de solucions=%d",2*vector[0]+4*vector[1]+8*vector[2]);
    fclose(file);
    printf("Matriu MS=\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", MS[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Matriu M2=\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", M2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Matriu M4=\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", M4[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Matriu M8=\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", M8[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("vector de solucions essencials\n");
    printf("VS=(%d,%d,%d)\n",vector[0],vector[1],vector[2]);
    printf("\n");
    printf("nombre de solucions essencials=%d\n",vector[0]+vector[1]+vector[2]);

    for (int i = 0; i < n; i++) {
        free(M2[i]);
        free(M4[i]);
        free(M8[i]);
        free(MS[i]);
    }
    free(vector);
    free(M2);
    free(M4);
    free(M8);
    free(MS);
}

int backtracking(int *tauler, int columna, int n, int *k,const char* nom_sortida) {
    for (int i = 0; i < n; i++) {
        if (acceptable(tauler, columna, i, n)) {
            tauler[columna] = i;
            if (columna == n - 1) {
                tractar_solucio(tauler, n, nom_sortida);
                (*k)++;
            } else {
                backtracking(tauler, columna + 1, n, k, nom_sortida);
            }
        }
    }
    return *k;
}

bool acceptable(int *tauler, int columna, int i, int n) {
    for (int j = 0; j < columna; j++) {
        if (tauler[j] == i || abs(tauler[j] - i) == abs(j - columna)) {
            return false;
        }
    }
    return true;
}

void tractar_solucio(int *tauler, int n,const char* nom_sortida) {
    FILE *file = fopen(nom_sortida ,"a");
    if (file == NULL) {
        printf("Error al obrir el document\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", tauler[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

bool es_solucio(int* vector, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vector[i] == vector[j] || abs(vector[i] - vector[j]) == abs(i - j)) {
                return false;
            }
        }
    }
    return true;
}

int* vector_aleatori(int n) {
    int *vector = (int*)malloc(n * sizeof(int));
    if (vector == NULL) {
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        vector[i] = i + 1;
    }
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = vector[i];
        vector[i] = vector[j];
        vector[j] = temp;
    }
    return vector;
}

int* llegir_vector(const char* nom, int n) {
    FILE *file = fopen(nom, "r");
    if (file == NULL) {
        fprintf(stderr, "Error a l'obrir l'archiu %s\n", nom);
        exit(1);
    }

    int *vector = (int*)malloc(n * sizeof(int));
    if (vector == NULL) {
        fprintf(stderr, "Error a l'assignar memòria\n");
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &vector[i]) != 1) {
            fprintf(stderr, "Error al llegir l'archiu %s\n", nom);
            free(vector);
            fclose(file);
            exit(1);
        }
    }

    fclose(file);
    return vector;
}

bool inv_per_r2(int *vector, int n) {
    for (int i = 0; i < n; i++) {
        if (vector[i] != (n - 1 - vector[n - i - 1])) {
            return false;
        }
    }
    return true;
}

bool inv_per_r(int *vector, int n) {
    for (int i = 0; i < n; i++) {
        if (vector[n - 1 - vector[i]] != i) {
            return false;
        }
    }
    return true;
}

void backtracking_especial(int *tauler, int columna, int n, int cf, int ff, int *m2, int *m4, int *m8, int *k) {
    if (columna == n) {
        (*k)++;
        if (inv_per_r2(tauler,n)){
            if (inv_per_r(tauler,n)){
            (*m2)++;
            return;
        }
        else{
            (*m4)++;
            return;}
            }
        else {
            (*m8)++;
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        if (acceptable(tauler, columna, i, n) && (columna != cf || i == ff)) {
            tauler[columna] = i;
            backtracking_especial(tauler, columna + 1, n, cf, ff, m2, m4, m8, k);
        }
    }
}

void fer_simetries(int* vector, int n, int** simetries) {
    for (int i = 0; i < n; i++) {
        simetries[0][i] = vector[n - 1 - i];
    }

    for (int i = 0; i < n; i++) {
        simetries[1][vector[i] - 1] = n - i;
    }

    for (int i = 0; i < n; i++) {
        simetries[2][vector[i] - 1] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        simetries[3][n - vector[i]] = n - i;
    }

    for (int i = 0; i < n; i++) {
        simetries[4][i] = simetries[1][n - 1 - i];
        simetries[5][i] = simetries[2][n - 1 - i];
        simetries[6][i] = simetries[3][n - 1 - i];
    }
}

int es_duplicada(int* vector, int** solucions_uniques, int solucions_trobades, int n) {
    for (int i = 0; i < solucions_trobades; i++) {
        int es_igual = 1;
        for (int j = 0; j < n; j++) {
            if (solucions_uniques[i][j] != vector[j]) {
                es_igual = 0;
                break;
            }
        }
        if (es_igual) {
            return 1;
        }
    }
    return 0;
}

void totes_les_solucions_aleatories(int n, const char* nom_sortida) {
    FILE *file = fopen(nom_sortida, "w");
    if (file == NULL) {
        printf("Error en obrir el fitxer.\n");
        exit(1);
    }

    srand(time(NULL));
    int solucions_trobades = 0;
    int *vector;
    int **solucions_uniques = (int**)malloc(solucions_totals[n-1] * sizeof(int*));
    int **simetries = (int**)malloc(7 * sizeof(int*));
    for (int i = 0; i < 7; i++) {
        simetries[i] = (int*)malloc(n * sizeof(int));
    }
    
    if (solucions_uniques == NULL || simetries == NULL) {
        printf("Error de memòria.\n");
        fclose(file);
        exit(1);
    }

    while (solucions_trobades < solucions_totals[n-1]) {
        vector = vector_aleatori(n);
        if (es_solucio(vector, n)) {
            fer_simetries(vector, n, simetries);
            if (!es_duplicada(vector, solucions_uniques, solucions_trobades, n)) {
                solucions_uniques[solucions_trobades] = vector;
                for (int i = 0; i < n; i++) {
                    fprintf(file, "%d ", vector[i]);
                    printf("%d ", vector[i]);
                }
                fprintf(file, "\n");
                printf("\n");
                solucions_trobades++;

                for (int i = 0; i < 7; i++) {
                    if (!es_duplicada(simetries[i], &vector, 1, n)) {
                        int* nova_solucio = (int*)malloc(n * sizeof(int));
                        for (int j = 0; j < n; j++) {
                            nova_solucio[j] = simetries[i][j];
                        }
                        solucions_uniques[solucions_trobades] = nova_solucio;
                        for (int j = 0; j < n; j++) {
                            fprintf(file, "%d ", nova_solucio[j]);
                            printf("%d ", nova_solucio[j]);
                        }
                        printf("\n");
                        fprintf(file, "\n");
                        solucions_trobades++;
                    }
                }
            } else {
                free(vector);
            }
        } else {
            free(vector);
        }
    }
    fprintf(file, "dim=%d (aleatori3)\n", n);
    for (int i = 0; i < solucions_trobades; i++) {
        free(solucions_uniques[i]);
    }
    free(solucions_uniques);
    for (int i = 0; i < 7; i++) {
        free(simetries[i]);
    }
    free(simetries);

    fclose(file);
}