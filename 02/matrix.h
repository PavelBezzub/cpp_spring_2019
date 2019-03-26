#include <new>
class Matrix
{
	class proxy
	{
	public:
		proxy() :arr(NULL), size(0) {}
		~proxy() { delete[](arr); }
		proxy(int columns)
		{ 
			arr = new int[columns];
			size = columns;
		}
		const int& operator[](int index) const;
		int& operator[](int index);
	private:
		size_t size;
		int *arr;
	};
public:
	Matrix(int  row, int columns);
	~Matrix();
	Matrix  &operator*=(int x);
	bool operator==(const Matrix& other);
	bool operator!=(const Matrix& other);
	const proxy& operator[](int index) const;
	proxy& operator[](int index);
	int getRows();
	int getColumns();

private:
	proxy *M_matrix;
	size_t row;
	size_t columns;
};

const int& Matrix::proxy::operator[](int index) const
{
	if (index >= size) throw std::out_of_range("");
	return arr[index];
}
int& Matrix::proxy::operator[](int index)
{
	if (index >= size) throw std::out_of_range("");
	return arr[index];
}

const Matrix::proxy& Matrix::operator[](int index) const {
	if (index >= row) throw std::out_of_range("");
	return M_matrix[index];
}
Matrix::proxy& Matrix::operator[](int index) {
	if (index >= row) throw std::out_of_range("");
	return M_matrix[index];
}

Matrix::Matrix(int rows, int column) : row(rows), columns(column)
{
	M_matrix = static_cast<proxy*>(operator new[](row * sizeof(proxy)));
	for (int i = 0; i < row; i++)
	{
		new(M_matrix + i) proxy(columns);
	}
}
Matrix::~Matrix()
{   
	for (int i = 0; i < row; i++)
	{
		M_matrix[i].~proxy();
	}
	operator delete[](M_matrix);
}

int Matrix::getRows() {
	return row;
}

int Matrix::getColumns() {
	return columns;
}

Matrix  &Matrix::operator*=(int x) {
	for (int i = 0; i < row; i++)
		for (int j = 0; j < columns; j++)
		{
			M_matrix[i][j] = M_matrix[i][j] * x;
		}
	return *this;
}

bool Matrix::operator==(const Matrix& other) {
	if ((columns != other.columns) || (row != other.row)) return false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < columns; j++)
		{
			if (M_matrix[i][j] != other.M_matrix[i][j]) return false;
		}
	}
	return true;
}
bool Matrix::operator!=(const Matrix& other) {
	return !(*this == other);
}
