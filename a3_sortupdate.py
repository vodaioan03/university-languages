from random import randint
import timeit

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
  print("4. Best Case")
  print("5. Average Case")
  print("6. Worst Case")
  print("7. Exit")
  print("============")
  option = introduce_number("Type the option: ")
  print(f"You choose option {option}")
  option_proceed(int(option),list_created, list,number_of_values)
  
  return

def print_time(function:str, values:list):
  count = 1
  for integer in range(0, len(values)):
    print(f"[{count}]The time taken is ", round(timeit.timeit(stmt=f'{function}({values[integer]})', globals=globals(), number = 1),6))
    count += 1
  return


def create_list(option:str, number_of_lists:int, length:int):
  list = []
  list_of_length = [length, 2*length, 4*length, 6*length, 8*length]
  if option == 'best':
    for i in range(0,number_of_lists):
      list.append(create_bestcase_list(list_of_length[i]))
  elif option == 'worst':
    for i in range(0,number_of_lists):
      list.append(create_worstcase_list(list_of_length[i]))
  elif option == 'average':
    for i in range(0,number_of_lists):
      list.append(create_random_list(list_of_length[i]))
  return list

def create_bestcase_list(number:int):
  list = [1]
  for integer in range(1,number):
    list.append(list[integer - 1] + 1)
  return list

def bestcase_generation():
  number_of_values = introduce_number("Number of values in array: ")
  lists = create_list('best', 5, number_of_values)
  print("Bubble Sort Complexity for Best Case")
  #print("The time taken is ",timeit.timeit(stmt=f'bubble_sort({list1})', globals=globals(), number = 1))
  print_time('bubble_sort', lists)
  lists = create_list('best', 5, number_of_values)
  print("Strand Sort Complexity for Best Case")
  print_time('strand_sort', lists)
  
# This function create an random list
def create_random_list(length:int):
  list = []
  for i in range(0,length):
    list.append(randint(0, 10000))
  return list

def averagecase_generation():
  number_of_values = introduce_number("Number of values in array: ")
  #lists = create_list('average', 5, number_of_values)
  print("Bubble Sort Complexity for Average Case")
 # print_time('bubble_sort', lists)
  lists = create_list('average', 5, number_of_values)
  print("Strand Sort Complexity for Average Case")
  print_time('strand_sort', lists)

def create_worstcase_list(number:int):
  list = [number]
  for integer in range(1,number):
    list.append(list[integer - 1] - 1)
  return list

def worstcase_generation():
  number_of_values = introduce_number("Number of values in array: ")
  lists = create_list('worst', 5, number_of_values)
  print("Bubble Sort Complexity for Worst Case")
  print_time('bubble_sort', lists)
  lists = create_list('worst', 5, number_of_values)
  print("Strand Sort Complexity for Worst Case")
  print_time('strand_sort', lists)

# This function proceed the option and call what function he need
def option_proceed(option:int,list_created:int,list:list,number_of_values:int):
  if option == 7:
    print("Good Luck!")
    return
  elif option == 1:
    number_of_values = introduce_number("Number of values in array: ")
    list = create_random_list(number_of_values)
    list_created = 1
  elif list_created == 1 and option == 2 or option == 3:
    number_of_steps = introduce_number(f"[{option}] Number of steps: ")
    if option == 2:
      bubble_sort_step(list, number_of_steps)
    elif option == 3:
      strand_sort_step(list, number_of_steps)
    list = create_random_list(number_of_values)
    print(f"We generated an new list for you!")
  elif option == 4:
    bestcase_generation()
  elif option == 5:
    averagecase_generation()
  elif option == 6:
    worstcase_generation()
  else:
    print("You need to generate the array. Choose option 1 first.")
  show_menu(list_created,list,number_of_values)
  return

# Bubble Sort
def bubble_sort(arr:list):
  for k in range(0, len(arr)):
    swapped = False
    for j in range(0,len(arr)-k-1):
      if arr[j] > arr[j+1]:
        arr[j], arr[j+1], swapped = arr[j+1], arr[j], True
    if swapped == False:
      return arr

# Strand Sort
def strand_sort(array:list):
  sublist, solution_list = [], []
  while len(array) > 0:
    sublist = []
    sublist.append(array[0])
    for i in range(1,len(array)):
      if array[i] > sublist[len(sublist)-1]:
        sublist.append(array[i])
    for i in range(0,len(sublist)):
      array.remove(sublist[i])
    solution_list = merge_arr(sublist,solution_list)
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

# Bubble Sort
def bubble_sort_step(arr:list, count:int):
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
def strand_sort_step(array:list,  step:int):
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

show_menu(0,[],0)