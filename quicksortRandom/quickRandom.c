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

void troca(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int esquerda, int direita, int* iteracoes) {
    int pivo = arr[direita];
    int i = (esquerda - 1);
    for (int j = esquerda; j <= direita - 1; j++) {
        (*iteracoes)++;
        if (arr[j] < pivo) {
            i++;
            troca(&arr[i], &arr[j]);
        }
    }
    troca(&arr[i + 1], &arr[direita]);
    return (i + 1);
}

int partitionRandomizado(int arr[], int esquerda, int direita, int* iteracoes) {
    int randomIndex = esquerda + rand() % (direita - esquerda);
    troca(&arr[randomIndex], &arr[direita]);
    return partition(arr, esquerda, direita, iteracoes);
}

void quickSortRandomizado(int arr[], int esquerda, int direita, int* iteracoes) {
    if (esquerda < direita) {
        int pi = partitionRandomizado(arr, esquerda, direita, iteracoes);
        quickSortRandomizado(arr, esquerda, pi - 1, iteracoes);
        quickSortRandomizado(arr, pi + 1, direita, iteracoes);
    }
}

int main() {
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    FILE *fp_quick_random = fopen("QuickSortRandomizadoIteracoesCasoMedio.txt", "w");
    if (fp_quick_random == NULL) {
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
            quickSortRandomizado(arr, 0, tam - 1, &iteracoes);
            fprintf(fp_quick_random, "%d ", iteracoes);
        }
        fprintf(fp_quick_random, "\n");

        free(arr); 
    }

    fclose(fp_quick_random);

    FILE *fp_quick_randomPiorCaso = fopen("QuickSortRandomizadoIteracoesPiorCaso.txt", "w");
    if (fp_quick_randomPiorCaso == NULL) {
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
            quickSortRandomizado(arr, 0, tam - 1, &iteracoes);
            fprintf(fp_quick_randomPiorCaso, "%d ", iteracoes);
        }
        fprintf(fp_quick_randomPiorCaso, "\n");

        free(arr); 
    }

    fclose(fp_quick_randomPiorCaso);

    return 0;
}
