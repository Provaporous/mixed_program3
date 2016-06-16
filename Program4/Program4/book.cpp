#include <iostream>
#include "book.h"
using namespace std;



Book::Book()
{

}
// default constructor, sets up blank book object

void Book::Set(const char* t, const char* a, Genre g, double p)
{

}

const char* Book::GetTitle() const	// returns the title stored in the object
{
	return title;
}
const char* Book::GetAuthor() const	// returns the author
{
	return author;
}
double Book::GetPrice() const		// returns the price
{
	return price;
}
Genre Book::GetGenre() const		// returns the genre
{
	return type;
}
void Book::Display() const			// described below
{

}