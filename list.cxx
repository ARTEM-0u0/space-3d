template<typename T>
class node
{
	public:
	T data;
	node<T>* next=nullptr;
	node<T>(const T& o):data(o),next(nullptr){}
};
template<typename T>
class list
{
	public:
	int count=0;
	node<T>* top=nullptr;
	~list()
	{
		while(top) {
			node<T>* tmp = top;
			top = top->next;
			delete tmp;
		}
	}
	void add(const T& data)
	{
		node<T>* new_node=new node<T>(data);
		if(top==nullptr)
		{
			top=new_node;
		}else{
			new_node->next=top;
			top=new_node;
		}
		count++;
	}
	void remove(int index)
	{
		if((index<0)||(index>=count))
		{return ;}
		
		node<T>* current=top;
		
		if(index==0){
			top=top->next;
			delete current;
			count--;
		return;}
		
		node<T>* connect=top;
		
		for(int i=0;i<index;i++)
		{
			connect=current;
			current=current->next;
		}
		
		connect->next=current->next;
		delete current;
		count--;
	}
	node<T>* get(int index)
	{
		if((index<0)||(index>=count))
		{return nullptr;}
		node<T>* current=top;
		for(int i=0;i<index;i++)
		{
			current=current->next;
		}
		return current;
	}
	T* get_data(int index)
	{
		if((index<0)||(index>=count))
		{return nullptr;}
		node<T>* current=top;
		for(int i=0;i<index;i++)
		{
			current=current->next;
		}
		return &current->data;
	}
};