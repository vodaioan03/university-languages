

from domain.idobject import IdObject
from datetime import date, timedelta, datetime

class Book(IdObject):
  
  def __init__(self,book_id:int,title:str,author:str) -> None:
    super().__init__(book_id)
    self._book_id = book_id
    self._title = title
    self._author = author
    self.__rented = False
    
  def update_book(self,title:str,author:str):
    self._title = title
    self._author = author
    
  @property
  def update_rent(self):
    self.__rented = not self.__rented
    
  @property
  def rented(self):
    return self.__rented
  
  @property
  def bookid(self):
    return self._book_id
  
  @property
  def booktitle(self):
    return self._title
  
  @property
  def bookauthor(self):
    return self._author
    
  def __str__(self) -> str:
    return f"[{self._book_id}] Author: {self._author} | Title: {self._title}"
    
  def __repr__(self) -> str:
    return self.__str__()
  
  
class Client(IdObject):
  
  def __init__(self,client_id:int, name:str) -> None:
    super().__init__(client_id)
    self._client_id = client_id
    self._name = name
    
  def update_client(self,new_name:str):
    self._name = new_name
    
  def __str__(self) -> str:
    return f"[{self._client_id} | Name: {self._name}]"
    
  def __repr__(self) -> str:
    return self.__str__()
  
  @property
  def clientname(self):
    return self._name
  
  @property
  def clientid(self):
    return self._client_id
  
  
  
  
class Rental(IdObject):
  
  def __init__(self,rental_id,client:IdObject,book:IdObject,rental_date:date,returned_date:date) -> None:
    super().__init__(rental_id)
    self.__rental = rental_id
    self._book = book
    self._client_id = client
    start_date =  rental_date.split(".")
    rental_date = datetime(int(start_date[2]), int(start_date[1]), int(start_date[0]))
    self._rental_date = rental_date
    returned_date = returned_date.split(".")
    returned_date = datetime(int(returned_date[2]), int(returned_date[1]), int(returned_date[0]))
    self._returned_date = returned_date
    self._book.update_rent
  
  
  def __str__(self) -> str:
    return f"[{self.__rental}] Client: {self._client_id.id} | Book: {self._book.id} | Rental: {self._rental_date} | End: {self._returned_date}"
    
  def __repr__(self) -> str:
    return self.__str__()

  def __len__(self):
    return (self._returned_date - self._rental_date).days + 1
  
  @property
  def client(self):
    return self._client_id
  
  @property
  def book(self):
    return self._book
 