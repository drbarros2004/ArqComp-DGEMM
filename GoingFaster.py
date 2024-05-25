#Going Faster 1: Matrix Multiply in Python

import random
import time

# Geração de matrizes aleatórias
a = [[random.uniform(0, 49) for _ in range(8192)] for _ in range(8192)]
b = [[random.uniform(0, 49) for _ in range(8192)] for _ in range(8192)]
c = [[0 for _ in range(8192)] for _ in range(8192)]


# print(a)
# print(b)


def multiplicacao_de_matriz(a, b, c):
    start_time, start_time2 = time.time(), time.process_time()
    
    # Multiplicação de matrizes
    for i in range(8192):
        for j in range(8192):
            for k in range(8192):
                c[i][j] += a[i][k] * b[k][j]

    end_time, end_time2 = time.time(), time.process_time()
    tempo_decorrido = end_time - start_time
    tempo_cpu = end_time2 - start_time2
    return c, tempo_decorrido, tempo_cpu

resultado, tempo_decorrido, tempo_cpu = multiplicacao_de_matriz(a, b, c)

#print(c)

print("\nTempo decorrido na multiplicação de matrizes: {:.2f} segundos".format(tempo_decorrido))
print("\nTempo decorrido (CPU) na multiplicação de matrizes: {:.2f} segundos".format(tempo_cpu))
