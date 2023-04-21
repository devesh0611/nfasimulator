//Name: Devesh Sharma
//Faculty Number: 20COB052
//Enrollment Number: GK5560
#include <iostream>
#include <fstream>
using namespace std;
struct node{
    int vertex;
    bool transition;
    struct node* next;
};
struct Node{
    int vertex;
    struct Node* next;
};
class stack
{
    private:
    Node* head;
    int size;
    public:
    stack():size(0)
    { head=NULL; }
    void push(int vt)
    {
        Node* new_node=(struct Node*)malloc(sizeof(struct Node));
        new_node->vertex=vt;
        if(head==NULL)
        {
            new_node->next=NULL;
            head=new_node;
        }
        else
        {
            new_node->next=head;
            head=new_node;
        }
        size++;
        return;
    }
    void pop()
    {
        if(head==NULL)
        return;
        else
        head=head->next;
        size--;
    }
    int Size()
    {
        return size;   
    }
    int peek()
    {
        if(head==NULL)
        return -1;
        else
        return head->vertex;
        
    }
    void make_empty()
    {
        head=NULL;
    }
    //function to check whether a given node is already present in the stack or not 
    bool check(int vt)
    {
        if(head==NULL)
        return 0;
        else
        {
            Node* ptr=head;
            while(ptr!=NULL)
            {
                if(ptr->vertex==vt)
                return 1;
                ptr=ptr->next;
            }
            return 0;
        }
    }
};
class linked_list{
    private:
    node* head;
    public:
    linked_list()
    { head=NULL; }
    void insert(int vt, bool ty)
    {
        node* new_node=(struct node*)malloc(sizeof( struct node));
        new_node->vertex=vt;
        new_node->transition=ty;
        new_node->next=NULL;
        if(head==NULL)
        head=new_node;
        else
        {
            node* ptr=head;
            while(ptr->next!=NULL)
            ptr=ptr->next;
            ptr->next=new_node;
        }
        return;
    }
    //This function tells us which nodes can be reached on a given character of input string
    //reached nodes are returned in a stack
    stack check(bool tr)
    {
        stack lst;
        node* ptr=head;
        if(ptr==NULL)
        return lst;
        else
        {
            while(ptr!=NULL)
            {
                if(ptr->transition==tr)
                lst.push(ptr->vertex);
                ptr=ptr->next;
            }
        }
        return lst;
    }
    void print_list()
    {
        node* ptr=head;
        if(ptr==NULL)
        cout<<"NULL";
        else
        {
            while(ptr!=NULL)
            {
                cout<<ptr->transition<<" | "<<ptr->vertex<<" ----> ";
                ptr=ptr->next;
            }
            cout<<"NULL";
        }
        return;
    }
    
};

int main()
{
        fstream input_file;
        input_file.open("inpt.txt");
    	int vertices;
		int edges;
	    input_file>>vertices;
		input_file>>edges;
		linked_list nfa[vertices];
		int initial_state, final_state;
	    input_file>>initial_state;
		cout<<"Initial state:"<<initial_state<<endl;
		int n_f; //no of final states
		input_file>>n_f;
		int final_states[n_f];
		for(int i=0; i<n_f; i++)
		{
		    input_file>>final_states[i];
		}
		cout<<"Final States:";
		for(int i=0; i<n_f; i++)
		cout<<final_states[i]<<"  ";
		cout<<endl;
		for(int i=0; i<edges; i++)
		{
		    int in, a, b;
		    input_file>>a>>b>>in;
		    nfa[a].insert(b, in);
		}
	    cout<<"The adjacency list representation of given NFA is given below:"<<endl;
	    for(int i=0; i<vertices; i++)
	    {
	        cout<<i<<"     ";
	        nfa[i].print_list();
	        cout<<endl;
	    }
	   int n; //number of characters in an input string
           cout<<"Enter size of input string:";
	   cin>>n;
	   int input[n];
           cout<<"Enter the space separated input binary string:"; 
	   for(int i=0; i<n; i++)
	   {
	       cin>>input[i];
	   }
	   cout<<"Input String is ";
	   for(int i=0; i<n; i++)
	   cout<<input[i];
	   cout<<endl;
	   input_file.close();
	   stack s; //stack to keep record of reached nodes 
	   int i=0;
	   s.push(initial_state); //initial  state is the first reached node
	   cout<<"Intermediate Steps:"<<endl;
	   while(i<n)
	   {
	       int sz=s.Size();
	       stack st[sz]; //st[0] to st[sz-1] contains all nodes that can reached on given character.
	       for(int j=0; j<sz; j++)
	       {
	          st[j]=nfa[s.peek()].check(input[i]);
	          s.pop();
	       }
	       s.make_empty(); // s is emptied to copy all nodes from st[0] to st[sz-1] to s.
	       cout<<input[i]<<"----------> { ";
           //this for loop will copy the contents of st[0], st[1],...., st[sz-1] to s without repition.
	       for(int j=0; j<sz; j++)
	       {
	           while(st[j].Size()>0)
	          {
	              if(s.check(st[j].peek())==0)
	               {
	                   cout<<st[j].peek()<<" ";
	                   s.push(st[j].peek());
	                   st[j].pop();
	              }
	           }
	          
	       }
	        cout<<"}"<<endl;
	       i++; //i is incremented to carry out same procedure for next character of input string.
	   }
	   int p=0;
       // check whether any of the final state is reached or not and print the output accordingly.
       while(p<n_f)
       {
           if(s.check(final_states[p])==1)
           break;
           p++;
       }
	   if(p==n_f)
	   {
	       cout<<"Since any final state has not been reached."<<endl;
	       cout<<"Input string is rejected by the given NFA"<<endl;
	   }
	   else
	   {
	       cout<<"Since final state "<<final_states[p]<<" has been reached."<<endl;
	       cout<<"Input string is accepted by the given NFA"<<endl;
	   }
    return 0;
}
