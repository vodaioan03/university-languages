
from domain.library import Book, Client, Rental
from repository.memory import Memory


class LogicalThings:
  
  def __init__(self) -> None:
    self.__rep = Memory()
    self.add_books()
    self.add_clients()
    
  def add_books(self):
    self.__rep.add_book(Book(1,"Book 1", "book 1"))
    self.__rep.add_book(Book(2,"Book 2", "book 12"))
    self.__rep.add_book(Book(3,"Book 3", "book 13"))
    self.__rep.add_book(Book(4,"Book 4", "book 14"))
    
  def add_clients(self):
    self.__rep.add_client(Client(1,"Name 1"))
    self.__rep.add_client(Client(2,"Name 2"))
    self.__rep.add_client(Client(3,"Name 3"))
    self.__rep.add_client(Client(4,"Name 4"))
    self.__rep.add_client(Client(5,"Name 5"))
    self.__rep.add_client(Client(6,"Name 6"))
  
  def add_book(self,data):
    self.__rep.add_book(Book(data[0],data[1],data[2]))
    
  def add_client(self,data):
    self.__rep.add_client(Client(data[0],data[1]))
    
  def delete_book(self,book_id:int):
    self.__rep.delete_book(book_id)
  
  def delete_client(self,client_id:int):
    self.__rep.delete_client(client_id)
  
  def update_book(self,book_id,title,author):
    self.__rep.update_book(book_id,title,author)
  
  def update_client(self,client_id,new_name):
    self.__rep.update_client(client_id, new_name)
  
  def show_list_with_clients(self):
    return self.__rep.get_all_clients
  
  def show_list_with_books(self):
    return self.__rep.get_all_books
  
  def show_rentals(self):
    return self.__rep.get_all_rentals
  
  def rental_book(self,rental_id:int,client_id:int,book_id:int,rental_date:str,end_date:str):
    client = self.__rep.find_client(client_id)
    book = self.__rep.find_book(book_id)
    rental = self.__rep.find_rental(rental_id)
    if rental == None:
      self.__rep.add_rental(Rental(rental_id,client,book,rental_date,end_date))
    else:
      raise ValueError("Rental already exist.")