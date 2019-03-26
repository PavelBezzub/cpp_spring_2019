#include <new>
class Matrix
{
	class proxy
	{
	public:
		proxy() :arr(NULL), size(0) {}
		~proxy() { delete[](arr); }
		proxy(size_t columns)
		{ 
			arr = new int[columns];
			size = columns;
		}
		const int& operator[](size_t index) const;
		int& operator[](size_t index);
	private:
		size_t size;
		int *arr;
	};
public:
	Matrix(size_t  row, size_t columns);
	~Matrix();
	Matrix  &operator*=(size_t x);
	bool operator==(const Matrix& other);
	bool operator!=(const Matrix& other);
	const proxy& operator[](size_t index) const;
	proxy& operator[](size_t index);
	const size_t getRows();
	const size_t getColumns();

private:
	proxy *M_matrix;
	size_t row;
	size_t columns;
};

const int& Matrix::proxy::operator[](size_t index) const
{
	if (index >= size) throw std::out_of_range("");
	return arr[index];
}
int& Matrix::proxy::operator[](size_t index)
{
	if (index >= size) throw std::out_of_range("");
	return arr[index];
}

const Matrix::proxy& Matrix::operator[](size_t index) const {
	if (index >= row) throw std::out_of_range("");
	return M_matrix[index];
}
Matrix::proxy& Matrix::operator[](size_t index) {
	if (index >= row) throw std::out_of_range("");
	return M_matrix[index];
}

Matrix::Matrix(size_t rows, size_t column) : row(rows), columns(column)
{
	M_matrix = static_cast<proxy*>(operator new[](row * sizeof(proxy)));
	for (size_t i = 0; i < row; i++)
	{
		new(M_matrix + i) proxy(columns);
	}
}
Matrix::~Matrix()
{   
	for (size_t i = 0; i < row; i++)
	{
		M_matrix[i].~proxy();
	}
	operator delete[](M_matrix);
}

const size_t Matrix::getRows() {
	return row;
}

const size_t Matrix::getColumns() {
	return columns;
}

Matrix  &Matrix::operator*=(size_t x) {
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < columns; j++)
		{
			M_matrix[i][j] = M_matrix[i][j] * x;
		}
	return *this;
}

bool Matrix::operator==(const Matrix& other) {
	if ((columns != other.columns) || (row != other.row)) return false;
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < columns; j++)
		{
			if (M_matrix[i][j] != other.M_matrix[i][j]) return false;
		}
	}
	return true;
}
bool Matrix::operator!=(const Matrix& other) {
	return !(*this == other);
}
