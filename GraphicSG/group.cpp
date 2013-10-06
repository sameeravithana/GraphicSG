#include "group.h"
#include "nodevisitor.h"
#include "state.h"


using namespace std;

Group::Group(Node* Parent, const char* Name)
    : m_Name(Name)
{
    m_Parent = Parent;
    
} // Constructor

Group::~Group(void)
{
    m_Parent = NULL;
    m_Children.clear();
} // Destructor


void Group::RemoveChildNode(Node* ChildNode)
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

const char* Group::GetGroupName(void) const
{
    return(m_Name);
}; // GetNodeName()


void Group::accept(class NodeVisitor* v){
    v->visit(this);
}

void Group::setGroupBackground()
{
    State state;
        state.setEnableLighting(new Light(),true);
        
        state.apply();
        
        
}

int Group::getNodeType(){
    return 1;
}