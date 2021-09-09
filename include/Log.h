#ifndef LOG_H
#define LOG_H

#include<cstdio>

class Log
{
    public:
        enum Level_enum{
            NONE,    //0
            ERROR,   //1
            WARN,    //2
            ALL      //3
        };
        Log(const char* path);
        ~Log();
        void setLevel(Level_enum level);
        void Warn(const char* description);
        void Error(const char* description);
        void Info(const char* description);
        FILE* logfile;


    protected:

    private:
        Level_enum level;
};

#endif // LOG_H
