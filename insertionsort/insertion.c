#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mistureVetor(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if ((rand() / (double)RAND_MAX) < 0.5) {
            int j = (int)((n - 1) * (rand() / (double)RAND_MAX));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

void insertionSort(int arr[], int n, int* iteracoes){
    int i, j, chave;
    for ( i = 1; i < n; i++)
    {
        chave = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > chave)
        {
            arr[j + 1] = arr[j];
            j -= 1;
            (*iteracoes)++;
        }
        
        arr[j + 1] = chave;
    }
    
}

int main() {
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    FILE *fp_insertion = fopen("insertionSortIteracoesCasoMedio.txt", "w");
    if (fp_insertion == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    srand(time(0)); 

    for (int i = 0; i < num_tamanhos; i++) {
        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));

        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam);
            int iteracoes;
            insertionSort(arr, tam, &iteracoes);
            fprintf(fp_insertion, "%d ", iteracoes);
        }
        fprintf(fp_insertion, "\n");

        free(arr); 
    }

    fclose(fp_insertion);

    FILE *fp_insertionPiorCaso = fopen("insertionSortIteracoesPiorCaso.txt", "w");
    if (fp_insertionPiorCaso == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    srand(time(0)); 

    for (int i = 0; i < num_tamanhos; i++) {
        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));

        for (int j = 0; j > tam; j++) {
            arr[j] = j;
        }

        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam);
            int iteracoes;
            insertionSort(arr, tam, &iteracoes);
            fprintf(fp_insertionPiorCaso, "%d ", iteracoes);
        }
        fprintf(fp_insertionPiorCaso, "\n");

        free(arr); 
    }

    fclose(fp_insertionPiorCaso);

    return 0;
}