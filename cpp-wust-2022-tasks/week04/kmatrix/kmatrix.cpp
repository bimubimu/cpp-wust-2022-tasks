#include"kmatrix.h"

template<typename T>
KMatrix<T>::KMatrix() : m_cHead(nullptr), m_rHead(nullptr), m_mu(0), m_nu(0) {}

template<typename T>
KMatrix<T>::KMatrix(int row, int column)
{
    init(row, column);
}

//�������캯��
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

//��ֵ���캯��
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
    //ʮ�������ʼ��
    m_mu = row;
    m_nu = column;
    m_rHead = (OLNode<T>**)malloc((row + 1) * sizeof(OLNode<T>*));
    if (!m_rHead) {
        cout << "��ʼ���ڴ�ʧ�ܣ�" << endl;
        exit(-1);
    }
    m_cHead = (OLNode<T>**)malloc((column + 1) * sizeof(OLNode<T>*));
    if (!m_cHead) {
        cout << "��ʼ���ڴ�ʧ�ܣ�" << endl;
        exit(-1);
    }

    for (int i = 1; i <= m_mu; i++) // ��ʼ����ͷָ������,��������Ϊ������    
        m_rHead[i] = nullptr;
    for (int i = 1; i <= m_nu; i++) // ��ʼ����ͷָ������,��������Ϊ������    
        m_cHead[i] = nullptr;
}

template<typename T>
void KMatrix<T>::destroy()
{
    for (int i = 1; i <= m_mu; i++)
        for (int j = 1; j <= m_nu; j++)
            //����ÿ��λ�ã������λ���ж�̬�ڴ�������ͷţ�������ȷ���С��������ָ��
            if (m_rHead[i] != nullptr && m_rHead[i]->column == j) {
                OLNode<T>* p = m_rHead[i];
                m_rHead[i] = p->right;
                m_cHead[j] = p->down;
                free(p);
            }

    //�ͷ��С�������
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
        cout << "����ֵ��λ�ò�����" << endl;
        return;
    }

    OLNode<T>* temp;
    if (getData(row, col)) {    //����ӽڵ�λ���Ƿ��Ѵ��ڷ�0ֵʱ
        if (value != 0) {
            temp = m_rHead[row];
            while (temp->column != col)
                temp = temp->right;
            temp->elem = value;
        }
        else
            setZero(row, col);
    }
    else {   //������ʱ���нڵ�����
        //ֵΪ0ʱ���ô��� 
        if(value != 0) {
            //Ϊ��ӵĽڵ������ڴ棬
            OLNode<T>* p = (OLNode<T>*)malloc(sizeof(OLNode<T>));
            if (!p)
                cout << "�ڴ����ʧ��" << endl;
            else {
                p->row = row;
                p->column = col;
                p->elem = value;

                OLNode<T>* temp;
                //��һ��û�нڵ����һ�нڵ����������µĽڵ�ʱ�����µĽڵ���뵽��һ��ͷ��
                if (nullptr == m_rHead[row] || m_rHead[row]->column > col) {
                    p->right = m_rHead[row];
                    m_rHead[row] = p;
                }
                else {    //�������������ҵ���ȷλ�ò���
                    for (temp = m_rHead[row]; temp->right && temp->right->column < col;)
                        temp = temp->right;
                    p->right = temp->right;
                    temp->right = p;
                }

                //����������ԭ��ͬ��
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
void KMatrix<T>::setZero(int row, int col)  //���õ��ڴ��ͷ�
{
    if (row <= 0 || row > m_mu || col <= 0 || col > m_nu)
        cout << "����ֵ��λ�ò�����" << endl;

    OLNode<T>* temp;
    OLNode<T>* left = m_rHead[row];
    OLNode<T>* up = m_cHead[col];

    //�����Ϊ0���ô���
    if (getData(row, col) == 0)
        return;

    //ȷ���ڵ�λ�ã�������ָ��
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

    //�ͷ��ڴ�
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
        cout << "���в�����" << endl;
        return;
    }

    OLNode<T>* temp = m_rHead[row];

    //������Ԫ��ȫ��Ϊ0
    while (temp != nullptr) {
        int col = temp->column;
        temp = temp->right;
        setZero(row, col);
    }

    //������ָ������  �����������нڵ���������һ
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

    //������һ
    m_mu--;
}

template<typename T>
void KMatrix<T>::eraseCol(int col)
{
    if (col <= 0 || col > m_nu) {
        cout << "���в�����" << endl;
        return;
    }

    OLNode<T>* temp = m_cHead[col];

    //������Ԫ��ȫ��Ϊ0
    while (temp != nullptr) {
        int row = temp->row;
        temp = temp->down;
        setZero(row, col);
    }

    //������ָ������  �����������нڵ���������һ
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

    //������һ
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
            //��λ��Ԫ�ض���Ϊ0
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
            if (pa != nullptr && pb != nullptr && pa->column == j && pb->column == j) {  //��λ��Ԫ�ض���Ϊ0 
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
            if (pa != nullptr && pb != nullptr && pa->column == j && pb->column == j) {  //��λ��Ԫ�ض���Ϊ0 
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
            if (pa != nullptr && pb != nullptr && pa->column == j && pb->column == j) {  //��λ��Ԫ�ض���Ϊ0 
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
    
    //��������ΪA,B  ����A������B������С�ľ��� ����ÿ��Ԫ����setData()ΪԪ�ظ�ֵ
    for(int row = 1; row <= res->m_mu; row ++)
        for (int col = 1; col <= res->m_nu; col++) {

            //��A��row����B��col�����

            //ͨ��pa, pb����A��row����B��col��
            OLNode<T>* pa = this->m_rHead[row];
            OLNode<T>* pb = other.m_cHead[col];

            T value = 0;   //��¼ÿ��Ԫ�صĽ��
            for (int i = 1; i <= this->m_nu; i++) {
                //��λ��Ԫ��ֵ����Ϊ0
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
            if (pa != nullptr && pb != nullptr && pa->column == j && pb->column == j) {  //��λ��Ԫ�ض���Ϊ0 
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
    //��ԭʮ�������е�Ԫ�ص�������������꣬��ָ�����ָ�뽻��
    for (int i = 1; i <= m_mu; i++) {
        OLNode<T>* p = m_rHead[i];
        while (p != nullptr) {
            //������������
            swap(p->row, p->column);

            //��������ָ��
            OLNode<T>* temp = p->right;
            p->right = p->down;
            p->down = temp;

            p = p->down;  //����������
        }
    }

    //��ʮ������ͷ��������ָ�뽻��
    OLNode<T>** temp = m_cHead;
    m_cHead = m_rHead;
    m_rHead = temp;

    //��ͷ����м�¼������������
    swap(m_mu, m_nu);
}

template<typename T>
void KMatrix<T>::print() const  //�������
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

