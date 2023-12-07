import os
import copy
import json

#from src.repository.repository import RepositoryError, Repository
from src.repository.memoryrep import RepositoryError, Memory
from src.domain.book import *
class JSON(Memory):
  
  def __init__(self,file_name) -> None:
    """JSON init for Repository

    Args:
        file_name (_type_): file name for saving
    """
    self.__file_name = file_name
    super().__init__()
    self.__load_file()
  
  def add_book(self,listof):
    """Adding book and saving

    Args:
        list (_type_): id class to be saved
    """
    super().add_book(listof)
    self.__save_file()
    
  def undo_list(self):
    """Undo list and saving in file
    """
    super().undo_list()
    self.__save_file()
    
  def modify_list(self,new_list):
    """Modify list and savinf

    Args:
        new_list (list): new list for modify
    """
    super().modify_list(new_list)
    self.__save_file()
    
  def __save_file(self):
    """Save file in JSON folder
    """
    json_data = []
    for each in self._data[-1]:
       json_data.append(each.serialize())
    with open(self.__file_name, "w") as outfile:
      json.dump(json_data,outfile)
    
       
  def __load_file(self):
    """Load file in JSON foler

    Raises:
        RepositoryError: File not found.
        RepositoryError: Cannot start repository
    """
    try:
        if os.path.getsize(self.__file_name) > 0: 
          file = open(self.__file_name) 
          line = json.load(file)
          books = []
          for each in line:
            line_splited = each
            books.append([copy.deepcopy(line_splited["isbn"].strip()),copy.deepcopy(line_splited["author"].strip()),copy.deepcopy(line_splited["title"].strip())])
          self._data.append([])
          for each in books:
            self._data[-1].append(Book(each[0],each[1],each[2]))
          file.close()
    except FileNotFoundError:
        raise RepositoryError("File not found.")
    except OSError:
        raise RepositoryError("Cannot start repository")
       
