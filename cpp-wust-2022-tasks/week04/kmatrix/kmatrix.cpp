#include"kmatrix.h"

template<typename T>
KMatrix<T>::KMatrix() : m_cHead(nullptr), m_rHead(nullptr), m_mu(0), m_nu(0) {}

template<typename T>
KMatrix<T>::KMatrix(int row, int column)
{
    init(row, column);
}

//拷贝构造函数
template<typename T>
KMatrix<T>::KMatrix(const KMatrix<T>& other)
{
    init(other.m_mu, other.m_nu);

    for (int i = 1; i <= m_mu; i++) {
        OLNode<T>* p = other.m_rHead[i];
        for (int j = 1; j <= m_nu; j++) {
            if (p != nullptr && p->column == j)
                setData(i, j, p->elem);
        }
    }
}

//赋值构造函数
template<typename T>
KMatrix<T>& KMatrix<T>::operator=(const KMatrix<T>& other)
{
    destroy();
    init(other.m_mu, other.m_nu);

    for (int i = 1; i <= m_mu; i++) {
        OLNode<T>* p = other.m_rHead[i];
        for (int j = 1; j <= m_nu; j++) {
            if (p != nullptr && p->column == j)
                setData(i, j, p->elem);
        }
    }
    return *this;
}

template<typename T>
KMatrix<T>::~KMatrix()
{
    destroy();
}

template<typename T>
void KMatrix<T>::init(int row, int column)
{
    //十字链表初始化
    m_mu = row;
    m_nu = column;
    m_rHead = (OLNode<T>**)malloc((row + 1) * sizeof(OLNode<T>*));
    if (!m_rHead) {
        cout << "初始化内存失败！" << endl;
        exit(-1);
    }
    m_cHead = (OLNode<T>**)malloc((column + 1) * sizeof(OLNode<T>*));
    if (!m_cHead) {
        cout << "初始化内存失败！" << endl;
        exit(-1);
    }

    for (int i = 1; i <= m_mu; i++) // 初始化行头指针向量,各行链表为空链表    
        m_rHead[i] = nullptr;
    for (int i = 1; i <= m_nu; i++) // 初始化列头指针向量,各列链表为空链表    
        m_cHead[i] = nullptr;
}

template<typename T>
void KMatrix<T>::destroy()
{
    for (int i = 1; i <= m_mu; i++)
        for (int j = 1; j <= m_nu; j++)
            //遍历每个位置，如果该位置有动态内存分配则释放，并重新确定行、列链表的指针
            if (m_rHead[i] != nullptr && m_rHead[i]->column == j) {
                OLNode<T>* p = m_rHead[i];
                m_rHead[i] = p->right;
                m_cHead[j] = p->down;
                free(p);
            }

    //释放行、列链表
    if (m_rHead)
        free(m_rHead);
    if (m_cHead)
        free(m_cHead);

    m_mu = 0;
    m_nu = 0;
}

template<typename T>
int KMatrix<T>::getRows() const
{
    return m_mu;
}

template<typename T>
int KMatrix<T>::getCols() const
{
    return m_nu;
}

template<typename T>
void KMatrix<T>::setData(int row, int col, T value)
{
    if (row <= 0 || row > m_mu || col <= 0 || col > m_nu) {
        cout << "设置值的位置不合理！" << endl;
        return;
    }

    OLNode<T>* temp;
    if (getData(row, col)) {    //新添加节点位置是否已存在非0值时
        if (value != 0) {
            temp = m_rHead[row];
            while (temp->column != col)
                temp = temp->right;
            temp->elem = value;
        }
        else
            setZero(row, col);
    }
    else {   //不存在时进行节点的添加
        //值为0时不用处理 
        if(value != 0) {
            //为添加的节点申请内存，
            OLNode<T>* p = (OLNode<T>*)malloc(sizeof(OLNode<T>));
            if (!p)
                cout << "内存分配失败" << endl;
            else {
                p->row = row;
                p->column = col;
                p->elem = value;

                OLNode<T>* temp;
                //这一行没有节点或这一行节点列数大于新的节点时，将新的节点插入到这一行头部
                if (nullptr == m_rHead[row] || m_rHead[row]->column > col) {
                    p->right = m_rHead[row];
                    m_rHead[row] = p;
                }
                else {    //否则向后遍历，找到正确位置插入
                    for (temp = m_rHead[row]; temp->right && temp->right->column < col;)
                        temp = temp->right;
                    p->right = temp->right;
                    temp->right = p;
                }

                //处理列链表，原理同上
                if (nullptr == m_cHead[col] || m_cHead[col]->row > row) {
                    p->down = m_cHead[col];
                    m_cHead[col] = p;
                }
                else {
                    for (temp = m_cHead[col]; temp->down && temp->down->row < row;)
                        temp = temp->down;
                    p->down = temp->down;
                    temp->down = p;
                }
            }
        }
    }
}

template<typename T>
void KMatrix<T>::setZero(int row, int col)  //将该点内存释放
{
    if (row <= 0 || row > m_mu || col <= 0 || col > m_nu)
        cout << "设置值的位置不合理！" << endl;

    OLNode<T>* temp;
    OLNode<T>* left = m_rHead[row];
    OLNode<T>* up = m_cHead[col];

    //本身就为0不用处理
    if (getData(row, col) == 0)
        return;

    //确定节点位置，并重置指针
    if (left->column == col) {
        temp = left;
        m_rHead[row] = left->right;
    }
    else {
        while (left->right->column != col)
            left = left->right;
        temp = left->right;
        left->right = temp->right;
    }

    if (up->row == row) 
        m_cHead[col] = up->down;
    else {
        while (up->down->row != row)
            up = up->down;
        up->down = up->down->down;
    }

    //释放内存
    free(temp);
}

template<typename T>
T KMatrix<T>::getData(int row, int col)
{
    T flag = 0;
    if (row <= 0 || row > m_mu || col <= 0 || col > m_nu)
        return flag;

    OLNode<T>* temp = m_rHead[row];

    while (temp != nullptr) {
        if (temp->column != col)
            temp = temp->right;
        else {
            flag = temp->elem;
            break;
        }
    }
    return flag;
}

template<typename T>
void KMatrix<T>::eraseRow(int row)
{
    if (row <= 0 || row > m_mu) {
        cout << "该行不存在" << endl;
        return;
    }

    OLNode<T>* temp = m_rHead[row];

    //将该行元素全置为0
    while (temp != nullptr) {
        int col = temp->column;
        temp = temp->right;
        setZero(row, col);
    }

    //行链表指针下移  并将后续所有节点的行坐标减一
    while (row < m_mu) {
        m_rHead[row] = m_rHead[row + 1];
        temp = m_rHead[row];
        while (temp) {
            temp->row--;
            temp = temp->right;
        }
        row++;
    }
    m_rHead[row] = nullptr;

    //行数减一
    m_mu--;
}

template<typename T>
void KMatrix<T>::eraseCol(int col)
{
    if (col <= 0 || col > m_nu) {
        cout << "该列不存在" << endl;
        return;
    }

    OLNode<T>* temp = m_cHead[col];

    //将该列元素全置为0
    while (temp != nullptr) {
        int row = temp->row;
        temp = temp->down;
        setZero(row, col);
    }

    //列链表指针右移  并将后续所有节点的列坐标减一
    while (col < m_nu) {
        m_cHead[col] = m_cHead[col + 1];
        temp = m_cHead[col];
        while (temp) {
            temp->column--;
            temp = temp->down;
        }
        col++;
    }
    m_cHead[col] = nullptr;

    //列数减一
    m_nu--;
}  

template<typename T>
KMatrix<T>* KMatrix<T>::operator+(const KMatrix<T>& other)
{
    KMatrix<T>* res = new KMatrix<T>(this->m_mu, this->m_nu);

    for (int i = 1; i <= this->m_mu; i++) {
        OLNode<T>* pa = this->m_rHead[i];
        OLNode<T>* pb = other.m_rHead[i];
        for (int j = 1; j <= this->m_nu; j++) {
            //该位置元素都不为0
            if (pa != nullptr && pb != nullptr && pa->column == j && pb->column == j) {   
                T value = pa->elem + pb->elem;
                pa = pa->right;
                pb = pb->right;
                res->setData(i, j, value);
            }
            else if (pa != nullptr && pa->column == j) {
                res->setData(i, j, pa->elem);
                pa = pa->right;
            }
            else if (pb != nullptr && pb->column == j) {
                res->setData(i, j, pb->elem);
                pb = pb->right;
            }
            else
                continue;
        }
    }
    return res;
}

template<typename T>
KMatrix<T>& KMatrix<T>::operator+=(const KMatrix<T>& other)
{
    for (int i = 1; i <= this->m_mu; i++) {
        OLNode<T>* pa = this->m_rHead[i];
        OLNode<T>* pb = other.m_rHead[i];
        for (int j = 1; j <= this->m_nu; j++) {
            if (pa != nullptr && pb != nullptr && pa->column == j && pb->column == j) {  //该位置元素都不为0 
                T value = pa->elem + pb->elem;
                pa = pa->right;
                pb = pb->right;
                this->setData(i, j, value);
            }
            else if (pa != nullptr && pa->column == j) 
                pa = pa->right;
            else if (pb != nullptr && pb->column == j) {
                this->setData(i, j, pb->elem);
                pb = pb->right;
            }
            else
                continue;
        }
    }
    return *this;
}

template<typename T>
KMatrix<T>* KMatrix<T>::operator-(const KMatrix<T>& other)
{
    KMatrix<T>* res = new KMatrix<T>(this->m_mu, this->m_nu);

    for (int i = 1; i <= this->m_mu; i++) {
        OLNode<T>* pa = this->m_rHead[i];
        OLNode<T>* pb = other.m_rHead[i];
        for (int j = 1; j <= this->m_nu; j++) {
            if (pa != nullptr && pb != nullptr && pa->column == j && pb->column == j) {  //该位置元素都不为0 
                T value = pa->elem - pb->elem;
                pa = pa->right;
                pb = pb->right;
                res->setData(i, j, value);
            }
            else if (pa != nullptr && pa->column == j) {
                res->setData(i, j, pa->elem);
                pa = pa->right;
            }
            else if (pb != nullptr && pb->column == j) {
                res->setData(i, j, -pb->elem);
                pb = pb->right;
            }
            else
                continue;
        }
    }
    return res;
}

template<typename T>
KMatrix<T>& KMatrix<T>::operator-=(const KMatrix<T>& other)
{
    for (int i = 1; i <= this->m_mu; i++) {
        OLNode<T>* pa = this->m_rHead[i];
        OLNode<T>* pb = other.m_rHead[i];
        for (int j = 1; j <= this->m_nu; j++) {
            if (pa != nullptr && pb != nullptr && pa->column == j && pb->column == j) {  //该位置元素都不为0 
                T value = pa->elem - pb->elem;
                pa = pa->right;
                pb = pb->right;
                this->setData(i, j, value);
            }
            else if (pa != nullptr && pa->column == j) 
                pa = pa->right;
            else if (pb != nullptr && pb->column == j) {
                this->setData(i, j, -pb->elem);
                pb = pb->right;
            }
            else
                continue;
        }
    }
    return *this;
}

template<typename T>
KMatrix<T>* KMatrix<T>::operator*(const KMatrix<T>& other)
{
    KMatrix<T>* res = new KMatrix<T>(m_mu, other.m_nu);
    
    //设两矩阵为A,B  创建A行数和B列数大小的矩阵 遍历每个元素用setData()为元素赋值
    for(int row = 1; row <= res->m_mu; row ++)
        for (int col = 1; col <= res->m_nu; col++) {

            //将A第row行与B第col列相乘

            //通过pa, pb遍历A第row行与B第col列
            OLNode<T>* pa = this->m_rHead[row];
            OLNode<T>* pb = other.m_cHead[col];

            T value = 0;   //记录每个元素的结果
            for (int i = 1; i <= this->m_nu; i++) {
                //该位置元素值都不为0
                if (pa != nullptr && pb != nullptr && pa->column == i && pb->row == i) {
                    value += pa->elem * pb->elem;
                    pa = pa->right;
                    pb = pb->down;
                }
                else if (pa != nullptr && pa->column == i)
                    pa = pa->right;
                else if (pb != nullptr && pb->row == i)
                    pb = pb->down;
                else
                    continue;
            }

            res->setData(row, col, value);
        }
    return res;
}

template<typename T>
KMatrix<T>* KMatrix<T>::dotMul(const KMatrix<T>& other)
{
    KMatrix<T>* res = new KMatrix<T>(this->m_mu, this->m_nu);

    for (int i = 1; i <= this->m_mu; i++) {
        OLNode<T>* pa = this->m_rHead[i];
        OLNode<T>* pb = other.m_rHead[i];
        for (int j = 1; j <= this->m_nu; j++) {
            if (pa != nullptr && pb != nullptr && pa->column == j && pb->column == j) {  //该位置元素都不为0 
                res->setData(i, j, pa->elem * pb->elem);
                pa = pa->right;
                pb = pb->right;
            }
            else if (pa != nullptr && pa->column == j)
                pa = pa->right;
            else if (pb != nullptr && pb->column == j)
                pb = pb->right;
            else
                continue;
        }
    }
    return res;
}

template<typename T>
void KMatrix<T>::transpose()
{
    //将原十字链表中的元素的行坐标和列坐标，行指针和列指针交换
    for (int i = 1; i <= m_mu; i++) {
        OLNode<T>* p = m_rHead[i];
        while (p != nullptr) {
            //交换行列坐标
            swap(p->row, p->column);

            //交换行列指针
            OLNode<T>* temp = p->right;
            p->right = p->down;
            p->down = temp;

            p = p->down;  //继续向后遍历
        }
    }

    //将十字链表头结点的行列指针交换
    OLNode<T>** temp = m_cHead;
    m_cHead = m_rHead;
    m_rHead = temp;

    //将头结点中记录的行列数交换
    swap(m_mu, m_nu);
}

template<typename T>
void KMatrix<T>::print() const  //输出矩阵
{
    for (int i = 1; i <= m_mu; i++) {
        OLNode<T>* p = m_rHead[i];
        for (int j = 1; j <= m_nu; j++) {
            if (p == nullptr || p->column != j)
                cout << "0   ";
            else {
                cout << p->elem << "   ";
                p = p->right;
            }
        }
        cout << endl;
    }
}

template KMatrix<int>;
template KMatrix<double>;

