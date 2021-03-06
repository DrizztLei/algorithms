#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;
template<class E>
struct node{
    E info;
    bool isVisit;
};
template<class T , class E>
class graph{
public:
    int ** matrix ;
    int ** weight;
    int ** copy;
    int length;
    node<E> * Graph;
    void DFS(int n, bool falg);
    bool invalid( int i , int l , vector<T> iterator);
    void innerForward(int count , int i = 0 , int j = 0 );
    bool forward(int n = 0);
    void show();
    bool adjust();
public:
    void init();
    graph();
    void BFS(int n = 0);
    void DFS(int n = 0);
    void reset();
    void outputTree();
    void outputMin();
    virtual ~graph();
};
template<class T , class E>
void graph<T , E> :: reset(){
    for(int i = 0 ; i < length ;i++)
        Graph[i].isVisit = false;
}
template<class T , class E>
void graph<T , E> ::  BFS(int n){
    cout << "IN BFS > " << endl;
    vector<int> left;
    vector<int> right;
    left.push_back(n);
    while(left.size() != 0 || right.size() != 0){
        if(left.size()){
            int Size = left.size();
            for(int i = 0 ; i < Size ; i++){
                cout << "Visit the node " << Graph[left[i]].info << " . " << endl;
                Graph[left[i]].isVisit = true;}
            for(int i = 0 ; i < Size ; i++){
                for(int k = 0 ; k < length ; k++){
                    if(matrix[k][left[i]] && (!Graph[k].isVisit)){
                        Graph[left[i]].isVisit = true;
                        right.push_back(k);
                    }
                }
            }
            left.clear();
        }
        else
        {
            int Size = right.size();
            for(int i = 0 ; i < Size ; i++){
                cout << "Visit the node " << Graph[right[i]].info << " . " << endl;
                Graph[right[i]].isVisit = true;
            }
            for(int i = 0 ; i < Size ; i++){
                for(int k = 0 ; k < length ; k++){
                    if(matrix[k][right[i]] && (!Graph[k].isVisit)){
                        Graph[right[i]].isVisit = true;
                        left.push_back(k);
                    }
                }
            }
            right.clear();
        }
    }
    reset();
}
template<class T , class E>
void graph<T , E> :: DFS(int n){
    DFS(n , true);
    reset();
}
template<class T , class E>
void graph<T , E> ::  DFS(int n , bool flag){
    if(false) reset();
    cout << "Visit the node " << Graph[n].info << " . " << endl;
    Graph[n].isVisit = true;
    for(int i = 0 ; i < length ; i++){
        if(matrix[i][n] && (!Graph[i].isVisit)){
            Graph[i].isVisit = true;
            DFS(i , false);
        }
    }
}
template<class T , class E>
void graph<T , E> :: outputTree(){
    if(copy != NULL)
    {
        for(int i = 0 ;i < length ; i++){
            delete[] copy[i];
        }
    }
    copy = new int* [length];
    for(int i = 0 ; i < length ; i++)
        copy[i] = new int[length];
    int count = 0;
    for(int i = 0 ; i < length ; i++)
    {
        for(int j = i ; j < length ; j++)
        {
            copy[i][j] = copy[j][i] = matrix[i][j];
            if(matrix[i][j] == 1) {
                count++;
                cout << "Get the connect of " << i << " and " << j << endl;
            }
        }
    }
    cout << "----------------------->" << endl;
    innerForward(count);
    reset();
}
template<class T , class E>
void graph<T , E> :: innerForward(int count , int i , int j){
    if(count < length - 1)
    {
        return;
    }
    if(j + 1 == length)
    {
        j = ++ i;
    }
    else
    {
        j ++;
    }
    if(count == length - 1 && i == length && j == length)
    {
        int ** temp = new int * [length];
        for(int i = 0 ; i < length ; i++)
            temp[i] = new int[length];
        for(int i = 0 ; i < length ; i++)
            for(int j = i ; j < length ; j++)
                temp[i][j] = temp[j][i] = copy[i][j];
        if(adjust())
        {
            cout << "Find the tree " << endl;
            copy = temp;
            show();
        }
        copy = temp;
        reset();
        return ;
    }
    else if(i == length && j == length)
    {
        return;
    }
    if(copy[i][j] == 1)
    {
        innerForward(count , i , j);
        copy[i][j] = copy[j][i] = 0;
        innerForward(count - 1 , i , j);
        copy[i][j] = copy[j][i] = 1;
    }
    else
    {
        innerForward(count , i , j);
    }
}
template<class T , class E>
void graph<T , E> :: show(){
    cout << "------------------------------------------------------>" << endl;
    for(int l = 0 ; l < length ; l++)
    {
        for(int m = l ; m < length ; m++)
        {
            if(copy[m][l] == 1) cout << "Connect the " << m << " and  " << l << endl;
        }
    }
    cout << "------------------------------------------------------<" << endl;
}
template<class T , class E>
bool graph<T , E> :: forward(int n){
    for(int i = 0 ; i < length ; i++){
        if(copy[n][i] == 1){
            copy[n][i] = copy[i][n] = 0;
            Graph[i].isVisit = true;
            Graph[n].isVisit = true;
            forward(i);
        }
    }
}
template<class T , class E>
bool graph<T , E> :: adjust(){
    forward();
    for(int i = 0 ; i < length ; i++){
        if(!Graph[i].isVisit) return false;
    }
    for(int i = 0 ; i < length ; i++)
        delete[] copy[i];
    return true;
}
template<class T , class E>
void graph<T , E> :: outputMin(){
    for(int i = 0 ; i < length ; i++)
        for(int j = 0 ; j < length ; j++)
            weight[i][j] = matrix[i][j] == 0 ? 1 << sizeof(int) * 3 - 2 : i + j;
    for(int i = 0 ; i < length ; i++){
        for(int j = 0 ; j < length ; j++){
            cout << weight[i][j] << "\t";
        }
        cout <<endl;
    }
    int min = weight[0][0];
    vector<T> iterator ;
    vector<T> edge;
    int select_i = 0 , select_j = 0;
    bool flag = true;
    for(int i = 0 ; i < length ; i++)
    {
        for(int j = 0 ; j < length - i; j++)
        {
            if(min > weight[i][j])
            {
                min = weight[i][j];
                select_i = i;
                select_j = j;
                flag = false;
            }
        }
    }
    if(flag) return;
    iterator.push_back(select_i);
    iterator.push_back(select_j);
    edge.push_back(min);
    bool isSelected = true;
    while(!flag && iterator.size() != length){
        int size = iterator.size();
        int min , select;
        for(int i = 0 ; i < size ; i++)
        {
            for(int j = 0 ; j < length ; j++)
            {
                if(invalid(iterator[i] , j , iterator) && (isSelected || min > weight[iterator[i]][j]))
                {
                    min = weight[iterator[i]][j];
                    select = j;
                    flag = true;
                    if(isSelected)
                    {
                        isSelected = false;
                    }
                }
            }
        }
        if(flag){
            iterator.push_back(select);
            edge.push_back(min);
            flag = false;
            isSelected = true;
        }else{
            break;
        }
    }
    cout << "Output  the min tree order : " << endl;
    for(int i = 0 ; i < iterator.size() ; i++)
        cout << iterator[i] << endl;
    cout << "Output  the min edge order : " << endl;
    for(int i = 0 ; i < edge.size() ; i++)
        cout << edge[i] << endl;
    iterator.clear();
    reset();
}
template<class T , class E>
bool graph<T , E> :: invalid(int i , int l , vector<T> iterator){
    if(matrix[i][l] == 0) return false;
    for(int j = 0 ; j < iterator.size() ; j++)
    {
        if(l == iterator[j]) return false;
    }
    return true;
}
template<class T , class E>
void graph<T ,E> :: init(){
    copy = new int * [length];
    cout << "START > " << endl;
    int length;
    length = 7;
    this -> length = length;
    matrix = new E * [length];
    weight = new int * [length];
    for(int i = 0 ; i < length ; i++ ){
        matrix[i] = new int[length]();
        weight[i] = new int[length]();
    }
    Graph = new node<T>[length];
    cout << "DONE > " << endl;
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[1][6] = 1;
    matrix[6][1] = 1;
    matrix[2][3] = 1;
    matrix[3][2] = 1;
    matrix[3][4] = 1;
    matrix[4][3] = 1;
    matrix[4][2] = 1;
    matrix[2][4] = 1;
    matrix[4][5] = 1;
    matrix[5][4] = 1;
    matrix[4][6] = 1;
    matrix[6][4] = 1;
    matrix[2][5] = 1;
    matrix[5][2] = 1;
    Graph[0].info = 0;
    Graph[1].info = 1;
    Graph[2].info = 2;
    Graph[3].info = 3;
    Graph[4].info = 4;
    Graph[5].info = 5;
    Graph[6].info = 6;
}
template<class T , class E>
graph<T , E> :: graph(){
    init();
}
template<class T , class E>
graph<T , E > :: ~graph(){
    for(int i = 0 ; i < length ; i++){
        delete[] matrix[i];
        delete[] weight[i];
    }
    delete matrix;
    delete weight;
    delete[] Graph;
    cout << "ALL THINGS DONE > " << endl;
}
void test(int i , int size , int * array){
    if(i == size){
        for(int l = 0 ; l < size ; l++)
            cout << array[l] << "\t";
        cout << endl;
        return;
    }
    array[i] = 1;
    test(i+1 , size , array);
    array[i] = 0;
    test(i+1 , size , array);
}
int main(int argc , char ** argv){
    graph<int , int> TEMP;
    TEMP.DFS();
    TEMP.BFS();
    TEMP.outputMin();
    TEMP.outputTree();
    cout << "TEMP " << endl;
    return 0;
}
