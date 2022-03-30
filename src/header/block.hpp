#ifndef BLOCK_HPP__
#define BLOCK_HPP__

//#include "mino.hpp"
//#include "status.hpp"

class Block {
private:
    Mino kind;
    Status status;

public:
    Block(Mino kind, Status status);
    Mino   get_kind();
    Status get_status();
    void   stop();
};

#endif