import matplotlib.pyplot as plt

def get_list(file_path):
    list = []
    with open(file_path, 'r') as f:
        lines = f.readlines()
        for i in range(0, len(lines)):
            str = lines[i].rstrip('\n')
            list.append(int(str))
    return list

list_vec = get_list("E:\\Users\\fangliang\\source\\repos\\Test\\Release\\insert_begin_vec.txt")
list_list = get_list("E:\\Users\\fangliang\\source\\repos\\Test\\Release\\insert_begin_list.txt")
list_deque = get_list("E:\\Users\\fangliang\\source\\repos\\Test\\Release\\insert_begin_deque.txt")

plt.plot(list_vec, color='green', label='vec')
plt.plot(list_list, color='red', label='list')
plt.plot(list_deque, color='yellow', label='deque')

plt.xlim(0, 1024)
plt.ylim(0, 200)
plt.show()

