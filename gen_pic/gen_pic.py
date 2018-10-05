import os
import matplotlib.pyplot as plt

def get_data(file_path):
    list = []
    with open(file_path, 'r') as f:
        lines = f.readlines()
        base = 0
        for i in range(0, len(lines)):
            str = lines[i].rstrip('\n')
            if len(str) == 0:
                break
            if i == 0:
                base = int(str)
            list.append(int(str) - base)
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
    type_color = {'vector': "red",
                 'deque': "green", 
                 'list': "blue", 
                 'forwardlist': "cyan", 
                 'set' : "magenta", 
                 'multiset' : "magenta",
                 'unorderedset' : "orange",
                 'unorderedmultiset' : "orange",
                 'map' : "mediumvioletred",
                 'multimap' : "mediumvioletred",
                 'unorderedmap' : "black",
                 'unorderedmultimap' : "black"} 
    return type_color.get(type, "pink")

def get_linestyle(type):
    type_linestyle = {'vector': "-",
                 'deque': "-", 
                 'list': "-", 
                 'forwardlist': "--", 
                 'set' : "-", 
                 'multiset' : "--",
                 'unorderedset' : "-",
                 'unorderedmultiset' : "--",
                 'map' : "-",
                 'multimap' : "--",
                 'unorderedmap' : "-",
                 'unorderemultidmap' : "--"} 
    return type_linestyle.get(type, "-.")

def get_file_name(title, x, withhighest):
    file_name = title
    if None == x:
        x = "full"
    file_name += "_"
    file_name += str(x)

    if withhighest:
       file_name += "_"
       file_name += "highest"

    file_name += ".png"
    return file_name

def draw_line(file_name, x_axis):
    if None == file_name:
        return
    type = get_type(file_name)
    color = get_color(type)
    linestyle = get_linestyle(type)
    data = get_data(file_name)
    data = data[:x_axis]
    plt.plot(data, color = color, label = type, linestyle = linestyle)

def analyze_results(file_list, x_axis = None, withhighest = True):
    if len(file_list) == 0:
        return

    title = ""
    data_list = []
    for i in range(0, len(file_list)):
        file_name = file_list[i]
        if len(title) == 0:
            title = get_title(file_name)

        data = get_data(file_name)
        if None == x_axis:
            x_axis = len(data)

        max_v = max(data[:x_axis])
        data_list.append((max_v, file_name))

    data_list.sort()
    draw_list_len = len(data_list)

    if False == withhighest:
        draw_list_len = draw_list_len - 1

    for i in range(0, draw_list_len):
        draw_line(data_list[i][1], x_axis)
    
    plt.title(title)
    plt.xlabel('Counts')
    plt.ylabel('Nanosecond')

    file_name = get_file_name(title, x_axis, withhighest)
    plt.legend(loc = 'best', fontsize = 'small', shadow = True)
    #plt.show()
    plt.rcParams['savefig.dpi'] = 300
    plt.rcParams['figure.dpi'] = 300
    plt.savefig(file_name)
    plt.close()

class Analyze(object):
    def __init__(self, floder_path, prefix):
        self.file_list = get_file_list(floder_path, prefix)
    def show(self, x = None, withhighest = True):
        analyze_results(self.file_list, x, withhighest)

def show_result(floder_path, prefix):
    analyze = Analyze(floder_path, prefix)
    analyze.show()
    analyze.show(withhighest = False)
    analyze.show(128 * 32)
    analyze.show(x = 128 * 32, withhighest = False)
    analyze.show(128 * 8)
    analyze.show(x = 128 * 8, withhighest = False)
    analyze.show(128 * 2)
    analyze.show(x = 128 * 2, withhighest = False)

#windows
#analyze_floder = "..\\x64\\Release\\"

#ubuntu
analyze_floder = "..\\all\\"

def show_insert_begin():
    show_result(analyze_floder, "test_insert_begin")

def show_insert_mid():
    show_result(analyze_floder, "test_insert_mid")

def show_insert_end():
    show_result(analyze_floder, "test_insert_end")

def show_erase_begin():
    show_result(analyze_floder, "test_erase_begin")

def show_erase_mid():
    show_result(analyze_floder, "test_erase_mid")

def show_erase_end():
    show_result(analyze_floder, "test_erase_end")

def show_traversal_begin():
    show_result(analyze_floder, "test_traversal_begin")

def show_traversal_mid():
    show_result(analyze_floder, "test_traversal_mid")

def show_traversal_end():
    show_result(analyze_floder, "test_traversal_end")

def show_find():
    show_result(analyze_floder, "test_find")

    
show_find()

show_insert_begin()
show_insert_mid()
show_insert_end()

show_erase_begin()
show_erase_mid()
show_erase_end()

show_traversal_begin()
show_traversal_mid()
show_traversal_end()


