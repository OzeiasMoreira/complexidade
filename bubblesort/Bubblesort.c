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

void bubblesort(int arr[],int n,int* iteracoes){
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[j] = temp;
                (*iteracoes)++;
            }
            
        }
        
    }
    
}

int main() {
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    FILE *fp_bubble = fopen("BubblesortIteracoesCasoMedio.txt", "w");
    if (fp_bubble == NULL) {
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
            bubblesort(arr, tam, &iteracoes);
            fprintf(fp_bubble, "%d ", iteracoes);
        }
        fprintf(fp_bubble, "\n");

        free(arr); 
    }

    fclose(fp_bubble);

    FILE *fp_bubblepiorcaso = fopen("BubblesortIteracoesPiorCaso.txt", "w");
    if (fp_bubblepiorcaso == NULL) {
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
            bubblesort(arr, tam, &iteracoes);
            fprintf(fp_bubblepiorcaso, "%d ", iteracoes);
        }
        fprintf(fp_bubblepiorcaso, "\n");

        free(arr); 
    }

    fclose(fp_bubblepiorcaso);

    return 0;
}