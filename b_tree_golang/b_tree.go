package main

import "slices"

type BTree struct {
    root BTreeNode  // root
    height int      // h
    minNodes int    // t
}

type BTreeNode struct {
    numKeys int             // n
    keys []int              // keys list
    children []BTreeNode    // Children list
    leaf bool               // leaf
}

func CreateBTree (minNodes int) (btree BTree, err error) {
    treeRoot := BTreeNode{
        0,
        nil,
        nil,
        true,
    }

    btree = BTree{
        treeRoot,
        0,
        minNodes,
    }
    return btree, err
}

func (tree *BTree) InsertElement (element int) (_ int, err error) {
    currentRoot := tree.root
    if currentRoot.numKeys == ((2 * tree.minNodes) - 1) {
        splitedRoot := BTreeNode{
            0,
            nil,
            []BTreeNode{currentRoot},
            false,
        }
        tree.root = splitedRoot
        _, err = tree.splitTreeNode(splitedRoot, 1)

        if err != nil {
            return 1, err
        }

        _, err = splitedRoot.insertNonFull(element, tree.minNodes)

        if err != nil {
            return 1, err
        }

        return 0, err
    }

    _, err = currentRoot.insertNonFull(element, tree.minNodes)

    return 0, err
}

func (tree *BTree) splitTreeNode (parentNode BTreeNode, indexChildNode int) (_ int, err error) {
    splitChild := parentNode.children[indexChildNode]
    newChild := BTreeNode{
        tree.minNodes - 1,
        nil,
        nil,
        splitChild.leaf,
    }

    for i := 0; i < tree.minNodes - 1; i++ {
        newChild.keys = append(newChild.keys, splitChild.keys[i + tree.minNodes])
    }

    if ! newChild.leaf {
        for i := 0; i < tree.minNodes; i++ {
            newChild.children = append(newChild.children, splitChild.children[i + tree.minNodes])
        }
    }

    splitChild.numKeys = tree.minNodes - 1
    parentNode.children = slices.Insert(parentNode.children, indexChildNode + 1, newChild)
    parentNode.keys = slices.Insert(parentNode.keys, indexChildNode, tree.minNodes)
    parentNode.numKeys++

    return 0, err
}

func (treeNode *BTreeNode) insertNonFull (element int, minNodes int) (_ int, err error) {
    numNodeElements := treeNode.numKeys

    if treeNode.leaf {
        for numNodeElements >= 1 && element < treeNode.keys[numNodeElements] {
            numNodeElements--    
        }
        
        treeNode.keys = slices.Insert(treeNode.keys, numNodeElements + 1, element)

    } else {
        for numNodeElements >= 1 && element < treeNode.keys[numNodeElements] {
            numNodeElements--
        }

        numNodeElements++
        
        if treeNode.children[numNodeElements].numKeys == (2 * minNodes) - 1 {
            
        }
    }
        

    return 0, err
}

func main () {}
