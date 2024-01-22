def main():
    infile = open('in.txt','r')
    numbers = infile.read()
    infile.close()
    outfile = open('out.txt','w')
    counter = len(numbers)
    for i in range(counter):
        outfile.write(numbers[i])
#       print(numbers[i],end='')
        if (i+1)%3==0:          # you can see file after program run. It is wierd. It is not what you expectd.
            outfile.write('\n')
    outfile.close()
    #print content of the list
    #piece of program that uses the writelines method to save a list of strings to a file.
    listA=['aaa','bbb','ccc']
    outfileA = open('outA.txt','w')
    # write the listA to the file
    outfileA.writelines(listA)
    outfileA.close()
    #piece of program that saves a list of strings to a file.
    listB=['ddd','ggg','fff']
    outfileB = open('outB.txt','w')
    # write the listB to the file
    for item in listB:
        outfileB.write(item+'\n')
    outfileB.close()
    
    print ("testFile  4 input and 4 corresponding output files")
    for i in range(4):
        testFile("in"+str(i)+".txt","out"+str(i)+".txt")
        
#read whole file content into list data[]
def readData(inputFile, data):
   
    with open(inputFile, "r") as f:
        for line in f:
            data.extend([int(x) for x in line.split()])

def testFile(inputFilename, outputFilename):
    fout =""
    data = []
    print("Input file " + inputFilename + ", Output file " + outputFilename)
    readData(inputFilename,data)
    counter = len(data)
# output list data[] in output file in one line with space between elements
    for ind in range(counter):
        fout+=str(data[ind])+" "
    
    with open(outputFilename, "w") as o:
        o.write(fout)
    print("Done\n")
if __name__ == '__main__':
    main()
