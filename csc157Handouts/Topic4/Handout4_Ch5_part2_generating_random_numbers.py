'''
Created on Feb 1, 2020

@author: kamilla
Ch5 Part2 value returning functions: generating random numbers
'''
import random
def main(): 
    print ('Chapter 5 Functions part 2 value returning functions: generating random numbers')
    print("""Read textbook Gaddis 4E, pages 239-249""")
    print ("There is example with random numbers generator in this handout ")
    theSamePseudoNumbers = input("Do you want to generate the same sequence of random numbers when you run program next time? y/n: ")
    if theSamePseudoNumbers == 'y':
        random.seed(10)
        print ("We set seed")
    
    # get random number between 1 and 1
    number = random.randint(1,1)
    print ("random integer number between 1 and 1 is ", number)
    # get random number between 1 and 2
    number = random.randint(1,2)
    print ("random integer number between 1 and 2 is ", number)
    # get random number between 1 and 3
    number = random.randint(1,3)
    print ("random integer number between 1 and 3 is ", number)
    # get random number between 1 and 4
    number = random.randint(1,4)
    print ("random integer number between 1 and 4 is ", number)
    print ("print 5 random integer numbers between 5 and 20")
    for count in range (5):
        print (count,". ",random.randint(5,20))
    # number will be one of 0,1,2,3
    number = random.randrange(4)
    print ("random integer number such as 0<=number<4 is ", number)
    # number will be one of 4,5,6,7
    number = random.randrange(4,8)
    print ("random integer number such as 4<=number<8 is ", number)
    # number will be one of 4,6,8
    number = random.randrange(4,10,2)
    print ("random integer number such as 4<=number<10, with step 2 is ", number)
    numberf = random.random()
    print ("random floating point number such as 0.0<=number<1.0 is ", numberf)
    numberf = random.uniform(1.0,5.0)
    print ("random floating point number such as 1.0<=number<5.0 is ", numberf)
    # number will be one of 4,6,8
    number = random.randrange(4,10,2)
if __name__ == '__main__':
    main()
    pass

