'''
Created on Jan 11, 2020

@author: kamilla
'''

print("How do you feel?")
print("Just Great")
print("""Let's
start""")

print ('Chapter4 Repetition Structures (Loops)')
print("""
You can find information online by searching 
'Repetition Structures'
""")
print ('The while Loop: A Condition-Controlled Loop')
print ('while is a Pretest Loop')
print ("""
while condition:
     statement
     statement
     etc.
""")
ch = 'y'
i  = 0
while ch == 'y':
    print (i)
    i = i+1
    print ("""We must eventually change the value of condition,
    condition must eventually become False
     otherwise we will get infinite loop
     """)
    ch=input('Repeat? y/n: ')

print ('The for Loop: A Count-Controlled Loop')
print ("""
for variable in [value1, value2, etc.]:
     statement
     statement
     etc.
""")
print ("display numbers 1 2 3 4 5 6 7 8 9 10")
for number in [1,2,3,4,5,6,7,8,9,10]:
    print (number)
print ("Using the range Function with the for Loop")
print ("""
for num in range(5):
     print (num)
     
gives the same output as

for num in [0, 1, 2, 3, 4]:
     print (num).
""")
for num in range(5):
    print (num)
     
print ('gives the same output as')

for num in [0, 1, 2, 3, 4]:
    print (num)
    
print ("""
for num in range(1, 5):
     print (num)
     
gives the same output as

for num in [1, 2, 3, 4]:
     print (num).
""")
for num in range(1, 5):
    print (num)
print ('gives the same output as')
for num in [1, 2, 3, 4]:
    print (num)
print ("""
for num in range(5):
     print (num)
     
gives the same output as

for num in [0, 1, 2, 3, 4]:
     print (num).
""")
for num in range(5):
    print (num)
     
print ('gives the same output as')

for num in [0, 1, 2, 3, 4]:
    print (num)
    
print ("""
for num in range(1, 10, 2):   #2 is step here
     print (num)
     
gives the same output as

for num in [1, 3, 5, 7, 9]:
     print (num).
""")
for num in range(1, 10, 2):
    print (num)
print ('gives the same output as')
for num in [1, 3, 5, 7, 9]:
    print (num)
print ("See in the handout assignment statements")
x=9
print ("x=",x)
x=x+2
print ("x=x+2, x=",x)
x=x-1
print ("x=x-1, x=",x)
x=x*3
print ("x=x*3, x=",x)
x=x/2
print ("x=x/2, x=",x)
x=x//2
print ("x=x//2, x=",x)
x=x%3
print ("x=x%3, x=",x)

print("The Augmented Assignment operators: +=,-=,*=,/+,%=")
x=9
print ("x=",x)
x+=2
print ("x+=2, x=",x)
x-=1
print ("x-=1, x=",x)
x*=3
print ("x*=3, x=",x)
x/=2
print ("x/=2, x=",x)
x//=2
print ("x//=2, x=",x)
x%=3
print ("x%=3, x=",x)
print ("Nested Loops")
for col in range(6):
    print ('*', end='')
print("printing rectangle using asterisks")
"""
Please enter number of rows:5
Please enter number of columns:5
*****
*****
*****
*****
*****
"""
rows = int(input("Please enter number of rows:"))
columns = int(input("Please enter number of columns:"))
for r in range (rows):
    for c in range (columns):
        print ("*",end='')
    print()
print("printing right triangle using asterisks")
"""
How long is the base of the right triangle? 5
*
**
***
****
*****
"""
base = int(input("How long is the base of the right triangle? "))

for r in range (base):
    for c in range (r+1):
        print ('*',end='')
    print() 

if __name__ == '__main__':
    print("Have a nice studies!")
    pass

