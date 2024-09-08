#include "crescendo_btree.h"

namespace Crescendo {

// Constructor para BTreeNode.
BTreeNode::BTreeNode(bool is_leaf) : is_leaf_(is_leaf), n_(0) {
    keys_.resize(2 * MIN_DEGREE - 1);
    children_.resize(2 * MIN_DEGREE);
}

// Método para recorrer el árbol.
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n_; i++) {
        if (!is_leaf_) {
            children_[i]->traverse();
        }
        std::cout << " " << keys_[i];
    }

    if (!is_leaf_) {
        children_[i]->traverse();
    }
}

// Método para buscar una clave en el nodo.
std::shared_ptr<BTreeNode> BTreeNode::search(int key) {
    int i = 0;
    while (i < n_ && key > keys_[i]) {
        i++;
    }

    if (keys_[i] == key) {
        return shared_from_this();
    }

    if (is_leaf_) {
        return nullptr;
    }

    return children_[i]->search(key);
}

// Método para insertar una clave en un nodo no lleno.
void BTreeNode::insertNonFull(int key) {
    int i = n_ - 1;

    if (is_leaf_) {
        while (i >= 0 && keys_[i] > key) {
            keys_[i + 1] = keys_[i];
            i--;
        }

        keys_[i + 1] = key;
        n_++;
    } else {
        while (i >= 0 && keys_[i] > key) {
            i--;
        }

        if (children_[i + 1]->n_ == 2 * MIN_DEGREE - 1) {
            splitChild(i + 1, children_[i + 1]);

            if (keys_[i + 1] < key) {
                i++;
            }
        }
        children_[i + 1]->insertNonFull(key);
    }
}

// Método para dividir un nodo hijo lleno.
void BTreeNode::splitChild(int i, std::shared_ptr<BTreeNode> y) {
    auto z = std::make_shared<BTreeNode>(y->is_leaf_);
    z->n_ = MIN_DEGREE - 1;

    for (int j = 0; j < MIN_DEGREE - 1; j++) {
        z->keys_[j] = y->keys_[j + MIN_DEGREE];
    }

    if (!y->is_leaf_) {
        for (int j = 0; j < MIN_DEGREE; j++) {
            z->children_[j] = y->children_[j + MIN_DEGREE];
        }
    }

    y->n_ = MIN_DEGREE - 1;

    for (int j = n_; j >= i + 1; j--) {
        children_[j + 1] = children_[j];
    }

    children_[i + 1] = z;

    for (int j = n_ - 1; j >= i; j--) {
        keys_[j + 1] = keys_[j];
    }

    keys_[i] = y->keys_[MIN_DEGREE - 1];
    n_++;
}

// Constructor de BTree.
BTree::BTree() : root_(std::make_shared<BTreeNode>(true)) {}

// Método para recorrer el árbol.
void BTree::traverse() const {
    if (root_ != nullptr) {
        root_->traverse();
    }
}

// Método para buscar una clave en el árbol.
std::shared_ptr<BTreeNode> BTree::search(int key) const {
    return (root_ == nullptr) ? nullptr : root_->search(key);
}

// Método para insertar una clave en el árbol.
void BTree::insert(int key) {
    if (root_->n_ == 2 * MIN_DEGREE - 1) {
        auto s = std::make_shared<BTreeNode>(false);
        s->children_[0] = root_;
        s->splitChild(0, root_);
        root_ = s;
    }

    root_->insertNonFull(key);
}

}  // namespace Crescendo
