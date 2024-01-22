'''
Created on Feb 1, 2020

@author: kamilla
Ch5 Part3 Writing your own value returning functions
'''

def main(): 
    print ('Chapter 5 Functions part 3 value returning functions')
    print("""Read textbook Gaddis 4E, pages 250-261""")
    print ("""
def function_name():
    statement
    statement
    etc.
    return expression
""")
    num1=float(input("Please input first  decimal value: "))
    num2=float(input("Please input second decimal value: "))
    av = average(num1,num2)
    print("average of ", num1, " and ", num2, " is ", av)    
    print("you can print average using one statement below")
    print("average of ", num1, " and ", num2, " is ", average(num1,num2))
    
    print ("function average2() gives the same result as function average()")
    av2 = average2(num1,num2)   
    print("average2(): average of ", num1, " and ", num2, " is ", av2)    
    print("average2(): you can print average using one statement below")
    print("average2(): average of ", num1, " and ", num2, " is ", average2(num1,num2))
    
    print ("Returning String")
    dayOfTheWeek=getDay(7)
    print ("Day of the week is ", dayOfTheWeek)
    print ("Returning Boolean Values")
    dayOff=isDayOff(7)
    
    print ("Day of the week is ", dayOff)
    print ("The same as")
    print ("Day of the week is ", isDayOff(7))
    print ("Also possible:")
    if isDayOff(7):
        print ("Day is off")
    else:
        print ("Day is not off")
        
    print (" Returning multiple values")
    few_times = 'y'
    while few_times=='y':
        owner = input("Please enter name of the owner: ")
        cat,dog = get_pet_name(owner)
        print(owner+"'s cat name is", cat, owner+"'s dog name is", dog)
        few_times = input("Are you still interested in cat's and dog's names? y/n: ")
        
def average (var1,var2):
    av=(var1+var2)/2
    return av

def average2 (var1,var2):
    return (var1+var2)/2

def getDay(numberOfDay):
    if numberOfDay == 1:
        day = "Sunday"
    elif numberOfDay == 2:
        day = "Monday"
    elif numberOfDay == 3:
        day = "Tuesday"
    elif numberOfDay == 4:
        day = "Wednesday"
    elif numberOfDay == 5:
        day = "Thursday"
    elif numberOfDay == 6:
        day = "Friday"
    elif numberOfDay == 7:
        day = "Saturday"
    else:
        day = "not_possible_day" 
    return day 

def isDayOff(numberOfDay):
    if numberOfDay==7 or numberOfDay ==1:
        return True
    return False

def get_pet_name(owner):
    if owner == "TechSmith":
        cat = "Belly"
        dog = "Pompon"
    elif owner == "Camtasia":
        cat = "Queen"
        dog = "King"
    else:
        cat= "catOf"+owner
        dog= "dogOf"+owner      
    return cat, dog

if __name__ == '__main__':
    main()
    pass

