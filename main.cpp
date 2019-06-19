
#include <iostream>
#include "log.h"

using namespace wz;

void test1()
{
    while(true)
    {
        log::debug("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
        log::info("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
        log::warn("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
        log::error("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
        log::fatal("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
    }
}

void test2()
{
    int i = 1;
    while(i)
    {
        if(++i == 500)
        {
            i = 0;
        }
        log::debug("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
        log::info("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
        log::warn("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
        log::error("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
        log::fatal("aa%dbb%dcc%xdd%cee%.10f",10,(long)1234567890,10,'A',654.321);
    }
}

int main(int argc,char** argv)
{
    printf("----------Log Test-------------\n");

    test1();

    // test2();

    return 0;
}
