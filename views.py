import matplotlib.pyplot as plt
import numpy as np

# Função para ler os dados dos arquivos e calcular a média das iterações
def ler_dados_e_calcular_media(filename):
    with open(filename, 'r') as file:
        linhas = file.readlines()
        medias = []
        for linha in linhas:
            iteracoes = list(map(int, linha.split()))
            media = np.mean(iteracoes)
            medias.append(media)
    return medias

# Ler os dados dos arquivos
tamanhos = [5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000]
bubble_medio = ler_dados_e_calcular_media('BubblesortIteracoesCasoMedio.txt')
bubble_pior = ler_dados_e_calcular_media('BubblesortIteracoesPiorCaso.txt')
insertion_medio = ler_dados_e_calcular_media('insertionSortIteracoesCasoMedio.txt')
insertion_pior = ler_dados_e_calcular_media('insertionSortIteracoesPiorCaso.txt')
merge_medio = ler_dados_e_calcular_media('mergeSortIteracoesCasoMedio.txt')
merge_pior = ler_dados_e_calcular_media('mergeSortIteracoesPiorCaso.txt')
quick_medio = ler_dados_e_calcular_media('QuickSortIteracoesCasoMedio.txt')
selection_medio = ler_dados_e_calcular_media('SelectionSortIteracoesCasoMedio.txt')
selection_pior = ler_dados_e_calcular_media('SelectionSortIteracoesPiorCaso.txt')
quickRandom_medio = ler_dados_e_calcular_media('QuickSortRandomizadoIteracoesCasoMedio.txt')
quickRandom_pior = ler_dados_e_calcular_media('QuickSortRandomizadoIteracoesPiorCaso.txt')

# Criar gráficos
plt.figure(figsize=(14, 7))

# Caso Médio
plt.subplot(1, 2, 1)
plt.plot(tamanhos, bubble_medio, label='Bubble Sort')
plt.plot(tamanhos, insertion_medio, label='Insertion Sort')
plt.plot(tamanhos, merge_medio, label='Merge Sort')
plt.plot(tamanhos, quick_medio, label='Quick Sort')
plt.plot(tamanhos, selection_medio, label='Selection Sort')
plt.plot(tamanhos, quickRandom_medio, label='Quick Sort Random')
plt.title('Número Médio de Iterações - Caso Médio')
plt.xlabel('Tamanho do Vetor')
plt.ylabel('Número Médio de Iterações')
plt.legend()

# Pior Caso
plt.subplot(1, 2, 2)
plt.plot(tamanhos, bubble_pior, label='Bubble Sort')
plt.plot(tamanhos, insertion_pior, label='Insertion Sort')
plt.plot(tamanhos, merge_pior, label='Merge Sort')
plt.plot(tamanhos, label='Quick Sort')
plt.plot(tamanhos, selection_pior, label='Selection Sort')
plt.plot(tamanhos, quickRandom_pior, label='Quick Sort Random')
plt.title('Número Médio de Iterações - Pior Caso')
plt.xlabel('Tamanho do Vetor')
plt.ylabel('Número Médio de Iterações')
plt.legend()

plt.tight_layout()
plt.show()