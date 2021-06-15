//
//  main.cpp
//  Splay Tree
//
//  Created by Riccardo Raciti on 05/01/21.
//
#include <iostream>

using namespace std;

template<class T> struct Node{
    T key;
    Node<T>* left;
    Node<T>* right;
};

template <class T> class SplayTree
{
private:
    
    Node<T>* _NewNode(T key){
        Node<T>* x = new Node<T>;
        if(!x){
            cout<<"ERRORE"<<endl;
            return NULL;
        }
        x->key = key;
        x->left = x->right = NULL;
        return x;
    }
    
    Node<T>* R_Rotate(Node<T>* x){
        Node<T>* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    
    Node<T>* L_Rotate(Node<T>* x){
        Node<T>* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    
    Node<T>* Splay(T key, Node<T>* root){
        if(!root) return NULL;
        Node<T> head;
        head.left = head.right = NULL;
        // creo due sotto alberi e li faccio puntare ad una "root" comune
        Node<T>* T1 = &head;
        Node<T>* T2 = &head;
        while (1) {
            if (key < root->key) {
                if(!root->left)
                    break;
                if (key < root->left->key) {
                    root = R_Rotate(root);
                    if(!root->left)
                        break;
                }
                T2->left= root;
                T2 = T2->left;
                root = root->left;
                T2->left = NULL;
            }
            else if (key > root->key){
                if(!root->right)
                    break;
                if (key > root->right->key) {
                    root = L_Rotate(root);
                    if(!root->right)
                        break;
                }
                T1->right= root;
                T1 = T1->right;
                root = root->right;
                T1->right = NULL;
            }
            else
                break;
        }
        T1->right = root->left;
        T2->left = root->right;
        root->left = head.right;
        root->right = head.left;
        return root;
    }
    
public:

    Node<T>* Ins(T key, Node<T>* root)
    {
        //utilizzo un nodo static per tenerlo e per valutare se esiste o no la root
       static Node<T>* x = NULL;
       if (!x)
       x = _NewNode(key);
       else
       x->key = key;
       if (!root)
       {
          root = x;
          x = NULL;
          return root;
       }
       root = Splay(key, root);
       if (key < root->key)
       {
          x->left= root->left;
          x->right = root;
          root->left = NULL;
          root = x;
       }
       else if (key > root->key)
       {
          x->right = root->right;
          x->left = root;
          root->right = NULL;
          root = x;
       }
       else
       return root;
       x = NULL;
       return root;
    }
    
    Node<T>* Delete(T key, Node<T>* root)
    {
       Node<T>* temp;
       if (!root)   return NULL; //se l'albero è vuoto
       root = Splay(key, root);
       if (key != root->key)  return root; //se l'albero ha un solo elemento
       else
       {
          if (!root->left)
          {
             temp = root;
             root = root->right;
          }
          else
          {
             temp = root;
             root = Splay(key, root->left);
             root->right = temp->right;
          }
          free(temp);
          return root;
       }
    }
    
    Node<T>* Search(T key, Node<T>* root)
    {
       return Splay(key, root);
    }
    
    void Preorder(Node<T>* root)
    {
       if (root)
       {
          
          cout<< "key: " <<root->key;
          if(root->left)
          cout<< " | left child: "<< root->left->key;
          if(root->right)
          cout << " | right child: " << root->right->key;
          cout<< "\n";
          Preorder(root->left);
          Preorder(root->right);
       }
    }
};

template<class T> void blocco(Node<T>* root, SplayTree<T>& ST, int l){
    T i;
    char c;
    if(l == 1){
        while(1)
        {
            
            cout<<"1. Inserisci "<<endl;
            cout<<"2. Cancella"<<endl;
            cout<<"3. Ricerca"<<endl;
            cout<<"4. Uscita"<<endl;
            cout<<"Inserisci la tua scelta: ";
            cin>>c;
            switch(c){
                case 49:
                    cout<<"Inserisci valore: ";
                    cin>>i;
                    root = ST.Ins(i, root);
                    cout<<endl;
                    cout<<"Dopo l'inserimento: "<<i<<endl;
                    ST.Preorder(root);
                    break;
                case 50:
                    cout<<"Inserisci valore da eliminare: ";
                    cin>>i;
                    root = ST.Delete(i, root);
                    cout<<endl;
                    cout<<"Dopo la cancellazione: "<<i<<endl;
                    ST.Preorder(root);
                    break;
                case 51:
                    cout<<"Inserisci valore da cercare: ";
                    cin>>i;
                    root = ST.Search(i, root);
                    cout<<endl;
                    cout<<"Dopo la ricerca "<<i<<endl;
                    ST.Preorder(root);
                    break;
                case 52:
                    exit(1);
                default:
                    cout<<endl;
                    cout<<"Scelta non valida! \n RIPROVARE! "<<endl;
                    break;
           }
        }
    }
    else{
        while(1)
        {
            
            cout<<"1. Insert "<<endl;
            cout<<"2. Delete"<<endl;
            cout<<"3. Search"<<endl;
            cout<<"4. Exit"<<endl;
            cout<<"Enter your choice: ";
            cin>>c;
            switch(c){
                case 49:
                    cout<<"Enter value to be inserted: ";
                    cin>>i;
                    root = ST.Ins(i, root);
                    cout<<endl;
                    cout<<"After Insert: "<<i<<endl;
                    ST.Preorder(root);
                    break;
                case 50:
                    cout<<"Enter value to be deleted: ";
                    cin>>i;
                    root = ST.Delete(i, root);
                    cout<<endl;
                    cout<<"After Delete: "<<i<<endl;
                    ST.Preorder(root);
                    break;
                case 51:
                    cout<<"Enter value to be searched: ";
                    cin>>i;
                    root = ST.Search(i, root);
                    cout<<endl;
                    cout<<"After Search "<<i<<endl;
                    ST.Preorder(root);
                    break;
                case 52:
                    exit(1);
                default:
                    cout<<endl;
                    cout<<"Invalid type! "<<endl;
                    break;
           }
        }
    }
}

int main(){
    bool v = true;
    int l = 0;
    
    //scelta della lingua
    while (v) {
        cout<<"SCEGLI LINGUA"<<endl;
        cout<<"CHOOSE LENGUAGE"<<endl;
        cout<<"Type 1 for Italian"<<endl;
        cout<<"Type 2 for English"<<endl;
        cin >> l;
        if(l == 1 or l == 2) v = false;
        if(l != 1 and l != 2)
            cout<<"Digitazione errata/Incorrect entry"<<endl;
    }
    
    //Scelta del tipo
    char type = '\0';
    v = true;
    cout << endl;
    if(l == 2){
        while (v) {
            cout << "CHOOSE TYPE" << endl;
            cout << "Type 'i' for int" << endl;
            cout << "Type 'd' for double" << endl;
            cout << "Type 'c' for char" << endl;
            cin >> type;
            
            if(type == 'i' || type == 'd' || type == 'c') v = false;
            else
                cout<<"\n\nIncorrect type, try again!" << endl;
        }
        cout<<endl;
        if(type == 'i'){
            SplayTree<int> ST;
            Node<int>* root;
            root = NULL;
            ST.Preorder(root);
            blocco(root, ST,l);
        }
        if(type == 'd'){
            SplayTree<double> ST;
            Node<double>* root;
            root = NULL;
            ST.Preorder(root);
            blocco(root, ST,l);
        }
        if(type == 'c'){
            SplayTree<char> ST;
            Node<char>* root;
            root = NULL;
            ST.Preorder(root);
            blocco(root, ST,l);
        }
        
    }
    if(l == 1){
        while (v) {
            cout << "SCEGLIERE TIPO" << endl;
            cout << "Digitare 'i' per int" << endl;
            cout << "Digitare 'd' per double" << endl;
            cout << "Digitare 'c' per char" << endl;
            cin >> type;
            if(type == 'i' || type == 'd' || type == 'c') v = false;
            else
                cout<<"\n\nTipo incorretto, RIPROVARE!" << endl;
        }
        cout<<endl;
        if(type == 'i'){
            SplayTree<int> ST;
            Node<int>* root;
            root = NULL;
            ST.Preorder(root);
            blocco(root, ST,l);
        }
        if(type == 'd'){
            SplayTree<double> ST;
            Node<double>* root;
            root = NULL;
            ST.Preorder(root);
            blocco(root, ST,l);
        }
        if(type == 'c'){
            SplayTree<char> ST;
            Node<char>* root;
            root = NULL;
            ST.Preorder(root);
            blocco(root, ST,l);
        }
    }
    return 0;
}
