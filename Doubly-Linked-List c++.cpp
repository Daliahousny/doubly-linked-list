#include<iostream>
using namespace std;

template <class T>
class Node
{
public:
    T data;
    Node<T>* next;
    Node<T>* previous;
};

template <class T>
class linkedList
{
    private:
    Node<T>* first;
    Node<T>* last;
    int Count;

    public:
    linkedList() //default constructor
    {
        first=NULL;
        last=NULL;
        Count=0;
    }
    linkedList(T value , int initial_size) //parametrized constructor
    {
        Count=initial_size;
        first = new Node<T>;
        first->data = value;
        first->next = NULL;
        first->previous = NULL;
        last = first;
        for(int i=0 ; i<Count-1 ; i++)
        {
             Node<T>* newNode = new Node<T>;
             newNode->data = value;
             newNode->next = NULL;
             newNode->previous = NULL;

             first->previous = newNode;
             newNode->next = first;
             first = newNode;
        }
    }
    int Size() const
    {
        return Count;
    }
    bool isEmptyList()
    {
        return first==NULL;
    }

    class Iterator
    {
    private:
        Node<T>* current;
    public:
        Iterator() //default constructor
        {
            current=NULL;
        }
        Iterator(Node<T>* n) //paramtertized constructor
        {
            current=new Node<T>;
            current=n;
        }
        Iterator(const Iterator& itr) //paramtertized constructor
        {
            current=new Node<T>;
            current=itr.current;
        }
        void operator++ (int)
        {
            try
            {
                if(current->next==NULL)
                {
                    string ex="Already reached the end of the list";
                    throw ex;
                }
                else
                {
                    current=current->next;
                }
            }
            catch(string ex)
            {
                cout<<endl<<ex<<endl;
            }
        }
        void  operator-- (int)
        {
            try
            {
                if(current->previous==NULL)
                {
                    string ex="Already at the head of the list";
                    throw ex;
                }
                else
                {
                    current=current->previous;
                }
            }
            catch(string ex)
            {
                cout<<endl<<ex<<endl;
            }
        }

        Node<T>* getCurrent(){
            return current;
        }
        void setCurrent(Node<T>* c){
            current=c;
        }
        bool operator == (const Iterator& itr )
        {
            return(current==itr.current);

        }
        T operator * ()
        {
            return current->data;
        }

    };

    Iterator Begin()
    {
        Iterator temp(first);
        return temp;
    }

    Iterator End()
    {
        Iterator temp (last);
        return temp;
    }

    void Insert(T value , Iterator position)
    {
        Node<T> *newNode=new Node<T>;
        newNode->data=value;
        newNode->next=NULL;
        newNode->previous=NULL;

        if(first==NULL) //list empty
        {
            first=newNode;
            last=newNode;
        }
        else{ //list is not empty
            if (position==first){
                    newNode->next=first;
                    first->previous=newNode;
                    first=newNode;
            }
            else if(position==last){
                last->next=newNode;
                newNode->previous=last;
                last=newNode;
            }
            else{
                Node <T>* temp=position.getCurrent();
                position--;
                position.getCurrent()->next=newNode;
                newNode->next=temp;
            }
        }
        Count++;
    }

    void Insert(T value){
        Count++;
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = NULL;
        newNode->previous = NULL;
        if(first == NULL){
            first = newNode;
            last = newNode;
        }
        else{
            last->next = newNode;
            newNode->previous = last;
            last = newNode;
        }
    }

    linkedList<T>& operator = (linkedList<T> secondList)
    {
        if( first!=NULL ){
            Node<T>* itr;
            while( first != NULL ){
                itr=first;
                first=first->next;
                delete itr;
            }
            last=NULL;
        }
        if(secondList.first==NULL){
            first=NULL;
            last=NULL;
            Count=0;
            return *this;
        }
        else{
            Node<T> *itr = secondList.first;

            while (itr != NULL){
                Insert(itr->data);
                itr=itr->next;
            }
            return *this;
        }
    }

    void print()
    {
        Node<T>* temp = first;
        if(temp==NULL)
        {
            cout<<"Nothing to print the list is empty"<<endl;
        }
        else
        {
            while(temp != NULL)
            {
                cout<<temp->data<<"  ";
                temp=temp->next;
            }
        }
    }

    Iterator Erase(Iterator position)
    {
        if(first==NULL){
            string ex ="The list is empty";
            throw ex;
        }
        else{
            if(position==first){
                Count--;
                if(first==last){
                    delete first;
                    first=last=NULL;
                    string ex ="The list is empty";
                    throw ex;
                }
                else{
                    position++;
                    Node<T>* temp=first;
                    first=first->next;
                    first->previous=NULL;
                    delete temp;
                    return position;
                }
            }
            else if (position==last){
                Count--;
                if(first==last){
                    delete last;
                    first=last=NULL;
                    string ex ="The list is now empty";
                    throw ex;
                }
                else{
                    position++;
                    Node<T>* temp=last;
                    last=last->previous;
                    last->next=NULL;
                    delete temp;
                    string ex ="Already Reached the end of the list";
                    throw ex;
                }
            }
            else{
                Count--;
                Node<T> *temp =position.getCurrent();
                position++;
                temp->next->previous=temp->previous;
                temp->previous->next=temp->next;
                delete temp;
                return position;
            }
        }
    }

    ~linkedList() //destructor
    {
        Node<T>* temp;
        while( first != NULL ){
            temp=first;
            first=first->next;
            delete temp;
        }
        last=NULL;
    }

};

int main()
{
    linkedList<int> List;
    linkedList<int>:: Iterator itr , itr2 ;
    cout<<"Testing insert function:"<<endl;
    List.Insert(4 , List.Begin());
    List.Insert(5,List.Begin());
    List.Insert(6,List.Begin());
    List.Insert(20,List.Begin());
    cout<<"After insertion your list is : ";
    List.print();
    cout<<endl<<"========================================"<<endl;

    itr=List.Begin();
    cout<<endl<<"Testing iterator operator ++"<<endl;
    cout<<"Iterator current position is :  "<<*itr<<endl;
    itr++;
    cout<<"Iterator after first ++ :  "<<*itr<<endl;
    itr++;
    cout<<"Iterator after second ++ :  "<<*itr<<endl;
    cout<<"========================================="<<endl;


    List.Insert(10,itr);
    cout<<endl<<"After inserting at iterator current position : ";
    List.print();

    itr=List.End();
    List.Insert(50,itr);
    cout<<endl<<"After inserting at last position : ";
    List.print();
    cout<<endl<<"=========================================="<<endl;

    cout<<endl<<"Testing iterator operator -- "<<endl;
    itr=List.End();
    cout<<"Iterator current position is :  "<<*itr<<endl;
    itr--;
    cout<<"Iterator after first --  : "<<*itr<<endl;
    itr--;
    cout<<"Iterator after second --  : "<<*itr<<endl;
    cout<<"Your list size is : " << List.Size()<<endl;
    cout<<"============================================="<<endl;


    cout<<endl<<"Testing erase function:"<<endl;
    try{
        itr2=List.Begin();
        itr2++;
        int val= *itr2;
        itr2=List.Erase(itr2);
        cout<<endl<<endl<<"The list after erasing " << val <<" is : ";
        List.print();
        cout<<endl<<"And the iterator now points to : "<< *itr2 <<endl;
    }catch(string ex){
        cout<<ex<<endl;
    }

    try{
        itr=List.Erase(List.Begin());
        cout<<endl<<"The list after erasing first item is : ";
        List.print();
        cout<<endl<<"And the iterator now points to : "<< *itr <<endl;
    }catch(string ex){
        cout<<endl<<ex<<endl;
    }

    try{
        itr=List.Erase(List.End());
    }catch(string ex){
        cout<<"The list after erasing last item is : ";
        List.print();
    }
    cout<<endl<<"Your list size is : " << List.Size() <<endl;
    cout<<endl<<"=============================================="<<endl;

    linkedList<int> list2;
    cout<<endl<<"Testing operator '=' :"<<endl;
    list2= List;
    cout<<"Your list is copied successfully"<<endl;
    cout<<"The new list contains : ";
    list2.print();
    cout<<endl<<"Your list size is : " << list2.Size() <<endl;
    return 0;
}
