
from domain.idobject import IdObject

class RepositoryError(Exception):
  pass

class Memory:
  
  def __init__(self) -> None:
    self.__books = {}
    self.__clients = {}
    self.__rentals = {}
    
  def add_book(self,book:IdObject):
    if not isinstance(book, IdObject):
      raise TypeError("Can only add IdObject instances")
    if book.id in self.__books:
      raise RepositoryError("Book already exists.")
    self.__books[book.id] = book
    
  def add_rental(self,rental:IdObject):
    if not isinstance(rental, IdObject):
      raise TypeError("Can only add IdObject instances")
    if rental.id in self.__rentals:
      raise RepositoryError("Rental already exists.")
    rental.idbook.update_rent
    print(rental.idbook)
    self.__rentals[rental.id] = rental
    
  def add_client(self,client:IdObject):
    if not isinstance(client, IdObject):
      raise TypeError("Can only add IdObject instances")
    if client.id in self.__clients:
      raise RepositoryError("Client already exists.")
    self.__clients[client.id] = client
    
  def delete_book(self,book: int):
    
    if book in self.__books:
      book = self.__books[book]
    else:
      raise RepositoryError("Book doesen't exist.")
    if not isinstance(book, IdObject):
      raise TypeError("Can only add IdObject instances")
    del self.__books[book.id]
  
  def delete_client(self,client: int):
    if client in self.__clients:
      client = self.__clients[client]
    else:
      raise RepositoryError("Client doesen't exist.")
    if not isinstance(client, IdObject):
      raise TypeError("Can only add IdObject instances")
      
    del self.__clients[client.id]
    
  def update_client(self,client:int, new_name:str):
    if client in self.__clients:
      client = self.__clients[client]
    else:
      raise RepositoryError("Client doesen't exist.")
    if not isinstance(client, IdObject):
      raise TypeError("Can only add IdObject instances")
    client.modify_name(new_name)
    
  def update_book(self,book_id:int,title:str,author:str):
    if book_id in self.__books:
      book_id = self.__books[book_id]
    else:
      raise RepositoryError("Book doesen't exist.")
    if not isinstance(book_id, IdObject):
      raise TypeError("Can only add IdObject instances")
    book_id.modify_book(title,author)
    
  def find_client(self,client_id:int):
    return self.__clients[client_id] if client_id in self.__clients.keys() else None
  
  def find_book(self,book_id:int):
    return self.__books[book_id] if book_id in self.__books.keys() else None
  
  def find_rental(self,rental_id:int):
    return self.__rentals[rental_id] if rental_id in self.__rentals.keys() else None
  
  @property
  def get_all_clients(self):
    return self.__clients
  @property
  def get_all_books(self):
    return self.__books
  @property
  def get_all_rentals(self):
    return self.__rentals
