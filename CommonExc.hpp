#pragma once
#include <exception>
#include <string>

class AdditionalInfo
{
private:
    string addInfo;
public:
    explicit AdditionalInfo(string str):
        addInfo(str){}
  
    string info(void) const {
        return addInfo;
    };
    virtual ~AdditionalInfo() {};
};

class OutRange : public exception,  public AdditionalInfo
{
public:
   explicit OutRange(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("Denied access to memory: " + info()).c_str();
    }
};


class MemoryAlloc : public exception, public AdditionalInfo
{
public:
    explicit MemoryAlloc(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("Reserve memory: " + info()).c_str();
    }
};


class EmptyContainer : public exception, public AdditionalInfo
{
public:
     explicit EmptyContainer(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("EmptyContainer: " + info()).c_str(); 
    }
};


class InputFail : public exception, public AdditionalInfo
{
public:
    explicit InputFail(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("InputFail: " + info()).c_str(); 
    }
};


class InfinityValue : public exception, public AdditionalInfo
{
public:
    explicit InfinityValue(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("InfinityValue: " + info()).c_str(); 
    }
};

