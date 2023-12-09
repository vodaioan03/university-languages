

from domain.idobject import IdObject


class Book(IdObject):
  
  def __init__(self,book_id:int,title:str,author:str) -> None:
    super().__init__(book_id)
    self._book_id = book_id
    self._title = title
    self._author = author
    self.__rented = False
    
  def modify_book(self,title,author):
    self._title = title
    self._author = author
  @property
  def update_rent(self):
    self.__rented = not self.__rented
  
  @property
  def idbook(self):
    return self._book_id
  
  @property
  def title(self):
    return self._title
  @property
  def author(self):
    return self._author
  
  @property
  def rented(self):
    return self.__rented
  
  def __str__(self) -> str:
    return f"[{self.id}] {self.title} | {self.author} | {self.__rented}"
  
  def __repr__(self):
    return  self.__str__()
  
  
  
class Client(IdObject):
  
  def __init__(self,client_id:int, name:str) -> None:
    super().__init__(client_id)
    self._client_id = client_id
    self._name = name
    
  def __str__(self) -> str:
    return f"[{self._client_id}] {self._name}"
  
  def __repr__(self):
    return self.__str__()
    
  def modify_name(self,name:str):
    self._name = name
    
  @property
  def client(self):
    return self._client_id
  
  @property
  def name(self):
    return self._name
  
  
  
class Rental(IdObject):
  
  def __init__(self,rental_id,client:IdObject,book:IdObject,rental_date:str,returned_date:str) -> None:
    super().__init__(rental_id)
    self.__rental = rental_id
    self._book = book
    self._client_id = client
    self._rental_date = rental_date
    self._returned_date = returned_date
  
  def __str__(self) -> str:
    return f"[{self.__rental}] {self._client_id.name} | BOOK: {self._book.id} | Rent Date: {self._rental_date} | END: {self._returned_date}"
  
  def __repr__(self) -> str:
    return self.__str__()
    
  @property
  def idbook(self):
    return self._book
  
  @property
  def client(self):
    return self._client_id
  
  @property
  def rentalid(self):
    return self._rental_id
  
  @property
  def rentaldate(self):
    return self._rental_date
  
  @property 
  def returndate(self):
    return self._returned_date