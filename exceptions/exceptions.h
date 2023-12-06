//
// Created by HUAWEI on 06.12.2023.
//

#ifndef MAINSOLUTION_EXCEPTIONS_H
#define MAINSOLUTION_EXCEPTIONS_H
#include <exception>

using namespace std;

class NotUniqueAchievementException : public exception{
private:
    char * message;

public:
    explicit NotUniqueAchievementException(char *message) : message(message) {}

    char * what () {
        return message;
    }
};
#endif //MAINSOLUTION_EXCEPTIONS_H
