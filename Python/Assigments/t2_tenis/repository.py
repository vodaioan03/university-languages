import copy
import os

from domain import *

class TextFileRepo:
  
  def __init__(self) -> None:
    self._data = []
    self.filename = 'input.txt'
    self.__load_file()
    
  def addItem(self,value):
    self._data.append(value)
    self.__save_file()
    
  def deleteItem(self,value):
    index = self._data.index(value)
    if index != None:
      del self._data[index]
    self.__save_file()
  @property
  def getItems(self):
    return self._data
  
  @property
  def numberOfItems(self):
    return len(self._data)

  def __save_file(self):
    FileOpen = open(self.filename,'w')
    string = ''
    for each in self._data:
      if isinstance(each,Player):
        string += f'{each.textForFile()} \n'
      else:
        print("xxxxxxxxxxxxxxxxxxxxxxxx#######################")
        print(each)
    FileOpen.write(string)
    FileOpen.close()
    
    
  def __load_file(self):
    FileOpen = open(self.filename,'r')
    players = FileOpen.readlines()
    for each in players:
      line = copy.deepcopy(each.strip())
      line = line.split(',')
      line[1] = line[1].strip()
      line[2] = line[2].strip()
      self.addItem(Player(int(line[0]),line[1],int(line[2])))
