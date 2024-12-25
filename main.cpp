#include <iostream>
#include <cmath>

using namespace std;

//Максимальное количество узлов в списке
const int MAX_NODES = 10000;

//Структура узла односвязного списка
struct Node {
    int data;
    int next;  //Индекс следующего узла (не указатель)
};

//Функция для проверки наличия повторяющихся цифр в числе
bool hasRepeatingDigits(int n) {
    int digits[10] = {0}; //Массив для подсчета цифр
    while (n > 0) {
        int digit = n % 10;
        if (digits[digit] > 0) return true;
        digits[digit]++;
        n /= 10;
    }
    return false;
}

//Функция для извлечения последней цифры
int lastDigit(int n) {
    return n % 10;
}

//Функция для вставки элемента в начало списка (массив)
void insertAtBeginning(Node nodes[], int& head, int& nodeCount, int data) {
    nodes[nodeCount].data = data;
    nodes[nodeCount].next = head;
    head = nodeCount;
    nodeCount++;
}

//Функция для печати списка
void printList(Node nodes[], int head) {
    int current = head;
    while (current != -1) {
        cout << nodes[current].data << " ";
        current = nodes[current].next;
    }
    cout << endl;
}

//Функция для удаления списка (обозначим как -1 в next)
void deleteList(Node nodes[], int &head, int& nodeCount) {
   for (int i=0; i< nodeCount; ++i){
        nodes[i].next = -1;
   }
    head = -1;
    nodeCount = 0;

}

//Функция для сортировки массива
void sortList(Node nodes[], int head) {
    if (head == -1 || nodes[head].next == -1) return; // Пустой список или один элемент

    int current, next_node;
    for (current = head; nodes[current].next != -1; current = nodes[current].next){
        for(next_node = nodes[current].next; next_node != -1; next_node = nodes[next_node].next)
        {
           if(lastDigit(nodes[current].data) < lastDigit(nodes[next_node].data)){

                swap(nodes[current].data,nodes[next_node].data);
           }
        }
    }
}

int main() {
    int n;
    cin >> n;

    Node nodes[MAX_NODES];
    int head = -1; //Начало списка
    int nodeCount = 0; //Счётчик узлов

    bool has_repeating = false;

    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        if (hasRepeatingDigits(num)) {
            has_repeating = true;
        }
        insertAtBeginning(nodes, head, nodeCount, num);
    }

    if (!has_repeating) {
          sortList(nodes, head);
    } else {

        int current = head;
        int new_head = -1;
        int new_nodeCount = 0;

        while (current != -1) {
          int first_digit = nodes[current].data;
          while(first_digit >= 10) first_digit /= 10;

            if (first_digit % 2 != 0) {
                insertAtBeginning(nodes, new_head, new_nodeCount, nodes[current].data);
                insertAtBeginning(nodes, new_head, new_nodeCount, nodes[current].data);
            }
           current = nodes[current].next;
         }
        deleteList(nodes, head, nodeCount);
        head = new_head;
        nodeCount = new_nodeCount;
    }
    printList(nodes, head);
    deleteList(nodes, head, nodeCount); //Обозначим, что список удален


    return 0;
}
