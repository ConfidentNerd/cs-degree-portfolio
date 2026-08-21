# Example Python Code to Insert a Document 

from pymongo import MongoClient 
from bson.objectid import ObjectId 

class AnimalShelter(object): 
    """ CRUD operations for Animal collection in MongoDB """
    # set the parameters to default values
    def __init__(self, USER='aacuser', PASS='myDopePwd123', HOST='localhost', PORT=27017, DB='aac', COL='animals'): 
       
        # Initialize Connection 
        self.client = MongoClient('mongodb://%s:%s@%s:%d' % (USER,PASS,HOST,PORT)) 
        self.database = self.client['%s' % (DB)] 
        self.collection = self.database['%s' % (COL)] 
            
    # Complete this create method to implement the C in CRUD. 
    def create(self, data):
        if data is not None:
            try:
                self.collection.insert_one(data)  # data should be dictionary
                return True

            except Exception:
                print("Something went wrong during insertion")
                return False
    
        raise Exception("Nothing to save, because data parameter is empty")

    # Create method to implement the R in CRUD.
    def read(self, query):
        if query is not None:
            try:
                # converted cursor to a list
                res = list(self.collection.find(query))
                return res
            
            except Exception:
                print("Something went wrong during DB lookup")
                
        return []
    
    def update(self, query, data):
        if data is not None and query is not None:
            try:
                # updates all matches
                res = self.collection.update_many(query, data)
                
                return res.modified_count
        
            except Exception:
                print("Something went wrong during DB update")
                # if we haven't updated anything the modified count is 0.
                return 0
            
        raise Exception("Nothing to save, because data or query parameters are empty")
        
    def delete(self, query):
        if query is not None:
            try:
                # deletes all matches
                res = self.collection.delete_many(query)
                
                return res.deleted_count
            
            except Exception:
                print("Something went wrong during DB deletion")
                return 0
                
        raise Exception("Nothing to delete, because query parameter is empty")