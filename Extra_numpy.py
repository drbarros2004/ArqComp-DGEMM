import numpy as np
import time

A = np.random.rand(8192, 8192)
B = np.random.rand(8192, 8192)

start_time = time.time()
C = A @ B
end_time = time.time()

execution_time = end_time - start_time
print(f"Tempo de execução da multiplicação de matrizes usando @: {execution_time} segundos")
