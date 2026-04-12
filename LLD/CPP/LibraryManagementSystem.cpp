#include<iostream>
#include<chrono>
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
    const int MAX_BOOKS = 5;
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

    bool canBorrow() {
        return borrowedBooks.size() < MAX_BOOKS;
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

class Transaction {
    string id;
    Book* book;
    Member* member;
    string borrowDate;
    string dueDate;
    bool isActive = true;
public:
    Transaction(string lId, Book* b, Member* mem) :
            id(lId), book(b), member(mem) {
        auto now = chrono::system_clock::now();
        auto tt = chrono::system_clock::to_time_t(now);
        borrowDate = ctime(&tt);

        long long days = 5;
        std::chrono::hours hours_to_add(24 * days); // explicit hours type
        std::chrono::system_clock::time_point future = now + hours_to_add;

        std::time_t tt_future = std::chrono::system_clock::to_time_t(future);
        dueDate = ctime(&tt_future);
    }

    string getId() {
        return id;
    }

    Book* getBook() {
        return book;
    }

    Member* getMember() {
        return member;
    }

};

class LibraryManagementSystem {
    unordered_map<string, Member*> members;
    Catalog catalog;
    unordered_map<string, Transaction*> transactions;

    int transactionIdCounter = 0;
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

    void borrowABook(string memberName, string bookTitle) {
        Member* member = members[memberName];

        if(!member or !member->canBorrow()) return;
        
        for(auto &book: catalog.searchByTitle(bookTitle)) {
            if(!book->isBookAvailable()) continue;

            string transactionId = "l" + to_string(transactionIdCounter++);

            transactions[transactionId] = new Transaction(transactionId, book, member);
            book->setAvailabilityStatus(false);
            member->addBorrowedBook(book);
        }
    }

    void returnBook(string memberName, Book* book) {
        Member* member = members[memberName];

        if(!member or !book) return;
        auto books = member->getBorrowedBooks();

        auto it = find(books.begin(), books.end(), book);

        if(it == books.end()) return;

        book->setAvailabilityStatus(true);
        member->removeBorrowedBook(book);

        string loanId = "";

        for(auto &[_, transaction]: transactions) {
            if(transaction->getBook() == book and transaction->getMember() == member) {
                loanId = transaction->getId();
                break;
            }
        }

        transactions.erase(loanId);
    }

};