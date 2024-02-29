from repository import *

class ServiceTenis:
  
  def __init__(self) -> None:
    self.repository = TextFileRepo()
    self.pows = []
    self.currentRound = 'Qualification'
    self.createPow()
    
  def createPow(self):
    for i in range(101):
      self.pows.append(pow(2,i))
      
  def getNumberOfPlayers(self):
    return self.repository.numberOfItems
      
      
  def getRound(self):
    """Getting name for round based on number of players

    Returns:
        str: text with round name
    """
    numberOfPlayers = self.repository.numberOfItems
    if numberOfPlayers in self.pows:
      return f'Last {numberOfPlayers}'
    else:
      return self.currentRound
    
  def getDifference(self):
    """Getting difference between number of players and pow of 2

    Returns:
        int: difference
    """
    numberOfPlayers = self.repository.numberOfItems
    powBiggerThanNumber = 0
    if numberOfPlayers in self.pows:
      return numberOfPlayers//2
    for i in range(len(self.pows)):
      if self.pows[i] > numberOfPlayers:
        if i-1 > 0:
          powBiggerThanNumber = self.pows[i-1]
        break
    difference = numberOfPlayers-powBiggerThanNumber
    return difference
  
  def getPlayersForMatches(self,difference):
    """Getting all players needs for matches

    Args:
        difference (int): difference

    Returns:
        list: matches
    """
    numberOfPlayers = difference * 2
    players = self.sortPlayers()
    return players[:numberOfPlayers]
  
  def setMatches(self,players,difference):
    """Getting all matches needs for players

    Args:
        players (list): list with all players
        difference (int): number of matches

    Returns:
        _type_: _description_
    """
    matches = []
    for i in range(difference):
      matches.append([players[i*2],players[i*2+1]])
    return matches
  
  def uploadPlayers(self,players,winner):
    """Setting data for players

    Args:
        players (list): list with all players
        winner (int): number of winner
    """
    player1 = players[0]
    player2 = players[1]
    winner = players[winner-1]
    winner.increaseStrength(1)
    if player1 == winner:
      self.repository.deleteItem(player2)
    else:
      self.repository.deleteItem(player1)
      
  def getWinner(self):
    return self.repository.getItems[0]


  def sortPlayers(self):
    players = self.repository.getItems
    sortedPlayers = sorted(players, key=lambda x:x.getStrength)
    return sortedPlayers