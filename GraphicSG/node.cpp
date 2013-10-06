#include "node.h"
#include <cstring>

Node::Node(Node* Parent, const char* Name)
    : m_Name(Name)
{
    m_Parent = Parent;
    
} // Constructor

Node::~Node()
{
    m_Parent = NULL;
    m_Children.clear();
} // Destructor

void Node::Update(void)
{
    if(!m_Children.empty())
    {
        for(size_t i = 0; i < m_Children.size(); ++i)
        {
            if(NULL != m_Children[i])
            {
                m_Children[i]->Update();
            }
        }
    }
} // Update()

std::vector<Node*>* Node::getChildNodes()
{
    if(!m_Children.empty())
    {
        return &(this->m_Children);
    }
}

Node* Node::GetParentNode(void) const
{
    return(m_Parent);
}; // GetParentNode()

void Node::SetParentNode(Node* NewParent)
{
    if(NULL != m_Parent)
    {
        m_Parent->RemoveChildNode(this);
    }
    m_Parent = NewParent;
}; // SetParentNode()

void Node::AddChildNode(Node* ChildNode)
{
    if(NULL != ChildNode)
    {
        if(NULL != ChildNode->GetParentNode())
        {
            ChildNode->SetParentNode(this);
        }
        m_Children.push_back(ChildNode);
    }
}; // AddChildNode()

void Node::RemoveChildNode(Node* ChildNode)
{
    if(NULL != ChildNode && !m_Children.empty())
    {
        for(size_t i = 0; i < m_Children.size(); ++i)
        {
            if(m_Children[i] == ChildNode)
            {
                m_Children.erase(m_Children.begin() + i);
                break; // break the for loop
            }
        }
    }
}; // RemoveChildNode()

void Node::setNodeName(const char* name)
{
    this->m_Name=name;
}

const char* Node::GetNodeName(void) const
{
    return(m_Name);
}; // GetNodeName()


const size_t Node::CountChildNodes(const bool &RecursiveCount) const
{
    if(!RecursiveCount)
    {
        return(m_Children.size());
    }
    else
    {
        size_t Retval = m_Children.size();
        for(size_t i = 0; i < m_Children.size(); ++i)
        {
            Retval += m_Children[i]->CountChildNodes(true);
        }
        return(Retval);
    }
}; // CountChildNodes()

Node* Node::GetChildNodeByName(const char *SearchName)
{
    Node* Retval = NULL;
    if(!m_Children.empty())
    {
        for(size_t i = 0; i < m_Children.size(); ++i)
        {
            if(0 == strcmp(m_Children[i]->m_Name, SearchName))
            {
                Retval = m_Children[i];
                break; // break the for loop
            }
        }
    }
    return(Retval);
}; // GetChildNodeByName()

void Node::setColor(int col)
{
    this->color=&col;
}

int Node::getColor()
{
    return *(this->color);
}