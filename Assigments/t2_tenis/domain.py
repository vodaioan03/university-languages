
# 100, Alice, 45
# 101, Bob, 34

class Player:
  
  def __init__(self,idPlayer:int, name:str,playingStrength:int) -> None:
    self.idPlayer = idPlayer
    self.name = name
    self.strength = playingStrength
    
  @property
  def getIdPlayer(self):
    return self.idPlayer
  @property
  def getName(self):
    return self.name
  @property
  def getStrength(self):
    return self.strength
  
  def increaseStrength(self,value):
    self.strength += value
  
  def textForFile(self):
    return f'{self.getIdPlayer}, {self.getName}, {self.getStrength}'
  
  def __str__(self) -> str:
    return f'ID: {self.getIdPlayer}, Name: {self.getName}, Strength: {self.getStrength}'
  def __repr__(self) -> str:
    return self.__str__()