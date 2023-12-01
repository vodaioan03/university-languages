import pickle
import copy
import os
from src.repository.memoryrep import RepositoryError

class Pickle():
  
  def __init__(self,file_name) -> None:
    print("init pickle")
    self.__file_name = file_name
    self.__data = [[]]
    self.__load_file()
  
  def add_book(self,list):
    print("Add book Pickle")
    new_list = copy.deepcopy(self.__data[-1])
    new_list.append(list)
    self.__data.append(new_list)
    self.__save_file()
    
  def get_books(self):
    print("Get book Pickle")
    return self.__data[-1]
  
  def undo_list(self):
    print("Undo List Pickle")
    self.__data.pop()
    self.__save_file()
    
  def __save_file(self):
      file = open(self.__file_name, "wb")  
      pickle.dump(self.__data, file)
      file.close()

  def __load_file(self):
      try:
          if os.path.getsize(self.__file_name) > 0: 
            file = open(self.__file_name, "rb") 
            self.__data = pickle.load(file)
            file.close()
      except FileNotFoundError:
          raise RepositoryError("File not found.")
      except OSError:
          raise RepositoryError("Cannot start repository")

  def __len__(self):
      return len(self.__data)
    
  def modify_list(self,new_list):
    print("Modify List Pickle")
    self.__data.append(new_list)
    self.__save_file()