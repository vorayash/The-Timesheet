#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define ll long long

struct
{
    string date;
    string time;
    string status;
    long long int tot_sec;
} emp[12];

string secondsToTimeString(long long int seconds)
{
    int hours = seconds / 3600;
    seconds -= hours * 3600;
    int minutes = seconds / 60;
    seconds -= minutes * 60;

    string hoursStr = to_string(hours);
    if (hours < 10)
    {
        hoursStr = "0" + hoursStr;
    }

    string minutesStr = to_string(minutes);
    if (minutes < 10)
    {
        minutesStr = "0" + minutesStr;
    }

    string secondsStr = to_string(seconds);
    if (seconds < 10)
    {
        secondsStr = "0" + secondsStr;
    }

    return hoursStr + ":" + minutesStr + ":" + secondsStr;
}

long long int getTime(string str1, string str2)
{
    lli hour1, minute1, second1;
    lli hour2, minute2, second2;

    hour1 = stoi(str1.substr(0, 2));
    minute1 = stoi(str1.substr(3, 2));
    second1 = stoi(str1.substr(6, 2));

    hour2 = stoi(str2.substr(0, 2));
    minute2 = stoi(str2.substr(3, 2));
    second2 = stoi(str2.substr(6, 2));

    long long int second;

    if (second2 > second1)
    {
        minute1--;
        second1 += 60;
    }

    if (minute2 > minute1)
    {
        hour1--;
        minute1 += 60;
    }

    second = (hour1 - hour2) * 3600 + (minute1 - minute2) * 60 + second1 - second2;
    return second;
}

void output(int Case)
{
    long long int best = 0, worst = 1e8, total = 0, count = 0;

    for (int i = 0; i < 11; i++)
    {
        if (emp[i].date != "")
        {
            if (emp[i].status == "clock-in" || emp[i].status == "break-stop")
            {
                emp[i].tot_sec += min(getTime("17:30:00", emp[i].time), (lli)21600);
            }
            best = max(best, emp[i].tot_sec);
            worst = min(worst, emp[i].tot_sec);
            total += emp[i].tot_sec;
            count++;
        }
    }

    cout << "Case #" << Case << ": " << secondsToTimeString(best) << " " << secondsToTimeString(worst) << " " << secondsToTimeString(total / count) << endl;
}

int main()
{

    freopen("./Dataset/TT_large.txt", "r", stdin);
    freopen("TT_large_output.txt", "w", stdout);

    string temp;
    cin >> temp;
    int n = stoi(temp), Case = 1;

    for (int i = 0; i < n; i++)
    {
        int emp_id;
        string date, time, status;
        cin >> temp >> date >> time >> status;

        emp_id = stoi(temp.substr(4));

        if (emp[emp_id].date != "")
        {
            if (emp[emp_id].date.substr(5, 2) != date.substr(5, 2))
            {
                output(Case++);
                memset(emp, 0, sizeof(emp));
                emp[emp_id].date = date;
                emp[emp_id].time = time;
                emp[emp_id].status = status;
                emp[emp_id].tot_sec = 0;
            }
            else if (date == emp[emp_id].date)
            {
                if (status == "break-start")
                {
                    emp[emp_id].tot_sec += getTime(time, emp[emp_id].time);
                    emp[emp_id].status = status;
                    emp[emp_id].time = time;
                }
                else if (status == "break-stop")
                {
                    emp[emp_id].status = status;
                    emp[emp_id].time = time;
                }
                else if (status == "clock-in")
                {
                    emp[emp_id].status = status;
                    emp[emp_id].time = time;
                }
                else if (status == "clock-out")
                {
                    emp[emp_id].tot_sec += getTime(time, emp[emp_id].time);
                    emp[emp_id].status = status;
                    emp[emp_id].time = time;
                    emp[emp_id].date = date;
                }
            }
            else
            {
                if (emp[emp_id].status == "clock-in" || emp[i].status == "break-stop")
                {
                    emp[emp_id].tot_sec += min(getTime("17:30:00", emp[emp_id].time), (lli)21600);
                    emp[emp_id].status = status;
                    emp[emp_id].time = time;
                    emp[emp_id].date = date;
                }
                else
                {
                    emp[emp_id].status = status;
                    emp[emp_id].time = time;
                    emp[emp_id].date = date;
                }
            }
        }
        else
        {
            emp[emp_id].date = date;
            emp[emp_id].time = time;
            emp[emp_id].status = status;
            emp[emp_id].tot_sec = 0;
        }
    }

    output(Case++);
}
