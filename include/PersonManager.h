#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H

#include <string>

class Library;

class PersonManager {
public:
    PersonManager(Library& library) : library(library) {}
    void addPerson(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& gender, const std::string& phoneNumber);
    void deletePerson(const std::string& reader_id);
    void searchPerson(const std::string& phoneNumber);
    void updatePerson(const std::string& reader_id, const std::string& newEmail, const std::string& newPhoneNumber, const std::string& last_name);
private:
    Library& library;
};

#endif // PERSONMANAGER_H

