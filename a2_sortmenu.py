"""
- Before starting each sort, the program will ask for the value of parameter `step`. During sorting, the program will display the partially sorted list on the console each time it makes `step` operations or passes, depending on the algorithm (e.g., if `step=2`, display the partially sorted list after each 2 element swaps in bubble sort, after each 2 element insertions in insert sort, after every 2nd generation of a permutation in permutation sort etc.).
"""

from random import randint

# This function validate input only if is an integer number!
def valid_option(text:str):
  if text.strip().isnumeric():
    return int(text)
  else:
    print(f"Invalid option {text}. You need to write an integer number")
    return 0

# I use this function for organize the code
def introduce_number(input_message:str):
  input_number = input(input_message)
  while not valid_option(input_number):
    input_number = input(input_message)
  return int(input_number)
  
# Function for menu
def show_menu(list_created:int, list:list,number_of_values:int):
  print("=== Menu ===")
  print("1. Create a random list")
  print("2. Bubble Sort")
  print("3. Strand Sort")
  print("4. Exit")
  print("============")
  option = introduce_number("Type the option: ")
  print(f"You choose option {option}")
  option_proceed(int(option),list_created, list,number_of_values)
  return

# This function proceed the option and call what function he need
def option_proceed(option:int,list_created:int,list:list,number_of_values:int):
  if option == 4:
    print("Good Luck!")
    return
  elif option == 1:
    number_of_values = introduce_number("Number of values in array: ")
    list = create_random_list(number_of_values)
    list_created = 1
  elif list_created == 1:
    number_of_steps = introduce_number(f"[{option}] Number of steps: ")
    if option == 2:
      bubble_sort(list, number_of_steps)
    elif option == 3:
      strand_sort(list, number_of_steps)
    list = create_random_list(number_of_values)
    print(f"We generated an new list for you!")
  else:
    print("You need to generate the array. Choose option 1 first.")
  show_menu(list_created,list,number_of_values)
  return

# This function create an random list
def create_random_list(length:int):
  list = []
  for i in range(0,length):
    list.append(randint(0, 5000))
  return list

# Bubble Sort
def bubble_sort(arr:list, count:int):
  print(f"Initial array: {arr}")
  step_count = 0
  for k in range(0, len(arr)):
    swapped = False
    for j in range(0,len(arr)-k-1):
      step_count += 1
      if arr[j] > arr[j+1]:
        arr[j], arr[j+1], swapped = arr[j+1], arr[j], True
      if step_count % count == 0:
        print(f"{step_count}. {arr}")
    if swapped == False:
      print(f"The array has been sorted! New array is: {arr}")
      return arr

# Strand Sort
def strand_sort(array:list,  step:int):
  print(f"Initial array: {array}")
  sublist, solution_list = [], []
  step_count = 0
  while len(array) > 0:
    sublist = []
    sublist.append(array[0])
    for i in range(1,len(array)):
      if array[i] > sublist[len(sublist)-1]:
        sublist.append(array[i])
        step_count += 1
        if step_count % step == 0:
          print(f"{step_count}. Solution: {solution_list}")
          print(f"{step_count}. Sublist: {sublist}")
    for i in range(0,len(sublist)):
      array.remove(sublist[i])
    solution_list = merge_arr(sublist,solution_list)
  print(f"The array has been sorted! New array is: {solution_list}")
  return solution_list
  
# Merge Function for Strand Sort
def merge_arr(arr1:list, arr2:list):
  counter_arr1 = 0
  counter_arr2 = 0
  solution_list = []
  while counter_arr1 < len(arr1) and counter_arr2 < len(arr2):
    if arr1[counter_arr1] < arr2[counter_arr2]:
      solution_list.append(arr1[counter_arr1])
      counter_arr1 += 1
    elif arr2[counter_arr2] < arr1[counter_arr1]:
      solution_list.append(arr2[counter_arr2])
      counter_arr2 += 1
    else:
      solution_list.append(arr2[counter_arr2])
      solution_list.append(arr1[counter_arr1])
      counter_arr1 += 1
      counter_arr2 += 1
  while counter_arr1 < len(arr1):
    solution_list.append(arr1[counter_arr1])
    counter_arr1 += 1
  while counter_arr2 < len(arr2):
    solution_list.append(arr2[counter_arr2])
    counter_arr2 += 1
  return solution_list

show_menu(0,[],0)