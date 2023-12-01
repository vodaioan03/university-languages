#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
from colorama import *
from list_of_contestant import *
from contestant import *
from copy import *

def show_menu_for_help():
  print("\t Avalible commands")
  print("\n(A) Add the result of a new participant")
  print("\tadd <P1 score> <P2 score> <P3 score> |e.g add a new participant with scores `3`,`8` and `10` (scores for `P1`, `P2`, `P3` respectively) ")
  print("\tinsert <P1 score> <P2 score> <P3 score> at <position> | e.g insert 10 10 9 at 5` - insert scores `10`, `10` and `9` at position `5` in the list (positions numbered from `0")
  print("\n(B) Modify scores")
  print("\tremove <position> |e.g set the scores of the participant at position `1` to `0")
  print("\tremove <start position> to <end position> |e.g remove 1 to 3` - set the scores of participants at positions `1`, `2` and `3` to `0`")
  print("\treplace <old score> <P1 | P2 | P3> with <new score> |e.g replace 4 P2 with 5` - replace the score obtained by participant `4` at `P2` with `5")
  print("\n(C)  Display participants whose score has different properties.")
  print("\tlist - display all numbers | e.g")
  print("\tlist sorted | display participants sorted in decreasing order of average score")
  print("\tlist modulo [ < | = | > ] <score> |e.g list < 4` - display participants with an average score")
  print("\n(D) Establish the podium")
  print("\ttop <number> |e.g top 3 - display the 3 participants having the highest average score, in descending order of average score")
  print("\ttop <number> <P1 | P2 | P3> |e.g top 4 P3` - display the 4 participants who obtained the highest score for P3, sorted descending by that score")
  print("\tremove [ < | = | > ] <score> |e.g remove > 89` - set the scores of participants having an average score `>89` to `0`")
  print("\n(E) Undo")
  print("\tundo | the last operation that modified program data is reversed. The user can undo all operations performed since program start by repeatedly calling this function.\n")
  print(Fore.GREEN+"For each command you need to write like in menu E.g: insert 10 10 9 at 2"+Style.RESET_ALL)

def input_command(history_list:list,list_of_contestants:list):
  command_inserted = input(">>> ").strip()
  command_splited = command_inserted.split()
  try:
    command_proceed(command_splited,list_of_contestants,history_list)
  except ValueError as e:
    print(Fore.RED + str(e) + Style.RESET_ALL)
 
def to_be_added(command_inserted:str):
  if command_inserted == "undo" or command_inserted == "help" or command_inserted == "exit" or command_inserted == "list" or command_inserted == "top":
    return False
  return True   

def transform_string_to_lower(string:list):
  for i in range(len(string)):
    string[i] = string[i].lower()

def command_proceed(command_inserted:list, list_of_contestants:list,history_list:list):
  command_dict = {"add":add, "insert":insert, "remove":remove, "replace":replace, "list":list_comm, "top":top, "undo":undo, "exit":exit, "help":help}
  transform_string_to_lower(command_inserted)
  if command_inserted[0] in command_dict:
    command_dict[command_inserted[0]](command_inserted,list_of_contestants,history_list)
    if to_be_added(command_inserted[0]):
      add_to_history(history_list, list_of_contestants)
  else:
    raise ValueError("Command wrong. Type help for commands.")
    
      
# ALL COMMANDS FUNCTION

def add(string_remaining:list,list_of_contestants:list,history:list):
  if not valid_add(string_remaining):
    raise ValueError("The string inserted isn't correct") 
  score_values = [int(string_remaining[1]),int(string_remaining[2]),int(string_remaining[3])]
  add_new_contestant_in_list(list_of_contestants, create_new_contestant(score_values))
  
def valid_add(string_rem:list):
  if len(string_rem) != 4:
    return False
  string_rem = string_rem[1:]
  for each in string_rem:
    if not str(each).isdigit() or str(each).isdigit() and not 0 <= int(each) <= 10:
      return False
  return True
 
 
def insert(string_remaining:list,list_of_contestants:list,history:list):
  if len(list_of_contestants) == 0:
    raise ValueError("You can't use that command because list is empty!")
  if not valid_insert(string_remaining):
    raise ValueError("The string inserted isn't correct") 
  try:
    insert_in_list(list_of_contestants, string_remaining[1:])
  except ValueError as e:
    raise e

def valid_insert(string_rem:list):
  if len(string_rem) != 6:
    return False
  string_rem = string_rem[1:]
  digits = 0
  position_at = -1
  for i in range(len(string_rem)):
    if str(string_rem[i]).isdigit():
      digits += 1
    if str(string_rem[i]) != "at" and not str(string_rem[i]).isdigit():
      return False
    if str(string_rem[i]) == "at":
      position_at = i
  if digits != 4 or position_at != 3:
    return False
  return True


def remove(string_remaining:list,list_of_contestants:list,history:list):
  if len(list_of_contestants) == 0:
    raise ValueError("You can't use that command because list is empty!")
  if not valid_remove(string_remaining,list_of_contestants):
    raise ValueError("The string inserted isn't correct, or position is too big.") 
  try:
    if string_remaining[1].isnumeric():
      tuple_of_positions = extract_from_remove_command(string_remaining[1:])
      remove_from_list(list_of_contestants,tuple_of_positions)
    else:
      remove_from_list_with_sign(list_of_contestants,string_remaining[1:])
  except ValueError as e:
    raise e

def valid_remove(string_rem:list,list_of_contestants:list):
  if len(string_rem) < 2 and len(string_rem) > 4:
    return False
  string_rem = string_rem[1:]
  if len(string_rem) == 1:
    if not string_rem[0].isdigit():
      return False
  elif len(string_rem) == 2:
    valid_signs = '<=>'
    if not string_rem[1].isnumeric() or not string_rem[0] in valid_signs or len(string_rem[0]) != 1:
      return False
    if int(string_rem[0]) > len(list_of_contestants):
      return False
  elif len(string_rem) == 3:
    if not string_rem[0].isdigit() or not string_rem[2].isdigit() or string_rem[1].lower() != "to":
      return False
    if int(string_rem[0]) >= len(list_of_contestants) or int(string_rem[2]) >= len(list_of_contestants):
      return False
  else:
    return False
  
  return True

def replace(string_remaining:list,list_of_contestants:list,history:list):
  if len(list_of_contestants) == 0:
    raise ValueError("You can't use that command because list is empty!")
  if not replace_valid(string_remaining,list_of_contestants):
    raise ValueError("The string inserted isn't correct") 
  old_score = int(string_remaining[1])
  position = string_remaining[2].lower()
  new_score = int(string_remaining[4])
  replace_score(list_of_contestants, old_score, position, new_score)

def replace_valid(string_remaining:list,list_of_contestants:list):
  if len(string_remaining) != 5:
    return False
  if not string_remaining[1].isnumeric():
    return False
  if string_remaining[1].isnumeric() and int(string_remaining[1]) > len(list_of_contestants):
    return False
  accepted_string = ["p1","p2","p3"]
  if not string_remaining[2].lower() in accepted_string:
    return False
  if string_remaining[3].lower() != "with":
    return False
  if not string_remaining[4].isnumeric():
    return False
  if string_remaining[4].isnumeric() and (int(string_remaining[4]) > 10 or int(string_remaining[4]) < 0):
    return False
  return True

#List comm
def list_comm(string_remaining:list,list_of_contestants:list,history:list):
  if len(list_of_contestants) == 0:
    raise ValueError("You can't use that command because list is empty!")
  if len(string_remaining) == 1:
    new_sorted_list = list_of_contestants
    print_contestant_list(new_sorted_list)  
  elif len(string_remaining) == 2:
    if string_remaining[1].lower() == 'sorted':
      new_sorted_list = sort_contestant_list(list_of_contestants)
      print_contestant_list(new_sorted_list)  
    else:
      raise ValueError("Invalid parameters for list. Type help for commands.")
  elif len(string_remaining) == 3:
    if not list_valid(string_remaining):
      raise ValueError("Invalid parameters for list. Type help for commands.")
    new_sorted_list,list_with_id = show_list_for_sign(list_of_contestants,string_remaining[1],int(string_remaining[2]))
    print_contestant_list_with_id(new_sorted_list,list_with_id)

def list_valid(string:list):
  signs = '<=>'
  if not string[1] in signs or not string[2].isnumeric() or len(string[1]) != 1:
    return False
  return True  

def top(string_remaining:list,list_of_contestants:list,history:list):
  if len(list_of_contestants) == 0:
    raise ValueError("You can't use that command because list is empty!")
  if not is_valid_top(string_remaining):
    raise ValueError("The string inserted isn't correct") 
  number = -1
  sort_by = 'average'
  if len(string_remaining) == 2:
    if int(string_remaining[1]) > len(list_of_contestants):
      raise ValueError("Number inserted is bigger than length.")
    number = int(string_remaining[1])
  elif len(string_remaining) == 3:
    number = int(string_remaining[1])
    sort_by = string_remaining[2].lower()
  new_list, id_list = top_list(list_of_contestants,sort_by,number)
  print_contestant_list_with_id(new_list,id_list)

def is_valid_top(string_remaining:list):
  if len(string_remaining) < 2 or len(string_remaining) > 3 or not string_remaining[1].isnumeric():
    return False
  if len(string_remaining) == 2:
    return True
  if len(string_remaining) == 3:
    accept_string = ["p1", "p2", "p3"]
    if string_remaining[2].lower() in accept_string:
      return True
  return False

def undo(string_remaining:list,list_of_contestant:list,history:list):
  if len(string_remaining) != 1:
    raise ValueError("Wrong command! Type help for commands")
  if len(history) == 1:
    raise ValueError("No more commands remaining.")
  undo_value(history)
  
  
def help(string_remaining:list,list_of_contestants:list,history:list):
  show_menu_for_help()
  
def exit(string_remaining:list,list_of_contestants:list,history:list):
  quit()
  
# FUNCTIONS FOR PRINT CONTESTANTS
def print_contestant_list(contestant_list:list):
  print("\nHere is the list of contestances \n")
  for i in range(len(contestant_list)):
    print_contestant(contestant_list[i],i)
    
    
def print_contestant_list_with_id(contestant_list:list, id_list:list):
  print("\nHere is the list of contestances with id \n")
  for i in range(len(contestant_list)):
    print_contestant(contestant_list[i],id_list[i])

def print_contestant(contestant:dict, id:int):
  string = f'ID:{id} Scores:'
  for each in contestant:
    string += f"{each} : {contestant[each]} "
  print(string)