#
#include <iostream>
#include <queue>

using namespace std;

struct node
{
    string position;
    node* first;
    node* second;
};

struct org_tree
{
    node* root;
    //루트 노드를 생성하는 정적 함수
    static org_tree create_org_structure(const string& pos)
    {
        org_tree tree;
        tree.root = new node {pos, NULL, NULL};
        return tree;
    }
    //직책 이름에 해당하는 노드를 반환하는 정적 함수
    static node* find(node* root, const string& value)
    {
        if(root == NULL)
            return NULL;

        if(root->position == value)
            return root;

        auto firstFound = org_tree::find(root->first, value);

        if(firstFound != NULL)
            return firstFound;

        return org_tree::find(root->second, value);
    }

    bool addSubordinatte(const string& manager, const string& subordinate)
    {
        auto managerNode = org_tree::find(root, manager);

        if(!managerNode)
        {
            cout << manager << "을(를) 찾을 수 없습니다: " << endl;
            return false;
        }

        if(managerNode->first && managerNode->second)
        {
            cout << manager << " 아래에 " << subordinate << "을(를) 추가할 수 없습니다." << endl;
            return false;
        }
        if(!managerNode->first)
            managerNode->first = new node {subordinate, NULL, NULL};
        else
            managerNode->second = new node {subordinate, NULL, NULL};

        cout << manager << " 아래에 " << subordinate << "을(를) 추가했습니다." << endl;
        return true;
    }

    //전위 순회 구현
    static void preOrder(node* start)
    {
        if(!start)
            return;
        //먼저 호출
        cout << start->position << ", ";
        //재귀적인 호출. 왼쪽 노드가 먼저
        preOrder(start->first);
        preOrder(start->second);
    }

    //중위 순회 구현
    static void inOrder(node* start)
    {
        if(!start)
            return;

        inOrder(start->first);
        cout << start->position;
        inOrder(start->second);
    }

    //후위 순회 구현
    static void postOrder(node* start)
    {
        if(!start)
            return;
        
        postOrder(start->first);
        postOrder(start->second);
        cout << start->position << ", ";
    }
    //레벨 순서 순회 구현
    static void levelOrder(node* start)
    {
        //루트 노드가 없으면 함수 리턴
        if(!start)
            return;
        //자식 노드를 넣을 큐 선언
        queue<node*> q;
        //최초로 루트 노드를 큐에 넣고
        q.push(start);

        //한 레벨을 단위로 반복 큐가 전부 빌 때 까지
        while(!q.empty())
        {
            int size = q.size();
            for(int i = 0; i < size; i++)
            {
                //따로 맨 앞에 원소를 저장
                auto current = q.front();
                // 맨 앞 원소 제거
                q.pop();
                // 맨 앞 원소 출력
                cout << current->position << ", ";
                //맨 앞 원소에 자식이 있다면 큐에 저장 해둠
                if(current->first)
                    q.push(current->first);
                if(current->second)
                    q.push(current->second);
            }

            cout << endl;
        }
    }
};
int main()
{
    auto tree = org_tree::create_org_structure("CEO");

    tree.addSubordinatte("CEO", "부사장");
    tree.addSubordinatte("부사장", "IT부장");
    tree.addSubordinatte("부사장", "마케팅부장");
    tree.addSubordinatte("IT부장", "보안팀장");
    tree.addSubordinatte("IT부장", "앱개발팀장");
    tree.addSubordinatte("마케팅부장", "물류팀장");
    tree.addSubordinatte("마케팅부장", "홍보팀장");
    tree.addSubordinatte("부사장", "재무부장");

    org_tree::levelOrder(tree.root);

    return 0;
}