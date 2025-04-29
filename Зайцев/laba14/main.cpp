#include <iostream>

using namespace std;

struct tnode {
    int field;
    tnode* left;
    tnode* right;
    tnode(int value) : field(value), left(nullptr), right(nullptr) {}
};

// Обход дерева сверху вниз
void treeprint(tnode* tree) {
    if (tree != NULL) {
        cout << tree->field << " ";
        treeprint(tree->left);
        treeprint(tree->right);
    }
}

// Заполнение дерева (слева меньшее значение)
tnode* insert(tnode* root, int value) {
    if (root == nullptr) {
        return new tnode(value);
    }
    if (value < root->field) {
        root->left = insert(root->left, value);
    }
    else {
        root->right = insert(root->right, value);
    }

    return root;
}

// Заполнение дерева (слева большее значение)
tnode* insert(tnode* root, int value, int choise) {
    if (root == nullptr) {
        return new tnode(value);
    }
    if (value > root->field) { // Значения больше идут в левое поддерево
        root->left = insert(root->left, value, choise);
    }
    else { // Значения меньше или равные идут в правое поддерево
        root->right = insert(root->right, value, choise);
    }

    return root;
}

// Проверка на зеркальность деревьев
bool checker(tnode* root, tnode* root_one) {
    if (root == nullptr && root_one == nullptr) {
        return true; // Оба дерева пустые — зеркальны
    }
    if (root == nullptr || root_one == nullptr) {
        return false; // Одно из деревьев пустое — не зеркальны
    }
    return (root->field == root_one->field &&
        checker(root->left, root_one->right) &&
        checker(root->right, root_one->left));
}

int main() {
    setlocale(LC_ALL, "Russian");

    tnode* root = nullptr;
    tnode* root_one = nullptr;

    // Создаем первое дерево (слева меньшее значение)
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 7);

    // Создаем второе дерево (слева большее значение)
    root_one = insert(root_one, 10, 1);
    root_one = insert(root_one, 5, 1);
    root_one = insert(root_one, 15, 1);
    root_one = insert(root_one, 3, 1);
    root_one = insert(root_one, 7, 1);

    // Печатаем деревья
    cout << "Первое дерево: ";
    treeprint(root);
    cout << endl;

    cout << "Второе дерево: ";
    treeprint(root_one);
    cout << endl;

    // Проверяем зеркальность
    if (checker(root, root_one)) {
        cout << "Заданные деревья зеркальны" << endl;
    }
    else {
        cout << "Заданные деревья не зеркальны" << endl;
    }

    return 0;
}
