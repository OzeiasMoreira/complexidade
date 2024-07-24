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

void insertionSort(int arr[], int n, int* iteracoes) {
    *iteracoes = 0;
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
            (*iteracoes)++;
        }
        arr[j + 1] = chave;
        (*iteracoes)++;
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
        if (arr == NULL) {
            printf("Erro ao alocar memória.\n");
            fclose(fp_insertion);
            return 1;
        }

        for (int j = 0; j < tam; j++) {
            arr[j] = j;
        }

        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam);
            int iteracoes = 0;
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

    for (int i = 0; i < num_tamanhos; i++) {
        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));
        if (arr == NULL) {
            printf("Erro ao alocar memória.\n");
            fclose(fp_insertionPiorCaso);
            return 1;
        }

        for (int j = 0; j < tam; j++) {
            arr[j] = tam - j;
        }

        for (int j = 0; j < 30; j++) {
            int iteracoes = 0;
            insertionSort(arr, tam, &iteracoes);
            fprintf(fp_insertionPiorCaso, "%d ", iteracoes);

            // Reverter o array para o pior caso novamente
            for (int k = 0; k < tam / 2; k++) {
                int temp = arr[k];
                arr[k] = arr[tam - k - 1];
                arr[tam - k - 1] = temp;
            }
        }
        fprintf(fp_insertionPiorCaso, "\n");

        free(arr);
    }

    fclose(fp_insertionPiorCaso);

    return 0;
}
