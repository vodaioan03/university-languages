import os
import copy
import json

from src.repository.memoryrep import RepositoryError

class Text:
  def __init__(self,file_name) -> None:
    self.__file_name = file_name
    self.__data = [[]]
    self.__save_file()
    self.__load_file()
  
  def add_book(self,listof):
    print("Add book Text")
    new_list = copy.deepcopy(self.__data[-1])
    print(new_list)
    new_list.append(listof)
    self.__data.append(new_list)
    print(self.__data)
    print("in add book")
    self.__save_file()
    
  def get_books(self):
    return self.__data[-1]
    
  def undo_list(self):
    print("Undo List Text")
    self.__data.pop()
    self.__save_file()
    
  def modify_list(self,new_list):
    print("Modify List Text")
    
  def __save_file(self):
    print(f"Actual List {self.__data}")
    self.File_object = open(self.__file_name ,"w")
    self.File_object.write(str(self.__data))
    self.File_object.close()
    print("SUCCES")
    
  def __load_file(self):
      try:
          if os.path.getsize(self.__file_name) > 0: 
            file = open(self.__file_name, "r") 
            self.__data = json.loads(file.read())
            file.close()
      except FileNotFoundError:
          raise RepositoryError("File not found.")
      except OSError:
          raise RepositoryError("Cannot start repository")