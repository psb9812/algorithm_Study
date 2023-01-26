#include <iostream>

using namespace std;

struct node
{
    int data;
    node* left;
    node* right;
};

//BST 이진트리
struct bst
{
    node* root = nullptr;

    //검색 함수
    node* find(int value)
    {
        //재귀적으로 동작하기 때문에 구현을 따로 나눠놓았음
        return find_impl(root, value);   
    }
    //삽입 함수
    void insert(int value)
    {
        if(!root)
            root = new node{value, NULL, NULL};
        else
            insert_impl(root, value);
    }
    //중위 순회 함수
    void inOrder()
    {
        inOrder_impl(root);
    }
    //후손 노드를 찾는 함수
    node* successor(node* start)
    {
        auto current = start->right;
        while(current && current->left)
            current = current->left;
        return current;
    }
    //삭제 함수
    void deleteValue(int value)
    {
        root = delete_impl(root, value);
    }

private:
    node* find_impl(node* current, int value)
    {
        if(!current)
        {
            cout << endl;
            return NULL;
        }

        if(current->data == value)
        {
            cout << value << "을(를) 찾았습니다." << endl;
            return current;
        }

        if(value < current->data)
        {
            cout << current->data << "에서 왼쪽으로 이동: ";
            return find_impl(current->left, value);
        }

        //value 값이 현재 노드 오른쪽에 있는 경우
        cout << current->data << "에서 오른쪽으로 이동: ";
        return find_impl(current->right, value);
    }

    void insert_impl(node* current, int value)
    {
        if(value < current->data)
        {
            //현재 노드의 왼쪽에 자식 노드가 없다면 그냥 그곳에 삽입힌다.
            //왼쪽 자식노드가 존재한다면 다시 재귀적으로 함수를 호출한다.
            if(!current->left)  
                current->left = new node{value, NULL, NULL};
            else
                insert_impl(current->left, value);
        } else
        {
            if(!current->right)
                current->right = new node{value, NULL, NULL};
            else
                insert_impl(current->right, value);
        }
    }

    void inOrder_impl(node* start)
    {
        if(!start)
            return;
        
        inOrder_impl(start->left);       //왼쪽 서브 트리 방문
        cout << start->data << " "; //현재 노드 출력
        inOrder_impl(start->right);      //오른쪽 서브 트리 방문
    }

    node* delete_impl(node* start, int value)
    {
        if(!start)
            return NULL;
        if(value < start->data)
            start->left = delete_impl(start->left, value);
        else if(value > start->data)
            start->right = delete_impl(start->right, value);
        else
        {
            if(!start->left)    //자식 노드가 전혀 없거나, 왼쪽 자식 노드만 없는 경우
            {
                auto tmp = start->right;
                delete start;
                return tmp;
            }
            if(!start->right)   //오른쪽 자식 노드만 없는 경우
            {
                auto tmp = start->left;
                delete start;
                return tmp;
            }

            //자식 노드가 둘 다 있는 경우
            auto succNode = successor(start);
            start->data = succNode->data;

            //오른쪽 서브 트리에서 후속(successor)을 찾아 삭제
            start->right = delete_impl(start->right, succNode->data);
        }
        return start;
    }
};

int main()
{
    bst tree;
    tree.insert(12);
    tree.insert(10);
    tree.insert(20);
    tree.insert(8);
    tree.insert(11);
    tree.insert(15);
    tree.insert(28);
    tree.insert(4);
    tree.insert(2);

    cout << "중위 순회: ";
    tree.inOrder();
    cout << endl;

    tree.deleteValue(12);
    cout << "12를 삭제한 후 중위 순회: ";
    tree.inOrder();
    cout << endl;

    if(tree.find(12))
        cout << "원소 12는 트리에 있습니다" << endl;
    else
        cout << "원소 12는 트리에 없습니다." << endl;

    return 0;
}