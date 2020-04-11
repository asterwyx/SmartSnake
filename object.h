/**
 *  \file object.h
 *  \brief 地图上交互物体的基类
 *  author: asterwyx
 */

#ifndef _OBJECT_H
#define _OBJECT_H
#include <list>
#include <vector>
#include <SDL.h>

/**
 *  命名空间base，主要是一些游戏基本物体类，包括点，交互物体等
 * 
 */
namespace base {
class CPoint
{
public:
    CPoint(int aPosX, int aPosY);
    void SetPos(int aPosX, int aPosY);
    int GetPosX();
    int GetPosY();
private:
    int m_iPosX;
    int m_iPosY;
};

/**
 *  交互物体的结点
 */
class CNode
{
public:
    CNode(int aPosX, int aPosY, int pWidth, int pHeight, SDL_Texture *aTexture);
    void Render(SDL_Renderer *pRenderer);
    SDL_Texture *GetTexture();
    int GetWidth();
    int GetHeight();
    CNode(const CNode &pSource);
    ~CNode();
    
private:
    CPoint *m_Pos;
    SDL_Texture *m_Texture;
    int m_iWidth;
    int m_iHeight;
};

/**
 *  结点集合（比如蛇）基类
 * 
 */
class CObject
{
public:
    CObject();
    void Draw(SDL_Renderer *pRenderer);
    const std::list<base::CNode> *GetNodeList() const;
    void SetNodeList(std::list<base::CNode> *pSourceList);
    CObject(const CObject &aSource);
    ~CObject();

private:
    std::list<base::CNode> *m_NodeDList;

};
}

/**
 *  命名空间collision，与碰撞检测相关的类
 * 
 */
namespace collision
{
typedef enum BoundType
{
    RECTANGLE,
    CIRCLE,
    TRIANGLE
} EBoundType;
/**
 *  碰撞检测边界类，存储了关于碰撞检测边界的信息
 *  \member m_BoundCenter 碰撞边界几何图形的中心，这个中心是人为规定的，不一定是几何图形的中心，比如矩形可能是左上角，也可以说是基准点
 *  \member m_eBoundType 碰撞检测边界的类型，是圆形还是矩形还是三角形，不同的形状检测的方法不一样
 *  \member m_BoundPoints 构成碰撞检测边界的点的vector
 */
class CBound
{
public:
    CBound(base::CPoint *aBoundCenter, EBoundType aBoundType, std::vector<int> *pBoundSizes);
    /**
     * pBoundSize用来指定一个Bound的相关大小参数以结合BoundCenter确定BoundPoints
     */
    CBound(int aCenterX, int aCenterY, EBoundType aBoundType, std::vector<int> *pBoundSizes);
    void SetBoundCenter(int aPosX, int aPosY);
    const base::CPoint *GetBoundCenter();
    const std::vector<int> *GetBoundSizes();
    void SetBoundSizes(std::vector<int> *pBoundSizes);

private:
    base::CPoint *m_BoundCenter;
    EBoundType m_eBoundType;
    std::vector<base::CPoint *> *m_BoundPoints;
    std::vector<int> *m_BoundSizes;
};
} // namespace collision
#endif /* _OBJECT_H */