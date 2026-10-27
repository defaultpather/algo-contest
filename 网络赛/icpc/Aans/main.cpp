#include <bits/stdc++.h>
using namespace std;

int main()
{
    // int expected = 0, verdict = 1;
    // printf("Input number of test cases: ");
    // scanf("%d", &expected);//T
    // for (int test_case = 1; test_case <= expected; test_case++)
    // {
    //     printf("Running on test #%d: ", test_case);
    //     if (!verdict)
    //     {
    //         printf("Skipped\n");
    //         continue;
    //     }
    //     system("gen > data.in");//generate data
    //     system("my < data.in > my.out");//each one cin data from generater
    //     system("brute < data.in > std.out");//too
    //     if (system("fc 1.out 1.ans > 1.log"))
    //     {
    //         printf("WA\n");
    //         verdict = 0;
    //         continue;x   
    //     }
    //     printf("AC\n");
    // }
    // if (verdict)
    //     printf("Verdict: AC\n");
    // else
    //     printf("Verdict: WA\n");
    // return 0;
    int cnt = 0;

    while (cnt<1000)
    {
        cnt++;

        system("gen > data.in");

        system("my < data.in > my.out");

        system("std < data.in > std.out");

        int res = system("fc my.out std.out");

        if (res)
        {
            cout << "Found Wrong Answer!\n";
            cout << "Test : " << cnt << endl;

            cout << "\n===== Input =====\n";
            system("type data.in");

            cout << "\n===== My Output =====\n";
            system("type my.out");

            cout << "\n===== Std Output =====\n";
            system("type std.out");

            break;
        }

        cout << "Accepted on test " << cnt << endl;
    }
}
