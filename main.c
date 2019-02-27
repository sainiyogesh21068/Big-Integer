#include<math.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
//#include"Bigint.h"
typedef int num_type;
typedef struct Bigint_tag
{
  num_type* num;
  int size;
  char sign;
}Bigint;

int sizeOfnum_type();
Bigint get_Big_Integer();
void display_Big_Integer(Bigint ptr);
int sizeof_Bigint(Bigint ptr);
int compare_Big_Integer(Bigint num1,Bigint num2);
Bigint add_Big_Integer(Bigint num1,Bigint num2);
Bigint sub_Big_Integer(Bigint num1,Bigint num2);
Bigint mult_Big_Integer(Bigint num1,Bigint num2);
Bigint intialise(Bigint num);

void main()
{
  system("cls");
  int choice,i=0;
  Bigint x1,x2;
  x1=intialise(x1);
  x2=intialise(x2);
  printf("\n\n\tEnter Number 1 : ");
    x1=get_Big_Integer();
    printf("\n");
  printf("\n\tEnter Number 2 : ");
    x2=get_Big_Integer();
    printf("\n");
  do{
      system("cls");
      printf("\n\tNumber 1:");
      display_Big_Integer(x1);
      printf("\n");
      printf("\tNumber 2:");
      display_Big_Integer(x2);
      printf("\n");
      printf("\n\t\t\t!!!MENU OF OPERATIONS!!!\n");
      printf("\t1.ADD\n\t2.SUBTRACT\n\t3.MULTIPLY\n\t");
      scanf("%d",&choice);
      switch(choice)
      {
        case 1:
                  {
                    Bigint result=add_Big_Integer(x1,x2);
                    display_Big_Integer(result);
                    printf("\n");
                    break;
                  }
        case 2:   {
                    Bigint result=sub_Big_Integer(x1,x2);
                    display_Big_Integer(result);
                    printf("\n");
                    break;
                  }
        case 3:   {
                    Bigint result=mult_Big_Integer(x1,x2);
                    display_Big_Integer(result);
                    printf("\n");
                    break;
                  }
        default :
                  {
                    printf("!!!Choose Valid Option!!!");
                  }
      }
      printf("\nWant some More Operations (0/1)");
      scanf("%d",&i);
    }while(i);
}


int sizeOfnum_type()
{
  int size=sizeof(num_type);
  int length=((int)(size*8*log10(2))+1);
  return length-1;
}

Bigint intialise(Bigint num)
{
  num.size=0;
  num.num=NULL;
  num.sign=' ';
  return num;
}

Bigint get_Big_Integer()
{

  int s=1;
  Bigint ptr;
  ptr.num=(num_type*)malloc(s*sizeof(num_type));
  int x=sizeOfnum_type();
  char word[400];
  if(word[0]=='-')
  {
    ptr.sign='-';
    word[0]='0';
  }
  scanf("%s",&word);
    char* substr=(char*)malloc(sizeof(char)*x);
  int len=strlen(word);
  int i,j;
  int index;
  for(i=len-1; i>=0; i=i-x )
  {

    index=x-1;
    for(j=i; j>i-x && j>-1; j-- )
    {
     substr[index]=word[j];
     index--;
    }
    if(index>=0)
    {
        while(index>=0){
        substr[index]='0';
        index--;
        }
    }
    *(ptr.num+s-1)=atoi(substr);
    s++;
    ptr.num=(num_type*)realloc(ptr.num,(s+1)*sizeof(num_type));
  }
  ptr.size=s-1;
  return ptr;
}

void display_Big_Integer(Bigint ptr)
{
  int i=(ptr.size-1),n;
  int count=0,stop=0;
  int x=sizeOfnum_type();
  if(ptr.sign=='-')
  {
    printf("%c",ptr.sign);
  }
  while(stop==0)
  {
    n=*(ptr.num+i);
    count=0;
    while(n!= 0)
    {
        n /= 10;
        ++count;
    }
    if(count==x)
    {
      stop=1;
    }
    printf("%d",*(ptr.num+i));
    i--;
  }
  while(i>=0)
  {
    if(1)
    {
      n=*(ptr.num+i);
      count=0;
      while(n!= 0)
      {
          // n = n/10
          n /= 10;
          ++count;
      }
      if(count<x)
      {
        while(count<x)
        {
          printf("0");
          count++;
        }
      }
    }
    printf("%d",*(ptr.num+i));
    i--;
  }
}

Bigint add_Big_Integer(Bigint num1,Bigint num2)
{
  int size1=num1.size,size2=num2.size;    //sizes of numbers array;
  long int carry=0,temp_result=0;
  int i=0;                                  //defines size of result
  long int max=pow(10,sizeOfnum_type())+1;  //maximum number a array element can store
  Bigint result;
  result.num=(num_type*)malloc(1*sizeof(num_type));  //result pointer
  while(size1!=0 && size2!=0)
  {
    temp_result=*(num1.num)+*(num2.num)+carry;  //adding the respective elements of array with carry
    if(temp_result>=max)
    {
      carry=1;              //carry cannot be greater than 1
    }
    else{
      carry=0;
    }
    *(result.num+i)=temp_result%max;      //storing the part without carry
    //printf("\n%ld\t%d\t%d + %d = %d\n",temp_result,carry,*(num1.num),*(num2.num),*(result.num+i));
    i++;
    result.num=(num_type*)realloc(result.num,(i+1)*sizeof(num_type));
    num1.num=num1.num+1;
    num2.num=num2.num+1;
    size1--;
    size2--;
  }
  if(size1==0)
  {
      //do the same as above in loop except the num1 will not be considered now
      while(size2!=0){
        temp_result=*(num2.num)+carry;
        if(temp_result>=max)
        {
          carry=1;
        }
        else{
          carry=0;
        }
        *(result.num+i)=temp_result%max;
        i++;
        result.num=(num_type*)realloc(result.num,(i+1)*sizeof(num_type));
        num2.num=num2.num+1 ;
        size2--;
      }
  }
  else
  {
    //do the same as above in loop except the num1 will not be considered now
    while(size1!=0){
      temp_result=*(num1.num)+carry;
      if(temp_result>=max)
      {
        carry=1;
      }
      else{
        carry=0;
      }
      *(result.num+i)=temp_result%max;
      i++;
      result.num=(num_type*)realloc(result.num,(i+1)*sizeof(num_type));
      num1.num=num1.num+1;
      size1--;
    }
  }

  //if the sizes of the array element is equal than there could be an extra carry left at the end of loop

  if(carry==1)
  {
    *(result.num+i)=1;
    i++;
  }

  result.size=i;
  return result;
}
int compare_Big_Integer(Bigint num1,Bigint num2)
{
  int j=1,flag=0;
  int size1=num1.size,size2=num2.size;
  if(size1>size2)
  {
    flag=1;
  }
  else if(size2>size1)
  {
    flag=2;
  }
  else
  {
    do {
      if(*(num1.num+size1-j)>*(num2.num+size2-j))
      {
        flag=1;
      }
      else if(*(num1.num+size1-j)<*(num2.num+size2-j))
      {
        flag=2;
      }
      j++;
    } while((*(num1.num+size1-j)==*(num2.num+size2-j)) && (size1-j)!=0  && flag==0);
  }
  return flag;
}
Bigint sub_Big_Integer(Bigint num1,Bigint num2)
{
  int size1=num1.size,size2=num2.size;    //sizes of numbers array;
  long int carry=0,temp_result=0;
  int i=0;                                  //defines size of result
  long int max=pow(10,sizeOfnum_type())+1;  //maximum number a array element can store
  Bigint l_ptr,s_ptr,result;
  int flag=compare_Big_Integer(num1,num2);
    if(flag==1 || flag==0)
    {
      l_ptr=num1;
      s_ptr=num2;
      size1=l_ptr.size;
      size2=s_ptr.size;
    }
    else if(flag==2)
    {
      l_ptr=num2;
      s_ptr=num1;
      size1=l_ptr.size;
      size2=s_ptr.size;
      result.sign='-';
    }
  result.num=(num_type*)malloc(1*sizeof(num_type));
    //result pointer
  while(size1!=0 && size2!=0)
  {
    temp_result=*(l_ptr.num)-*(s_ptr.num)+carry;  //adding the respective elements of array with carry
    if(temp_result<0)
    {
      temp_result+=max;
      carry=-1;              //carry cannot be greater than 1
    }
    else{
      carry=0;
    }
    *(result.num+i)=temp_result;      //storing the part without carry
    //printf("\n%ld\t%d\t%d - %d = %d\n",temp_result,carry,*(l_ptr.num),*(s_ptr.num),*(result.num+i));
    i++;
    result.num=(num_type*)realloc(result.num,(i+1)*sizeof(num_type));
    l_ptr.num=l_ptr.num+1;
    s_ptr.num=s_ptr.num+1;
    size1--;
    size2--;
  }
  if(size1==0)
  {
      //do the same as above in loop except the l_ptr will not be considered now
      while(size2!=0){
        temp_result=*(s_ptr.num)+carry;  //adding the respective elements of array with carry
        if(temp_result<0)
        {
          temp_result+=max;
          carry=-1;              //carry cannot be greater than 1
        }
        else{
          carry=0;
        }
        *(result.num+i)=temp_result;
        //printf("\n%ld\t%d\t%d - %d = %d\n",temp_result,carry,0,*(s_ptr.num),*(result.num+i));
        i++;
        result.num=(num_type*)realloc(result.num,(i+1)*sizeof(num_type));
        s_ptr.num=s_ptr.num+1;
        size2--;
      }
  }
  else
  {
    //do the same as above in loop except the l_ptr will not be considered now
    while(size1!=0){
      temp_result=*(l_ptr.num)+carry;  //adding the respective elements of array with carry
      if(temp_result<0)
      {
        temp_result+=max;
        carry=-1;              //carry cannot be greater than 1
      }
      else{
        carry=0;
      }
      *(result.num+i)=temp_result;
      //printf("\n%ld\t%d\t%d - %d = %d\n",temp_result,carry,*(l_ptr.num),0,*(result.num+i));
      i++;
      result.num=(num_type*)realloc(result.num,(i+1)*sizeof(num_type));
      l_ptr.num=l_ptr.num+1;
      size1--;
    }
  }
  result.size=i;
  return result;
}

Bigint mult_Big_Integer(Bigint num1,Bigint num2)
{
  int size1=num1.size,size2=num2.size;    //sizes of numbers array;
  unsigned long long int carry=0,temp_result=0;
  int i=0,j,index,shift;                                  //defines size of result
  long int max=pow(10,sizeOfnum_type())+1;  //maximum number a array element can store
  Bigint l_ptr,s_ptr,result,temp,inner_ptr;
  result=intialise(result);
      l_ptr=num1;
      s_ptr=num2;
      size1=l_ptr.size;
      size2=s_ptr.size;
    result.num=(num_type*)malloc((num1.size+num2.size)*sizeof(num_type));
    for(i=0;i<num1.size+num2.size;i++)
    {
      *(result.num+i)=0;
    }
    i=0;
  while(size1!=0)
  {
    //printf("\n%d\n",i);
    inner_ptr=s_ptr;
    size2=s_ptr.size;
    index=i;
    j=0;
    while(size2!=0)
    {
      //printf("\n%d\n",j);
      shift=index+j;
      temp_result=(unsigned long long int)(*(l_ptr.num))*(unsigned long long int)(*(inner_ptr.num))+(unsigned long long int)carry+(unsigned long long int)*(result.num+(shift));
      //printf("\n%llu\t%llu\t%d * %d = %d\n",temp_result,carry,*(l_ptr.num),*(inner_ptr.num),*(result.num+(shift)));
      if(temp_result>=max)
      {
        carry=temp_result/max;
        temp_result=temp_result%max;
      }
      else{
        carry=0;
      }
      *(result.num+(shift))=temp_result;
      //printf("\n%llu\t%llu\t%d * %d = %d\n",temp_result,carry,*(l_ptr.num),*(inner_ptr.num),*(result.num+(shift)));
      j++;
      //result.num=(num_type*)realloc(ptr.num,(j+1)*sizeof(num_type));
      // result.size++;
      inner_ptr.num=inner_ptr.num+1;
      size2--;
    }
    if(carry>0)
    {
        shift++;
      *(result.num+(shift))=carry;
    }
    carry=0;
    i++;
    l_ptr.num=l_ptr.num+1;
    size1--;
  }
  if(carry>0)
  {
    *(result.num+(num1.size+num2.size-1))=carry;
  }
  result.size=num1.size+num2.size;
  if((num1.sign=='-'&& num2.sign==' ') || (num1.sign==' ' && num2.sign=='-'))
  {
    result.sign='-';
  }
  else
  {
    result.sign=' ';
  }
  return result;
}
