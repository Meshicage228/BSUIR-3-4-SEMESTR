#ifndef MAINSOLUTION_EXCEPTIONS_H
#define MAINSOLUTION_EXCEPTIONS_H
#include <exception>

using namespace std;
class EmptyWhareHouseException : public exception{
private:
    char * message;

public:
    explicit EmptyWhareHouseException(char *message) : message(message) {}

    char * what () {
        return message;
    }
};
class NotEnogthMoneyException : public exception{
private:
    char * message;

public:
    explicit NotEnogthMoneyException(char *message) : message(message) {}

    char * what () {
        return message;
    }
};
class NegativeNumberException : public exception{
private:
    char * message;

public:
    explicit NegativeNumberException(char *message) : message(message) {}

    char * what () {
        return message;
    }
};
class EmptyBusketException : public exception{
private:
    char * message;

public:
    explicit EmptyBusketException(char *message) : message(message) {}

    char * what () {
        return message;
    }
};
#endif
