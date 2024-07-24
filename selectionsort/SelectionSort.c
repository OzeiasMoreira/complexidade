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

void selectionSort(int arr[], int n, int* iteracoes) {
    *iteracoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*iteracoes)++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    FILE *fp_selection = fopen("SelectionSortIteracoesCasoMedio.txt", "w");
    if (fp_selection == NULL) {
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
            selectionSort(arr, tam, &iteracoes);
            fprintf(fp_selection, "%d ", iteracoes);
        }
        fprintf(fp_selection, "\n");

        free(arr); 
    }

    fclose(fp_selection);

    FILE *fp_selectionPiorCaso = fopen("SelectionSortIteracoesPiorCaso.txt", "w");
    if (fp_selectionPiorCaso == NULL) {
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
            selectionSort(arr, tam, &iteracoes);
            fprintf(fp_selectionPiorCaso, "%d ", iteracoes);
        }
        fprintf(fp_selectionPiorCaso, "\n");

        free(arr); 
    }

    fclose(fp_selectionPiorCaso);

    return 0;
}
