import copy
from src.domain.book import *

class RepositoryError(Exception):
    """_summary_

    Args:
        Exception (_type_): _description_

    Returns:
        _type_: _description_
    """
    @property
    def message(self) -> str:
      """_summary_

      Returns:
          str: _description_
      """
      return self.__message

    def __init__(self, message: str = "Not specified Reository Error"):
      """_summary_

      Args:
          message (str, optional): _description_. Defaults to "Not specified Reository Error".
      """
      self.__message = message

    def __str__(self) -> str:
      """_summary_

      Returns:
          str: _description_
      """
      return self.__message

class Repository:
  
  def __init__(self) -> None:
    """Define data with a null list.
    """
    self._data = [[]]
  
  def add_book(self,listof):
    """Function for add book with id of Class

    Args:
        listof (id): id of class to be added in list

    Returns:
        list: list with all data
    """
    new_list = copy.deepcopy(self._data[-1])
    new_list.append(listof)
    self._data.append(new_list)
    return self._data
    
  def get_books(self):
    """Function for get actual book list

    Returns:
        list: actual list with books
    """
    return self._data[-1]
    
  def undo_list(self):
    """Function for undo last operation

    Returns:
        list: list with all remainings books
    """
    self._data.pop()
    return self._data
    
  def modify_list(self,new_list):
    """Function for adding new list modified

    Args:
        new_list (list): list with all books modified

    Returns:
        list: actual list with all history
    """
    self._data.append(new_list)
    return self._data
  
  def length_of(self):
    """Length of actual list with history

    Returns:
        int: length of list
    """
    return len(self._data)