#include "block.hpp"

Block::Block(Mino kind, Status status){
    this->kind   = kind;
    this->status = status;
}

Mino Block::get_kind(){
    return this->kind;
}

Status Block::get_status(){
    return this->status;
}

void make_static(){
    this->status = Status::STOP;
}