#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#

from contestant import *
from copy import *
"""_summary_
  This module works with lists of contestant
"""
# def generate_new_list_of_contestants():
#   return []

def generate_history_command():
  """Generate a empty list with lists

  Returns:
      list: list with list
  """
  return [[]]

def add_to_history(history:list,current_list:list):
  """Adding to list history the list transmited

  Args:
      history (list): list with history
      current_list (list): list to be added
  """
  history.append(copy(current_list))

def add_new_contestant_in_list(list_of_contestants:list,scores:dict):
  """Add contestant in list

  Args:
      list_of_contestants (list): list with contestants, where need to be inserted
      scores (dict): list for insert
  """
  list_of_contestants.append(scores)
  
def undo_value(history:list):
  """Remove last element from list

  Args:
      history (list): list with elements
  """
  history.pop()

def insert_in_list(list_of_contestants:list, values:list):
  """_summary_

  Args:
      list_of_contestants (list): _description_
      values (list): _description_

  Raises:
      ValueError: _description_
      ValueError: _description_
  """
  if int(values[4]) >= len(list_of_contestants):
    raise ValueError("Final position is bigger than the length of list.")
  position = int(values.pop())
  values.pop()
  for i in range(len(values)):
    values[i] = int(values[i])
    if values[i] > 10 or values[i] < 0:
      raise ValueError("Scores needs to be between 0 and 10.")
  list_of_contestants[position] = create_new_contestant(values)
  
def remove_from_list(list_of_contestants:list, position:tuple):
  """_summary_

  Args:
      list_of_contestants (list): _description_
      position (tuple): _description_
  """
  first_position = position[0]
  while first_position <= position[1]:
    list_of_contestants[first_position] = create_new_contestant()
    first_position += 1
  
def remove_from_list_with_sign(list_of_contestants:list, command:list):
  """_summary_

  Args:
      list_of_contestants (list): _description_
      command (list): _description_
  """
  score = int(command[1])
  remove_from_list_with_score(list_of_contestants, score, command[0])
  
def remove_from_list_with_score(list_of_contestants:list, score:int, sign:str): 
  """_summary_

  Args:
      list_of_contestants (list): _description_
      score (int): _description_
      sign (str): _description_
  """
  if sign == '=':
    for i in range(len(list_of_contestants)):
      if get_value_from_contestant(list_of_contestants[i], "average") == score:
        list_of_contestants[i] = create_new_contestant()
  elif sign == '<':
    for i in range(len(list_of_contestants)):
      if get_value_from_contestant(list_of_contestants[i], "average") < score:
        list_of_contestants[i] = create_new_contestant()
  elif sign == '>':
    for i in range(len(list_of_contestants)):
      if get_value_from_contestant(list_of_contestants[i], "average") > score:
        list_of_contestants[i] = create_new_contestant()
    
def replace_score(list_of_contestants:list,old_score:int, position:str, new_score:int):
  """_summary_

  Args:
      list_of_contestants (list): _description_
      old_score (int): _description_
      position (str): _description_
      new_score (int): _description_
  """
  new_contestants = create_new_contestant(get_value_from_contestant(list_of_contestants[old_score], "p1"),get_value_from_contestant(list_of_contestants[old_score], "p2"),get_value_from_contestant(list_of_contestants[old_score], "p3"))
  new_contestants[position] = new_score
  list_of_contestants[old_score] = new_contestants    
    
#LOGICAL FUNCTIONS FOR COMMANDS

def extract_from_remove_command(command:list):
  """_summary_

  Args:
      command (list): _description_

  Returns:
      _type_: _description_
  """
  positions = ()
  if command[0].isnumeric():
    if len(command) == 1:
      positions = (int(command[0]), int(command[0]))
    else:
      positions = (int(command[0]), int(command[2]))
  else:
    positions = (0,0)
  return positions

def sort_contestant_list(list_of_contestants:list):
  """_summary_

  Args:
      list_of_contestants (list): _description_

  Returns:
      _type_: _description_
  """
  sorted_list = sorted(list_of_contestants, key=lambda i: i['average'])
  return sorted_list
  
def show_list_for_sign(list_of_contestants:list,sign:str,score:int):  
  """Processing list and sorting with conditions given

  Args:
      list_of_contestants (list): list with contestants
      sign (str): sign for comparation
      score (int): score for comparation

  Returns:
      list: list modified and list with id
  """
  new_list = []
  list_with_id = []
  if sign == '=':
    for i in range(len(list_of_contestants)):
      if get_value_from_contestant(list_of_contestants[i], "average") == score:
        new_list.append(list_of_contestants[i])
        list_with_id.append(i)
  elif sign == '<':
    for i in range(len(list_of_contestants)):
      if get_value_from_contestant(list_of_contestants[i], "average") < score:
        new_list.append(list_of_contestants[i])
        list_with_id.append(i)
  elif sign == '>':
    for i in range(len(list_of_contestants)):
      if get_value_from_contestant(list_of_contestants[i], "average") > score:
        new_list.append(list_of_contestants[i])
        list_with_id.append(i)
  return new_list,list_with_id

def sort_list_by(list_of_contestants_original:list,sort_by:str):
  """Sort list by a element id given

  Args:
      list_of_contestants_original (list): list with contestants
      sort_by (str): elemnt for dict

  Returns:
      list: new list and id list
  """
  sorted = False
  sort_by = sort_by.lower()
  id_list = []
  list_of_contestants = list_of_contestants_original.copy()
  for i in range(len(list_of_contestants)):
    sorted = True
    id_list.append(i)
    for j in range(1,len(list_of_contestants)):
      if get_value_from_contestant(list_of_contestants[j],sort_by) > get_value_from_contestant(list_of_contestants[j-1],sort_by):
        aux = list_of_contestants[j-1]
        list_of_contestants[j-1] = list_of_contestants[j]
        list_of_contestants[j] = aux
        sorted = False
        id_list[-1] = j-1
    if sorted == True:
      i = len(list_of_contestants)
  return list_of_contestants,id_list

def top_list(list_of_contestants:list,sort_by:str,number:int):
  """Processing for top list showing

  Args:
      list_of_contestants (list): list with contestants
      sort_by (str): element for sort
      number (int): number for length of list

  Returns:
      list: new list and id list with number elements
  """
  new_sort, id_list = sort_list_by(list_of_contestants,sort_by)
  return new_sort[:number], id_list[:number]