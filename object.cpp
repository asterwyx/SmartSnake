#include "object.h"

/**
 * CBound的函数定义
 */
collision::CBound::CBound(base::CPoint *aBoundCenter, EBoundType aBoundType, std::vector<int> *pBoundSizes)
{
    this->m_BoundCenter = aBoundCenter;
    this->m_eBoundType = aBoundType;
    this->m_BoundPoints = new std::vector<base::CPoint*>();
    this->m_BoundSizes = pBoundSizes;
    this->m_BoundPoints->push_back(this->m_BoundCenter);

    switch (this->m_eBoundType)
    {
    case CIRCLE:
        break;
    case RECTANGLE:
        {// 设定矩形的左上角顶点为Bound的中心
            auto rightUp = new base::CPoint(this->m_BoundCenter->GetPosX() + this->m_BoundSizes->at(0), this->m_BoundCenter->GetPosY());
            auto rightDown = new base::CPoint(this->m_BoundCenter->GetPosX() + this->m_BoundSizes->at(0), this->m_BoundCenter->GetPosY() - this->m_BoundSizes->at(1));
            auto leftDown = new base::CPoint(this->m_BoundCenter->GetPosX(), this->m_BoundCenter->GetPosY() - this->m_BoundSizes->at(1));
            this->m_BoundPoints->push_back(rightUp);
            this->m_BoundPoints->push_back(rightDown);
            this->m_BoundPoints->push_back(leftDown);
        }
        break;
    case TRIANGLE:
        // 三角形以某一个顶点为Bound的中心，sizes中存放另外两个点以中心为起点的向量
        {
            auto vertex1 = new base::CPoint(this->m_BoundCenter->GetPosX() +  this->m_BoundSizes->at(0), this->m_BoundCenter->GetPosY() + this->m_BoundSizes->at(1));
            auto vertex2 = new base::CPoint(this->m_BoundCenter->GetPosX() + this->m_BoundSizes->at(2), this->m_BoundCenter->GetPosY() + this->m_BoundSizes->at(3));
            this->m_BoundPoints->push_back(vertex1);
            this->m_BoundPoints->push_back(vertex2);
        }
        break;
    default:
        break;
    }
}

/**
 *  重载的构造函数，调用了第一个复杂的构造函数，不用自己创建CPoint对象
 */
collision::CBound::CBound(int aCenterX, int aCenterY, EBoundType aBoundType, std::vector<int> *pBoundSizes) : 
    CBound(nullptr, aBoundType, pBoundSizes)
{
    this->m_BoundCenter = new base::CPoint(aCenterX, aCenterY);
}

void collision::CBound::SetBoundCenter(int aPosX, int aPosY)
{
    this->m_BoundCenter->SetPos(aPosX, aPosY);
}

const base::CPoint *collision::CBound::GetBoundCenter()
{
    return this->m_BoundCenter;
}

const std::vector<int> *collision::CBound::GetBoundSizes()
{
    return this->m_BoundSizes;
}

void collision::CBound::SetBoundSizes(std::vector<int> *pBoundSizes)
{
    this->m_BoundSizes = pBoundSizes;
}

/**
 * CPoint的函数定义
 */
base::CPoint::CPoint(int aPosX, int aPosY)
{
    this->m_iPosX = aPosX;
    this->m_iPosY = aPosY;
}

int base::CPoint::GetPosX()
{
    return this->m_iPosX;
}

int base::CPoint::GetPosY()
{
    return this->m_iPosY;
}

void base::CPoint::SetPos(int aPosX, int aPosY)
{
    this->m_iPosX = aPosX;
    this->m_iPosY = aPosY;
}

/**
 * CNode的函数定义
 */
base::CNode::CNode(int aPosX, int aPosY, int pWidth, int pHeight, SDL_Texture *aTexture)
{
    this->m_Pos = new base::CPoint(aPosX, aPosY);
    this->m_iWidth = pWidth;
    this->m_iHeight = pHeight;
    this->m_Texture = aTexture;

}

/**
 *  \brief 渲染一个节点的Texture
 *  \param pRenderer 用来渲染的渲染器
 *  使用RenderCopy将Texture复制到合适位置
 */
void base::CNode::Render(SDL_Renderer *pRenderer)
{
    SDL_Rect r;
    r.x = this->m_Pos->GetPosX();
    r.y = this->m_Pos->GetPosY();
    r.w = this->m_iWidth;
    r.h = this->m_iHeight;
    SDL_RenderCopy(pRenderer, this->m_Texture, NULL, &r);
}

SDL_Texture *base::CNode::GetTexture()
{
    return this->m_Texture;
}

int base::CNode::GetWidth()
{
    return this->m_iWidth;
}

int base::CNode::GetHeight()
{
    return this->m_iHeight;
}

base::CNode::CNode(const CNode &pSource)
{
    this->m_Pos = new base::CPoint(pSource.m_Pos->GetPosX(), pSource.m_Pos->GetPosY());
    // 因为不了解Texture的自主构造，SDL也没有提供复制函数，所以这里干脆使用浅拷贝，这里就要注意，如果Node是由复制构造函数得来的，那么它们是共享一个Texture的，一定要注意不要轻易更改Texture。
    this->m_Texture = pSource.m_Texture;
    this->m_iWidth = pSource.m_iWidth;
    this->m_iHeight = pSource.m_iHeight;
}

base::CNode::~CNode()
{
    this->m_Pos->~CPoint();
    // 因为是共享的Texture，就不在这里Destroy了
}


/**
 * CObject的函数定义 
 */
base::CObject::CObject()
{
    this->m_NodeDList = new std::list<CNode>();
}

/**
 *  \brief 画一个Object
 *  \param pRenderer 使用的窗口的渲染器
 *  具体步骤是将每一个Node的Texture拷贝到pRenderer上，然后最后show一下这个renderer
 */
void base::CObject::Draw(SDL_Renderer *pRenderer)
{
    SDL_SetRenderTarget(pRenderer, NULL);
    std::list<base::CNode>::iterator iter = this->m_NodeDList->begin(); // 获取迭代器
    while (iter != this->m_NodeDList->end())
    {
        iter->Render(pRenderer);
        ++iter;
    }
    // 展示渲染结果
    SDL_RenderPresent(pRenderer);
}

const std::list<base::CNode> *base::CObject::GetNodeList() const
{
    return this->m_NodeDList;
}

void base::CObject::SetNodeList(std::list<base::CNode> *pSourceList)
{
    delete this->m_NodeDList;
    this->m_NodeDList = pSourceList;
}

// CObject的复制构造函数
base::CObject::CObject(const CObject &pSource)
: CObject()
{
    const std::list<CNode> *nodeList = pSource.GetNodeList();
    // 这里的迭代器实际上就是一个元素的指针，可以使用解引用获取该元素
    std::list<CNode>::const_iterator iter = nodeList->begin();
    for (; iter != nodeList->end(); ++iter)
    {
        // push_back会调用对象的复制构造函数，默认复制构造函数是浅拷贝，我们重写构造函数实现一个深拷贝
        this->m_NodeDList->push_back(*iter);
    }
}

base::CObject::~CObject()
{
    // delete会调用对象的析构函数，这里直接delete掉动态内存成员即可。
    delete this->m_NodeDList;
}