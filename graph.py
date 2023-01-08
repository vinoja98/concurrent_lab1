import matplotlib.pyplot as plt
  
names = []
marks = []
  
f = open('tempData.txt','r')
for row in f:
    row = row.split(' ')
    names.append(row[0])
    marks.append(float(row[1]))
  
plt.bar(names, marks, color = 'g', label = 'Execution Time')
  
plt.xlabel('Number of Threads', fontsize = 10)
plt.ylabel('Average Execution Time', fontsize = 10)
  
plt.title('Graph of Average Execution Time vs. the Number of Threads', fontsize = 12)
plt.legend()
plt.show()