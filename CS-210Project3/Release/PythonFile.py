import re
import string
from collection import Counter 

def printsomething():
print("Hello from python!")

def PrintMe(v):
print("You sent me: " + v)
return 100;

def SquareValue(v):
return v * v 

 def read_File();
     
     ticket = open("project_three_input_file.txt")
     products = ticket.read().split()

     unique_Product = sorted(set(products))

     for word in unique_Product:
     print("---------------------------")
     print("\n")
     print(products.count(word), " : ",  word)
     print("\n")
     print("---------------------------")

     ticket.close()

  
  def locate_Total_Product_Amount(v):
       
       ticket = open("project_three_input_file.txt")
       products = ticket.read().split()
       unique_Product = sorted(set(products))
       ticket.close()

       tot = 0
       tot_inventory = 0
       tot_inventory_count = 0

       for word in unique_Product:
            tot_inventory_count += 1

       for word in unique_Product:
           temp_String = word
           tot_inventory += 1
           if (temp_String == v):
               tot = products.count(word)
               tot_inventory -= 1 
           if (temp_String != v and tot_inventory == tot_inventory_count):
                return -1 


        return tot

   def read_AND_Write_File():

        ticket = open("project_three_input_file.txt")
        data = open("frequency.dat", "w")
        products = ticket.read().split()
        unique_Product = sorted(set(products))

        for word in unique_Product:
            data.write(word)
            data.write(" ")
            data.write(str(products.count(word)))
            data.write("\n")

        data.close()

        histo_data = open("frequency.dat",  "r")
        product_data = histo_data.readlines()


        temp_freq = 0
        temp_product = ""

        for line in product_data:
            temp_int = 0
            temp_string = line.split()
            for word in temp_string:
                temp_int += 1
                if (temp_int == 1):
                    temp_product = word
                    print(temp_product, end = " ")
                if (temp_int == 2):
                    temp_freq = int(word)


            for i range(temp_freq):
                print("+", end = "")
            print("\n")
            print("---------------------------")
            print("\n")
