#include <iostream>
#include <stdio.h>
#include <time.h>
#include <sys/time.h> // gettimeofday

using namespace std;

/* ms */
int64_t GetCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec*1000 + tv.tv_usec/1000;
}

void OutPutCurrentTime()
{
    /* time stamp */
    struct timeval tv;
    gettimeofday(&tv, NULL);
    std::cout << "tv.tv_sec:" << tv.tv_sec << std::endl;
    std::cout << "tv.tv_usec:" << tv.tv_usec << std::endl;

    /* time stamp --> local time */
    struct tm *ptm;
    ptm = localtime(&(tv.tv_sec));
    cout << "year       : "<< ptm->tm_year + 1900 << endl;
    cout << "month      : "<< ptm->tm_mon + 1 << endl;
    cout << "day        : "<< ptm->tm_mday << endl;
    cout << "hour_      : "<< ptm->tm_hour << endl;
    cout << "minute_    : "<< ptm->tm_min << endl;
    cout << "second_    : "<< ptm->tm_sec << endl;

    cout << "millisec_  : "<< tv.tv_usec/1000 << endl;
    cout << "microsec_  : "<< tv.tv_usec%1000 << endl;

    /* format out - use local time */
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", ptm);
    printf("%s\n", time_str);


    time_t rawtime; // == timeval.tv_sec
    time(&rawtime);
    cout << "rawtime    : " << rawtime << endl;


    return;
}

long getTwoGivenTimeDiff()
{
    // given time : 
    // 2019/12/3 9:0:0 (200)
    // 2019/12/3 8:59:58 (200)

    struct tm old_t;
    struct tm new_t;

    new_t.tm_year = 2019;
    new_t.tm_mon = 12;
    new_t.tm_mday = 3;
    new_t.tm_hour = 9;
    new_t.tm_min = 0;
    new_t.tm_sec = 0;

    old_t.tm_year = 2019;
    old_t.tm_mon = 12;
    old_t.tm_mday = 3;
    old_t.tm_hour = 8;
    old_t.tm_min = 59;
    old_t.tm_sec = 58;
    

}

int main()
{
    OutPutCurrentTime();
    std::cout << "nowTime:" << GetCurrentTime() << std::endl;
    return 0;
}