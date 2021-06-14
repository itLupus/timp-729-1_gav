#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// test
// Структ1ура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node
{
    long int value;      // значение узла
    struct node *right;  // адрес на левого потомка
    struct node *left;   // адрес на правого потомка
    struct node *parent; // адрес предка
} node;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree
{
    long int count;    // кооличество элементов в дереве
    struct node *root; // адрес на корень дерева
} tree;

long int remove_min(node *n);
// Инициализация дерева
void init(tree *t)
{
    node *tempNode = (node *)malloc(sizeof(node)); // выделили память под узел
    tree *tempTree = (tree *)malloc(sizeof(tree)); // выделили память под дерево
    tempNode->parent = NULL;
    tempNode->right = NULL;
    tempNode->left = NULL;
    tempTree->root = tempNode;

    *t = *tempTree;
}

// Удалить все элементы из дерева
void clean(tree *t)
{
    node *tempNode = (node *)malloc(sizeof(node));
    tempNode = t->root;
    while (tempNode->left || tempNode->right)
        remove_min(tempNode);
    tempNode->left = NULL;
    tempNode->right = NULL;
    tempNode->parent = NULL;
    t->root = NULL;
    free(tempNode);
}

// Поиск элемента по значению. Вернуть NULL если элемент не найден
node *find(tree *t, long int value)
{
    if (t)
    { // если список инициализирован
        if (t->count > 0)
        { // если в списке есть элементы
            node *tempNode;
            tempNode = (node *)malloc(sizeof(node)); // выделение памяти под узел
            tempNode = t->root;

            while (tempNode)
            { // пока есть узлы
                if (tempNode->value == value)
                {
                    return tempNode;
                }
                else if (value > tempNode->value && tempNode->right)
                {
                    tempNode = tempNode->right;
                }
                else if (value < tempNode->value && tempNode->left)
                {
                    tempNode = tempNode->left;
                }
                else
                {
                    return NULL;
                }
            }
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
long int insert(tree *t, long int value)
{
    node *insertNode;
    insertNode = (node *)malloc(sizeof(node));
    insertNode->parent = insertNode;
    insertNode->left = NULL;
    insertNode->right = NULL;
    insertNode->value = value;

    tree *tempTree;
    tempTree = (tree *)malloc(sizeof(tree)); // выделение памяти
    tempTree = t;

    tree *tempTree1;
    tempTree1 = (tree *)malloc(sizeof(tree)); // выделение памяти
    tempTree1 = t;

    node *tempNode;
    tempNode = (node *)malloc(sizeof(node));
    tempNode = tempTree->root;

    long int countNode = tempTree->count;
    if (tempTree && tempNode && insertNode)
    {
        if (find(tempTree1, value))
        {
            return 1;
        }
        else
        {
            if (countNode != 0)
            {
                tempNode = tempTree->root;
                while (tempNode)
                {
                    if (value > tempNode->value)
                    {
                        if (tempNode->right)
                        {
                            tempNode = tempNode->right;
                            continue;
                        }
                        else
                        {
                            insertNode->parent = tempNode;
                            tempNode->right = insertNode;
                            tempTree->count = countNode + 1;
                            return 0;
                        }
                    }
                    else
                    {
                        if (tempNode->left)
                        {
                            tempNode = tempNode->left;
                            continue;
                        }
                        else
                        {
                            insertNode->parent = tempNode;
                            tempNode->left = insertNode;
                            tempTree->count = countNode + 1;
                            return 0;
                        }
                    }
                }
                return 2;
            }
            else
            {
                tempTree->root = insertNode;
                tempTree->count = 1;
                return 0;
            }
        }
    }
    else
    {
        return 2;
    }
}

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
long int remove_node(tree *t, long int value)
{
    tree *tempTree;
    tempTree = (tree *)malloc(sizeof(tree));
    tempTree = t;

    node *foundNode; // для найденного узла
    foundNode = (node *)malloc(sizeof(node));
    foundNode = find(t, value);

    node *foundNode1; // для найденного узла
    foundNode1 = (node *)malloc(sizeof(node));
    foundNode1 = foundNode;

    if (foundNode)
    {
        if (foundNode->left && foundNode->right)
        { // если есть оба потомка
            node *leftmostNode = (node *)malloc(sizeof(node));
            node *rightRoot = (node *)malloc(sizeof(node));
            node *leftRoot = (node *)malloc(sizeof(node));
            node *leftRightRootNode = (node *)malloc(sizeof(node));
            node *leftmostRightRootNode = (node *)malloc(sizeof(node));
            rightRoot = foundNode->right; // корень правого поддерева
            leftRoot = foundNode->left;   // корень левого поддерева
            if (rightRoot->left)
            {
                // если у правого корня есть левый потомок
                leftmostNode = rightRoot->left; // самый левый потомок правого узла
                while (leftmostNode->left)      // находим действительно самый левый потомок правого узла
                    leftmostNode = leftmostNode->left;
                if (leftmostNode->right)
                {
                    // если у самого левого потомка правого узла есть правый потомок
                    leftRightRootNode = leftmostNode->right;
                    if (rightRoot->right)
                    {
                        // если у правого корня поддерева есть правый потомок
                        leftmostRightRootNode = rightRoot->right;
                        while (leftmostRightRootNode->left)
                        { // ищем минимальный элемент правого поддерева
                            leftmostRightRootNode = leftmostRightRootNode->left;
                        }
                    }
                    else
                    {
                        // если у корня правого дерева нет правого потомка
                        leftmostRightRootNode = leftmostNode->parent;
                    }
                    // делаем так, что теперь у минимального элемента правого поддерва есть минимальные элементы левого поддерева
                    leftRightRootNode->parent = leftmostRightRootNode;
                    leftmostRightRootNode->left = leftRightRootNode;
                    leftmostNode->right = NULL;
                }
                leftmostNode->parent->left = NULL; // теперь родитель самого левого потомка на него не ссылается
                leftmostNode->parent = NULL;       // у самого левого потомка теперь нет родителя
                leftmostNode->right = rightRoot;   // теперь правый потомок для самого левого элемента - правый корень поддерева
                rightRoot->parent = NULL;
                rightRoot->parent = leftmostNode; // теперь родитель для корня правого поддерева - самый левый элемент этого поддерева
                leftmostNode->left = leftRoot;
                leftRoot->parent = NULL;
                leftRoot->parent = leftmostNode; // теперь родитель для корня левого поддерева - самый левый элемент правого поддерева
                leftmostNode->parent = foundNode->parent;
                if (leftmostNode->parent == foundNode)
                { // если удаляемый элемент корень дерева
                    leftmostNode->parent = leftmostNode;
                    t->root = leftmostNode;
                }
                else
                {
                    // если удаляемый элемент не корень дерева
                    if (leftmostNode->parent->value < leftmostNode->value)
                    {
                        // если наш элемент стоит справа от родительского узла
                        leftmostNode->parent->right = leftmostNode;
                    }
                    else
                    {
                        // если наш элемент стоит слева от родительского узла
                        leftmostNode->parent->left = leftmostNode;
                    }
                }
                foundNode->left = NULL;
                foundNode->right = NULL;
                foundNode->parent = NULL;
                foundNode = NULL;
                return 0; // элемент удален
            }
            else
            {
                // если у правого корня нет левого потомка
                rightRoot->left = leftRoot;
                leftRoot->parent = NULL;
                leftRoot->parent = rightRoot;
                rightRoot->parent = foundNode->parent;
                if (rightRoot->parent == foundNode)
                {
                    rightRoot->parent = rightRoot;
                    t->root = rightRoot;
                }
                else
                {
                    if (rightRoot->parent->value < rightRoot->value)
                    {
                        rightRoot->parent->right = rightRoot;
                    }
                    else
                    {
                        rightRoot->parent->left = rightRoot;
                    }
                }
                foundNode->left = NULL;
                foundNode->right = NULL;
                foundNode->parent = NULL;
                foundNode = NULL;
                return 0; // элемент удален
            }
            return 0;
        }
        else if (foundNode->left)
        { // если есть только левый дочерний узел
            node *firstLeftNode = (node *)malloc(sizeof(node));
            firstLeftNode = foundNode->left;
            if (t->root == foundNode)
            {
                firstLeftNode->parent = firstLeftNode;
                t->root = firstLeftNode;
            }
            else
            {
                firstLeftNode->parent = foundNode->parent;
                if (foundNode->value > foundNode->parent->value)
                {
                    // если искомое число стояло справа
                    firstLeftNode->parent->right = firstLeftNode;
                }
                else
                {
                    firstLeftNode->parent->left = firstLeftNode;
                }
            }
            return 0;
        }
        else if (foundNode->right)
        { // если есть только правый дочерний узел
            node *firstRightNode = (node *)malloc(sizeof(node));
            firstRightNode = foundNode->right;
            if (foundNode == t->root)
            {
                firstRightNode->parent = firstRightNode;
                t->root = firstRightNode;
            }
            else
            {
                firstRightNode->parent = foundNode->parent;
                if (foundNode->value > foundNode->parent->value)
                {
                    firstRightNode->parent->right = firstRightNode;
                }
                else
                {
                    firstRightNode->parent->left = firstRightNode;
                }
            }
            return 0;
        }
        else
        {
            // если нет дочерних узлов

            if (foundNode->value > foundNode->parent->value)
            {
                // если элемент стоит справа
                foundNode->parent->right = NULL;
            }
            else
            {
                foundNode->parent->left = NULL;
            }
            foundNode->parent = NULL;
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элементаА
long int remove_min(node *n)
{
    long int valueNode;

    node *tempNode;
    tempNode = (node *)malloc(sizeof(node));
    tempNode = n;

    node *leftmostNode;
    leftmostNode = (node *)malloc(sizeof(node));
    leftmostNode = tempNode;

    node *parentNode;
    parentNode = (node *)malloc(sizeof(node));
    parentNode = tempNode->parent;

    while (tempNode->left)
    {
        tempNode = tempNode->left;
    }
    if (tempNode->right)
    {
        tempNode = tempNode->right;
        remove_min(tempNode);
    }
    else
    {
        valueNode = tempNode->value;
        if (tempNode->value > tempNode->parent->value)
        {
            tempNode->parent->right = NULL;
        }
        else
        {
            tempNode->parent->left = NULL;
        }
        tempNode->parent = NULL;
        free(tempNode);
        return valueNode;
    }
}

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
long int rotate_right(node *n)
{
    node *tempNode;
    tempNode = (node *)malloc(sizeof(node));
    tempNode = n;

    node *leftRoot;
    leftRoot = (node *)malloc(sizeof(node));
    leftRoot = tempNode->left;

    if (tempNode && leftRoot)
    {
        tempNode->left = leftRoot->right;
        if (leftRoot->right)
            leftRoot->right->parent = tempNode;
        leftRoot->parent = tempNode->parent;
        if (leftRoot->parent == tempNode)
        {
            leftRoot->parent = leftRoot;
        }
        else
        {
            if (leftRoot->parent->value < leftRoot->value)
            {
                // если элемент стоит справа
                leftRoot->parent->right = leftRoot;
            }
            else
            {
                leftRoot->parent->left = leftRoot;
            }
        }
        leftRoot->right = tempNode;
        tempNode->parent = leftRoot;
        return 0;
    }
    else
    {
        return 1;
    }
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
long int rotate_left(node *n)
{
    node *tempNode; // отвечает за начальный узел
    tempNode = (node *)malloc(sizeof(node));
    tempNode = n;

    node *rightRoot; // отвечает за правый корень поддерева начального узла
    rightRoot = (node *)malloc(sizeof(node));
    rightRoot = tempNode->right;

    node *leftRightRoot;
    leftRightRoot = (node *)malloc(sizeof(node));

    if (tempNode && rightRoot)
    {
        leftRightRoot = rightRoot->left;
        tempNode->right = leftRightRoot;
        if (leftRightRoot)
            leftRightRoot->parent = tempNode;

        rightRoot->parent = tempNode->parent;
        if (rightRoot->parent == tempNode)
            rightRoot->parent = rightRoot;
        tempNode->parent = rightRoot;
        rightRoot->left = tempNode;
        return 0;
    }
    else
    {
        return 1;
    }
}

// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке.
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _.
// Если дерево пусто, вывести -
void print(node *n)
{
    node *tempNode;
    tempNode = (node *)malloc(sizeof(node));
    tempNode = n;

    node *reserveNode;
    reserveNode = (node *)malloc(sizeof(node));
    reserveNode->left = reserveNode;
    reserveNode->right = reserveNode;
    reserveNode->value = 11;

    if (tempNode)
    {
        long int oldlvl = 1, lvl = 1, cnt = 0, i = 0, j = 0;
        node **arrNode = (node **)malloc(lvl * sizeof(node *));
        node **tempArr = NULL;
        arrNode[0] = tempNode;
        printf("%ld\n", arrNode[0]->value);
        bool flag = true;
        long int size = oldlvl;
        while (flag)
        {
            flag = false;
            oldlvl = lvl;
            lvl *= 2;
            size += lvl;
            arrNode = (node **)realloc(arrNode, size * sizeof(node *));
            for (i = oldlvl - 1, j = lvl - 1; i < (lvl - 1); i++, j++)
            {
                if (arrNode[i]->left && arrNode[i] != reserveNode)
                {
                    flag = true;
                    arrNode[j] = arrNode[i]->left;
                }
                else
                {
                    arrNode[j] = reserveNode;
                }
                ++j;
                if (arrNode[i]->right && arrNode[i] != reserveNode)
                {
                    flag = true;
                    arrNode[j] = arrNode[i]->right;
                }
                else
                {
                    arrNode[j] = reserveNode;
                }
            }
            if (flag)
            {
                for (i = oldlvl - 1, j = lvl - 1; i < (lvl - 1); i++, j++)
                {
                    if (arrNode[i]->left && arrNode[i] != reserveNode)
                    {
                        printf("%ld ", arrNode[i]->left->value);
                    }
                    else
                    {
                        printf("_ ");
                    }
                    ++j;
                    if (arrNode[i]->right && arrNode[i] != reserveNode)
                    {
                        printf("%ld ", arrNode[i]->right->value);
                    }
                    else
                    {
                        printf("_ ");
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    else
    {
        printf("-\n");
        printf("\n");
        return;
    }
}

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree *t)
{
    node *rootNode;
    rootNode = (node *)malloc(sizeof(node));
    rootNode = t->root;
    if (t->count > 0 && rootNode)
        print(rootNode);
    else
    {
        printf("-\n");
        printf("\n");
        return;
    }
}

// обход дерева в ширину
void bfs(node *n)
{
    node *tempNode;
    tempNode = (node *)malloc(sizeof(node));
    tempNode = n;

    node *reserveNode;
    reserveNode = (node *)malloc(sizeof(node));
    reserveNode->left = reserveNode;
    reserveNode->right = reserveNode;
    reserveNode->value = 11;

    if (tempNode)
    {
        long int oldlvl = 1, lvl = 1, cnt = 0, i = 0, j = 0;
        node **arrNode = (node **)malloc(lvl * sizeof(node *));
        node **tempArr = NULL;
        arrNode[0] = tempNode;
        printf("%ld ", arrNode[0]->value);
        bool flag = true;
        long int size = oldlvl;
        while (flag)
        {
            flag = false;
            oldlvl = lvl;
            lvl *= 2;
            size += lvl;
            arrNode = (node **)realloc(arrNode, size * sizeof(node *));
            for (i = oldlvl - 1, j = lvl - 1; i < (lvl - 1); i++, j++)
            {
                if (arrNode[i]->left && arrNode[i] != reserveNode)
                {
                    flag = true;
                    arrNode[j] = arrNode[i]->left;
                }
                else
                {
                    arrNode[j] = reserveNode;
                }
                ++j;
                if (arrNode[i]->right && arrNode[i] != reserveNode)
                {
                    flag = true;
                    arrNode[j] = arrNode[i]->right;
                }
                else
                {
                    arrNode[j] = reserveNode;
                }
            }
            if (flag)
            {
                for (i = oldlvl - 1, j = lvl - 1; i < (lvl - 1); i++, j++)
                {
                    if (arrNode[i]->left && arrNode[i] != reserveNode)
                    {
                        printf("%ld ", arrNode[i]->left->value);
                    }
                    ++j;
                    if (arrNode[i]->right && arrNode[i] != reserveNode)
                    {
                        printf("%ld ", arrNode[i]->right->value);
                    }
                }
            }
        }
        printf("\n");
    }
    else
    {
        printf("\n");
        return;
    }
}

int main()
{
    tree *t = (tree *)malloc(sizeof(tree));
    node *tempNode = (node *)malloc(sizeof(node));
    init(t);
    long int value;

    // 1. считывает 7 элементов и заносит их в дерево
    for (long int i = 0; i < 7; i++)
    {
        scanf("%ld", &value);
        insert(t, value);
    }
    // ЗДЕСЬ ОБХОД В ШИРИНУ
    tempNode = t->root;
    bfs(tempNode);
    return 0;
}
// end.
