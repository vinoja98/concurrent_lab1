import matplotlib.pyplot as plt
import numpy as np

X = ['1','2','4','8']
serial = [0.148263,0,0,0]
one_mutex = [0.198891,0.206902,0.212567,0.218792]
read_write_lock = [0.204849,0.176875,0.188650,0.267402]

X_axis = np.arange(len(X))

plt.bar(X_axis - 0.2, serial, 0.2, label = 'Serial')
plt.bar(X_axis , one_mutex, 0.2, label = 'One Mutex')
plt.bar(X_axis + 0.2, read_write_lock, 0.2, label = 'Read Write Lock')

plt.xticks(X_axis, X)
plt.xlabel('Number of Threads', fontsize = 10)
plt.ylabel('Average Execution Time (Seconds)', fontsize = 10)
plt.title('Graph of Average Execution Time vs. Number of Threads:  Case 03', fontsize = 12)
plt.legend()
plt.savefig('graphs/Case 03/Case 03.png')
plt.show()