#include <vector>
struct Document;
// struct IMachine{
//     virtual void print(std::vector<Document*> docs) = 0;
//     virtual void scan(std::vector<Document*> docs) = 0;
//     virtual void fax(std::vector<Document*> docs) = 0;
// };
// struct MFP : IMachine{
//     virtual void print(std::vector<Document*> docs) override;
//     virtual void scan(std::vector<Document*> docs) override;    
//     virtual void fax(std::vector<Document*> docs) override;
// };
struct IPrinter {
    virtual void print(std::vector<Document*> docs) = 0;
};
struct IScanner{
    virtual void scan(std::vector<Document*> docs) = 0;
};
struct Printer : IPrinter{
    virtual void print(std::vector<Document*> docs) override;
};
struct Scanner : IScanner{
    virtual void scan(std::vector<Document*> docs) override;
};

struct IMachine : IPrinter, IScanner {};
// Decorator Pattern
struct Machine : IMachine {
    IPrinter &printer;
    IScanner &scanner;
    Machine(IPrinter &printer, IScanner &scanner) : printer(printer),scanner(scanner){};
    void print(std::vector<Document*> documents) override;
    void scan(std::vector<Document*> documents) override;
};