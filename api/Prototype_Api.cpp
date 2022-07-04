#include<iostream>
using namespace std;

int main()
{
    cout<<"Content-type:text/html\r\n\r\n";

    // For get request
    cout<<"Return String is "<<getenv("QUERY_STRING");

    // For post request
    int len;
    char* lenstr = getenv("CONTENT_LENGTH");


    if(lenstr != NULL &&(len = atoi(lenstr)) !=0)
    {
        char *post_data = new char[len];
        fgets(post_data,len+1,stdin);

        cout<<len<<endl<<post_data;
    }


    return 0;
}