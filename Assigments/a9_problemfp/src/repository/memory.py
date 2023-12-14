
from domain.idobject import IdObject
from domain.library import *
from ui.errors import *
import pickle
import os
import sys
import copy

class RepositoryCounter:
    def __init__(self, data: list):
        self._data = data
        self.__pos = -1

    def __next__(self):
        # return the next item we iterate over
        self.__pos += 1
        if self.__pos == len(self._data):
            raise StopIteration()
        return self._data[self.__pos]

class Memory:
  
  def __init__(self,filerep='',classe='',client_rep='',book_rep='') -> None:
    self._data = {}
    
  def add(self, object: IdObject):
    if not isinstance(object, IdObject):
        raise TypeError("Can only add IdObject instances")

    if object.id in self._data.keys():
      raise ValidationException("Already exists.")

    self._data[object.id] = object
    return object
    
  def delete(self,object: IdObject):
    if not isinstance(object, IdObject):
        raise TypeError("Can only delete IdObject instances")

    if not object.id in self._data.keys():
        raise ValidationException("This object doesen't exist.")
    del self._data[object.id]
    return object
  
  def __iter__(self):
    return RepositoryCounter(list(self._data.values()))
      
  def __getitem__(self, item):
    if item not in self._data:
        return None
    return self._data[item]
    
  def __len__(self):
    return len(self._data)
  
  def find(self,id:int):
    return self._data[id] if id in self._data.keys() else None
    
  @property
  def get_all(self):
    return self._data
  
  
class Pickle(Memory):
  
  def __init__(self,filerep,classe,client_rep='',book_rep='') -> None:
    super().__init__(filerep)
    self.__file_name = filerep
    self.__load_file()
  
  def add(self, object: IdObject):
    super().add(object)
    self.__save_file()
    
  def delete(self,object: IdObject):
    super().delete(object)
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
        raise ValidationException("File not found.")
    except OSError:
        raise ValidationException("Cannot start repository")
      
      
class Text(Memory):
  
  def __init__(self,filerep,classe,client_rep='',book_rep='') -> None:
    self.__file_name = filerep
    self.__class_rep = classe
    self.__clients_rep = client_rep
    self.__books_rep = book_rep
    super().__init__(filerep)
    self.__load_file()
    
  def add(self, object: IdObject):
    super().add(object)
    self.__save_file()
    return object
    
  def delete(self,object: IdObject):
    super().delete(object)
    self.__save_file()
    return object
     
  def __save_file(self):
    """Save file in text file folder
    """
    self.File_object = open(self.__file_name ,"w")
    strings = ''
    for each in self._data:
      strings += self._data[each].get_items()
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
          strings = []
          line = ''
          
          with open(self.__file_name, "r")  as file:
            line = file.readlines()
          for each in line:
            strings.append([])
            line_splited = each.split(",")
            for linespl in line_splited:
              strings[-1].append(copy.deepcopy(linespl))
          for each in strings:
            each[-1] = each[-1].replace("\n",' ')
            if self.__class_rep == 'Client':
              object = getattr(sys.modules[__name__], self.__class_rep)(int(each[0]),each[1].strip())
            elif self.__class_rep == 'Book':
              object = getattr(sys.modules[__name__], self.__class_rep)(int(each[0]),each[1],each[0])
            elif self.__class_rep == 'Rental':
              client = self.__clients_rep.find(int(each[1]))
              book = self.__books_rep.find(int(each[2]))
              if client == None or book == None:
                continue
              object = getattr(sys.modules[__name__], self.__class_rep)(int(each[0]),client,book,each[3],each[4])
            self._data[object.id] = object
    except FileNotFoundError:
        raise ValidationException("File not found.")
    except OSError:
        raise ValidationException("Cannot start repository")
     