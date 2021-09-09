#include "Log.h"

Log::Log(const char* path)
{
    setLevel(ALL);
    logfile = fopen(path,"w");
}

Log::~Log()
{
    fclose(logfile);
}

void
Log::setLevel(Level_enum level){
    this->level = level;
}

void
Log::Warn(const char* description){
    if(level >= WARN){
        fprintf(logfile,"[WARN]:%s\n",description);
        fprintf(stderr ,"[WARN]:%s\n",description);
    }
}
void
Log::Error(const char* description){
    if(level >= ERROR){
        fprintf(logfile,"[ERROR]:%s\n",description);
        fprintf(stderr ,"[ERROR]:%s\n",description);
    }
}
void
Log::Info(const char* description){
    if(level == ALL){
        fprintf(logfile,"[INFO]:%s\n",description);
        fprintf(stderr ,"[INFO]:%s\n",description);
    }
}
