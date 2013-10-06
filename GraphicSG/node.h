/* 
 * File:   node.h
 * Author: samtube405
 *
 * Created on September 21, 2013, 12:36 PM
 */


#ifndef __node_h_
#define __node_h_ 1
#include <vector>
#include <iostream>

using namespace std;
 
class Node
{
public:
    Node(Node* Parent = NULL, const char* Name = NULL);
    virtual ~Node(void);
 
    virtual void accept(class NodeVisitor* v)=0;
    
    virtual void Update(void);
 
    Node* GetParentNode(void) const;
    void SetParentNode(Node* NewParent);
    
    std::vector<Node*>* getChildNodes();
 
    void AddChildNode(Node* ChildNode);
    void RemoveChildNode(Node* ChildNode);
 
    void setNodeName(const char* name);
    const char* GetNodeName(void) const;
    const size_t CountChildNodes(const bool& RecursiveCount = false) const;
    
    
    //const bool IsRootNode(void) const = 0;
 
    Node* GetChildNodeByName(const char* SearchName);
    
    void setColor(int col);
    int getColor();
    
    
 
private:
    Node* m_Parent;
    const char* m_Name;
    std::vector<Node*> m_Children;
    int* color;
    
    
 
}; // class Node
 
#endif

