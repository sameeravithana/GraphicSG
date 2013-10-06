/* 
 * File:   group.h
 * Author: samtube405
 *
 * Created on September 21, 2013, 5:55 PM
 */


#ifndef GROUP_H
#define	GROUP_H

#include "node.h"


class Group : public Node{
    public:
        Group(){};
        Group(Node* Parent, const char* Name);
        ~Group();
        
        void accept(class NodeVisitor* v);
        
        //void AddChildNode(Group* ChildNode);
        void RemoveChildNode(Node* ChildNode);
        
        const char* GetGroupName(void) const;
        //const size_t CountChildNodes(const bool& RecursiveCount = false) const;
        void setGroupBackground();
        
        int getNodeType();
        
    private:
        //int nodecount;
        
        Node* m_Parent;
        const char* m_Name;
        std::vector<Node*> m_Children;
            
        
       
};


#endif	/* GROUP_H */

