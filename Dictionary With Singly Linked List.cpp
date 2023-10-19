#include <iostream>
using namespace std;

class Distionary
{
protected:
	class Node_for_word
    {
    public:
        string word;
        string meaning;
        Node_for_word* Next_word;

        Node_for_word(string word, string meaning)
        {
            this->word = word;
            this->meaning = meaning;
            Next_word = NULL;
        }
    };
    
    class Node_for_alphabet
    {
    public:
        string alphabet;
        Node_for_word* word;
        Node_for_alphabet* Next_alphabet;

        Node_for_alphabet(string alphabet)
        {
            this->alphabet = alphabet;
            word = NULL;
            Next_alphabet = NULL;
        }
    };
    
    class Stack_for_Alphabet
    {
    private:
        Node_for_alphabet* top;

    public:
         Stack_for_Alphabet()
        {
            top = NULL;
        }

    void Push(Node_for_alphabet* alphabetNode)
{
    Node_for_alphabet* newNode = new Node_for_alphabet(alphabetNode->alphabet);
    newNode->word = alphabetNode->word;

    if (top == NULL)
    {
        top = newNode;
    }
    else
    {
        newNode->Next_alphabet = top;
        top = newNode;
    }
}

        Node_for_alphabet* Pop()
{
    if (top == NULL)
    {
        cout << "Stack is empty. Cannot pop." << endl;
        return NULL;
    }

    Node_for_alphabet* poppedNode = top;
    top = top->Next_alphabet;
    poppedNode->Next_alphabet = NULL;
    return poppedNode;
}

        bool IsEmpty()
        {
            return top == NULL;
        }
    };
    
    

    Stack_for_Alphabet stack_alphabet;
   

public:
	Node_for_alphabet* head;
    Distionary()
    {
        head = NULL;
    }

    void Insertion_at_alphabet(string alphabet)
    {
        Node_for_alphabet* new_alphabetnode = new Node_for_alphabet(alphabet);
        if (head == NULL)
        {
            head = new_alphabetnode;
        }
        else
        {
            Node_for_alphabet* temp = head;
            while (temp->Next_alphabet != NULL)
            {
                temp = temp->Next_alphabet;
            }
            temp->Next_alphabet = new_alphabetnode;
        }
    }


void Add_word_atlast(string word, string meaning, Node_for_alphabet* current_alphabet)
{
    Node_for_word* current = current_alphabet->word;
    Node_for_word* newword = new Node_for_word(word, meaning);

    if (current == NULL)
    {
        current_alphabet->word = newword;
        return;
    }

    while (current->Next_word != NULL)
    {
        current = current->Next_word;
    }
    current->Next_word = newword;
}

 void Insertion_for_word(string alphabet, string word, string meaning)
{
    Node_for_alphabet* temp = head;
    while (temp != NULL)
    {
        if (temp->alphabet == alphabet)
        {
            break;
        }
        temp = temp->Next_alphabet;
    }
	if (temp == NULL)
    {
        cout << "Alphabet '" << alphabet << "' does not exist. You can add it first." << endl;
        return;
    }
    
    Node_for_word* newword = new Node_for_word(word, meaning);
    Node_for_word* current = temp->word;
    Node_for_word* previous = NULL; 

    while (current != NULL)
    {
        if (current->word == word)
        {
            cout << "Word Already Exists." << endl;
            cout << "Meaning of that word is: " << current->meaning << endl;
            cout << "If you want to add this word again, enter 'yes': ";
            string yes_or_no;
            cin >> yes_or_no;
            if (yes_or_no == "yes")
            {
                Add_word_atlast(word, meaning, temp);
                return;
            }
            else
            {
                return;
            }
        }

        previous = current; 
        current = current->Next_word;
    }

	Add_word_atlast(word,meaning,temp);

}

	bool  Search_for_word(string alphabet,string word)
	{
		if(head==NULL)
		{
			cout << "Alphabet " << alphabet << " does not exist."  << endl;
			return false;
		}
		Node_for_alphabet*current=head;
		
		while(current!=NULL)
		{
			if(current->alphabet==alphabet)
			{
				break;
			}
			else
			{
				current=current->Next_alphabet;
			}
		}
		
		Node_for_word* temp=current->word;
		while(temp!=NULL)
		{
			if(temp->word==word)
			{
				cout<<"Word Exist in dictionary "<<endl;
				cout<<"Word is"<<word<<" Meaning: "<<temp->meaning<<endl;
				return true;
			}
			else
			{
				temp=temp->Next_word;
			}
		}
		return false;
	}
	
void Delete_word(string alphabet,string word)
{
    if (head == NULL)
    {
        cout << "There is no linked list available." << endl;
        return;
    }

    Node_for_alphabet* temp = head;
    while (temp != NULL)
    {
        if (temp->alphabet == alphabet)
        {
            break;
        }
        else
        {   
            temp = temp->Next_alphabet;
        }
    }

    if (temp == NULL)
    {
        cout << "Alphabet not found." << endl;
        return;
    }

    Node_for_word* current = temp->word;
    Node_for_word* previous_word = NULL;

    while (current != NULL)
    {
        if (current->word == word)
        {
            if (previous_word == NULL)
            {
                temp->word = current->Next_word;
            }
            else
            {
                previous_word->Next_word = current->Next_word;
            }
            delete current;
            return;
        }
        else
        {
            previous_word = current;
            current = current->Next_word;
        }
    }
    cout << "Word not found in the specified alphabet." << endl;
}
	
	void Print_Dictionary()
	{
		if(head==NULL)
		{
			cout<<"No linked lsit available "<<endl;
		}
		Node_for_alphabet* current = head;
		if(current==NULL)
		{
			cout<<"No alphabetic is available "<<endl;
			return;
		}
		while(current!=NULL)
		{
			Node_for_word* temp=current->word;
			if(temp==NULL)
			{
				cout<<"No word exist for Alphabet "<<current->alphabet<<endl;
				current=current->Next_alphabet;
				continue;
			}
			cout<<"Words of alphabet "<<current->alphabet<<" are"<<endl;
			while(temp!=NULL)
			{
				cout<<temp->word<<"->";
				temp=temp->Next_word;
			}
			cout<<"Null"<<endl;
			current=current->Next_alphabet;	
		}
	}
	
	void Recursion_PrintDictionary(Node_for_alphabet* current)
{
    if (current == NULL)
    {
        return;
    }

    if (current->Next_alphabet != NULL)
    {
        Recursion_PrintDictionary(current->Next_alphabet);
    }

    Node_for_word* temp = current->word;

    if (temp == NULL)
    {
        cout << "No words available for alphabet '" << current->alphabet << "'." << endl;
        return;
    }

    cout << "Words for alphabet '" << current->alphabet << "':" << endl;
    while (temp != NULL)
    {
        cout << temp->word << "->";
        temp = temp->Next_word;
    }
    cout << "NULL" << endl;
}
	
void PrintDictionaryInReverse()
{
	if (head == NULL)
    {
        cout << "The dictionary is empty." << endl;
        return;
    }

    Node_for_alphabet* current = head;
    cout << "Dictionary (from last to first):" << endl;

    while (current != NULL)
    {
        stack_alphabet.Push(current);
        current = current->Next_alphabet;
    }

    while (!stack_alphabet.IsEmpty())
    {
        Node_for_alphabet* alphabetNode = stack_alphabet.Pop();
        cout << "Words of alphabet " << alphabetNode->alphabet << " are:" << endl;
        Node_for_word* temp = alphabetNode->word;
        
        while (temp != NULL)
        {
            cout << temp->word << "->";
            temp = temp->Next_word;
        }
        cout << "NULL" << endl;
    }
}
	void Display_Alphabet()
    {
    	if (head == NULL)
    {
        cout << "The dictionary is empty." << endl;
        return;
    }
        Node_for_alphabet* current = head;
        while (current != NULL)
        {
            cout << current->alphabet << "->";
            current = current->Next_alphabet;
        }
        cout <<"NULL"<< endl;
    }
    
    void Display_word(string alphabet)
    {
    	if (head == NULL)
	{
    	cout << "The dictionary is empty." << endl;
    	return;
	}
    	Node_for_alphabet* current=head;
    	while(current!=NULL)
    	{
    		if(current->alphabet==alphabet)
    		{
    			break;
			}
			else
			{
				current=current->Next_alphabet;
			}
		}
		Node_for_word* temp=current->word;
		cout<<"Alphabet "<<current->alphabet<<" Words are "<<endl;
		while(temp !=NULL)
		{
			cout<<temp->word<<"->";
			temp=temp->Next_word;
		}
		cout<<"Null"<<endl;
	}
	
	void Display_wordandMeaning(string alphabet)
    {
    	if (head == NULL)
	{
    	cout << "The dictionary is empty." << endl;
    	return;
	}
    	Node_for_alphabet* current=head;
    	
    	while(current!=NULL)
    	{
    		if(current->alphabet==alphabet)
    		{
    			break;
			}
			else
			{
				current=current->Next_alphabet;
			}
		}
		if(current==NULL)
    	{
    		cout<<"specific alphabet"<<current->alphabet<<" doesnot exists "<<endl;
    		return;
		}
		Node_for_word* temp=current->word;
		if(temp==NULL)
		{
			cout<<"No words exists for alphabets "<<current->alphabet<<endl;
    		return;
		}
		
		cout<<"Alphabet "<<current->alphabet<<" Words And Meaning are "<<endl;
		while(temp !=NULL)
		{
			cout<<temp->word<<"->"<<temp->meaning<<endl;
			temp=temp->Next_word;
		}

	}
	
	void Delete_meaning(string alphabet,string word,string meaning)
{
    if (head == NULL)
{
    cout << "The dictionary is empty." << endl;
    return;
}

    Node_for_alphabet* temp = head;
    while (temp != NULL)
    {
        if (temp->alphabet == alphabet)
        {
            break;
        }
        else
        {   
            temp = temp->Next_alphabet;
        }
    }

    if (temp == NULL)
    {
        cout << "Alphabet not found." << endl;
        return;
    }

    Node_for_word* current = temp->word;
    Node_for_word* previous_word = NULL;

    while (current != NULL)
    {
        if (current->word == word && current->meaning==meaning)
        {
            if (previous_word == NULL)
            {
                temp->word = current->Next_word;
            }
            else
            {
                previous_word->Next_word = current->Next_word;
            }
            delete current;
            return;
        }
        else
        {
            previous_word = current;
            current = current->Next_word;
        }
    }
    cout << "Meaning of that word not found in the specified alphabet." << endl;
}
	
	void Display_meaning_ofwords(string alphabet,string word)
    {
    	if (head == NULL)
	{		
    cout << "The dictionary is empty." << endl;
    return;
	}
    	Node_for_alphabet* current=head;
    	while(current!=NULL)
    	{
    		if(current->alphabet==alphabet)
    		{
    			break;
			}
			else
			{
				current=current->Next_alphabet;
			}
		}
		
		if(current==NULL)
		{
			cout<<"Specific alphabet is not exist ";
			return;
		}
		
		Node_for_word* temp=current->word;
		if(temp==NULL)
		{
			cout<<"No word exist for  "<<current->alphabet<<endl;
			return;
		}
		cout<<"Alphabet "<<current->alphabet<<" All meaning of "<<word<<endl;
		while(temp!=NULL)
		{
			if(temp->word==word)
			{
				cout<<word<<" Meaning is "<<temp->meaning<<endl;
			}
			temp=temp->Next_word;
		}
		
		cout<<"This is all meaning of "<<word<<endl;
		cout<<"Which meaning do you want to delete."<<endl;
		cout<<"Enter that meaning ";
		string meaning;
		cin>>meaning;
		
		temp=current->word;
		while(temp!=NULL)
		{
			if(temp->meaning==meaning)
			{
				Delete_meaning(current->alphabet,temp->word,temp->meaning);
				break;
			}
			temp=temp->Next_word;
		}
		
	}
double CalculateAverageSearchTime()
{
	if (head == NULL)
{
    cout << "The dictionary is empty." << endl;
    return 0.0;
}
    double totalJumps = 0.0;
    double totalWords = 0.0;

    Node_for_alphabet* currentAlphabet = head;

    
    if (currentAlphabet == NULL)
    {
        cout << "No words found in the dictionary." << endl;
        return 0.0;
    }

    while (currentAlphabet != NULL)
    {
        Node_for_word* currentWord = currentAlphabet->word;

        while (currentWord != NULL)
        {
            Node_for_word* wordTraversal = currentWord; 

            totalJumps += 1.0; 

            while (wordTraversal->Next_word != NULL)
            {
                totalJumps += 1.0;
                wordTraversal = wordTraversal->Next_word; 
            }

            totalWords += 1.0; 

            currentWord = currentWord->Next_word; 
        }

        currentAlphabet = currentAlphabet->Next_alphabet; 
    }
	cout<<"Total Jumps"<<totalJumps<<endl;
	cout<<"Total words"<<totalWords<<endl;
    double averageSearchTime = totalJumps / totalWords;
    return averageSearchTime;
}

};





class Linked_List:public Distionary
    {
    	private:
    		Node_for_word* Head;
    	public:
    		Linked_List()
    		{
    			Head=NULL;
			}
			
			void Insert(string word, string meaning)
		{
    		Node_for_word* newNode = new Node_for_word(word, meaning);
    		if (Head == NULL)
    		{
       			 Head = newNode;
    		}
    		else
    		{
        		Node_for_word* current = Head;
        		while (current->Next_word != NULL)
        			{
            			current = current->Next_word;
        			}
        			current->Next_word = newNode;
    		}
		}
		
		void displayLinkedList() 
		{
    		Node_for_word* current = Head; 
			if (current == NULL) {
        	cout << "Linked list is empty." << endl;
        	return;
   		 }
    		while (current != NULL) 
			{
        		cout << current->word << " -> ";
        		current = current->Next_word;
    		}
    		cout << "NULL" << endl;	
    	}
    
    bool searchWord(string word) 
	{
		
    	Node_for_word* current = Head;
    	if (current == NULL) 
		{
        cout << "Linked list is empty. Word not found: " << word << endl;
        return false;
    	}

    	while (current != NULL) 
		{
        	if (current->word == word) 
			{
            	cout << "Word found: " << word << " -> " << current->meaning << endl;
            	return true;  
        	}
        current = current->Next_word;
    	}
    cout << "Word not found: " << word << endl;
    return false;  
	}
	
	void copy_allwords(Node_for_alphabet* distionaryHead) 
	{
		if (distionaryHead == NULL) 
		{
        cout << "The dictionary is empty. Nothing to copy." << endl;
        return;
    	}
    	Node_for_alphabet* currentAlphabet = distionaryHead;

    	while (currentAlphabet != NULL) 
		{
       		Node_for_word* currentWord = currentAlphabet->word;
        	while (currentWord != NULL) 
			{
            	Insert(currentWord->word, currentWord->meaning);
            	currentWord = currentWord->Next_word;
        	}
        	currentAlphabet = currentAlphabet->Next_alphabet;
    	}
	}

double CalculateAverageSearchTime() 
{
    if (Head == NULL) {
        cout << "The linked list is empty." << endl;
        return 0.0;
    }

    double totalJumps = 0.0;
    double totalWords = 0.0;

    Node_for_word* current = Head;

    while (current != NULL) {
        Node_for_word* wordTraversal = current;

        totalJumps += 1.0;

        while (wordTraversal->Next_word != NULL) {
            totalJumps += 1.0;
            wordTraversal = wordTraversal->Next_word;
        }

        totalWords += 1.0;

        current = current->Next_word;
    }

    cout << "Total Jumps: " << totalJumps << endl;
    cout << "Total Words: " << totalWords << endl;

    double averageSearchTime = totalJumps / totalWords;
    return averageSearchTime;
	
	}

};

int main()
{
    Distionary dist;
    Linked_List l1;
    string alphabet, word, meaning;
	char yes_no;
    do  
	{
        cout << "-----------------------------" << endl;
        cout << "Dictionary Menu:" << endl;
        cout << "1. Add a new Alphabet" << endl;
        cout << "2. Add a new word" << endl;
        cout << "3. Search for a word" << endl;
        cout << "4. Delete a word" << endl;
        cout << "5. Display dictionary" << endl;
        cout << "6. Print dictionary in reverse" << endl;
        cout << "7. Print dictionary in reverse By stack" << endl;
        cout << "8. Calculate average search time for the dictionary" << endl;
        cout << "9. Display words of an alphabet" << endl;
        cout << "10. Display words and meanings of an alphabet" << endl;
        cout << "11. Delete a meaning" << endl;
        cout << "12. Display meanings of a word" << endl;
        cout << "13. Exit" << endl;
        cout << "Enter your choice (1-13): ";

        int choice;
        cin >> choice;

        switch (choice) {
        	case 1: {
                cout << "Enter alphabet: ";
                cin >> alphabet;
                dist.Insertion_at_alphabet(alphabet);
                break;
            }
            case 2: {
                cout << "Enter alphabet: ";
                cin >> alphabet;
                cout << "Enter word: ";
                cin >> word;
                cout << "Enter meaning: ";
                cin >> meaning;
                dist.Insertion_for_word(alphabet, word, meaning);
                break;
            }
            case 3: {
                cout << "Enter alphabet: ";
                cin >> alphabet;
                cout << "Enter word to search: ";
                cin >> word;
                dist.Search_for_word(alphabet, word);
                break;
            }
            case 4: {
                cout << "Enter alphabet: ";
                cin >> alphabet;
                cout << "Enter word to delete: ";
                cin >> word;
                dist.Delete_word(alphabet, word);
                break;
            }
            case 5: {
                dist.Print_Dictionary();
                break;
            }
            case 6: {
                dist.PrintDictionaryInReverse();
                break;
            }
            case 7: {
                dist.Recursion_PrintDictionary(dist.head);
                break;
            }
            case 8: {
                double avgSearchTime = dist.CalculateAverageSearchTime();
                cout << "Average Search Time: " << avgSearchTime << endl;
                break;
            }
            case 9: {
                string alphabet;
                cout << "Enter alphabet to display words: ";
                cin >> alphabet;
                dist.Display_word(alphabet);
                break;
            }
            case 10: {
                string alphabet;
                cout << "Enter alphabet to display words and meanings: ";
                cin >> alphabet;
                dist.Display_wordandMeaning(alphabet);
                break;
            }
            case 11: {
                string alphabet, word, meaning;
                cout << "Enter alphabet: ";
                cin >> alphabet;
                cout << "Enter word: ";
                cin >> word;
                cout << "Enter meaning to delete: ";
                cin >> meaning;
                dist.Delete_meaning(alphabet, word, meaning);
                break;
            }
            case 12: {
                string alphabet, word;
                cout << "Enter alphabet: ";
                cin >> alphabet;
                cout << "Enter word to display meanings: ";
                cin >> word;
                dist.Display_meaning_ofwords(alphabet, word);
                break;
            }
            case 13: {
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please enter a valid option (1-13)." << endl;
                break;
            }
        }
        cout<<"Do you want to continue y/n "<<endl;
        cin>>yes_no;
    }while(yes_no=='y');
    
string word1,meaning1;
    
    do
	 {
        cout << "-----------------------------" << endl;
        cout << "Linked List Menu:" << endl;
        cout << "1. Insert a word" << endl;
        cout << "2. Display linked list" << endl;
        cout << "3. Search for a word in linked list" << endl;
        cout << "4. Calculate average search time in linked list" << endl;
        cout << "5. Copy words from dictionary to linked list" << endl;
        
        cout << "Enter your choice (1-6): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter word: ";
                cin>>word1;
                cout << "Enter meaning: ";
                cin >> meaning1;
                l1.Insert(word1, meaning1);
                break;
            }
            case 2: {
                l1.displayLinkedList();
                break;
            }
            case 3: {
                cout << "Enter word to search in linked list: ";
                cin >> word1;
                l1.searchWord(word1);
                break;
            }
            case 4: {
                double avgSearchTime = l1.CalculateAverageSearchTime();
                cout << "Average Search Time in Linked List: " << avgSearchTime << endl;
                break;
            }
            case 5: {
                l1.copy_allwords(dist.head);
                cout << "Words copied from dictionary to linked list." << endl;
                break;
            }
            
            default: {
                cout << "Invalid choice. Please enter a valid option (1-5)." << endl;
                break;
            }
        }
        cout<<"Do you want to continue y/n ";
        cin>>yes_no;
    }while(yes_no=='y');
   return 0;
}

    

