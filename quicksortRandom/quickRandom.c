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


int partition(int arr[], int esquerda, int direita, int *iteracoes) {
    int pivo = arr[direita];
    int i = esquerda - 1;
    
    for (int j = esquerda; j < direita; j++) {
        (*iteracoes)++;
        if (arr[j] < pivo) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[direita];
    arr[direita] = temp;
    
    return i + 1;
}


void quickSort(int arr[], int esquerda, int direita, int *iteracoes) {
    if (esquerda < direita) {
        int pi = partition(arr, esquerda, direita, iteracoes);
        quickSort(arr, esquerda, pi - 1, iteracoes);
        quickSort(arr, pi + 1, direita, iteracoes);
    }
}

int main() {
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    
    FILE *fp_quick = fopen("QuickSortIteracoesCasoMedio.txt", "w");
    if (fp_quick == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    srand(time(0)); 

    for (int i = 0; i < num_tamanhos; i++) {
        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));
        if (arr == NULL) {
            printf("Erro ao alocar memória!\n");
            fclose(fp_quick);
            return 1;
        }

       
        for (int j = 0; j < tam; j++) {
            arr[j] = j;
        }

       
        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam);
            int iteracoes = 0;

            
            quickSort(arr, 0, tam - 1, &iteracoes);
            fprintf(fp_quick, "%d ", iteracoes);
        }
        fprintf(fp_quick, "\n");
        free(arr); 
    }

    
    fclose(fp_quick);

    FILE *fp_quickPiorcaso = fopen("QuickSortIteracoesPiorCaso.txt", "w");
    if (fp_quickPiorcaso == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    srand(time(0)); 

    for (int i = 0; i < num_tamanhos; i++) {
        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));
        if (arr == NULL) {
            printf("Erro ao alocar memória!\n");
            fclose(fp_quickPiorcaso);
            return 1;
        }

        for (int j = 0; j < tam; j++) {
            arr[j] = tam - j;
        }

        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam);
            int iteracoes = 0;

            quickSort(arr, 0, tam - 1, &iteracoes);
            fprintf(fp_quickPiorcaso, "%d ", iteracoes);
        }
        fprintf(fp_quickPiorcaso, "\n");
        free(arr);
    }

    fclose(fp_quickPiorcaso);
    return 0;
}