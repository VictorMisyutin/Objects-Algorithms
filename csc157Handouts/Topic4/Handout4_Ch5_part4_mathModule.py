'''
Created on Feb 1, 2020

@author: kamilla
Ch5 Part4 mathModule
'''
import math
def main(): 
    print ('Chapter 5 Functions part 4 math Module')
    print("""Read textbook Gaddis 4E, pages 261-268""")
    print ("Important: import math") 

    num =float(input("Please input a decimal value: "))
    square_root = math.sqrt(num)
    print("1. Square root of",num, "is",square_root)
    print("2. Square root of",num, "is",math.sqrt(num))
    
    print ("Page 263 Table 5-2 math Module Functions")
    print ("math.pi =",math.pi)
    print ("math.e  =",math.e)
    print ("Calculation of")
    for x in [-1.0,-0.5,0.0,0.5,1.0, math.sqrt(3)/2, -math.sqrt(3)/2]:
        print ("math.acos(",x,")=",math.acos(x),"=",math.acos(x)/math.pi,"pi == ", math.degrees(math.acos(x)),"degrees")
    
    x = float(input("acos(x), returns the arc cosine of x, in radians. Enter x such as -1<=x<=1: "))
    print ('acos(',x,")=",math.acos(x),"=",math.acos(x)/math.pi,"pi")
    
    x = float(input("asin(x), returns the arc sine of x, in radians. Enter x such as -1<=x<=1: "))
    print ('asin(',x,")=",math.asin(x),"=",math.asin(x)/math.pi,"pi")
    
    x = float(input("atan(x), returns the arc tangent of x, in radians. Enter x such as x is decimal : "))
    print ('atan(',x,")=",math.atan(x),"=",math.atan(x)/math.pi,"pi")
    
    print ("You can analyse and test other math functions, I leave it to you as ToDo(no grade)")
    print ("math functions:")
    print ("ceil(x) Returns the smallest integer that is greater than or equal to x.")
    print ("cos(x) Return the cosine of x in radians.")
    print ("degrees(x) Assuming x is an angle in radian, the function returns the angle converted to degrees-tested above.")
    print ("exp(x)   Return e^x")
    print ("floor(x) Returns the largest integer that is less than or equal to x.")
    print ("hypot(x,y) Returns the length of a hypotenuse that extends from (0,0) to (x,y).")
    print ("log(x) Returns the natural logarithm of x.")
    print ("log10(x) Returns the base-10 logarithm of x.")
    print ("radians(x) Assuming x is an angle in degrees, the function returns the angle converted to radians.")
    print ("radians(",90,")=",math.radians(90))
    print ("sin(x) Returns the sine of x in radians")
    print ("sqrt(x) Returns the square root of x.")
    print ("tan(x) Returns the tangent of x in radians. x cannot be the values when cos(x) is 0, that is x!=pi/2+N*pi, where N is integer")
    print ("exact tan(pi/2) does not exist, but here it is approximation, it must be a huge number")
    print (180/2,"degrees=pi/2=",math.pi/2)
    print ("tan(pi/2)=",math.tan(math.pi/2)) 
    print ("tan(",math.pi/2,")=",math.tan(math.pi/2)," must be huge number") 
    print (180/4,"degrees=pi/4=",math.pi/4)  
    print ("tan(pi/4)=",math.tan(math.pi/4)) 
    print ("tan(",math.pi/4,")=",math.tan(math.pi/4))
    print (180/3,"degrees=pi/3=",math.pi/3)
    print ("tan(pi/3)=",math.tan(math.pi/3)) 
    print ("tan(",math.pi/3,")=",math.tan(math.pi/3))
    print (180/6,"degrees=pi/6=",math.pi/6)
    print ("tan(pi/6)=",math.tan(math.pi/6)) 
    print ("tan(",math.pi/6,")=",math.tan(math.pi/6))
    x = float(input("calculating tan(x), Enter x (in radians): "))
    print('tan(',x,")=",math.tan(x),"=",math.tan(x)/math.pi,"pi=",math.degrees(x))
if __name__ == '__main__':
    main()
    pass

