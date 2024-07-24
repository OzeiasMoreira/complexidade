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

void merge(int arr[], int esquerda,int meio, int direita,int* iteracoes){
    int i,j,k;

    int tam_esquerda = meio - esquerda + 1;
    int tam_direita = direita - meio;

    int* lado_esquerdo = (int*)malloc(tam_esquerda * sizeof(int));
    int* lado_direito = (int*)malloc(tam_direita * sizeof(int));

    for ( i = 0; i < tam_esquerda; i++)
    {
        lado_esquerdo[i] = arr[esquerda + i];
    }

    for ( j = 0; j < tam_direita; j++)
    {
        lado_direito[j] = arr[meio + 1 + j];
    }
    
    i = 0;
    j = 0;
    k = esquerda;

    while (i < tam_esquerda && j < tam_direita)
    {
        (*iteracoes)++;
        if (lado_esquerdo[i] <= lado_direito[j])
        {
            arr[k] = lado_esquerdo[i];
            i++;
        } else {
            arr[k] = lado_direito[j];
            j++;
        }
        
        k++;
    }

    while (i < tam_esquerda)
    {
        arr[k] = lado_esquerdo[i];
        i++;
        k++;
    }

    while (j < tam_direita)
    {
        arr[k] = lado_direito[j];
        j++;
        k++;
    }
    
    free(lado_esquerdo);
    free(lado_direito);
    
}

void mergeSort(int arr[], int esquerda, int direita, int* iteracoes){
    if (esquerda < direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(arr, esquerda , meio , iteracoes);
        mergeSort(arr, direita, meio + 1, iteracoes);

        merge(arr, esquerda , meio, direita , iteracoes);
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

        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam);
            int iteracoes;
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
            mergeSort(arr, 0, tam - 1, &iteracoes);
            fprintf(fp_mergePiorCaso, "%d ", iteracoes);
        }
        fprintf(fp_mergePiorCaso, "\n");

        free(arr); 
    }

    fclose(fp_mergePiorCaso);

    return 0;
}