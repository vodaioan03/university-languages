import copy

class RepositoryError(Exception):
    @property
    def message(self) -> str:
        return self.__message

    def __init__(self, message: str = "Not specified Reository Error"):
        self.__message = message

    def __str__(self) -> str:
        return self.__message

class Memory:
  
  def __init__(self,file_name):
    self.actual_list = []
    self.history = [[]]
    print("init memory")
    
  def add_book(self,list):
    self.actual_list.append(list)
    self.history.append(copy.deepcopy(self.actual_list))
    
  def get_books(self):
    return self.actual_list
  
  def undo_list(self):
    self.history.pop()
    self.actual_list = self.history[-1]
    
  def modify_list(self,new_list):
    self.actual_list = new_list
    self.history.append(copy.deepcopy(self.actual_list))