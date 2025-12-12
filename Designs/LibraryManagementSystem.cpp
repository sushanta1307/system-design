// Add/Remove Books
// Register new Members
// Borrow/Return Books

#include<iostream>
#include<list>
using namespace std;

class Book {
    string title;
    string author;
    string isbn;
    bool isAvailable;
public:
    Book(string bTitle, string bAuthor, string bIsbn) :
        title(bTitle), author(bAuthor), isbn(bIsbn), isAvailable(true) {}

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    string getIsbn() {
        return isbn;
    }

    bool isBookAvailable() {
        return isAvailable;
    }

    void setAvailabilityStatus(bool status) {
        isAvailable = status;
    }
};

class Member {
    string id;
    string name;
    string email;
    list<Book*> borrowedBooks;
public:
    Member(string mId, string mName, string mEmail) :
        id(mId), name(mName), email(mEmail) {}

    void addBorrowedBook(Book* book) {
        borrowedBooks.push_back(book);
    }

    void removeBorrowedBook(Book* book) {
        borrowedBooks.remove(book);
    }

    string getId() {
        return id;
    }

    string getName() {
        return name;
    }
    string getEmail() {
        return email;
    }
    list<Book*> getBorrowedBooks() {
        return borrowedBooks;
    }

};

class Catalog {
    unordered_map<string, vector<Book*>> booksbyTitle;
    unordered_map<string, vector<Book*>> booksByAuthor;
    unordered_map<string, vector<Book*>> booksByIsbn;
public:
    void add(Book* book) {
        booksbyTitle[book->getTitle()].push_back(book);
        booksByAuthor[book->getAuthor()].push_back(book);
        booksByIsbn[book->getIsbn()].push_back(book);
    }

    vector<Book*> searchByAuthor(string author) {
        return booksByAuthor[author];
    }

    vector<Book*> searchByTitle(string title) {
        return booksbyTitle[title];
    }

    vector<Book*> searchByIsbn(string isbn) {
        return booksByIsbn[isbn];
    }
};

class Loan {
    string id;
    Book* book;
    Member* member;
    long long borrowDate;
    long long dueDate;

    bool isActive = true;
    const int MAX_BORROW_DAYS = 15;
    const int MAX_BOOKS_BORROWED = 3;
public:
    Loan(string lId, Book* b, Member* mem, long long bDate) :
        id(lId), book(b), member(mem), borrowDate(bDate), dueDate(bDate+15) {}

    void closeLoan() {
        //TODO
    }

    string getId() {
        return id;
    }

};

class LibraryManagementSystem {
    unordered_map<string, Member*> members;
    Catalog catalog;
    unordered_map<string, Loan*> loans;
public:

// add book, removebook, borrow book, return book, register member, search by author/title/isbn
    void registerMember(string id, string name, string email) {
        members[id] = new Member(id, name, email);
    }

    void addBook(string title, string author, string isbn) {
        catalog.add(new Book(title, author, isbn));
    }

    vector<Book*> searchByAuthor(string author) {
        return catalog.searchByAuthor(author);
    }

    vector<Book*> searchByTitle(string author) {
        return catalog.searchByTitle(author);
    }

    vector<Book*> searchByIsbn(string author) {
        return catalog.searchByIsbn(author);
    }

    void borrowABook(string loanId, string memberName, string bookTitle) {
        // check eligibilty
        // curr timestamp is 100
        
        // loans[loanId] = new Loan(loanId, catalog.searchByTitle(), members[memberName], 100L);
    }

};