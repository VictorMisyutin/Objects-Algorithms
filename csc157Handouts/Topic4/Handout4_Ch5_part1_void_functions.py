'''
Created on Feb 1, 2020
Ch5 void functions
@author: kamilla
'''
some_global= 55555
PI = 3.14
def main():
    print("How do you feel?")
    print("Just Great")
    print("""Let's
    start""")
    
    print ('Chapter 5 Functions Part1 void functions')
    print("""
    You can find information online by searching 
    'Python functions'
    """)
    print ("""A function is a group of statements that exist within 
    a program for the purpose of performing a specific task""")
    print ('There the two types of functions: ')
    print ('void functions and value-returning functions')
    print ("""
    def function_name():
         statement
         statement
         etc.
    """)
    print ("""
    #call function
    function_name()
    """)
    print ("""
    def main():
         statement
         statement
         etc.
    """)
    print ("""
    #call the main function
    main()
    """)
    print ("""
    Designing a Program to Use Functions
    using to-down design to break down an algorithm into functions.
    """)
    message()
    length = int(input("Please enter the length of the room in inches: "))
    width  = int(input("Please enter the width  of the room in inches: "))
    print("Passing arguments to a function areaOfRectangle()")
    areaOfRectangle(length,width)
    value = int(input("Please enter integer value "))
    print ("you just inputed value", value)
    set_to_zero(value)
    print ("We are back. Does not matter that function changed value, now value is", value)
    test_global_varable()
    print("Simulation of global constant PI=",PI)
def message():
    print ("inside function message()")
    day = input("What is day of the week today? ")
    print("day is local variable inside function message()")
    print("A local vaiable is created inside a function and cannot")
    print ("be accessded by statement that are outside the function.")
    print("Different functions can have local variables with the same names")
    print("because the functions cannot see each other's local variables.")
    print("Today is",day)
    agree = input("The weather today is nice. Isn't it? y or yes or :) ")
    if agree=="y" or agree=="yes"or agree == ":)":
        print("I am glad, that you are agree with me.")
        
def test_global_varable():
    global some_global
    show_global()
    some_global=int(input("Let's change global variable some_global, enter new value: "))
    show_global()
def show_global():
    print("Global variable some_global = ",some_global)
def areaOfRectangle(length,width):
    area =length*width
    print("area OfRectangle with length",length,"and width",width, "is equal to ",area)
def set_to_zero(value):
    value = 0
    print("inside function set_to_zero()")
    print("does not matter what you inputed, now local variable value is", value)
    
if __name__ == '__main__':
    main()
    pass

