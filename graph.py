import matplotlib.pyplot as plt
import numpy as np
# names = []
# marks = []
  
# f = open('tempData.txt','r')
# for row in f:
#     row = row.split(' ')
#     names.append(row[0])
#     marks.append(float(row[1]))
  
# plt.bar(names, marks, color = 'g', label = 'Execution Time')
  



# plt.legend()
# plt.savefig('my_plot.png')
# plt.show()

# plt.close()

X = ['1','2','4','8']
serial = [0.049744,0,0,0]
one_mutex = [0.071907,0.030658,0.013694,0.006924]
read_write_lock = [0.068751,0.020252,0.00944,0.007911]
  
X_axis = np.arange(len(X))
  
plt.bar(X_axis - 0.2, serial, 0.2, label = 'Serial')
plt.bar(X_axis , one_mutex, 0.2, label = 'One Mutex')
plt.bar(X_axis + 0.2, read_write_lock, 0.2, label = 'Read Write Lock')
  
plt.xticks(X_axis, X)
plt.xlabel('Number of Threads', fontsize = 10)
plt.ylabel('Average Execution Time', fontsize = 10)
plt.title('Graph of Average Execution Time vs. the Number of Threads:  Case 01', fontsize = 12)
plt.legend()
plt.savefig('graphs/Case 01/Case 01.png')
plt.show()