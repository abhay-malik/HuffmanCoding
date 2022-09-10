#include<bits/stdc++.h>

using namespace std;

// Huffman Tree Nodes
struct Node
{
    Node *left;
    Node *right;
    char data; 
    int freq;
    Node(char data,int freq)
    {
        this->data = data;
        this->freq = freq;
        left = right = NULL;
    }
};


// Comparator for the Nodes based on frequency.
struct compare{
    bool operator()(Node* n1,Node* n2)
    {
        return n1->freq > n2->freq;
    }
};


//Print Nodes
void printNodes(Node *root,string str,unordered_map<char,int> &mp)
{
    if(!root)
        return;
    
    if(root->data != '$'){
        mp[root->data] = str.size();
    }
    
    
    printNodes(root->left,str+'0',mp);
    printNodes(root->right,str+'1',mp);
}

// To Return compression percentage.
float getPer(int i,int j)
{
    return (float(i-j)/float(i))*100;
}


// Main HUFFMAN Code
float getCode(string text)
{
    unordered_map<char,int> mp;
    unordered_map<char,int> freq;
    for(auto i:text)
        freq[i]++;
    
    priority_queue<Node*,vector<Node*>,compare> pq;

    for(auto i:freq)
    {
        pq.push(new Node(i.first,i.second));
    }

    Node *left,*right,*top;
    
    while(pq.size() != 1)
    {
        left = pq.top();
        pq.pop();
        right = pq.top();
        pq.pop();

        top = new Node('$',left->freq+right->freq);
        top->left = left;
        top->right = right;

        pq.push(top);
    }

    printNodes(pq.top(),"",mp);

    int oTextSize = text.size()*8;
    int encodedSize = 0;
    
    for(auto i:mp){
        encodedSize += i.second*freq[i.first];
    }

    return getPer(oTextSize,encodedSize);
}


// TO Read files.
string readFile(string loc)
{
    string res = "";
    fstream my_file;
	my_file.open(loc, ios::in);
	if (!my_file) {
        cout<<loc<<" ";
		cout << "No such file";
	}
	else {
		char ch;

		while (1) {
			my_file >> ch;
			if (my_file.eof())
				break;
			res += ch;
		}

	}
	my_file.close();
    return res;
}

int main()
{
    float per = 0.0;
    for(int i=1;i<=8;i++){
        string originalText = readFile(to_string(i)+".txt");
        per += getCode(originalText);
    }
    cout<<per/8<<"%";
    return 0;
}