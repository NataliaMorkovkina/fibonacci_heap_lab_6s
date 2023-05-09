#include <vector>
#include <cassert>
#include <iostream>
using namespace std;


struct Pair
{
    int v, l;

    Pair(int _v, int _l) :
        v(_v), l(_l)
    {}

    Pair()
    {
        v = l = 0;
    }
};

struct Node {
    Pair n;
    int degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    char mark;
    char C;

    Node(Pair _n)
    {
        n = _n;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        left = nullptr;
        right = nullptr;
        C = 'N';
    }

    Node()
    {
        n = Pair(0,0);
        degree = 0;
        parent = nullptr;
        child = nullptr;
        left = nullptr;
        right = nullptr;
        C = 'N';
    }
};

class Heap
{
private:
    int nH;
    Node* H = nullptr;

public:
    void Fibonnaci_link(Node* H1, Node* y, Node* z)
    {
        (y->left)->right = y->right;
        (y->right)->left = y->left;
        if (z->right == z)
            H1 = z;
        y->left = y;
        y->right = y;
        y->parent = z;
        if (z->child == nullptr)
            z->child = y;
        y->right = z->child;
        y->left = (z->child)->left;
        ((z->child)->left)->right = y;
        (z->child)->left = y;
        if (y->n.l < (z->child)->n.l)
            z->child = y;
        z->degree++;
    }

    Node* Union(Node* H1, Node* H2)
    {
        Node* np;
        Node* H0 = H1;
        (H0->left)->right = H2;
        (H2->left)->right = H0;
        np = H0->left;
        H0->left = H2->left;
        H2->left = np;
        return H0;
    }

    void Consolidate()
    {
        int d, i;
        float f = (log(nH)) / (log(2));
        int D = f;
        Node** A = new Node*[D];
        for (i = 0; i <= D; i++)
            A[i] = nullptr;
        Node* x = H;
        Node* y;
        Node* np;
        Node* pt = x;
        do
        {
            pt = pt->right;
            d = x->degree;
            while (A[d] != nullptr)
            {
                y = A[d];
                if (x->n.l > y->n.l)
                {
                    np = x;
                    x = y;
                    y = np;
                }
                if (y == H)
                    H = x;
                Fibonnaci_link(H, y, x);
                if (x->right == x)
                    H = x;
                A[d] = nullptr;
                d = d + 1;
            }
            A[d] = x;
            x = x->right;
        }

        while (x != H);
        H = nullptr;
        for (int j = 0; j <= D; j++)
        {
            if (A[j] != nullptr)
            {
                A[j]->left = A[j];
                A[j]->right = A[j];
                if (H != nullptr)
                {
                    (H->left)->right = A[j];
                    A[j]->right = H;
                    A[j]->left = H->left;
                    H->left = A[j];
                    if (A[j]->n.l < H->n.l)
                        H = A[j];
                }
                else
                {
                    H = A[j];
                }
                if (H == nullptr)
                    H = A[j];
                else if (A[j]->n.l < H->n.l)
                    H = A[j];
            }
        }
    }

    Node* Extract_Min()
    {
        Node* p;
        Node* ptr;
        Node* z = H;
        p = z;
        ptr = z;
        if (z == nullptr)
            return z;
        Node* x;
        Node* np;
        x = nullptr;
        if (z->child != nullptr)
            x = z->child;
        if (x != nullptr)
        {
            ptr = x;
            do
            {
                np = x->right;
                (H->left)->right = x;
                x->right = H;
                x->left = H->left;
                H->left = x;
                if (x->n.l < H->n.l)
                    H = x;
                x->parent = nullptr;
                x = np;
            } while (np != ptr);
        }
        (z->left)->right = z->right;
        (z->right)->left = z->left;
        H = z->right;
        if (z == z->right && z->child == nullptr)
            H = nullptr;
        else
        {
            H = z->right;
            Consolidate();
        }

        nH = nH - 1;

        return p;
    }

    void Insert(Node* x)
    {
        x->degree = 0;
        x->parent = nullptr;
        x->child = nullptr;
        x->left = x;
        x->right = x;
        x->mark = 'F';
        x->C = 'N';
        if (H != nullptr)
        {
            (H->left)->right = x;
            x->right = H;
            x->left = H->left;
            H->left = x;
            if (x->n.l < H->n.l)
                H = x;
        }
        else
        {
            H = x;
        }
        nH = nH + 1;
    }
};

void createGraph(int numVertices, int numEdges, vector<Pair>& vertices, vector<Pair>& edges) {
  
    for (int i = 0; i < numVertices; i++) {
        vertices.push_back(Pair(i, i));
    }

  
    for (int i = 0; i < numEdges; i++) {
        int u = rand() % numVertices;
        int v = rand() % numVertices;
        edges.push_back(Pair(u, v));
    }
}



