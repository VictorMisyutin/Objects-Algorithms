'''
Created on Jan 11, 2020

@author: kamilla
'''

print("How do you feel?")
print("Just Great")
print("""OK4
OK5
OK6?""")
print ('OK7!')

print ('Before running this program you have to install Eclipse using the link from agenda')
print ('You can use different IDE, but it will be your responsibility to make it work')
print ('Python Gaddis 4E Chapter1')
print ('Just read the chapter, it is introduction to Computers and Programming')
print ('Chapter2 - starting programming')
print ('At this point you are already familiar with console output-these output')

print ('Comments are in the text of the program')
# one line comment
print ("Computer programs perform:")
print ("1. input is received.")
print ("2. some process is performed." )
print ("3. output is produced.")

print ("To print single quote'")
print ("I'm here to help")
print ("""To print double quote" """)
print ("""Another way 
to print 
multiple 
lines""")

print ('type(1)   =',type(1))
print ('type(1.0) =',type(1.0))
var = 3.5
print ('var =',var,'type(var) =',type(var))
print ("input from console")
name = input("What is your name? ")
temperature  = int(input("What is temperature outside? (in Fahrenheit) "))
print ("Right now temperature outside is", temperature)
q = float(input("How many dollars in 5 quarters? "))
if q==1.25:  # bite from ch3
    print("you are absolutely right")
else:
    print ("sorry, but you are wrong")
    
print ("Expressions")
print ('5//2=',5//2)  #output 5//2= 2
print ("5/2 =",5/2)   #output 5/2 = 2.5
print("Ouput examples")
print ('One','Two','Three')          #output One Two Three
print ('One','Two','Three',sep ='')  #output OneTwoThree
print ('One','Two','Three',sep ='*') #output One*Two*Three
print ('One\tTwo\tThree')            #output One    Two    Three

var2 = 123456789.12345
print ("Formatted output")
print (var2, format(var2,',.2f'))    #123456789.12345 123,456,789.12
print (var2, format(var2,',f'))      #123456789.12345 123,456,789.123450
print (var2, format(var2,'12,.2f'))  #123456789.12345 123,456,789.12
print (var2, format(var2,'12.2f'))   #123456789.12345 123456789.12

percent =0.49
print (format(percent,'%'))          #49.000000%
print (format(percent,'.0%'))        #49%

someInteger=123456789
print(format(someInteger,'d'))       #123456789
print(format(someInteger,',d'))      #123,456,789
print(format(someInteger,'20d'))     #           123456789
print(format(someInteger,'20,d'))    #         123,456,789

print ("NAMED_CONSTANTS")
INTEREST_RATE= 0.04
print ('INEREST_RATE=',INTEREST_RATE) #INEREST_RATE= 0.04
INTEREST_RATE= 0.05
print ('INEREST_RATE=',INTEREST_RATE) #INEREST_RATE= 0.05
if __name__ == '__main__':
    print("Have a nice studies!")
    pass