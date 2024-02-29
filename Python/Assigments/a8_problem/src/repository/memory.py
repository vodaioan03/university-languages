
from domain.idobject import IdObject
from ui.errors import *

class RepositoryCounter:
    def __init__(self, data: list):
        self.__data = data
        self.__pos = -1

    def __next__(self):
        # return the next item we iterate over
        self.__pos += 1
        if self.__pos == len(self.__data):
            raise StopIteration()
        return self.__data[self.__pos]

class Memory:
  
  def __init__(self) -> None:
    self.__data = {}
    
  def add(self, object: IdObject):
    if not isinstance(object, IdObject):
        raise TypeError("Can only add IdObject instances")

    if object.id in self.__data.keys():
        raise ValidationException("Already exists.")

    self.__data[object.id] = object
    
  def delete(self,object: IdObject):
    if not isinstance(object, IdObject):
        raise TypeError("Can only add IdObject instances")

    if not object.id in self.__data.keys():
        raise ValidationException("This object doesen't exist.")
    del self.__data[object.id]
    
  def __iter__(self):
    return RepositoryCounter(list(self.__data.values()))
      
  def __getitem__(self, item):
    if item not in self.__data:
        return None
    return self.__data[item]
    
  def __len__(self):
    return len(self.__data)
  
  def find(self,id:int):
    return self.__data[id] if id in self.__data.keys() else None
    
  @property
  def get_all(self):
    return self.__data