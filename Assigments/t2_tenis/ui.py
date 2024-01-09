from services import *
from domain import *

class Ui:
  
  def __init__(self) -> None:
    self.service = ServiceTenis()
    self.isPlaying = False
    
  def displayAllPlayers(self):
    playersList = self.service.sortPlayers()
    for each in playersList:
      print(each)
      
  def playtournament(self):
    roundName = self.service.getRound()
    print('\n',roundName, ' round! \n')
    difference = self.service.getDifference()
    players = self.service.getPlayersForMatches(difference)
    matches = self.service.setMatches(players,difference)
    for each in matches:
      print(f'Match {matches.index(each)+1} \n')
      print(f'Player 1: {each[0]} \nPlayer 2: {each[1]}')
      winnerSet = False
      while not winnerSet:
        winner = input('Pick player (1 or 2): ').strip()
        if not winner.isnumeric():
          print("Try again, type integer number.")
        else:
          winner = int(winner)
          self.service.uploadPlayers(each,winner)
          winnerSet = True
        
        
  def printWinner(self):
    winner = self.service.getWinner()
    print(f"Winner: {winner}")
  
  def startGame(self):
    self.isPlaying = True
    
    self.displayAllPlayers()
    while self.service.getNumberOfPlayers() > 1:
      self.playtournament()
    self.printWinner()

if __name__ == '__main__':
  uiMenu = Ui()
  uiMenu.startGame()