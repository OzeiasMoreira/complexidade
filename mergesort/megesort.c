#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mistureVetor(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void merge(int arr[], int esquerda, int meio, int direita, int* iteracoes) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];

    i = 0;
    j = 0;
    k = esquerda;
    while (i < n1 && j < n2) {
        (*iteracoes)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int esquerda, int direita, int* iteracoes) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSort(arr, esquerda, meio, iteracoes);
        mergeSort(arr, meio + 1, direita, iteracoes);
        merge(arr, esquerda, meio, direita, iteracoes);
    }
}

int main() {
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    FILE *fp_merge = fopen("mergeSortIteracoesCasoMedio.txt", "w");
    if (fp_merge == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    srand(time(0)); 

    for (int i = 0; i < num_tamanhos; i++) {
        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));

        for (int j = 0; j < tam; j++) {
            arr[j] = j;
        }

        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam);
            int iteracoes = 0;
            mergeSort(arr, 0, tam - 1, &iteracoes);
            fprintf(fp_merge, "%d ", iteracoes);
        }
        fprintf(fp_merge, "\n");

        free(arr); 
    }

    fclose(fp_merge);

    FILE *fp_mergePiorCaso = fopen("mergeSortIteracoesPiorCaso.txt", "w");
    if (fp_mergePiorCaso == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    for (int i = 0; i < num_tamanhos; i++) {
        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));

        for (int j = 0; j < tam; j++) {
            arr[j] = tam - j;
        }

        for (int j = 0; j < 30; j++) {
            int iteracoes = 0;
            mergeSort(arr, 0, tam - 1, &iteracoes);
            fprintf(fp_mergePiorCaso, "%d ", iteracoes);
        }
        fprintf(fp_mergePiorCaso, "\n");

        free(arr); 
    }

    fclose(fp_mergePiorCaso);

    return 0;
}
