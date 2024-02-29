import os
import copy
import json

#from src.repository.repository import RepositoryError, Repository
from src.repository.memoryrep import RepositoryError, Memory
from src.domain.book import *
class Text(Memory):
  
  def __init__(self,file_name) -> None:
    """TestFile init for Repository

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
    """Save file in text file folder
    """
    self.File_object = open(self.__file_name ,"w")
    strings = ''
    for each in self._data[-1]:
      strings += f"{each.isbn},{each.author},{each.title} \n"
    self.File_object.write(strings)
    self.File_object.close()
    
       
  def __load_file(self):
    """Load file in text file foler

    Raises:
        RepositoryError: File not found.
        RepositoryError: Cannot start repository
    """
    try:
        if os.path.getsize(self.__file_name) > 0: 
          books = []
          line = ''
          with open(self.__file_name, "r")  as file:
            line = file.readlines()
          for each in line:
            line_splited = each.split(",")
            books.append([copy.deepcopy(line_splited[0].strip()),copy.deepcopy(line_splited[1].strip()),copy.deepcopy(line_splited[2].strip())])
          self._data.append([])
          for each in books:
            self._data[-1].append(Book(each[0],each[1],each[2]))
    except FileNotFoundError:
        raise RepositoryError("File not found.")
    except OSError:
        raise RepositoryError("Cannot start repository")