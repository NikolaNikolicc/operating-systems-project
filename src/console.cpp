
#include "../h/console.hpp"

Console::Console() {
    input_buffer = new MyBuffer(1024);
    output_buffer = new MyBuffer(1024);
}

void Console::put_in_input(char c){
    input_buffer->put(c);
}

char Console::get_from_input(){
    return (char)input_buffer->get();
}

void Console::put_in_output(char c){
    output_buffer->put(c);
}
char Console::get_from_output(){
    return (char)output_buffer->get();
}