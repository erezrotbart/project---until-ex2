// IMenuFormat.h
#ifndef IMENUFORMAT_H
#define IMENUFORMAT_H

class IMenuFormat {
public:
    virtual ~IMenuFormat() {}
    virtual void printMenuFormat() = 0;
};

#endif // IMenuFormat_H