#include <iostream>
#include <string>
using namespace std;

typedef struct HTNode {
int data;
int parent, lchild, rchild;
} HTNode, *HufTree;

int main() {
int N;
cout << "请输入元素个数:";
cin >> N;
cout << "请输入各元素的权值:";
HufTree HT;
HT = (HufTree)malloc(2 * N * sizeof(HTNode)); // 动态分配2*N个空间
for (int i = 1; i <= N; i++) { // 输入原始节点
cin >> HT[i].data;
HT[i].parent = -1;
HT[i].lchild = -1;
HT[i].rchild = -1;
}
// 构建哈夫曼树
for (int i = N + 1; i < 2 * N; i++) { // 哈夫曼树中共有2*N-1个节点
int m1 = i - 1, m2 = i - 1; // m1保存第一小的位置，m2保存第二小的位置
int x1 = 1e9, x2 = 1e9; // x1保存第一小的值，x2保存第二小的值
for (int j = 1; j < i; j++) { // 寻找两个权重最小的位置
if (HT[j].parent == -1 && HT[j].data < x1) { // 符合条件的值，双亲必须为空
x2 = x1;
x1 = HT[j].data;
m2 = m1; // m2接替原m1，保存当前第二小的位置
m1 = j; // 将当前最小值的位置赋给m1
} else if (HT[j].parent == -1 && HT[j].data < x2) {
x2 = HT[j].data;
m2 = j;
}
}
// 添加新树
HT[m1].parent = i; // 添加双亲
HT[m2].parent = i; // 添加双亲
HT[i].data = HT[m1].data + HT[m2].data; // 新加入的节点，权重为两个最小值的和
HT[i].lchild = m1; // 将第一小的位置作为左子树
HT[i].rchild = m2; // 将第二小的位置作为右子树
HT[i].parent = -1; // 新节点的双亲为空
}
// 打印输出各原始节点的编码
string s;
for (int i = 1; i <= N; i++) {
int j = i;
int p = HT[j].parent;
while (p != -1) {
if (j == HT[p].lchild) {
s.append(1, '0'); // 如果是双亲的左子树则编为0
} else {
s.append(1, '1'); // 如果是双亲的右子树则编为1
}
j = p;
p = HT[p].parent;
}
cout << "权重为" << HT[i].data << "的节点的编码为";
for (int k = s.size() - 1; k >= 0; k--) { // 倒序输出的才是正确的编码方式
cout << s[k];
}
cout << endl;
s.clear();
}
return 1;
}