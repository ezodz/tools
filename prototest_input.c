#include <stdio.h>


#define SPCH_NUM 11

char spch[SPCH_NUM]={'a','b','f','n','r','t','v','\\','\'','\"','0'};


//one char to a number
int hex2i(char c)
{
    int ret;
    if(c>='0' && c<='9')
        ret=c-'0';
    else if(c>='a' && c<='z')
        ret=c-'a'+10;
    else if(c>='A' && c<='Z')
        ret=c-'A'+10;
    else
        ret=-1;
    return ret;
}


//0 normal; 1 \+EOF fill 0: -1 overflow or unsupport fill -1
int special(char* des, int i, int length)
{
    char buf;
    int index=-1;

    int ten=0;
    int one=0;
    int sum=0;
    do
    {
        buf=getchar();
    }
    while(buf=='\n');

    if (buf=='x')
    {
        buf=getchar();
        ten=hex2i(buf);
        if(ten==-1)
        {
            des[i]=-1;
            return -1;
        }
        ten*=16;
        ten+=hex2i(buf);
        buf=getchar();
        one=hex2i(buf);
        if(one==-1)
        {
            des[i]=-1;
            return -1;
        }
        sum=ten+one;
        ((unsigned char*)des)[i]=(unsigned char)sum;
        return 0;
    }
    else if(buf==-1)
    {
        des[i]=0;
        return 1;
    }
    
    
    switch (buf)
    {
        case 'a':
            des[i]='\a';
            break;
        case 'b':
            des[i]='\b';
            break;
        case 'f':
            des[i]='\f';
            break;
        case 'r':
            des[i]='\r';
            break;
        case 'n':
            des[i]='\n';
            break;
        case 't':
            des[i]='\t';
            break;
        case 'v':
            des[i]='\v';
            break;
        case '\\':
            des[i]='\\';
            break;
        case '0':
            des[i]='\0';
            break;
        case '\'':
            des[i]='\'';
            break;
        case '\"':
            des[i]='\"';
            break;
        default:
            des[i]=-1;
            return -1;
    }
    return 0;


}



//max length
int getinput(char* des, int length)
{
    char buf;
    int i=0;
    int ret;
    for(i=0; i<=length-1; i++)
    {
        buf=getchar();

        //these don't need to check i
        if(buf==-1)
        {
            des[i]=0;
            break;
        }
        else if(buf=='\n')
        {
            i-=1;
            continue;
        }
        //these two need to check i
        else if(buf=='\\')
        {
            //currently des[i] is not written
            ret=special(des, i, length);
            //des[i] is just filled 
            if(ret == 1)
            {
                //des[i]='\0', and there is no '\' in the end
                return i;
            }
            if(ret==-1)
                return -1;
        }
        else
            des[i]=(char)buf;
    }

    if(i==length && des[i-1] != 0)
        return -1;
    return i;

}

int main()
{
    char test[256];
    getinput(test, 256);
    printf("%s",test);
    return 0;
}
    
