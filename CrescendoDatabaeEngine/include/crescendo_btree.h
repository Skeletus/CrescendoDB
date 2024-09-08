#ifndef CRESCENDO_BTREE_H
#define CRESCENDO_BTREE_H

#include <vector>
#include <iostream>
#include <memory> // Para std::shared_ptr

namespace Crescendo {

// Definición del grado mínimo del B-Tree (t).
constexpr int MIN_DEGREE = 3;

// Nodo del árbol B.
class BTreeNode : public std::enable_shared_from_this<BTreeNode>{
public:
    BTreeNode(bool is_leaf);

    // Inserta una nueva clave en el nodo.
    void insertNonFull(int key);

    // Divide el nodo hijo cuando se llena.
    void splitChild(int i, std::shared_ptr<BTreeNode> y);

    // Imprime todas las claves en el subárbol enraizado con este nodo.
    void traverse();

    // Función para buscar una clave en el árbol.
    std::shared_ptr<BTreeNode> search(int key);

    // Indica si el nodo es una hoja.
    bool isLeaf() const { return is_leaf_; }

    // Funciones amigas para acceder a miembros privados desde la clase BTree.
    friend class BTree;

private:
    std::vector<int> keys_;                       // Vector de claves del nodo.
    std::vector<std::shared_ptr<BTreeNode>> children_; // Punteros a los hijos del nodo.
    bool is_leaf_;                                // Indica si el nodo es una hoja.
    int n_;                                       // Número actual de claves en el nodo.
};

// Clase que representa un B-Tree.
class BTree {
public:
    BTree();

    // Función para recorrer el B-Tree.
    void traverse() const;

    // Función para buscar una clave en el B-Tree.
    std::shared_ptr<BTreeNode> search(int key) const;

    // Función para insertar una nueva clave en el B-Tree.
    void insert(int key);

private:
    std::shared_ptr<BTreeNode> root_; // Puntero a la raíz del B-Tree.
};

}  // namespace Crescendo

#endif  // CRESCENDO_BTREE_H
