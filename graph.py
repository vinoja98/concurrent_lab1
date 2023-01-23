import matplotlib.pyplot as plt
import numpy as np

X = ['1','2','4','8']
serial = [0.100027,0,0,0]
one_mutex = [0.144467,0.061615,0.027435,0.013708]
read_write_lock = [0.135741,0.039784,0.016597,0.015902]

X_axis = np.arange(len(X))

plt.bar(X_axis - 0.2, serial, 0.2, label = 'Serial')
plt.bar(X_axis , one_mutex, 0.2, label = 'One Mutex')
plt.bar(X_axis + 0.2, read_write_lock, 0.2, label = 'Read Write Lock')

plt.xticks(X_axis, X)
plt.xlabel('Number of Threads', fontsize = 10)
plt.ylabel('Average Execution Time (Seconds)', fontsize = 10)
plt.title('Graph of Average Execution Time vs. Number of Threads:  Case 02', fontsize = 12)
plt.legend()
plt.savefig('graphs/Case 02/Case 02.png')
plt.show()