from repository.memory import *
from services.requirments import *
from domain.library import *
from domain.idobject import *

import faker
import unittest

class TestClientClass(unittest.TestCase):

    def setUp(self):
      self.__clientlogical = ClientLogic('Memory','') 
        
    def test_add_client(self):
      
      fake = Faker()
      list_name = [fake.name() for _ in range(75)]
      for id_client in range(0,20):
        self.__clientlogical.add_client([id_client*100+20,list_name[id_client]])
      clients = self.__clientlogical.show_list_with_clients()
      self.assertEqual(len(clients), 20)
      for i in range(0,20):
        self.assertEqual(clients[i*100+20].clientid, i*100+20)
        
    def test_delete_client(self):
      self.__clientlogical.add_client([99999,"Client 1"])
      self.__clientlogical.add_client([999999,"Client 2"])
      self.__clientlogical.add_client([9999999,"Client 3"])
      
      self.__clientlogical.delete_client(99999)
      self.__clientlogical.delete_client(999999)
      clients = self.__clientlogical.show_list_with_clients()
      self.assertEqual(len(clients),1)
        
    def test_display_clients(self):
      fake = Faker()
      list_name = [fake.name() for _ in range(75)]
      for id_client in range(0,20):
        self.__clientlogical.add_client([id_client*100+20,list_name[id_client]])
      clients = self.__clientlogical.show_list_with_clients()
      self.assertEqual(len(clients), 20)
      
    def test_client_updatE(self):
      self.__clientlogical.add_client([99999,"Client 1"])
      self.__clientlogical.add_client([999999,"Client 2"])
      self.__clientlogical.add_client([9999999,"Client 3"])
      
      self.__clientlogical.update_client(999999,"zeze")
      self.__clientlogical.update_client(99999,"modified")
      clients = self.__clientlogical.show_list_with_clients()
      self.assertEqual(clients[999999].clientname, "zeze")
      self.assertEqual(clients[99999].clientname, "modified")
    

class TestBookClass(unittest.TestCase):

    def setUp(self):
      self.__booklogical = BookLogic('Memory','') 
        
    def test_add_books(self):
      fake = Faker()
      list_authors = [fake.name() for _ in range(75)]
      list_title = [fake.name() for _ in range(75)]
      for index in range(0,20):
        self.__booklogical.add_book([index*100+20,random.choice(list_title), random.choice(list_authors)])
      books = self.__booklogical.show_list_with_books()
      self.assertEqual(len(books), 20)
      for i in range(0,20):
        self.assertEqual(books[i*100+20].bookid, i*100+20)
        
    def test_delete_books(self):
        self.__booklogical.add_book([999999,"Titlu 1"," Author1"])
        self.__booklogical.add_book([9999999,"Titlu 2"," Author1"])
        self.__booklogical.add_book([99999999,"Titlu 3"," Author1"])
        self.__booklogical.delete_book(9999999)
        self.__booklogical.delete_book(999999)
        books = self.__booklogical.show_list_with_books()
        self.assertEqual(len(books), 1)
        
    def test_display_books(self):
      fake = Faker()
      list_authors = [fake.name() for _ in range(75)]
      list_title = [fake.name() for _ in range(75)]
      for index in range(0,20):
        self.__booklogical.add_book([index*100+20,random.choice(list_title), random.choice(list_authors)])
      books = self.__booklogical.show_list_with_books()
      self.assertEqual(len(books), 20)
      
    def test_modify_book(self):
      self.__booklogical.add_book([999999,"Titlu 1"," Author1"])
      self.__booklogical.add_book([9999999,"Titlu 2"," Author1"])
      self.__booklogical.add_book([99999999,"Titlu 3"," Author1"])
      
      self.__booklogical.update_book(999999,"Title Modified","Autho Modified")
      self.__booklogical.update_book(99999999,"zeze","ezez")
      
      books = self.__booklogical.show_list_with_books()
      
      self.assertEqual(books[99999999].booktitle,"zeze")
      self.assertEqual(books[99999999].bookauthor,"ezez")
      self.assertEqual(books[999999].booktitle,"Title Modified")
      self.assertEqual(books[999999].bookauthor,"Autho Modified")