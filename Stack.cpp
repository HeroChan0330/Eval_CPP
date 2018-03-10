template<typename T>
class Stack{
	private:
		int count;
		int Volume;
		T*Array;
	public:
		Stack(){
			Array=new T[64];
			count=0;
			Volume=64;
		}

	void Push(T num){
		if(count==Volume){
			Volume*=2;
			T*temp=new T[Volume];
			for(int i=0;i<count;i++){
				temp[i]=Array[i];
			}
			delete Array;
			Array=temp;
		}
		Array[count++]=num;
	}

	T Pop(){
		if(count==0)return 0;
			if(count*2==Volume){
			Volume/=2;
			T*temp=new T[Volume];
			for(int i=0;i<count;i++){
				temp[i]=Array[i];
			}
            delete Array;
			Array=temp;
		}

		return Array[--count];
	}
	int Size(){
		return count;
	}

	T Peek(){
	    if(count>0)
            return Array[count-1];
        else return 0;
	}
	bool isEmpty(){
		return (count>0)?0:1;
	}
	/*	void print(){
		printf("\n---stack---\n");
			for(int i=0;i<count;i++){
				printf("index%d: %d\n",i,Array[i]);
			}
				printf("---stack---\n");
		}
	*/
};
