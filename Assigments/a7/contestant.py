"""_summary_
  This module works with contestant
"""
  
def create_new_contestant(scores:list = [0,0,0]):
  """Creating a new contestant represented in dictionary

  Args:
      scores (list, optional): list of scores. Defaults to [0,0,0].

  Returns:
      dict: dict with scores and average 
  """
  average_score = (scores[0]+scores[1]+scores[2])*10 // 3
  return {"p1":scores[0],"p2":scores[1],"p3":scores[2],"average":average_score}

def get_value_from_contestant(contestant:dict, position:str = ''):
  """Get value from a dictionary from element position

  Args:
      contestant (dict): dictionary with information
      position (str, optional): id for element. Defaults to ''.

  Returns:
      str: information from dictionary from element position 
  """
  if position == '':
    return contestant
  return contestant[position.lower()]