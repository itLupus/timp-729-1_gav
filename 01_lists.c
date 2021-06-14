#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
int value; // значение узла
struct node* next; // следующий узел
struct node* prev; // предыдущий узел
} node; // структура узла

typedef struct list {
struct node* head; // начальный элемент
struct node* tail; // конечный элемент
} list; // структура списка

/// <summary>
/// Инициализация списка
/// </summary>
/// <param name="l">список</param>
void init(list* l)
{
list* tmp = (list*)malloc(sizeof(list));
tmp->head = tmp->tail = NULL;
*l = *tmp;
}

/// <summary>
/// Удалить все элементы списка
/// </summary>
/// <param name="l">список</param>
void clean(list* l)
{
node* tempNode = l->head; // передали адрес начального узла списка
node* removeNode = (node*)malloc(sizeof(node)); // узел для удаления
while (tempNode) // пока есть элементы
{
removeNode = tempNode;
tempNode = tempNode->next;
free(removeNode);
}
l->head = NULL;
l->tail = NULL;
}

/// <summary>
/// Проверка списка на пустоту
/// </summary>
/// <param name="l">список</param>
/// <returns>True - пустой список, False - в списке есть значения</returns>
bool is_empty(list* l)
{
if (l->head == NULL)
return 1;
else return 0;
}

/// <summary>
/// Поиск узла по значению
/// </summary>
/// <param name="l">Список</param>
/// <param name="value">Значение для поиска узла</param>
/// <returns>(node*) - узел найден, NULL - указанного значение в списке нет</returns>
node* find(list* l, int value)
{
node* tempNode = l->head; // адрес первого узла
while (tempNode) // пока есть элементы в списке
{
if (tempNode->value == value) // нашли значение
{
return tempNode; // вернули узел
}
tempNode = tempNode->next; // смотрим следующий элемент
}
return NULL;
}

/// <summary>
/// Добавление значение в конец списка
/// </summary>
/// <param name="l">список</param>
/// <param name="value">значение для добавления</param>
/// <returns>0 - успешное добавление</returns>
int push_back(list* l, int value)
{
node* tempNode = (node*)malloc(sizeof(node)); // выделение памяти под узел
if (tempNode == NULL)
{
return 0;
}
// инициализируем узел, кладем значение, следующий узел NULL, предыдущий - последний узел списка
tempNode->value = value;
tempNode->next = NULL;
tempNode->prev = l->tail;
if (l->tail) // последний элемент списка есть
{
l->tail->next = tempNode; // после последнего элемента новый узел
}
l->tail = tempNode; // новый узел - новый конец списка

if (l->head == NULL) // если голова пустая
{
l->head = tempNode; // голова - последний элемент списка
}
return 0;
}

/// <summary>
/// Добавление элемента в начало списка
/// </summary>
/// <param name="l">список</param>
/// <param name="value">значение для добавления</param>
/// <returns>0 - успешное добавление</returns>
int push_front(list* l, int value)
{
node* tempNode = (node*)malloc(sizeof(node)); // выделение памяти под узел
tempNode->value = value; // положили значение в узел
if (l->head == NULL) // если голова пустая
{
// значит список пустой
// голова и хвост -> новый узел
l->head = tempNode;
l->tail = tempNode;
}
else
{
// узел теперь головной
tempNode->next = l->head;
tempNode->next->prev = tempNode;
l->head = tempNode;
}
if (tempNode)
{
return 0;
}
}

/// <summary>
/// Добавление элемента после указанного узла
/// </summary>
/// <param name="l">список</param>
/// <param name="n">узел</param>
/// <param name="value">значение для добавления</param>
/// <returns>0 - успешная вставка</returns>
int insert_after(list* l, node* n, int value) {
node* tempNode = (node*)malloc(sizeof(node)); // выделение памяти под узел
if (n->next == NULL) // если нет следующего узла
{
tempNode->prev = n;
n->next = tempNode;
l->tail = tempNode;
tempNode->value = value;
return 0;
}
tempNode->value = value;
tempNode->prev = n;
tempNode->next = n->next;
n->next->prev = tempNode;
n->next = tempNode;
return 0;
}

/// <summary>
/// Добавление элемента перед указанным узлом
/// </summary>
/// <param name="l">список</param>
/// <param name="n">узел</param>
/// <param name="value">значение для добавления</param>
/// <returns>0 - успешная вставка</returns>
int insert_before(list* l, node* n, int value)
{
node* tempNode = (node*)malloc(sizeof(node)); // выделение памяти под узел
if (n->prev == NULL) // если предыдущего элемента нет
{
tempNode->next = n;
n->prev = tempNode;
l->head = tempNode;
tempNode->value = value;
return 0;
}
tempNode->value = value;
tempNode->prev = n->prev;
n->prev->next = tempNode;
tempNode->next = n;
n->prev = tempNode;
return 0;
}

/// <summary>
/// Удаление указанного значения из списка
/// </summary>
/// <param name="l">список</param>
/// <param name="value">значение для удаления</param>
/// <returns>0 - успешное удаление</returns>
int remove_node(list* l, int value)
{
node* tempNode = l->head;
while (tempNode != NULL) { // пока есть узлы
if (tempNode->value == value) { // нашли узел с заданным значением
if (tempNode->prev) { // если есть предыдущий элемент
tempNode->prev->next = tempNode->next; // скрепляем предыдущий и следующий узлы от указанного узла
}
if (tempNode->next) { // если есть следующий элемент
tempNode->next->prev = tempNode->prev; // скрепляем предыдущий и следующий узлы от указанного узла
}
if (!tempNode->prev) { // если предыдущиего элемента нет, значит головной узел
l->head = tempNode->next;
}
if (!tempNode->next) { // если следующего элемента нет, значит хвост
l->tail = tempNode->prev;
}
free(tempNode);
return 0;
}
else {
tempNode = tempNode->next;
}
}
return 1;
}

/// <summary>
/// Поиск последнего элемента в списке с заданным значением
/// </summary>
/// <param name="l">список</param>
/// <param name="value">значение для поиска</param>
/// <returns>(node*) - нашли элемент, NULL - такого элемента нет</returns>
node* findlast(list* l, int value) {
node* tempNode = l->tail;
if (!l->head) {
return NULL;
}
while (tempNode) {
if (tempNode->value == value)
return tempNode;
tempNode = tempNode->prev;
}
return NULL;
}

/// <summary>
/// Удаление посдледнего элемента с указанным значением
/// </summary>
/// <param name="l"></param>
/// <param name="value">значение для поиска</param>
/// <returns>0 - успешное удаление</returns>
int remove_last(list* l, int value) {
if (l->head == NULL) {
return 1;
}
node* tempNode = findlast(l, value);
if (tempNode != NULL) {
node* prevNode = tempNode->prev;
node* nextNode = tempNode->next;
if (prevNode != NULL) {
prevNode->next = nextNode;
}
if (nextNode != NULL) {
nextNode->prev = prevNode;
}
if (tempNode == l->head) {
l->head = tempNode->next;
}
if (tempNode == l->tail) {
l->tail = tempNode->prev;
}
free(tempNode);
}
return 0;
}

/// <summary>
/// Вывод элементов в прямом порядке
/// </summary>
/// <param name="l">список</param>
void print(list* l)
{
node* tempNode = l->head;
if (tempNode == NULL) {
return;
}
while (tempNode != NULL) {
printf("%d ", tempNode->value);
tempNode = tempNode->next;
}
printf("\n");
}

/// <summary>
/// Вывод элементов списка в обратном порядке
/// </summary>
/// <param name="l">список</param>
void print_invers(list* l)
{
node* tempNode = l->tail;
if (tempNode == NULL) {
return;
}
while (tempNode != NULL) {
printf("%d ", tempNode->value);
tempNode = tempNode->prev;
}
printf("\n");
}

int main() {
list* l; // объявление списка
init(l); // инициализация списка
int n, values, i;
scanf("%d", &n); // считывание значения
for (int i = 0; i < n; i++) // ввод n элементов в список
{
scanf("%d", &values);
push_back(l, values);
}
print(l); // вывод списка
for (int i = 0; i < 3; i++) // поиск 3 элементов в списке 1 - есть, 0 - нет
{
scanf("%d", &values);
if (find(l, values) == NULL)
{
printf("%d ", 0);
}
else
{
printf("%d ", 1);
}

}
printf("\n");
scanf("%d", &values);
push_back(l, values); // добавление элемента в конец
print_invers(l);
scanf("%d", &values);
push_front(l, values); // добавление элемента в начало
print(l);
int j, x;
scanf("%d", &j);
scanf("%d", &x);
node* temp = l->head;
for (i = 1; i < j; i++)
{
temp = temp->next;
}
insert_after(l, temp, x); // добавление элемента после указанного узла
print_invers(l);
int u, y;
scanf("%d", &u);
scanf("%d", &y);
temp = l->head;
for (i = 1; i < u; i++)
{
temp = temp->next;
}
insert_before(l, temp, y); // доабвление элемента перед указанным узлом
print(l);
scanf("%d", &values);
remove_node(l, values); // удаление узла по значению
print_invers(l);
scanf("%d", &values);
remove_last(l, values); // удаление последнего найденного значения
print(l);
clean(l); // очистка списка
return 0;
}
