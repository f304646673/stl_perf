import os
import matplotlib.pyplot as plt

def get_list(file_path):
    list = []
    with open(file_path, 'r') as f:
        lines = f.readlines()
        for i in range(0, len(lines)):
            str = lines[i].rstrip('\n')
            list.append(int(str))
    return list

def get_file_list(floder_path, prefix):
    ret_list = []
    list = os.listdir(floder_path)
    for i in range(0, len(list)):
        if (0 != list[i].find(prefix)):
            continue
        path = os.path.join(floder_path, list[i])
        if os.path.isfile(path):
            ret_list.append(path)
    return ret_list

def get_substr(src, start_str, end_str):
    first = src.rfind(start_str)
    last = src.rfind(end_str)
    substr = src[first + len(start_str) : last]
    return substr

def get_type(file_name):
    return get_substr(file_name, "_", ".")

def get_title(file_name):
    return get_substr(file_name, "test_", "_")

def get_color(type):
    type_color = {'vector': "r", 'deque': "g", 'list': "b", 'forward_list': "c"} # {'b', 'g', 'r', 'c', 'm', 'y', 'k', 'w'};
    return type_color.get(type, "k")

def analyze_results(file_list, x = None, y = None):
    title = ""
    for i in range(0, len(file_list)):
        if len(title) == 0:
            title = get_title(file_list[i])
        type = get_type(file_list[i])
        color = get_color(type)
        list = get_list(file_list[i])
        plt.plot(list, color = color, label = type)
    
    plt.title(title)
    if x != None:
        plt.xlim(0, x)
    if y != None:
        plt.ylim(0, y )
    plt.legend()
    plt.show()

class Analyze(object):
    def __init__(self, floder_path, prefix):
        self.file_list = get_file_list(floder_path, prefix)
    def show(self, x = None, y = None):
        analyze_results(self.file_list, x, y)

def show_insert_begin():
    file_list_begin = Analyze("E:\\Users\\fangliang\\source\\repos\\Test\\stl_perf\\Release\\", "test_insert_begin")
    file_list_begin.show()
    file_list_begin.show(128 * 16, 128 * 8)
    file_list_begin.show(128 * 8, 128 * 4)
    file_list_begin.show(128, 128)

def show_insert_mid():
    file_list_mid = Analyze("E:\\Users\\fangliang\\source\\repos\\Test\\stl_perf\\Release\\", "test_insert_mid")
    file_list_mid.show()
    file_list_mid.show(128 * 16, 128 * 8)
    file_list_mid.show(128 * 8, 128 * 4)
    file_list_mid.show(128, 128)

def show_insert_end():
    file_list_end = Analyze("E:\\Users\\fangliang\\source\\repos\\Test\\stl_perf\\Release\\", "test_insert_end")
    file_list_end.show()
    file_list_end.show(128 * 16, 128 * 8)
    file_list_end.show(128 * 8, 128 * 4)
    file_list_end.show(128, 128)

def show_erase_begin():
    file_list_begin = Analyze("E:\\Users\\fangliang\\source\\repos\\Test\\stl_perf\\Release\\", "test_erase_begin")
    file_list_begin.show()
    file_list_begin.show(128 * 16, 128 * 8)
    file_list_begin.show(128 * 8, 128 * 4)
    file_list_begin.show(128, 128)

def show_erase_mid():
    file_list_mid = Analyze("E:\\Users\\fangliang\\source\\repos\\Test\\stl_perf\\Release\\", "test_erase_mid")
    file_list_mid.show()
    file_list_mid.show(128 * 16, 128 * 8)
    file_list_mid.show(128 * 8, 128 * 4)
    file_list_mid.show(128, 128)

def show_erase_end():
    file_list_end = Analyze("E:\\Users\\fangliang\\source\\repos\\Test\\stl_perf\\Release\\", "test_erase_end")
    file_list_end.show()
    file_list_end.show(128 * 16, 128 * 8)
    file_list_end.show(128 * 8, 128 * 4)
    file_list_end.show(128, 128)

#show_insert_begin
#show_insert_mid()
#show_insert_end()
show_erase_begin()
show_erase_mid()
show_erase_end()


