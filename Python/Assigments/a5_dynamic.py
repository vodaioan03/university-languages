#7. Length and elements of a longest subarray of numbers where their	real part is in the form of a mountain (first the values increase, then they decrease). (e.g. `1-i, 2+6i, 4-67i, 90+3i, 80-7i, 76+i, 43-12i, 3`)

#12. The length and elements of a longest alternating subsequence, when considering each number's real part (e.g., given sequence [1, 3, 2, 4, 10, 6, 1], [1, 3, 2, 10] is an alternating subsequence, because 1 < 3 > 2 < 10)

#
# Write the implementation for A5 in this file
#
import random
import colorama
from colorama import Fore, Style

# Function for verification
# Verification for option!
def generate_list():
    """
    Generate an empty list for beginning
    Returns:
        Return an empty list
        _type_: list
    """
    return [] 

def generate_random_number(complex_number_inserted:list):
    """
    We generate a random 10 complex numbers and add to list
    Args:
        complex_number_inserted (list): list of number inserted
    """
    for _ in range(0,10):
        add_complex_number(f"{random.randint(1,120)} + {random.randint(0,100)}i",complex_number_inserted)
    

def valid(option_chosen:str):
    """
    We verify if option is a valid.
    Args:
        option_chosen (str): number of choosen option

    Returns:
        _type_: True if option is valid or False if option isn't valid
    """
    if option_chosen.isnumeric() and int(option_chosen) in [1,2,3,4,5,6,7,8,9]:
        return True
    return False
def clear_list(complex_number_inserted:list):
    """
    Here you make the list empty.
    Args:
        complex_number_inserted (list): list of complex number represented
    """
    complex_number_inserted.clear()


def test_for_7(complex_number_inserted:list):
    """
    Here you have a predeterminated list of numbers. 
    Args:
        complex_number_inserted (list): list of complex numbers
    """
    values = [ '1-i', '2+6i', '4-67i', '90+3i', '80-7i', '76+i', '43-12i', '3']
    for value in values:
        add_complex_number(str(value),complex_number_inserted)
def test_for_12(complex_number_inserted:list):
    """
    Here you have a predeterminated list of numbers. 
    Args:
        complex_number_inserted (list): list of complex numbers
    """
    values = [1, 3, 2, 4, 10, 6, 1]
    for value in values:
        add_complex_number(str(value),complex_number_inserted)
        
# Proceed option and call what function he need
def option_proceed(option_chosen:int,complex_number_inserted):
    """
    If option is valid we proceed the option and call specific function for each option
    Args:
        option_chosen (int): number of choosen option
        complex_number_inserted (_type_): list of complex numbers

    Raises:
        ValueError:  raise a error if list is empty
        ValueError:  raise a error if list is empty
        ValueError:  raise a error if list is empty
    """
    if option_chosen == 1:
        create_list_ui(complex_number_inserted)
    elif option_chosen == 2:
        print_complex_list(complex_number_inserted, "GREEN")
    elif option_chosen == 3:
        if len(complex_number_inserted) == 0:
            raise ValueError("Inserted List is empty. You need to insert complex numbers.")
        mountain_problem_ui(complex_number_inserted)
    elif option_chosen == 4:
        if len(complex_number_inserted) == 0:
            raise ValueError("Inserted List is empty. You need to insert complex numbers.")
        dynamic_problem_ui(complex_number_inserted)
    elif option_chosen == 5:
        quit()
    elif option_chosen == 6:
        test_for_7(complex_number_inserted)
    elif option_chosen == 7:
        test_for_12(complex_number_inserted)
    elif option_chosen == 8:
        generate_random_number(complex_number_inserted)
    elif option_chosen == 9:
        if len(complex_number_inserted) == 0:
            raise ValueError("Inserted List is empty. You need to insert complex numbers.")
        clear_list(complex_number_inserted)

# Verify if the input is a complex number
def valid_str(number:str):
    """
    Check if string is a valid complex number
    Args:
        number (str): input string

    Returns:
        _type_: True if is a complex number or false if isn't
    """
    if len(number) == 0:
        return False
    number_split = split_number(number)
    if len(number_split) == 1:
        return True
    if len(number_split) != 2:
        return False
    if number_split[1][0] == "-":
        number_split[1] = number_split[1][1::]
    if number_split[0][0] == "+" or number_split[0][0] == "-":
        number_split[0] = number_split[0][1::]
    index_i_on_imaginary_part = number_split[1].find("i")
    if index_i_on_imaginary_part != len(number_split[1])-1:
        return False
    imaginary_part = divide_imaginary_part(number_split[1])
    if  not valid_number(number_split[0]) or not valid_number(imaginary_part):
        return False
    return True

# Split number in real part and imaginary part
def split_number(number:str):
    """
    Split number in real part and imaginary part
    Args:
        number (str): string with complex number

    Returns:
        _type_: list of real part in position 0 and imaginary part in position 1
    """
    if number.isnumeric():
        return [number, 0]
    sign_real = ''
    middle_sign = ''
    number_split = ''
    if number[0] == "+" or number[0] == "-":
        sign_real = number[0]
        number = number[1::]
    if "+" in number:
        number_split = number.split("+")
    elif "-" in number:
        number_split = number.split("-")
        middle_sign = '-'
    if number_split == '':
        return [sign_real + number, '0i']
    for char in number_split[0]:
        sign_real += char
    number_split[0] = sign_real.strip()
    for char in number_split[1]:
        middle_sign += char
    number_split[1] = middle_sign.strip()
    return number_split

# Verify if imaginary or real part is valid for complex number.
def valid_number(part:str):
    """
    Check if part of number is ok
    Args:
        part (str): part of number

    Returns:
        _type_: True if have only digits and ".", false if he has another symbol
    """
    for char in part:
        if not char.isdigit() and char != '.':
            return False
    return True
# Extract imaginary part from input
def divide_imaginary_part(imaginary_part_split:str):
    """
    Return imaginary part of number
    Args:
        imaginary_part_split (str): string with imaginart part

    Returns:
        _type_: imaginary part
    """
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
    """
    UI Function for solving problem number 7
    Args:
        complex_number_inserted (list): list of number
    """
    max_subb, len_max_subb = mountain_problem(complex_number_inserted)
    print(Fore.GREEN +f"\nThe length of max subbaray form of a montain: {len_max_subb}" + Style.RESET_ALL)
    print(Fore.GREEN + f"The subbaray form of a montain:"+ Style.RESET_ALL)
    print_complex_list(max_subb, 'GREEN')

def mountain_problem(complex_number_inserted:list):
    """
    Logical Function for solving problem number 7
    
    Go in list at each element and verify if every elemnts from position i makes the longest subarray 
    Keep the longest subbaray and length and return at the end
    Complexity: O(n^2)
    Args:
        complex_number_inserted (list): list of number
    """
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
    """
    UI Function for solving problem number 12
    Args:
        complex_number_inserted (list): list of number
    """
    solution_list, length = dynamic_problem(complex_number_inserted)
    print(Fore.GREEN + f"The length and elements of a longest alternating subsequence, when considering each number's real part. Length: {length}" + Style.RESET_ALL)
    print_complex_list(solution_list, 'GREEN')

def dynamic_problem(complex_number_inserted:list):
    """
    Logical Function for solving problem number 12
    - make a matrix with 2 columns and length of complex number list rows and make 1 at the beggining
        at  column 0 we put Legth of the longest alternating subsequence  ending at index i and last element is greater than its previous element
        at column 1 we put Length of the longest alternating subsequence  ending at index i and last element is smaller than its previous element
    - take maximum length and go from bottom to top and search all numbers who makes the length
    - return the length and list
    Complexity: O(n^2)
    Args:
        complex_number_inserted (list): list of number

    Returns:
        result: list of complex numbers 
        length: integer, length of answer
    """
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
    return result, max_length

# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex_to_be_added(real_part:str,imaginary_part:str):
    """
    Add real part and imaginary part in a tuple
    Args:
        real_part (str): real part from complex number
        imaginary_part (str): imaginary part from complex number

    Returns:
        _type_: tuple of number
    """
    return (real_part, imaginary_part)

def get_imaginary_part(number:list):
    """
    Take imaginary part from list
    Args:
        number (list): list for complex number

    Returns:
        _type_: imaginary part
    """
    return number[1]

def get_real_part(number:list):
    """
    Take real part from list
    Args:
        number (list): list for complex number

    Returns:
        _type_: real part
    """
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
#     """
#     Add real part and imaginary part in a dict
#     Args:
#         real_part (str): real part from complex number
#         imaginary_part (str): imaginary part from complex number

#     Returns:
#         _type_: dict of number
#     """
#     return {"real": real_part, "imaginary": imaginary_part}

# def get_imaginary_part(number:list):
#     """
#     Take imaginary part from dict
#     Args:
#         number (list): list for complex number

#     Returns:
#         _type_: imaginary part
#     """
#     return number['imaginary']

# def get_real_part(number:list):
#     """
#     Take real part from dict
#     Args:
#         number (list): list for complex number

#     Returns:
#         _type_: real part
#     """
#     return number['real']

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_list_ui(complex_number_inserted:list):
    """
    Ui Insert and add number in list
    Args:
        complex_number_inserted (list): list of numbers
    """
    number = input("Type the complex number(a+bi): ")
    try:
        add_complex_number(number,complex_number_inserted)
    except ValueError as e:
        print(Fore.RED + "ERROR: " + str(e) + Style.RESET_ALL)

def add_complex_number(number:str,complex_number_inserted):
    """   
    Logical function for adding a number in list
    Args:
        number (str): complex number
        complex_number_inserted (_type_): list of complex numbers

    Raises:
        ValueError: for incorrent number

    Returns:
        _type_: list of numbers
    """
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
    """
    Function for printing menu with options
    """
    print("Menu for Complex Numbers")
    print("1. Add complex number to list(Initially list is empty).")
    print("2. Display The List")
    print("3. [7]Show length and elements of a longest subbaray where imaginary part is in form of a mountain.")
    print("4. [12]Length and elements of a alternating subsequence.")
    print("5. Exit")
    print("6. Test for 2 list: [ '1-i', '2+6i', '4-67i', '90+3i', '80-7i', '76+i', '43-12i', '3']")
    print("7. Test for 3 list: [1, 3, 2, 4, 10, 6, 1]")
    print("8. Generate 10 random numbers:")
    print("9. Clear inserted list.")

def print_complex_list(complex_number_inserted:list, color:str):
    """
    Printing list of number as a+bi
    Args:
        complex_number_inserted (list): list of number
        color (str): color for console
    """
    solution_subb = []
    for value in complex_number_inserted:
        imaginary_part = get_imaginary_part(value)
        if '-' in imaginary_part:
            solution_subb.append(get_real_part(value)+ '' + get_imaginary_part(value) + 'i')
        else:
            solution_subb.append(get_real_part(value)+ '+' + get_imaginary_part(value) + 'i')
    if color == 'GREEN':
        print(Fore.GREEN + f"\nInserted numbers: \n{solution_subb}\n" + Style.RESET_ALL)    
    elif color == 'CYAN':
        print(Fore.CYAN + f"\nInserted numbers: \n{solution_subb}\n" + Style.RESET_ALL)    
    
    
def choose_option(complex_number_inserted:list):
    """
    Here you choose your option and check if is ok
    Args:
        complex_number_inserted (list): list of numbers

    Raises:
        ValueError: if option isn't valid
    """
    option = input("Choose option: ")
    if not valid(option):
        raise ValueError("You need to write a valid option!")
    try:
        option_proceed(int(option),complex_number_inserted)
    except ValueError as e:
        print(Fore.RED + "ERROR: " + str(e) + Style.RESET_ALL)

def start():
    """
    Function for starting program
    """
    complex_number_inserted = generate_list()
    while True:
        print_complex_list(complex_number_inserted, 'CYAN')
        print_menu()
        try:
            choose_option(complex_number_inserted)
        except ValueError as e:
            print(Fore.RED + "ERROR: " + str(e) + Style.RESET_ALL)

if __name__ == "__main__":
    start()