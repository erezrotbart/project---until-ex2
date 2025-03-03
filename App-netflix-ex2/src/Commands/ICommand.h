// ICommand.h
#ifndef ICOMMAND_H
#define ICOMMAND_H

class ICommand {
public:
    virtual ~ICommand() {}
    virtual void Execute() = 0;
};

#endif // ICOMMAND_H