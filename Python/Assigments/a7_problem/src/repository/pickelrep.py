import pickle
import copy
import os
#from src.repository.repository import RepositoryError, Repository
from src.repository.memoryrep import RepositoryError, Memory

class Pickle(Memory):
  
  def __init__(self,file_name) -> None:
    """Pickle init for Repository

    Args:
        file_name (_type_): file name for saving
    """
    self.__file_name = file_name
    super().__init__()
    self.__load_file()
  
  def add_book(self,list):
    """Adding book and saving

    Args:
        list (_type_): id class to be saved
    """
    super().add_book(list)
    self.__save_file()
  
  def undo_list(self):
    """Undo list and saving in file
    """
    super().undo_list()
    self.__save_file()
    
  def __save_file(self):
    """Save file in pickle folder
    """
    file = open(self.__file_name, "wb")  
    pickle.dump(self._data, file)
    file.close()

  def __load_file(self):
    """Load file in pickle foler

    Raises:
        RepositoryError: File not found.
        RepositoryError: Cannot start repository
    """
    try:
        if os.path.getsize(self.__file_name) > 0: 
          file = open(self.__file_name, "rb") 
          self._data = pickle.load(file)
          file.close()
    except FileNotFoundError:
        raise RepositoryError("File not found.")
    except OSError:
        raise RepositoryError("Cannot start repository")
    
  def modify_list(self,new_list):
    """Modify list and savinf

    Args:
        new_list (list): new list for modify
    """
    super().modify_list(new_list)
    self.__save_file()
    