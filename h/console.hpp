#ifndef _console_hpp_
#define _console_hpp_

#include "../h/my_buffer.hpp"

class Console{
public:

    static Console& getInstance(){
        static Console instance;
        return instance;
    }

    Console(const Console&) = delete;
    void operator=(Console const&) = delete;

    void put_in_input(char c);
    char get_from_input();
    void put_in_output(char c);
    char get_from_output();
    int get_output_size(){ return output_buffer->getCnt(); }
    int get_input_size(){ return input_buffer->getCnt(); }
private:

    Console();

    MyBuffer* input_buffer;
    MyBuffer* output_buffer;
};

#endif