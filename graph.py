import matplotlib.pyplot as plt
import numpy as np

X = ['1','2','4','8']
serial = [0.098149,0,0,0]
one_mutex = [0.144952, 0.062469, 0.027505, 0.014296]
read_write_lock = [0.142103,0.046387,0.015754,0.014394]

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