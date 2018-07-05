#include "PyInterpreter.h"

int main(int argc,char** argv){
    PyInterpreter* interpreter=new PyInterpreter(argc,argv);
    interpreter->exec();

    return 0;
}
