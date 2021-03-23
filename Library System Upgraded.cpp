#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

string CorrPassword = "NYUADlib";
const int CAPACITY = 150;

class Shelf {
private:
	string shelfID;
	int numofbooks = 0;

public:
	Shelf(string id, int nob = 0)
	{
		shelfID = id;
		numofbooks = nob;
	};

	~Shelf() {};

	int getNumofBooks() {
		return numofbooks;
	};

	void setNumofBooks(int nob) {
		numofbooks = nob;
	};

	string getShelfID() {
		return shelfID;
	};

	void setNumofBooks(string id) {
		shelfID = id;
	};
};
class Book {
private:
	string title;
	string author;
	string ISBN;
	string year;
	int Num_of_Copies;
	string identifier;
	bool deleted = false;

public:
	Book()
	{
		title = "";
		author = "Empty";
		ISBN = "Empty";
		year = "Empty";
		Num_of_Copies = -1;
		//identifier = "XXXX";
	};

	Book(string tit, string aut, string isbn, string yr, int noc, string id) {
		title = tit;
		author = aut;
		ISBN = isbn;
		year = yr;
		Num_of_Copies = noc;
		identifier = id;
	};

	~Book() {}; //destructor

	const string getTitle() {
		return this->title;
	}

	//set all attributes of book
	void setTitle(string tit) {
		title = tit;

	};

	void setAuthor(string aut) {
		author = aut;           
	};
	string getAuthor(){
		return this->author;           
	};
	void setISBN(string isbn) {
		ISBN = isbn;
	};
	string getISBN() {
		return this->ISBN;
	};

	void setYear(string YEAR) {
		year = YEAR;
	};
	string getYear() {
		return this->year;
	};

	void setNum_of_Copies(int NoCopies) {
		Num_of_Copies = NoCopies;
	};
	int getNum_of_Copies() {
		return Num_of_Copies;
	};
	void setidentifier(string id) {
		identifier = id;
	};
	string getidentifier() {
		return identifier;
	};

	bool getDeleted() {
		return deleted;
	};
	void setdeleted(bool d) {
		deleted = d;
	};
	void print() {
		cout << title << endl;
		cout << author << endl;
		cout << ISBN << endl;
		cout << year << endl;
		cout << Num_of_Copies << endl;
		cout << identifier << endl;
	};

};

Book hashtable[CAPACITY];
vector<Shelf> s;
int totbooks = 0;
void readfiles(string filename);
int hashcode(string title, string author);
void insertbook(Book b, int hc);
void searchbook();
void addbook();
void removebook();
void printmenu();
void enterpassword();
void rearrangebook();
void booksonshelf();
void loadfile(string filename, string title, string author, string ISBN, string year, int Num_of_Copies);

int main()
{
	//read files
	string filenameA = "BookcaseA.csv";
	readfiles(filenameA);
	string filenameB = "BookcaseB.csv";
	readfiles(filenameB);
	string filenameC = "BookcaseC.csv";
	readfiles(filenameC);

	// for(int i = 0; i<CAPACITY; i++)
	// {
	// 	hashtable[i].print();
	// }

	printmenu();
}

void enterpassword()
{
	string password;
	int choice;

	cout << "Please enter the password." << endl;
	cin >> password;

	if (password != CorrPassword) //compare user entered password to correct password declared as a global variable
	{
		for (int i = 0; i < 2; i++)
		{

			cout << "Incorrect password. Please re-enter." << endl;
			cin >> password;

			if (password == CorrPassword)
				break;

			if (i == 1 && password != CorrPassword)
			{
				cout << "Sorry you do not have access to the database. " << endl;
				cout << "Press 1 to return to main menu or 2 to exit the system." << endl;
				cin >> choice;

				if (choice == 1)
					main();
				else
					exit(0);

			}
		}
	}

}

void printmenu()
{
	int choice = 0;
	while(choice!=7)
	{
		
		cout << "Welcome to the Library System!" << endl;
		cout << "There are " << totbooks << " books in the library" << endl;
		cout << "Please choose one of the following options: " << endl;

		cout << "1: Search for a book." << endl;
		cout << "2: Add a new book." << endl;
		cout << "3: Remove an existing book." << endl;
		cout << "4: Rearrange books." << endl;
		cout << "5: Access number of books on a shelf." << endl;
		cout << "6: Access number of bookcases in the library." << endl;
		cout << "7: Exit the system." << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:
			searchbook();
			break;
		case 2:
			enterpassword(); //call password function
			addbook();
			// for(int i = 0; i<CAPACITY; i++)
			// {
			// 	hashtable[i].print();
			// }
			break;
		case 3:
			enterpassword();
			removebook();
			// for(int i = 0; i<CAPACITY; i++)
			// {
			// 	hashtable[i].print();
			// }
			break;
		case 4:
		 	enterpassword();
			rearrangebook();
			// for(int i = 0; i<CAPACITY; i++)
			// {
			// 	hashtable[i].print();
			// }
			break;
		case 5:
		 	enterpassword();
		 	booksonshelf();

		 	break;
		case 6:
			enterpassword();
			cout << "There are " << "3" << " book cases in the library" << endl;
			break;
		case 7:
			exit(0);
		}
	}
}

void readfiles(string filename)
{

	string value = " ";
	string title;
	string author;
	string ISBN;
	string year;
	string id;
	int nob = 0;
	int Num_of_Copies = 0;
	int shelfnumber = 1;
	int booksonshelf = -1;
	int hc = 0;

	//open file
	ifstream File(filename, ios::in);

	if (File.fail()) 
	{
		cerr << "Error opening file.\n";
		exit(1);
	}

	getline(File, value); //read first line of file

	while (!File.eof())
	{

		if (booksonshelf >= 9)
		{	
			id = filename[8] + to_string(shelfnumber);
			s.push_back(Shelf(id, booksonshelf));
			booksonshelf = -1;
			shelfnumber++;
			//totbooks++;
		}

		string identifier = "";

		getline(File, value, ','); //read first line from file until comma
		title = value;

		getline(File, value, ',');
		author = value;

		getline(File, value, ',');
		ISBN = value;

		getline(File, value, ',');
		year = value;

		getline(File, value);
		Num_of_Copies = stoi(value);

		//increment number of books in a shelf
		for (int i = 0; i < Num_of_Copies; i++)
		{	
			booksonshelf++;
			totbooks++;

			if (booksonshelf > 9)
			{	
				id = filename[8] + to_string(shelfnumber);
				s.push_back(Shelf(id, booksonshelf));
				booksonshelf = -1;
				shelfnumber++;
				//totbooks++;
			}

			//booksonshelf++;

			//generate an identifier by concatenating a string
			identifier = filename[8] + to_string(shelfnumber) + "." + to_string(booksonshelf);

			//generate hashcode of every book
			hc = hashcode(title, author);

			//make a book object and add it to the hashtable num of copies times
			insertbook(Book(title, author, ISBN, year, Num_of_Copies, identifier), hc);
		}
	}

	id = filename[8] + to_string(shelfnumber);
	s.push_back(Shelf(id, booksonshelf));
}

//generate hash code from name and author
int hashcode(string title, string author)//average time complexity is again O(n) to generate a hashcode
{
	int code = 0;
	string firstname = "";

	author += ' ';
	for(int i = 0; author.size(); i++)
	{
		if(author[i] == ' ')
			break;
		else
			firstname += author[i];
	}

	transform(title.begin(), title.end(), title.begin(), ::toupper);
    transform(firstname.begin(), firstname.end(), firstname.begin(), ::toupper);

	for(int i = 0; i < title.length(); i++)
	{
		code += title[i]*i;
	}

	for(int i = 0; i < firstname.length(); i++)
	{
		code += firstname[i]*i;
	}

	return code;
}

void insertbook(Book b, int hc)
{
	int index = hc % CAPACITY;
	int counter = 0;

	//while the hashtable at the index is not empty increment index
	while(hashtable[index].getTitle() != "" && counter < CAPACITY)
	{
		index = (index+1) % CAPACITY;
		counter++;
	}
	hashtable[index] = b;

}
//search for a book in the library
void searchbook() //the average case time complexity is O(1) but if all buckets were to be filled except one the time complexity would be O(n)
{
	string title, author;
	int hc = 0;
	int counter = 0;
	bool found = false;

	string firstname = "";
	string aut = "";

	cin.ignore();
	cout << "Please enter the book title. " << endl;
	getline(cin,title);
	//cout << endl;
	cout << "Please enter the first author name. " << endl;
	getline(cin,author);

	author += ' ';
	for(int i = 0; author.size(); i++)
	{
		if(author[i] == ' ')
			break;
		else
			aut += author[i];
	}

	hc = hashcode(title, author);

	int index = hc % CAPACITY;

	transform(title.begin(), title.end(), title.begin(), ::toupper);
    transform(aut.begin(), aut.end(), aut.begin(), ::toupper);

	for(int i = 0; hashtable[index].getAuthor().size(); i++)
	{
		if(hashtable[index].getAuthor()[i] == ' ')
			break;
		else
			firstname += hashtable[index].getAuthor()[i];
	}

    while(hashtable[index].getTitle() != "" && counter < CAPACITY)
    {
         string titlecomp;
         titlecomp = hashtable[index].getTitle();
         transform(titlecomp.begin(), titlecomp.end(), titlecomp.begin(), ::toupper);

         string authorcomp;
         authorcomp = firstname;
         transform(authorcomp.begin(), authorcomp.end(), authorcomp.begin(), ::toupper);
         
        if (titlecomp == title && authorcomp == aut)
        {
             cout << "Book is located at " << hashtable[index].getidentifier() << endl;
             found = true;
             break;
        }

        else
        {
             index = (index+1) % CAPACITY;
             counter++;
        }
    }

	if (found == false)
		cout << "Book not found." << endl;
}
 //add books to the library
 void addbook()
 {
     string title;
     string author;
     string ISBN;
     string year;
     int Num_of_Copies;
     string location;
     string filename;
     string identifier;
     int hc = 0;
     bool space_available = true;
     bool book_exists = false;
     bool shelffound = false;
     int booknumber;
     int noc = 0;

     cin.ignore();
     //validation chcek in remove as well and rearrange as well
     //chcek if book exists on a shelf in that location but space available

     cout << "Enter the book title." << endl;
     getline(cin, title);

     cout << "Enter the book author." << endl;
     getline(cin, author);

     cout << "Enter the book ISBN." << endl;
     getline(cin, ISBN);

     cout << "Enter the publishing year of the book." << endl;
     getline(cin, year);

     cout << "Enter the number of copies to be added." << endl;
     cin >> Num_of_Copies;

     cout << "Enter the location to add the book." << endl;
     cin >> location;

     for (int i = 0; i < CAPACITY; i++)
     {	

         //if shelf is full or num of copies is greater than 10, no more books can be added
        if((hashtable[i].getidentifier()[0] == location[0] && hashtable[i].getidentifier()[1] == location[1] && (int(hashtable[i].getidentifier()[3])) + Num_of_Copies > 10) || Num_of_Copies > 10)
         {
             cout << "Error! Not enough space on shelf." << endl;
             space_available = false;
             break;
         }
         //if book already exists at that location
         if(hashtable[i].getidentifier()[0] == location[0] && hashtable[i].getidentifier()[1] == location[1] && hashtable[i].getidentifier()[3] == location[3])
         {
             book_exists = true;
         }
     }

     //if a book already exists at that location but space available in shelf shift books one step forward
     if (space_available == true)
     {	//char bookcase = location[0];
     	//filename = "Bookcase" + bookcase + ".csv"
     	//loadfile(filename, title, author, ISBN, year, Num_of_Copies);
     	cout << "Book successfully added." << endl;
     	totbooks += Num_of_Copies;
     	//increment the number of books on the shelf
     	for(int i = 0; i < s.size(); i++)
     	{
     		if (s[i].getShelfID()[0] == location[0] && s[i].getShelfID()[1] == location[1]){
     			s[i].setNumofBooks(s[i].getNumofBooks() + Num_of_Copies);
     			shelffound = true;
     			break;
     		}
     	}
 		char firstchar = location[0];
     	int secchar = location[1] - '0';
     	string id = firstchar + to_string(secchar);
     	//if shelf doesnt exist create a new shelf and add books
     	if(shelffound == false)
     		s.push_back(Shelf(id, Num_of_Copies));
         //if book exists in that location
         if (book_exists == true)
         {
             for (int i = 0; i < CAPACITY; i++)
             {
                 //check if same book already exists
                 if(hashtable[i].getTitle()==title && hashtable[i].getAuthor()==author && hashtable[i].getYear()==year && hashtable[i].getISBN()==ISBN)
                     //checK how many copies of that book exist
                     noc++;

                 //update identifiers of subsequent books
                 if(hashtable[i].getidentifier()[0] == location[0] && hashtable[i].getidentifier()[1] == location[1] && int(hashtable[i].getidentifier()[3]) > int(location[3]))
                 {
                     booknumber = int(hashtable[i].getidentifier()[3]);
                     booknumber = booknumber + Num_of_Copies;
                     
                     char shelfletter = hashtable[i].getidentifier()[0];
                     
                     int shelfnumber = 0;
                     shelfnumber = hashtable[i].getidentifier()[1] - '0';
                     
                     //generate an identifier by concatenating a string
                     identifier = shelfletter + to_string(shelfnumber) + "." + (char)booknumber;

                     hashtable[i].setidentifier(identifier);
         
                 }

             }
         } 

         booknumber = int(location[3]);
         for (int i = 0; i < Num_of_Copies; i++)
         {
             //generate an identifier by concatenating a string
            char shelfletter = location[0];
//            cout<< shelfletter<<endl;
             
            int shelfnumber = 0;
            shelfnumber = location[1] - '0';
             
             identifier = shelfletter + to_string(shelfnumber) + "." + (char)booknumber;
//             cout<<(char)booknumber<<endl;
             
             //generate hashcode of every book
             hc = hashcode(title, author);

             //this is where the book is actually added to the system and this occurs in O(1) time
             //the rest of the function are for simply checking if space is available on shelf and making space if not which occur in O(n)
             //make a book object and add it to the hashtable num of copies times
             insertbook(Book(title, author, ISBN, year, Num_of_Copies + noc, identifier), hc);

             booknumber++;
         }

         //update the number of copies of the existing books of the same kind
         for(int i = 0; i < CAPACITY; i++)
         {
             if(hashtable[i].getTitle()==title && hashtable[i].getAuthor()==author && hashtable[i].getYear()==year && hashtable[i].getISBN()==ISBN)
                 hashtable[i].setNum_of_Copies(hashtable[i].getNum_of_Copies()+noc);
         }
     }

 }
//(worst time complexity to remove a book is O(n) as it the worst case is that the book is located at the last index which will take n iterations
 //remove a book from the library
 void removebook() 
 {
     string location = "";
     int booknumber = 0;
     string newidentifier = "";
     string title, author;
     int index = 0;
     bool bookexists = false;


     //no empties shown
     cout << "Enter the book identifier." << endl;
     cin >> location;

     //iterate through hashtable to remove the book with the specifix identifier
    for (int i = 0; i < CAPACITY; i++)
    {
        if (hashtable[i].getidentifier() == location)
        {
             title = hashtable[i].getTitle();
             author = hashtable[i].getAuthor();
             
             hashtable[i].setTitle("");
             hashtable[i].setAuthor("Empty");
             hashtable[i].setYear("Empty");
             hashtable[i].setISBN("Empty");
             hashtable[i].setNum_of_Copies(-1);
             hashtable[i].setidentifier("");

             cout << "Book successfully removed..." << endl;
             totbooks -= 1;
             bookexists = true;
             index = i + 1;
            //decrement the number of books on the shelf
		 	for(int j = 0; j < s.size(); j++)
		 	{
		 		if (s[j].getShelfID()[0] == location[0] && s[j].getShelfID()[1] == location[1])
		 		{
		 			s[j].setNumofBooks(s[j].getNumofBooks() - 1);
		 			bookexists = true;
		 			break;
		 		}
		 	}
             break;
        }
    }
    if (bookexists == false)
    	cout << "Error! The book does not exist." << endl;
    else
    {
	     int temp = hashtable[index].getNum_of_Copies();

	     //decrease the number of copies
	    for(int i = 0; i < CAPACITY; i++)
	    {
		    if(hashtable[i].getTitle() == title && hashtable[i].getAuthor() == author)
		    {
		//       hashtable[index].setNum_of_Copies(hashtable[index-1].getNum_of_Copies() - 1);
		         hashtable[i].setNum_of_Copies(temp - 1);
		         //index = (index+1) % CAPACITY;
		    }
	 	}


	     //update identifiers of subsequent books on the shelf
	     for (int i = 0; i < CAPACITY; i++)
	    {
	        if(hashtable[i].getidentifier()[0] == location[0] && hashtable[i].getidentifier()[1] == location[1] && hashtable[i].getidentifier()[3] > location[3])
	        {
	             booknumber = int(hashtable[i].getidentifier()[3]);
	             booknumber--;
	         
	             char shelfletter = hashtable[i].getidentifier()[0];
	//             cout<< shelfletter<<endl;
	             
	             int shelfnumber = 0;
	             shelfnumber = hashtable[i].getidentifier()[1] - '0';
	                          
	             newidentifier = shelfletter + to_string(shelfnumber) + "." + (char)booknumber;
	             
	             hashtable[i].setidentifier(newidentifier);
	         }
	    }
	}
}


//rearrange the books (O(n) time complexity which is almost as effecient as O(1))
void rearrangebook() 
{	
	 string title;
     string author;
     string ISBN;
     string year;
     int Num_of_Copies;

     string identifier;
     int hc = 0;
     bool space_available = true;
     bool bookexists = false;
     bool book_exists = false;
     int noc = 0;

	 string location = "";
	 string removeID = "";
     int booknumber = 0;
     string newidentifier = "";
     int index = 0;

     //no empties shown
     cout << "Which book would you like to rearrange?" << endl;
     cin >> removeID;

	 //iterate through hashtable to remove the book with the specifix identifier
    for (int i = 0; i < CAPACITY; i++)
    {
        if (hashtable[i].getidentifier() == removeID)
        {
             title = hashtable[i].getTitle();
             author = hashtable[i].getAuthor();
             ISBN = hashtable[i].getISBN();
             year = hashtable[i].getYear();
          	 Num_of_Copies = hashtable[i].getNum_of_Copies(); 
             
             hashtable[i].setTitle("");
             hashtable[i].setAuthor("Empty");
             hashtable[i].setYear("Empty");
             hashtable[i].setISBN("Empty");
             hashtable[i].setNum_of_Copies(-1);
             hashtable[i].setidentifier("");

             bookexists = true;
             index = i + 1;
            //decrement the number of books on the shelf
		 	for(int j = 0; j < s.size(); j++)
		 	{
		 		if (s[j].getShelfID()[0] == removeID[0] && s[j].getShelfID()[1] == removeID[1])
		 		{
		 			s[j].setNumofBooks(s[j].getNumofBooks() - 1);
		 			bookexists = true;
		 			break;
		 		}
		 	}
             break;
        }
    }
    if (bookexists == false)
    	cout << "Error! The book does not exist." << endl;
    else
    {
	     int temp = hashtable[index].getNum_of_Copies();

	     //decrease the number of copies
	    for(int i = 0; i < CAPACITY; i++)
	    {
		    if(hashtable[i].getTitle() == title && hashtable[i].getAuthor() == author)
		    {
		//       hashtable[index].setNum_of_Copies(hashtable[index-1].getNum_of_Copies() - 1);
		         hashtable[i].setNum_of_Copies(temp - 1);
		         //index = (index+1) % CAPACITY;
		    }
	 	}


	     //update identifiers of subsequent books on the shelf
	     for (int i = 0; i < CAPACITY; i++)
	    {
	        if(hashtable[i].getidentifier()[0] == removeID[0] && hashtable[i].getidentifier()[1] == removeID[1] && hashtable[i].getidentifier()[3] > removeID[3])
	        {
	             booknumber = int(hashtable[i].getidentifier()[3]);
	             booknumber--;
	         
	             char shelfletter = hashtable[i].getidentifier()[0];
	//             cout<< shelfletter<<endl;
	             
	             int shelfnumber = 0;
	             shelfnumber = hashtable[i].getidentifier()[1] - '0';
	                          
	             newidentifier = shelfletter + to_string(shelfnumber) + "." + (char)booknumber;
	             
	             hashtable[i].setidentifier(newidentifier);
	         }
	    }
	}

	cout << "Where would you like to place this book?" << endl;
	cin >> location;

     for (int i = 0; i < CAPACITY; i++)
     {	
         //if shelf is full or num of copies is greater than 10, no more books can be added
         if(hashtable[i].getidentifier()[0] == location[0] && hashtable[i].getidentifier()[1] == location[1] && int(hashtable[i].getidentifier()[3]) + Num_of_Copies > 10 || (Num_of_Copies > 10))
         {
             cout << "Error! Not enough space on shelf." << endl;
             space_available = false;
             break;
         }
         //if book already exists at that location
         if(hashtable[i].getidentifier()[0] == location[0] && hashtable[i].getidentifier()[1] == location[1] && hashtable[i].getidentifier()[3] == location[3])
         {
             book_exists = true;
         }
     }

     //if a book already exists at that location but space available in shelf shift books one step forward
     if (space_available == true)
     {
         //if book exists in that location
         if (book_exists == true)
         {
             for (int i = 0; i < CAPACITY; i++)
             {
                 // //check if same book already exists
                 // if(hashtable[i].getTitle()==title && hashtable[i].getAuthor()==author && hashtable[i].getYear()==year && hashtable[i].getISBN()==ISBN)
                 //     //chech how many copies of that book exist
                 //     noc++;

                 //update identifiers of subsequent books
                 if(hashtable[i].getidentifier()[0] == location[0] && hashtable[i].getidentifier()[1] == location[1] && int(hashtable[i].getidentifier()[3]) > int(location[3]))
                 {
                     booknumber = int(hashtable[i].getidentifier()[3]);
                     booknumber = booknumber + Num_of_Copies;
                     
                     char shelfletter = hashtable[i].getidentifier()[0];
                     
                     int shelfnumber = 0;
                     shelfnumber = hashtable[i].getidentifier()[1] - '0';
                     
                     //generate an identifier by concatenating a string
                     identifier = shelfletter + to_string(shelfnumber) + "." + (char)booknumber;

                     hashtable[i].setidentifier(identifier);
         
                 }

             }
         } 

         booknumber = int(location[3]);

         //generate an identifier by concatenating a string
        char shelfletter = location[0];
         
        int shelfnumber = 0;
        shelfnumber = location[1] - '0';
         
         identifier = shelfletter + to_string(shelfnumber) + "." + (char)booknumber;
         
         //generate hashcode of every book
         hc = hashcode(title, author);

         //make a book object and add it to the hashtable num of copies times
         insertbook(Book(title, author, ISBN, year, Num_of_Copies + 1, identifier), hc);

         //update the number of copies of the existing books of the same kind
         for(int i = 0; i < CAPACITY; i++)
         {
             if(hashtable[i].getTitle()==title && hashtable[i].getAuthor()==author && hashtable[i].getYear()==year && hashtable[i].getISBN()==ISBN)
                 hashtable[i].setNum_of_Copies(hashtable[i].getNum_of_Copies()+1);
         }

     }


}
//get the number of books on a shelf (O(n) runtime)
void booksonshelf() 
{
	string location;
	bool shelfexists = false;

	cout << "Enter the shelf identifier." << endl;
	cin >> location;

 	for(int j = 0; j < s.size(); j++)
 	{
 		if (s[j].getShelfID()[0] == location[0] && s[j].getShelfID()[1] == location[1])
 		{
 			cout << "There are " << s[j].getNumofBooks() << " books on the shelf." << endl;
 			shelfexists = true;
 			break;
 		}
 	}
 	if (shelfexists == false)
 			cout << "There are 0 books on the shelf." << endl;
}

//reflect changes in excel files
void loadfile(string filename, string title, string author, string ISBN, string year, int Num_of_Copies)
{
	ofstream outFile(filename);

	if (outFile.fail()) 
	{
		cerr << "Error opening file.\n";
		exit(1);
	}

	outFile << title << ',' << author << ',' << ISBN << ',' << year << ',' << Num_of_Copies;

}


