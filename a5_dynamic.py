#7. Length and elements of a longest subarray of numbers where their	real part is in the form of a mountain (first the values increase, then they decrease). (e.g. `1-i, 2+6i, 4-67i, 90+3i, 80-7i, 76+i, 43-12i, 3`)

#12. The length and elements of a longest alternating subsequence, when considering each number's real part (e.g., given sequence [1, 3, 2, 4, 10, 6, 1], [1, 3, 2, 10] is an alternating subsequence, because 1 < 3 > 2 < 10)

#
# Write the implementation for A5 in this file
#
import random

# Function for verification
# Verification for option!
def valid(option_chosen:str):
    if option_chosen.isnumeric() and int(option_chosen) in [1,2,3,4,5,6,7]:
        return True
    return False
def clear_list(complex_number_inserted:list):
    complex_number_inserted.clear()


def test_for_7(complex_number_inserted:list):
    values = [ '1-i', '2+6i', '4-67i', '90+3i', '80-7i', '76+i', '43-12i', '3']
    for value in values:
        add_complex_number(str(value),complex_number_inserted)
def test_for_12(complex_number_inserted:list):
    values = [1, 3, 2, 4, 10, 6, 1]
    for value in values:
        add_complex_number(str(value),complex_number_inserted)
        
# Proceed option and call what function he need
def option_proceed(option_chosen:int,complex_number_inserted):
    if option_chosen == 1:
        create_list_ui(complex_number_inserted)
    elif option_chosen == 2:
        mountain_problem_ui(complex_number_inserted)
    elif option_chosen == 3:
        dynamic_problem_ui(complex_number_inserted)
    elif option_chosen == 4:
        quit()
    elif option_chosen == 5:
        test_for_7(complex_number_inserted)
    elif option_chosen == 6:
        test_for_12(complex_number_inserted)
    elif option_chosen == 7:
        clear_list(complex_number_inserted)

# Verify if the input is a complex number
def valid_str(number:str):
    if len(number) == 0:
        return False
    number_split = split_number(number)
    if number_split[1][0] == "-":
        number_split[1] = number_split[1][1::]
    if number_split[0][0] == "+" or number_split[0][0] == "-":
        number_split[0] = number_split[0][1::]
    if len(number_split) != 2:
        return False
    index_i_on_imaginary_part = number_split[1].find("i")
    if index_i_on_imaginary_part != len(number_split[1])-1:
        return False
    imaginary_part = divide_imaginary_part(number_split[1])
    if  not valid_number(number_split[0]) or not valid_number(imaginary_part):
        return False
    return True

# Split number in real part and imaginary part
def split_number(number:str):
    if number.isnumeric():
        return [number, 0]
    sign_real = ''
    middle_sign = ''
    if number[0] == "+" or number[0] == "-":
        sign_real = number[0]
        number = number[1::]
    if "+" in number:
        number_split = number.split("+")
    elif "-" in number:
        number_split = number.split("-")
        middle_sign = '-'
    for char in number_split[0]:
        sign_real += char
    number_split[0] = sign_real.strip()
    for char in number_split[1]:
        middle_sign += char
    number_split[1] = middle_sign.strip()
    return number_split

# Verify if imaginary or real part is valid for complex number.
def valid_number(part:str):
    for char in part:
        if not char.isdigit() and char != '.':
            return False
    return True
# Extract imaginary part from input
def divide_imaginary_part(imaginary_part_split:str):
    imaginary_part = ''
    if imaginary_part_split == 'i':
        return '1'
    for char in imaginary_part_split:
        if char != "i":
            imaginary_part += str(char)   
    if imaginary_part == '-':
        imaginary_part += '1'         
    return imaginary_part
    

# Problem Sloving

def mountain_problem_ui(complex_number_inserted:list):
    max_subb, len_max_subb = mountain_problem(complex_number_inserted)
    print(f"\nThe length of max subbaray form of a montain: {len_max_subb}")
    print(f"The subbaray form of a montain:")
    solution_subb = []
    for value in max_subb:
        imaginary_part = get_imaginary_part(value)
        if '-' in imaginary_part:
            solution_subb.append(get_real_part(value)+ '' + get_imaginary_part(value) + 'i')
        else:
            solution_subb.append(get_real_part(value)+ '+' + get_imaginary_part(value) + 'i')
    print(solution_subb)

def mountain_problem(complex_number_inserted:list):
    max_subarray = [complex_number_inserted[0]]
    len_max_subarray = 1
    current_subarray = []
    len_current_subarray = 0
    current_verif = 0 # 0 - if we need to verify if increase, 1 - if we need to verify if decrease
    for i in range(len(complex_number_inserted)):
        current_verif = 0
        len_current_subarray = 0
        current_subarray = []
        for j in range(i,len(complex_number_inserted)):
            value = complex_number_inserted[j]
            if len_current_subarray == 0:
                current_subarray.append(value)
                len_current_subarray += 1
            else:
                real_part = int(get_real_part(value))
                if current_verif == 0:
                    real_part_for_last_number = int(get_real_part(current_subarray[len_current_subarray-1]))
                    if real_part_for_last_number > real_part:
                        current_verif = 1
                    current_subarray.append(value)
                    len_current_subarray +=1
                else:
                    real_part_for_last_number = int(get_real_part(current_subarray[len_current_subarray-1]))
                    if real_part_for_last_number < real_part:
                        current_verif = 0
                        if len_max_subarray < len_current_subarray:
                            len_max_subarray = len_current_subarray
                            max_subarray = current_subarray
                        len_current_subarray = 0
                        current_subarray = []
                    current_subarray.append(value)
                    len_current_subarray +=1
            if len_max_subarray < len_current_subarray:
                len_max_subarray = len_current_subarray
                max_subarray = current_subarray
    return max_subarray, len_max_subarray

def dynamic_problem_ui(complex_number_inserted:list):
    solution_list, length = dynamic_problem(complex_number_inserted)
    print(f"The length and elements of a longest alternating subsequence, when considering each number's real part. Length: {length}")
    print_complex_list(solution_list)

def dynamic_problem(complex_number_inserted:list):
    length_of_list = len(complex_number_inserted)
    if length_of_list == 0:
        return []
    # Initializing matrix with 1,1 because on every step we can have a sublist with 1 length
    dp = [[1, 1] for _ in range(length_of_list)]

    # Make the matrix with
    # on dp[i][0] Length of the longest alternating subsequence  ending at index i and last element is greater than its previous element
    # on dp[i][1] Length of the longest alternating subsequence  ending at index i and last element is smaller than its previous element
    for i in range(length_of_list):
        real_part_of_i = int(get_real_part(complex_number_inserted[i]))
        for j in range(i):
            real_part_of_j = int(get_real_part(complex_number_inserted[j]))
            # if real part for i number is grater than real number for j number then check with dp[j][1]
            if real_part_of_i > real_part_of_j and dp[i][0] < dp[j][1] + 1:
                dp[i][0] = dp[j][1] + 1
            # if real part for i number is smaller than real number for j number then check with dp[j][0]
            elif real_part_of_i < real_part_of_j and dp[i][1] < dp[j][0] + 1:
                dp[i][1] = dp[j][0] + 1
    # We search max length of sub
    max_length = max(max(dp))
    result = []
    for i in range(length_of_list - 1, -1, -1):
        if max(dp[i]) == max_length:
            result.append(complex_number_inserted[i])
            max_length -= 1
    max_length = max(max(dp))
    return result[::-1], max_length

# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex_to_be_added(real_part:str,imaginary_part:str):
    return [real_part, imaginary_part]
def generate_list():
    return [] 

def get_imaginary_part(number:list):
    return number[1]

def get_real_part(number:list):
    return number[0]

#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
#=========================================================================
# def create_complex_to_be_added(real_part:str,imaginary_part:str):
#     return {"real": real_part, "imaginary": imaginary_part}
# def generate_list():
#     return []

# def get_imaginary_part(number:list):
#     return number['imaginary']

# def get_real_part(number:list):
#     return number['real']

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_list_ui(complex_number_inserted:list):
    number = input("Type the complex number(a+bi): ")
    try:
        add_complex_number(number,complex_number_inserted)
    except ValueError as e:
        print("ERROR:"+str(e))

def add_complex_number(number:str,complex_number_inserted):
    if number.isnumeric():
        number += ' + 0i'
    if not valid_str(number.strip()):
        raise ValueError("The inserted number is incorrect!")
    number_split = split_number(number)
    real_part = number_split[0]
    imaginary_part = divide_imaginary_part(number_split[1])
    complex_number_inserted.append(create_complex_to_be_added(real_part,imaginary_part))
    return complex_number_inserted

#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def print_menu():
    print("Menu for Complex Numbers")
    print("1. Add complex number to list(Initially list is empty).")
    print("2. [7]Show length and elements of a longest subbaray where imaginary part is in form of a mountain.")
    print("3. [12]Length and elements of a alternating subsequence.")
    print("4. Exit")
    print("5. Test for 2 list: [ '1-i', '2+6i', '4-67i', '90+3i', '80-7i', '76+i', '43-12i', '3']")
    print("6. Test for 3 list: [1, 3, 2, 4, 10, 6, 1]")
    print("7. Clear inserted list.")

def print_complex_list(complex_number_inserted:list):
    solution_subb = []
    for value in complex_number_inserted:
        imaginary_part = get_imaginary_part(value)
        if '-' in imaginary_part:
            solution_subb.append(get_real_part(value)+ '' + get_imaginary_part(value) + 'i')
        else:
            solution_subb.append(get_real_part(value)+ '+' + get_imaginary_part(value) + 'i')
    print(f"\nInserted numbers: \n{solution_subb}\n")    
    
    
def choose_option(complex_number_inserted:list):
    option = input("Choose option: ")
    if not valid(option):
        raise ValueError("You need to write a valid option!")
    option_proceed(int(option),complex_number_inserted)

def start():
    complex_number_inserted = generate_list()
    while True:
        print_complex_list(complex_number_inserted)
        print_menu()
        try:
            choose_option(complex_number_inserted)
        except ValueError as e:
            print("ERROR: "+ str(e))

if __name__ == "__main__":
    start()