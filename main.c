#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 256

typedef struct
{
    char **scelte;
    int n_scelte;
}Livello;

int princ_molt(int pos, Livello *val, char **sol, int n, int count);

int main()
{
    FILE* fp;
    int i, o, A, num, numero_soluzioni;
    char stringa[max];
    Livello *val;
    char **sol;

    fp= fopen("brani.txt", "r"); //CONTROLLO FILE DI INPUT
    if(fp==NULL)
    {
        printf("Errore");
        return -1;
    }

    fscanf(fp, "%d", &A); //LETTURA NUMERO DI AMICI

    val= malloc(A*sizeof(Livello)); //ALLOCAZIONE DINAMICA STRUTTURA DATI

    for(i=0; i<A; i++) //LETTURA + SCRITTURA BRANI
    {
        fscanf(fp, "%d", &num);
        val[i].n_scelte= num;
        val[i].scelte= malloc(num*sizeof(char *));
        for(o=0; o<num; o++)
        {
            fscanf(fp, "%s", stringa);
            val[i].scelte[o]= strdup(stringa);
        }
    }

    sol= malloc(A*sizeof(char *)); //ALLOCAZIONE MATRICE SOLUZIONE

    numero_soluzioni= princ_molt(0, val, sol, A, 0);
    printf("\nNumero soluzioni trovate:%d", numero_soluzioni);

    fclose(fp);
    return 0;
}

int princ_molt(int pos, Livello *val, char **sol, int n, int count)
{
    int i;

    if(pos>=n)
    {
        for(i=0; i<n; i++)
            printf("%s ", sol[i]);
        printf("\n");
        return count+1;
    }

    for(i=0; i<val[pos].n_scelte; i++)
    {
        sol[pos]= strdup(val[pos].scelte[i]);
        count= princ_molt(pos+1, val, sol, n, count);
    }
    return count;
}
