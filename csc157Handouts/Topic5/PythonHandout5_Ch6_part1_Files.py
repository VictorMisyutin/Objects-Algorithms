'''
Created on Jan 11, 2020

@author: kamilla
'''
def main():
    print("How do you feel?")
    print("Just Great")
    print("""Let's
    start""")
    
    print ('Chapter6  Files and Exceptions')
    print("""
    part1 Files
    """)
    print ('read pages 287-324')
    print ("""
    Openning a File
    file_variable = open(filename, mode)
    mode can be 'r', 'w', 'a'
    """)
    input_file            = open('in_r.txt','r')
    output_file           = open('out_w.txt','w')
    append_to_output_file = open('out_a.txt','a')
    name=input("What is your name? ")
    output_file.write("Diary of "+name+'\n')
    append_to_output_file.write("Continue Diary of "+name+'\n')
    number1 = int(input_file.readline())
    output_file.write("1.topic "+str(number1)+'\n')
    
    float1 = float(input_file.readline())
    output_file.write("2.topic "+str(float1)+'\n')
    
    string_line = input_file.readline()
    output_file.write("just read from input file single line: "+string_line)
    input_file2  = open('in_r2.txt','r')
    output_file2 = open('out_w2.txt','w')
    count = 0;
    for line in input_file2:
        count += 1
        output_file2.write(str(count)+" in loop just read from input file2: "+line)
    input_file.close()
    input_file2.close()
    output_file.close()
    output_file2.close()
    input_file3  = open('in_r3.txt','r')
    output_file3 = open('out_w3.txt','w')
    count = 0;
    line = input_file3.readline()
    while line!='':
        count += 1
        output_file3.write(str(count)+" in loop just read from input file3: "+line)
        line = input_file3.readline()
    input_file3.close()
    output_file3.close()
    append_to_output_file.close()
    
main()

