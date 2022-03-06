#include<iostream>
using namespace std;

template<typename elemType>
class Matrix
{
    friend Matrix operator+(const Matrix&, const Matrix&);
    friend Matrix operator*(const Matrix&, const Matrix&);

public:
    Matrix(int rows,int columns);
    Matrix(const Matrix&);
    Matrix& operator=(const Matrix& );
    ~Matrix();
    elemType& operator()(int row, int column)//索引操作
    {
        return _matrix[row * cols() + column];
    }

    const elemType& operator()(int row, int column) const//索引操作，不可改变
    {
        return _matrix[row * cols() + column];
    }
    void operator+=(const Matrix<elemType>&);
    /*elemType& operator()(int row, int column)
    {
        return _matrix[row][column];
    }*/

    // makes transition to general matrix simpler
    int rows() const { return _rows; }
    int cols() const { return _cols; }

    //elemType operator()(int row, int column) const
    //{
    //    return _matrix[row][column];
    //}

    ostream& print(ostream&) const;

private:
    int _rows;
    int _cols;
    elemType *_matrix;
};
template<typename elemType>
Matrix<elemType>::Matrix(int rows, int columns)
    :_rows(rows), _cols(columns)
{
    int size = _rows * _cols;
    _matrix = new elemType[size];
    for (int ix = 0; ix < size; ix++)
    {
        _matrix[ix] = elemType();
    }
}
template<typename elemType>
Matrix<elemType>::~Matrix<elemType>()
{
    delete[] _matrix;
}


template <typename elemType>
Matrix<elemType>::Matrix(const Matrix& rhs)
{
    _rows = rhs._rows; _cols = rhs._cols;
    int mat_size = _rows * _cols;
    _matrix = new elemType[mat_size];
    for (int ix = 0; ix < mat_size; ++ix)
        _matrix[ix] = rhs._matrix[ix];

}

template <typename elemType>
Matrix<elemType>& Matrix<elemType>::
operator=(const Matrix& rhs)
{
    if (this != &rhs)
    {
        _rows = rhs._rows; _cols = rhs._cols;
        int mat_size = _rows * _cols;
        delete[] _matrix;
        _matrix = new elemType[mat_size];
        for (int ix = 0; ix < mat_size; ++ix)
            _matrix[ix] = rhs._matrix[ix];
    }
    return *this;
}

template <typename elemType>
inline ostream& operator<<(ostream& os,  const Matrix<elemType>& m)
{
    return m.print(os);
}

template <typename  elemType>
Matrix<elemType> operator+(const Matrix<elemType>& m1, const Matrix<elemType>& m2) 
{
    Matrix<elemType> result(m1);
    result += m2;
    return result;
}

template<typename elemType>
Matrix<elemType> operator*(const Matrix<elemType>& m1, const Matrix<elemType>& m2)
{
    Matrix<elemType> result;
    for (int ix = 0; ix < m1.rows(); ix++) {
        for (int jx = 0; jx < m1.cols(); jx++) {
            result(ix, jx) = 0;
            for (int kx = 0; kx < m1.cols(); kx++)
                result(ix, jx) += m1(ix, kx) * m2(kx, jx);
        }
    }
    return result;
}

template<typename elemType>
void Matrix<elemType>::operator+=(const Matrix<elemType>& m)
{
    //assert(same_size(m) != 0);
    int matrix_size = cols() * rows();

    for (int ix = 0; ix < matrix_size; ++ix)
        (*(_matrix + ix)) += (*(m._matrix + ix));
}
template<typename  elemType>
ostream& Matrix<elemType>::print(ostream& os) const
{
    int col = cols();
    int matrix_size = col * rows();

    for (int ix = 0; ix < matrix_size; ++ix)
    {
        if (ix % col == 0) os << endl;
        os << (*(_matrix + ix)) << ' ';
    }

    os << endl;
    return os;
}

//template<typename elemType>
//Matrix<elemType>::Matrix<elemType>(elemType a11, elemType a12, elemType a13, elemType a14,
//    elemType a21, elemType a22, elemType a23, elemType a24,
//    elemType a31, elemType a32, elemType a33, elemType a34,
//    elemType a41, elemType a42, elemType a43, elemType a44)
//{
//    _matrix[0][0] = a11; _matrix[0][1] = a12;
//    _matrix[0][2] = a13; _matrix[0][3] = a14;
//    _matrix[1][0] = a21; _matrix[1][1] = a22;
//    _matrix[1][2] = a23; _matrix[1][3] = a24;
//    _matrix[2][0] = a31; _matrix[2][1] = a32;
//    _matrix[2][2] = a33; _matrix[2][3] = a34;
//    _matrix[3][0] = a41; _matrix[3][1] = a42;
//    _matrix[3][2] = a43; _matrix[3][3] = a44;
//}
//
//template<typename elemType>
//Matrix<elemType>::Matrix<elemType>(const elemType* array)
//{
//    int array_index = 0;
//    for (int ix = 0; ix < 4; ++ix)
//        for (int jx = 0; jx < 4; ++jx)
//            _matrix[ix][jx] = array[array_index++];
//
//}

void test()
{
    
    Matrix<float> identity(4, 4);
    cout << "identity: " << identity << endl;

    float ar[16] = {
        1., 0., 0., 0., 0., 1., 0., 0.,
        0., 0., 1., 0., 0., 0., 0., 1. };

    for (int i = 0, k = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            identity(i, j) = ar[k++];

    cout << "identity after set: " << identity << endl;

}

int main()
{

    test();
    system("pause");
	/*int i = 0;
	cout << i << endl;*/
	return 0;
}
