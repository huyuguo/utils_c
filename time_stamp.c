#include <stdio.h>
#include <time.h>

int days_before_this_year(int year) 
{
    int total_days = 0;
    for (int i = 1970; i < year; ++i)
    {
        if (((i%4)==0&&(i%100)!=0) || (i%400)==0)
        {
            total_days += 366;
        } 
        else 
        {
            total_days += 365;
        }
    }

    return total_days;
}

int seconds_of_this_year(int year, int month, int day, int hour, int minute, int second)
{
    int total_days = 0;
    for (int i = 1; i < month; ++i)
    {
        switch(i){
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            total_days += 31;
            break;
            case 4: case 6: case 9: case 11:
            total_days += 30;
            break;
            case 2:
            if (((year%4)==0&&(year%100)!=0) || year%400==0)
            {
                total_days += 29;
            } 
            else 
            {
                total_days += 28;
            }
            break;
        }
    }
    total_days += day - 1;
    return total_days*24*3600 + hour*3600 + minute * 60 + second;
}

int time_stamp(int year, int month, int day, int hour, int minute, int second)
{
    return days_before_this_year(year)*24*3600 + seconds_of_this_year(year, month, day, hour, minute, second) - 8*3600;
}

int main(int argc, char const *argv[])
{
    // 获取当前系统时间 年-月-日 时:分:秒
    time_t nowtime;
    struct tm *timeinfo;
    time( &nowtime );

    timeinfo = localtime( &nowtime );
    int year, month, day, hour, minute, second;
    year = timeinfo->tm_year + 1900;
    month = timeinfo->tm_mon + 1;
    day = timeinfo->tm_mday;
    hour = timeinfo->tm_hour;
    minute = timeinfo->tm_min;
    second = timeinfo->tm_sec;

    printf("%d-%d-%d %d:%d:%d\n", year, month, day, hour, minute, second);  // 2016-8-18 14:50:36
    printf("timeStamp = %d\n", time_stamp(year, month, day, hour, minute, second));
    return 0;
}