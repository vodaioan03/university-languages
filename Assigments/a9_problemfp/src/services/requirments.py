
from domain.library import Book, Client, Rental
from repository.memory import *
from faker import Faker
from services.undo_service import *
import random
from datetime import date,timedelta
from ui.errors import *
import sys

class BooksRental:
    def __init__(self, book: Book, day_count: int):
        self.__book = book
        self.__days = day_count

    @property
    def book(self):
        return self.__book

    @property
    def day_count(self):
        return self.__days

    def __lt__(self, other):
        return self.day_count <= other.day_count

    def __str__(self):
      return f"Book {self.__book} is rented for {self.__days} days"

    def __repr__(self):
        return str(self)
      
class ClientRental:
    def __init__(self, client: Client, day_count: int):
        self.__client = client
        self.__days = day_count

    @property
    def client(self):
        return self.__client

    @property
    def day_count(self):
        return self.__days

    def __lt__(self, other):
        return self.day_count <= other.day_count

    def __str__(self):
      return f"Client {self.__client} rent books for {self.__days} days"

    def __repr__(self):
        return str(self)
      
      
class AuthorRental:
    def __init__(self, author: str,days:int):
        self.__author = author
        self.__days = days

    @property
    def author(self):
        return self.__author

    @property
    def day_count(self):
        return self.__days

    def __lt__(self, other):
        return self.day_count <= other.day_count

    def __str__(self):
      return f"Author {self.__author} has: {self.__days} days"

    def __repr__(self):
        return str(self)

class RentalLogic:
  
  def __init__(self,undo_service : UndoService, client_rep: Memory , book_rep:Memory,rep,filename) -> None:
    self.__undo_service = undo_service
    self.__rentals_repo = getattr(sys.modules[__name__], rep)(filename,'Rental',client_rep,book_rep)
    self.__clients_repo = client_rep
    self.__books_repo = book_rep
    
  def show_rentals(self):
    return self.__rentals_repo.get_all
  
  def rental_book(self,rental_id:int,client_id:int,book_id:int,rental_date:str,end_date:str):
    client = self.__clients_repo.find(client_id)
    book = self.__books_repo.find(book_id)
    rental = self.__rentals_repo.find(rental_id)
    if not book:
      raise NoBookExist("Book doesen't exist.")
    if not client:
      raise ClientError("Client doesen't exist.")
    if book.rented:
      raise NoBookExist("The book already rented.")
    if rental == None:
      rental_id = self.__rentals_repo.add(Rental(rental_id,client,book,rental_date,end_date))
      fredo = FunctionCall(self.__rentals_repo.add, rental_id)
      fundo = FunctionCall(self.__rentals_repo.delete, rental_id)
      self.__undo_service.record(Operation(fundo, fredo))
    else:
      raise RentalError("Rental already exist.")
    
  def return_book(self,client_id:int,book_id:int):
    client = self.__clients_repo.find(client_id)
    book = self.__books_repo.find(book_id)
    rentals = self.__rentals_repo.get_all
    if not book:
      raise NoBookExist("Book doesen't exist.")
    if not client:
      raise ClientError("Client doesen't exist.")
    if not book.rented:
      raise NoBookExist("The book isn't rented.")
    for each in rentals:
      if rentals[each].client == client and rentals[each].book == book:
        rental_id = rentals[each]
        self.delete_rental(rental_id)
        return
    raise RentalError("Rental doesen't exist.")
  
  def delete_rental(self,rental_id):
    rental_id.book.update_rent
    self.__rentals_repo.delete(rental_id)
    fredo = FunctionCall(self.__rentals_repo.delete, rental_id)
    fundo = FunctionCall(self.__rentals_repo.add, rental_id)
    self.__undo_service.record(Operation(fundo, fredo))
    
  def delete_rentals(self,client,rentals:list):
    self.__clients_repo.delete(client)
    for each in rentals:
      self.__rentals_repo.delete(each)
      
  def add_rentals_deletes(self,client,rentals):
    self.__clients_repo.add(client)
    for each in rentals:
      self.__rentals_repo.add(each)
  
  def delete_rentals_books(self,book,rentals:list):
    self.__books_repo.delete(book)
    for each in rentals:
      self.__rentals_repo.delete(each)
  
  def add_rentals_deleted_books(self,book,rentals:list):
    self.__books_repo.add(book)
    for each in rentals:
      self.__rentals_repo.add(each) 
   
  def statistics_for_books(self):
    all_rentals = {}
    for rental in self.__rentals_repo:
      book_rental_id = rental.book.id
      if book_rental_id not in all_rentals:
        all_rentals[book_rental_id] = [rental]
      else:
        all_rentals[book_rental_id].append(rental)
    
    book_rental_days = {}
    for book_id in all_rentals:
      book_rental_days[book_id] = 0
      for rental in all_rentals[book_id]:
        book_rental_days[book_id] += len(rental)
        
    result_books = []    
    for each in book_rental_days:
      item = BooksRental(self.__books_repo[each],book_rental_days[each])
      result_books.append(item)
    result_books.sort(reverse=True)
    return result_books
  
  def statistics_for_client(self):
    client_rentals = {}
    for rental in self.__rentals_repo:
      client_rental_id = rental.client.id
      if client_rental_id not in client_rentals:
        client_rentals[client_rental_id] = [rental]
      else:
        client_rentals[client_rental_id].append(rental)
    
    client_rental_days = {}
    for client_id in client_rentals:
      client_rental_days[client_id] = 0
      for client in client_rentals[client_id]:
        client_rental_days[client_id] += len(client)
    
    result_clients = []
    for each in client_rental_days:
      item = ClientRental(self.__clients_repo[each],client_rental_days[each])
      result_clients.append(item)
    result_clients.sort(reverse=True)
    return result_clients
  
  def statistics_for_authors(self):
    author_rentals = {}
    for rental in self.__rentals_repo:
      author_rental_name = rental.book.bookauthor
      if author_rental_name not in author_rentals:
        author_rentals[author_rental_name] = [rental]
      else:
        author_rentals[author_rental_name].append(rental)
        
    author_rental_days = {}
    for author_name in author_rentals:
      author_rental_days[author_name] = 0
      for rental in author_rentals[author_name]:
        author_rental_days[author_name] += len(rental)
    
    result_author = []
    for each in author_rental_days:
      item = AuthorRental(each, author_rental_days[each])
      result_author.append(item)
    result_author.sort(reverse=True)
    return result_author
  
  def add_rentals(self):
    clients = self.__clients_repo.get_all
    books = self.__books_repo.get_all
    for index in range(0,20):
      start_date = date.today() + timedelta(days=random.randint(-60, -10))
      end_date = start_date + timedelta(days=random.randint(1, 10))
      book = random.choice(books)
      client = random.choice(clients)
      while book.rented:
        book = random.choice(books)
      day = random.randint(1,28)
      month = random.randint(1,10)
      year = random.randint(2023,2060)
      start_date = f"{day}.{month}.{year}"
      new_day = day + random.randint(0,28-day)
      new_monts = month + random.randint(0,12-month)
      end_date = f"{new_day}.{new_monts}.{year}"
      self.__rentals_repo.add(Rental(index,client,book,start_date,end_date))
      
  def filter_rentals(self,idclient:Client):
    rentals = self.__rentals_repo.get_all
    rental_result = []
    for each in rentals:
      if rentals[each]._client_id == idclient:
        rental_result.append(rentals[each])
    return rental_result
  
  def filter_rentals_books(self,idbook:Book):
    rentals = self.__rentals_repo.get_all
    rental_result = []
    for each in rentals:
      if rentals[each]._book == idbook:
        rental_result.append(rentals[each])
    return rental_result
      
   
  
class BookLogic:
  def __init__(self,undo_service: UndoService,rep,filename) -> None:
    self.__undo_service = undo_service
    self.__books_repo = getattr(sys.modules[__name__], rep)(filename,'Book')
    self.__rental_service = ''
  @property
  def bookrepo(self):
    return self.__books_repo
  def update_rental_service(self,rental_service):
    self.__rental_service = rental_service
    
  def add_book(self,data):
    book = self.__books_repo.add(Book(data[0],data[1],data[2]))
    fredo = FunctionCall(self.__books_repo.add, book)
    fundo = FunctionCall(self.__books_repo.delete, book)
    self.__undo_service.record(Operation(fundo, fredo))
    
  def delete_book(self,book_id:int):
    all_books = self.__books_repo.get_all
    if book_id in all_books:
      book_id = all_books[book_id]
    else:
      raise NoBookExist("Book doesen't exist.")
    rentals = self.__rental_service.filter_rentals_books(book_id)
    self.__rental_service.delete_rentals_books(book_id,rentals)
    fredo = FunctionCall(self.__rental_service.delete_rentals_books, book_id,rentals)
    fundo = FunctionCall(self.__rental_service.add_rentals_deleted_books, book_id,rentals)
    self.__undo_service.record(Operation(fundo, fredo))
    
    
  def update_book(self,book_id,title,author):
    all_books = self.__books_repo.get_all
    if book_id in all_books:
      book_id = all_books[book_id]
    else:
      raise NoBookExist("Book doesen't exist.")
    actual_title = book_id.booktitle
    actual_author = book_id.bookauthor
    book_id.update_book(title,author)
    fredo = FunctionCall(book_id.update_book, title,author)
    fundo = FunctionCall(book_id.update_book, actual_title,actual_author)
    self.__undo_service.record(Operation(fundo, fredo))
    self.bookrepo._save_modify()
  
  def search_book_id(self,book_id:int):
    books = self.__books_repo.get_all
    books_found = []
    for each in books:
      if str(book_id) in str(books[each].bookid):
        books_found.append(books[each])
    return books_found
  
    
  def show_list_with_books(self):
    return self.__books_repo.get_all
  
  def search_book_title(self,book_title:str):
    books = self.__books_repo.get_all
    books_found = []
    for each in books:
      if book_title.lower() in books[each].booktitle.lower():
        books_found.append(books[each])
    return books_found
  
  def search_book_author(self,book_author:str):
    books = self.__books_repo.get_all
    books_found = []
    for each in books:
      if book_author.lower() in books[each].bookauthor.lower():
        books_found.append(books[each])
    return books_found
  
  def _addbooks(self):
    fake = Faker()
    list_authors = [fake.name() for _ in range(75)]
    list_title = [fake.name() for _ in range(75)]
    for index in range(0,30):
      self.__books_repo.add(Book(index,random.choice(list_title), random.choice(list_authors)))
  
  
class ClientLogic:
  
  def __init__(self,undo_service:UndoService,rep,filename) -> None:
    self.__undo_service = undo_service
    self.__clients_repo = getattr(sys.modules[__name__], rep)(filename,'Client')
    self.__rental_service = ''

  @property
  def clientrepo(self):
    return self.__clients_repo  
  
  def update_rental_service(self,rental_service : RentalLogic):
    self.__rental_service = rental_service

  def add_client(self,data):
    client = self.__clients_repo.add(Client(data[0],data[1]))
    fredo = FunctionCall(self.__clients_repo.add, client)
    fundo = FunctionCall(self.__clients_repo.delete, client)
    self.__undo_service.record(Operation(fundo, fredo))
  
  def delete_client(self,client_id:int):
    all_clients = self.__clients_repo.get_all
    if client_id in all_clients:
      client_id = all_clients[client_id]
    else:
      raise ClientError("Client doesen't exist.")
    rentals = self.__rental_service.filter_rentals(client_id)
    self.__rental_service.delete_rentals(client_id,rentals)
    fredo = FunctionCall(self.__rental_service.delete_rentals, client_id,rentals)
    fundo = FunctionCall(self.__rental_service.add_rentals_deletes, client_id,rentals)
    self.__undo_service.record(Operation(fundo, fredo))
    
  def update_client(self,client_id,new_name):
    all_clients = self.__clients_repo.get_all
    if client_id in all_clients:
      client_id = all_clients[client_id]
    else:
      raise ClientError("Client doesen't exist.")
    actual_name = client_id.clientname
    client_id.update_client(new_name)
    fredo = FunctionCall(client_id.update_client, new_name)
    fundo = FunctionCall(client_id.update_client, actual_name)
    self.__undo_service.record(Operation(fundo, fredo))
    self.clientrepo._save_modify()
  
  def show_list_with_clients(self):
    return self.__clients_repo.get_all
  
  def search_client_id(self,client_id:int):
    clients = self.__clients_repo.get_all
    clients_found = []
    for each in clients:
      if str(client_id) in str(clients[each].clientid):
        clients_found.append(clients[each])
    return clients_found
  
  def search_client_name(self,client_name:str):
    clients = self.__clients_repo.get_all
    clients_found = []
    for each in clients:
      if client_name.lower() in clients[each].clientname.lower():
        clients_found.append(clients[each])
    return clients_found
  
  def add_clients(self):
    fake = Faker()
    list_name = [fake.name() for _ in range(75)]
    for id_client in range(0,40):
      self.__clients_repo.add(Client(id_client,list_name[id_client]))